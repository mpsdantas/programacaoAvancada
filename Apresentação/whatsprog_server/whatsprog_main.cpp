#include <iostream>
#include <locale.h>
#include "whatsprog_server.h"
using namespace std;

Server s;
bool fim = false;

DWORD WINAPI servidor(LPVOID lpParameter){
    setlocale(LC_ALL,"portuguese");
    cout << "Servidor online" << endl;
    while(!fim){
        s.monitorarChegada(fim);
        s.socketAceito();
        s.aguardarAcao();
    }
}
int main(){
    setlocale(LC_ALL,"portuguese");
    WSADATA wsaData;
    s.carregarUsuarios();
    // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
    // before making other Winsock functions calls
    // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
    WINSOCKET_STATUS iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    s.abrirConexao(iResult);
    // Cria a thread que recebe e reenvia as mensagens
    HANDLE tHandle = CreateThread(NULL, 0, servidor, NULL , 0, NULL);
    s.statusThread(tHandle);

    while(true){

    }

}
