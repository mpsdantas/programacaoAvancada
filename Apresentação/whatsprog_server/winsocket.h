#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <iostream>
#include <cstdlib>
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

using namespace std;

/*
###############################################################################

N�O ESQUECA DE LINKAR COM A BIBLIOTECA Ws2_32. Incluir essa op��o no compilador
No CodeBlocs: bot�o direito no nome do projeto, Build options, Linker settings,
adicionar biblioteca Ws2_32

###############################################################################

Infomacao sobre os sockets Windows:

INICIO:
https://msdn.microsoft.com/en-us/library/windows/desktop/ms738545(v=vs.85).aspx
CRIANDO UMA APLICACAO WINSOCK (cliente e servidor):
https://msdn.microsoft.com/en-us/library/windows/desktop/ms737629(v=vs.85).aspx
CLIENTE:
https://msdn.microsoft.com/en-us/library/windows/desktop/bb530741(v=vs.85).aspx
SERVIDOR:
https://msdn.microsoft.com/en-us/library/windows/desktop/bb530742(v=vs.85).aspx
SELECT:
https://msdn.microsoft.com/en-us/library/windows/desktop/ms740141(v=vs.85).aspx
SEND, RECV:
https://msdn.microsoft.com/en-us/library/windows/desktop/bb530746(v=vs.85).aspx
*/

typedef int WINSOCKET_STATUS;
#define SOCKET_OK 0
#define TAM_MAX_MSG_STRING 256

typedef enum
{
  WINSOCKET_IDLE=0,
  WINSOCKET_ACCEPTING=1,
  WINSOCKET_CONNECTED=2
} WINSOCKET_STATE;

// Predefini��o das classes
class winsocket_queue;
class tcp_winsocket;
class tcp_winsocket_server;

/* #############################################################
   ##  A classe base dos sockets                              ##
   ############################################################# */

class winsocket
{
 private:
  SOCKET id;
  WINSOCKET_STATE state;
 public:
  // Construtor por default
  inline winsocket(): id(INVALID_SOCKET), state(WINSOCKET_IDLE) {}
  // Proibe novos envios de dados via socket
  WINSOCKET_STATUS shutdown();
  // Fecha (caso esteja aberto) um socket
  void close();
  // ATEN��O: ao criar um destrutor que fechasse o socket, voc� n�o poderia mais passar nenhum socket
  // por c�pia como par�metro para uma fun��o, nem retornar um socket por valor. Se fizesse isso, seria
  // chamado o destrutor na c�pia, que fecharia o socket no Windows e afetaria o socket original.
  inline ~winsocket() {}
  // Testa se um socket � "virgem" ou foi fechado
  inline bool closed() const {return (id==INVALID_SOCKET && state==WINSOCKET_IDLE);}
  // Testa se um socket est� aberto (aceitando conex�es)
  inline bool accepting() const {return (id!=INVALID_SOCKET && state==WINSOCKET_ACCEPTING);}
  // Testa se um socket est� conectado (pronto para ler e escrever)
  inline bool connected() const {return (id!=INVALID_SOCKET && state==WINSOCKET_CONNECTED);}
  // Imprime um socket
  friend std::ostream& operator<<(std::ostream& os, const winsocket &);

  friend class tcp_winsocket_server;
  friend class tcp_winsocket;
  friend class winsocket_queue;
};

/* #############################################################
   ##  As classes dos sockets orientados a conex�o (TCP)      ##
   ############################################################# */

class tcp_winsocket_server: public winsocket
{
public:
  // Abre um novo socket para esperar conex�es
  // S� pode ser usado em sockets "virgens" ou explicitamente fechados
  WINSOCKET_STATUS listen(const char *port, int nconex=1);
  // Aceita uma conex�o que chegou em um socket aberto
  // S� pode ser usado em socket para o qual tenha sido feito um "listen" antes
  // Retorna um socket conectado (n�o-conectado em caso de erro)
  WINSOCKET_STATUS accept(tcp_winsocket&) const;
};

class tcp_winsocket: public winsocket
{
public:
  // Se conecta a um socket aberto
  // S� pode ser usado em sockets "virgens" ou explicitamente fechados
  WINSOCKET_STATUS connect(const char *name, const char *port);
  // Escreve em um socket conectado
  // S� pode ser usado em socket para o qual tenha sido feito um "connect" antes
  // Ou ent�o em um socket retornado pelo "accept" de um socket servidor
  WINSOCKET_STATUS write(const char*, size_t) const;
  // L� de um socket conectado
  // S� pode ser usado em socket para o qual tenha sido feito um "connect" antes
  // Ou ent�o em um socket retornado pelo "accept" de um socket servidor
  WINSOCKET_STATUS read(char *dado, size_t len, long milisec=-1) const;
  // Escreve um int32_t em um socket conectado
  WINSOCKET_STATUS write_int(const int32_t num) const;
  // L� um int32_t de um socket conectado
  WINSOCKET_STATUS read_int(int32_t &num, long milisec=-1) const;
  // Escreve uma string em um socket conectado
  // Primeiro escreve o numero de bytes da string (int32_T), depois os caracteres
  WINSOCKET_STATUS write_string(const string &msg) const;
  // L� uma string de um socket conectado
  // Primeiro l� o numero de bytes da string (int32_T), depois os caracteres
  WINSOCKET_STATUS read_string(string &msg, long milisec=-1) const;
};

/* #############################################################
   ##  A fila de sockets                                      ##
   ############################################################# */

class winsocket_queue
{
 private:
  fd_set set;
 public:
  inline void clean() {FD_ZERO(&set);};
  inline winsocket_queue() {clean();}
  inline ~winsocket_queue() {clean();}
  // Adiciona um socket a uma fila de sockets
  WINSOCKET_STATUS include(const winsocket &a);
  // Retira um socket de uma fila de sockets
  WINSOCKET_STATUS exclude(const winsocket &a);
  // Bloqueia at� haver alguma atividade de leitura em socket da fila
  WINSOCKET_STATUS wait_read(long milisec=-1);
  // Bloqueia at� haver alguma atividade de conex�o em socket da fila
  inline WINSOCKET_STATUS wait_connect(long milisec=-1) {
    return wait_read(milisec);}
  // Bloqueia at� haver alguma atividade de escrita em socket da fila
  WINSOCKET_STATUS wait_write(long milisec=-1);
  // Testa se houve atividade em um socket espec�fico da fila
  bool had_activity(const winsocket &a);
  friend std::ostream& operator<<(std::ostream& os, const winsocket_queue &);
};

#endif
