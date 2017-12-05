#include <iostream>
#include <string.h>
#include <locale.h>
#include "winsocket.h"
#include "mensageiro.h"

using namespace std;

/* ==================================================================

Este aplicativo cliente-servidor permite o envio de mensagens entre
os softwares clientes e o software servidor.
As mensagens trocadas sao formadas pelos seguintes campos:
1) Usuario - uma string formada por dois campos:
   1.1) Tamanho da string: um inteiro [ 4 bytes ]
   1.2) Caracteres da string: varios chars [ tamanho do texto ]
   Significa o destinatario, nas msgs do cliente para o servidor,
   ou o remetente, nas msgs do servidor para o cliente
2) Texto - uma string formada por dois campos:
   2.1) Tamanho do texto: um inteiro [ sizeof(int) bytes ]
   2.2) Caracteres do texto: varios chars [ tamanho do texto ]
   Contem a msg efetivamente enviada

A primeira msg a ser enviada pelo cliente para o servidor eh
diferente das demais. Deve conter apenas o nome do usuario. Esse
nome identificarah o cliente daih em diante: todas as msgs enviadas
para esse nome do usuario serao direcionadas pelo servidor para esse
cliente.

================================================================== */

/* ==================================================================

Este programa tem uma thread principal que espera que o usuário
digite alguma coisa e envia esta msg para um servidor via
socket. Uma outra thread imprime todas as msgs recebidas pelo
socket.

================================================================== */

// Aqui vao as variaveis globais das duas threads

tcp_winsocket s;
bool fim = false;

// Esta eh a thread que escreve em tela as mensagens recebidas

DWORD WINAPI le_msg(LPVOID lpParameter)
{
  string remetente,msg;
  WINSOCKET_STATUS iResult;
  int32_t codigo;

}

// O programa principal contém o ciclo que envia as mensagens digitadas

int main(int argc, char **argv)
{
  setlocale(LC_ALL,"portuguese");
  WSADATA wsaData;
  HANDLE tHandle;
  string usuario;
  string senha;
  string msg;
  int32_t codigo;
  int opcao;
  bool flag=true;
  WINSOCKET_STATUS iResult;

  // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
  // before making other Winsock functions calls
  // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
  iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
    cerr << "WSAStartup failed: " << iResult << endl;
    exit(1);
  }

  // Determina o numero IP do servidor (digitado ou lido do argumento de chamada)
  if( argc<2 )
  {
    cout << "Maquina onde estah rodando o servidor (IP): ";
    cin >> ws;
    getline(cin, msg);
  }
  else
  {
    msg = argv[1];
  }

  // Conecta com o servidor
  if (s.connect(msg.c_str(), PORTA_TESTE) == SOCKET_OK)
  {
    cout << "Conectado ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
  }
  else
  {
    cerr << "Problema na conexao ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
    exit(1);
  }

  // Cria a thread que escreve as mensagens recebidas
  tHandle = CreateThread(NULL, 0, le_msg, NULL , 0, NULL);
  if (tHandle == NULL)
  {
    cerr << "Problema na criacao da thread: " << GetLastError() << endl;
    exit(1);
  }


  // Envia para o servidor o nome de usuario que identificarah esse cliente
    while(1){
        cout << "Escolha uma opcao" << endl;
        cout << "Opcao==1, cadastro"<< endl;
        cout << "Opcao==2, login"<< endl;
        cin >> opcao;
        if(opcao==1 && flag){
            iResult = s.write_int(1001);
            cout << "Login deste cliente [4 a 16 caracteres]: ";
            cin >> usuario;
            s.write_string(usuario);
            cout << "Senha deste cliente [4 a 16 caracteres]: ";
            cin >> senha;
            s.write_string(senha);
            if ( iResult == SOCKET_ERROR )
            {
                cerr << "Problema no cadastro do usuario...\n";
                exit(1);
            }
            iResult = s.read_int(codigo);
            if(codigo==1003){
                cout << "Usuário cadastrado com sucesso"<<endl;
            }
            flag =false;
        }
        if(opcao==2){
            s.write_int(1002);
            cout << "Digite seu login"<<endl;
            cin >> usuario;
            s.write_string(usuario);
            cout << "Digite sua senha"<<endl;
            cin >> senha;
            s.write_string(senha);
            iResult = s.read_int(codigo,5*1000);
            if(codigo==1003){
                cout << "Login feito com sucesso."<<endl;
            }
            if ( iResult == SOCKET_ERROR )
            {
                cerr << "Problema na escrita do login no socket...\n";
                exit(1);
            }
            flag=false;
        }
        if(!flag){
            cout << "Usuário logado!!!!!!!!!!!!:"<<endl;
            cout << "Escolha uma ação.:"<<endl;
            cout << "1- enviar msg para usuario"<<endl;
            cout << "2- ver lista de msgs."<<endl;
            cout << "3-sair"<<endl;
            cin >> opcao;
            if(opcao==3){
                s.write_int(1013);
                cout<<"Fim";
                flag=true;
            }
        }
    }


/*
  // Este é o ciclo que envia as mensagens digitadas
  while (!fim)
  {
    if (!fim)
    {
      do
      {
        cout << "Usuario a enviar msg [4 a 16 caracteres, ALL para todos, FIM para terminar]: ";
        cin >> ws;
        getline(cin, usuario);
      } while (usuario!="ALL" && usuario!="FIM" && (usuario.size()<4 || usuario.size()>16));
      if (!fim) fim = (usuario=="FIM");
    }

    if (!fim)
    {
      do
      {
        cout << "Mensagem a enviar [max " << TAM_MAX_MSG_STRING << " caracteres, FIM para terminar]: ";
        cin >> ws;
        getline(cin, msg);
      } while (msg.size()==0 || msg.size()>TAM_MAX_MSG_STRING);
      if (!fim) fim = (msg=="FIM");
    }

    if (!fim)
    {
      iResult = s.write_string(usuario);
      if ( iResult == SOCKET_ERROR )
      {
        cout << "Problema na escrita do usuario no socket...\n";
        fim = true;
      }
    }
    if (!fim)
    {
      iResult = s.write_string(msg);
      if ( iResult == SOCKET_ERROR )
      {
        cout << "Problema na escrita do texto no socket...\n";
        fim = true;
      }
    }
    Sleep(1000); // Espera 1 seg para as mensagens não se sobreporem no terminal
  }
*/
/*
  // Desliga o socket
  s.shutdown();
  // Espera pelo fim da thread de recepção (máximo de 5 segundos)
  cout << "Aguardando o encerramento da outra thread...\n";
  WaitForSingleObject(tHandle, 5000);
  // Encerra na força bruta a thread de recepcao caso ela nao tenha terminado sozinha
  // (ou seja, a funcao WaitForSingleObject tenha saído por timeout)
  TerminateThread(tHandle,0);
  // Encerra o handle da thread
  CloseHandle(tHandle);
  // Encerra o socket
  s.close();
*/
  /* call WSACleanup when done using the Winsock dll */
  //WSACleanup();

}
