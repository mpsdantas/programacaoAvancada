#include <iostream>
#include <string.h>

#include "winsocket.h"
#include "mensageiro.h"

using namespace std;

/* Este programa tem uma thread principal que espera que o usuário
   digite alguma coisa e envia esta string para um servidor via
   socket. Uma outra thread imprime todas as strings recebidas pelo
   socket.  */

// Aqui vão as variáveis globais das duas threads

tcp_winsocket s;
bool fim = false;

// Esta é a thread que escreve em tela as mensagens recebidas

DWORD WINAPI le_msg(LPVOID lpParameter)
{
  int remetente;
  string msg;
  WINSOCKET_STATUS iResult;

  while (!fim) {
    iResult = s.read_int(remetente);
    if (iResult == SOCKET_ERROR)
    {
      if (!fim) {
        cerr << "Problema na leitura do remetente via socket...\n";
      }
      fim = true;
    }
    if (!fim)
    {
        iResult = s.read_string(msg);
        if (iResult == SOCKET_ERROR)
        {
            if (!fim) {
                cerr << "Problema na leitura da msg via socket...\n";
            }
            fim = true;
        }
    }
    if (!fim)
    {
      cout << endl
           << "=========================================================\n"
           << "Mensagem recebida de " << remetente <<":\n"
           << msg << endl
	       << "=========================================================\n";
      fim = (msg=="fim");
    }
  }
  return 0;
}

// O programa principal contém o ciclo que envia as mensagens digitadas

int main(int argc, char **argv)
{
  WSADATA wsaData;
  HANDLE tHandle;
  string msg;

  // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
  // before making other Winsock functions calls
  // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
  WINSOCKET_STATUS iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
      cerr << "WSAStartup failed: " << iResult << endl;
      exit(1);
  }

  if( argc<2 ) {
    cout << "Maquina onde esta rodando o servidor (IP): ";
    cin >> ws;
    getline(cin, msg);
  }
  else {
    msg = argv[1];
  }

  if (s.connect(msg.c_str(), PORTA_TESTE) == SOCKET_OK)
  {
    cout << "Conectado ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
  }
  else
  {
    cerr << "Problema na conexao ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
    exit(1);
  }

  //Sleep(1000); // Espera 1 seg para o socket estar ok

  // Cria a thread que escreve as mensagens recebidas
  tHandle = CreateThread(NULL, 0, le_msg, NULL , 0, NULL);
  if (tHandle == NULL)
  {
    cerr << "Problema na criacao da thread: " << GetLastError() << endl;
    exit(1);
  }

  // Este é o ciclo que envia as mensagens digitadas
  while (!fim)
  {
    do
    {
        cout << "Mensagem a enviar (max " << TAM_MAX_MSG_STRING << " caracteres, FIM para terminar): ";
        cin >> ws;
        getline(cin, msg);
    } while (!fim && (msg.size()==0 || msg.size()>TAM_MAX_MSG_STRING));

    if (!fim) fim = (msg=="FIM");
    if (!fim)
    {
      if ( s.write_string(msg) == SOCKET_ERROR ) {
        cout << "Problema na escrita no socket...\n";
        fim = true;
      }
    }
    Sleep(1000); // Espera 1 seg para as mensagens não se sobreporem no terminal
  }
  // Desliga o socket
  s.shutdown();
  // Espera pelo fim da thread de recepção (máximo de 5 segundos)
  cout << "Aguardando o encerramento da outra thread...\n";
  WaitForSingleObject(tHandle, 5000);
  // Encerra na força bruta a thread de recepção caso ela não tenha terminado sozinha
  // (ou seja, a função WaitForSingleObject tenha saído por timeout)
  TerminateThread(tHandle,0);
  // Encerra o handle da thread
  CloseHandle(tHandle);
  // Enderra o socket
  s.close();

  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
}
