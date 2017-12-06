#include <QApplication>
#include "whatsprogmain.h"
#include "dados_cliente.h"
#include "winsocket.h"
#include "dados_whatsprog.h"

// A variavel global que contem todas as msgs de todas as conversas
DadosCliente DCliente;

//Mensagem que sera utilizada para conectar o servidor com o cliente
Mensagem mensagem;

// O socket do cliente, a ser utilizado por todas as threas
tcp_winsocket s;

// O identificador da thread de leitura de dados do socket
HANDLE tHandle=NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WhatsProgMain w;

    // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
    // before making other Winsock functions calls
    // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
    WSADATA wsaData;
    WINSOCKET_STATUS iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        cerr << "WSAStartup failed: " << iResult << endl;
        exit(1);
    }

    w.show();
    int result = a.exec();

    // Desliga o socket
    s.shutdown();

    // Espera pelo fim da thread de recepção (máximo de TIMEOUT_WHATSPROG segundos)
    if (tHandle != NULL)
    {
        if (WaitForSingleObject(tHandle, 1000*TIMEOUT_WHATSPROG) == WAIT_TIMEOUT)
        {
            // A funcao WaitForSingleObject saiu por timeout
            // Encerra na força bruta a thread de recepcao, pois ela nao terminou sozinha
            TerminateThread(tHandle,0);
        }
    }
    // Encerra o handle da thread
    CloseHandle(tHandle);

    // Enderra o socket
    s.close();

    /* call WSACleanup when done using the Winsock dll */
    WSACleanup();

    return result;
}
