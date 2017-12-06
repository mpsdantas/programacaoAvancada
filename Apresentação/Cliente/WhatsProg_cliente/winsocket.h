#ifndef _WINSOCKET_H_
#define _WINSOCKET_H_

#include <iostream>
#include <cstdlib>
#include <stdint.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif // _WIN32_WINNT

#ifndef MSG_WAITALL
#define MSG_WAITALL 0x0008
#endif // MSG_WAITALL

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

using namespace std;

/*
###############################################################################

NAO ESQUECA DE LINKAR COM A BIBLIOTECA Ws2_32. Incluir essa opcao no compilador
No CodeBlocs: botao direito no nome do projeto, Build options, Linker settings,
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

// Predefinicao das classes
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
  // Retorna SOCKET_OK ou SOCKET_ERRO
  WINSOCKET_STATUS shutdown();
  // Fecha (caso esteja aberto) um socket
  void close();
  // ATENCAO: ao criar um destrutor que fechasse o socket, voce nao poderia mais passar nenhum socket
  // por copia como parametro para uma funcao, nem retornar um socket por valor. Se fizesse isso, seria
  // chamado o destrutor na copia, que fecharia o socket no Windows e afetaria o socket original.
  // Portanto, o destrutor nao fecha o socket. Voce tem que chamar close() explicitamente ao terminar de usar
  inline ~winsocket() {}
  // Testa se um socket eh "virgem" ou foi fechado
  inline bool closed() const {return (id==INVALID_SOCKET && state==WINSOCKET_IDLE);}
  // Testa se um socket estah aberto (aceitando conexoes)
  inline bool accepting() const {return (id!=INVALID_SOCKET && state==WINSOCKET_ACCEPTING);}
  // Testa se um socket estah conectado (pronto para ler e escrever)
  inline bool connected() const {return (id!=INVALID_SOCKET && state==WINSOCKET_CONNECTED);}
  // Imprime um socket
  friend std::ostream& operator<<(std::ostream& os, const winsocket &);

  friend class tcp_winsocket_server;
  friend class tcp_winsocket;
  friend class winsocket_queue;
};

/* #############################################################
   ##  As classes dos sockets orientados a conexao (TCP)      ##
   ############################################################# */

class tcp_winsocket: public winsocket
{
public:
  // Se conecta a um socket aberto
  // Soh pode ser usado em sockets "virgens" ou explicitamente fechados
  // Retorna SOCKET_OK, se tudo deu certo, ou outro valor, em caso de erro
  WINSOCKET_STATUS connect(const char *name, const char *port);
  // Escreve em um socket conectado
  // Soh pode ser usado em socket para o qual tenha sido feito um "connect" antes
  // Ou entao em um socket retornado pelo "accept" de um socket servidor
  // Retorna o numero de bytes enviados (ou seja, len), em caso de sucesso,
  // ou SOCKET_ERRO
  WINSOCKET_STATUS write(const char* dado, size_t len) const;
  // Leh de um socket conectado
  // Soh pode ser usado em socket para o qual tenha sido feito um "connect" antes
  // Ou entao em um socket retornado pelo "accept" de um socket servidor
  // O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
  // por dados; se for <0, que eh o default, espera indefinidamente.
  // Retorna o numero de bytes lidos (ou seja, len), em caso de sucesso,
  // zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  WINSOCKET_STATUS read(char *dado, size_t len, long milisec=-1) const;
  // Escreve um int32_t em um socket conectado
  // Retorna o numero de bytes enviados (ou seja, 4), em caso de sucesso,
  // ou SOCKET_ERRO
  WINSOCKET_STATUS write_int(const int32_t num) const;
  // Leh um int32_t de um socket conectado
  // O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
  // por dados; se for <0, que eh o default, espera indefinidamente.
  // Retorna o numero de bytes lidos (ou seja, len), em caso de sucesso,
  // zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  WINSOCKET_STATUS read_int(int32_t &num, long milisec=-1) const;
  // Escreve uma string em um socket conectado
  // Primeiro escreve o numero de bytes da string (int32_T), depois os caracteres
  // Retorna o numero de bytes enviados (ou seja, msg.size()), em caso de sucesso,
  // ou SOCKET_ERRO
  WINSOCKET_STATUS write_string(const string &msg) const;
  // Leh uma string de um socket conectado
  // Primeiro leh o numero de bytes da string (int32_T), depois os caracteres
  // O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
  // por dados; se for <0, que eh o default, espera indefinidamente.
  // Retorna o numero de bytes lidos (ou seja, msg.size()), em caso de sucesso,
  // zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  WINSOCKET_STATUS read_string(string &msg, long milisec=-1) const;
};

class tcp_winsocket_server: public winsocket
{
public:
  // Abre um novo socket para esperar conexoes
  // Soh pode ser usado em sockets "virgens" ou explicitamente fechados
  // Retorna SOCKET_OK ou SOCKET_ERRO
  WINSOCKET_STATUS listen(const char *port, int nconex=1);
  // Aceita uma conexao que chegou em um socket aberto
  // Soh pode ser usado em socket para o qual tenha sido feito um "listen" antes
  // O socket "a" passado como parametro, em caso de sucesso, estarah conectado
  // (nao-conectado em caso de erro)
  // Retorna SOCKET_OK ou SOCKET_ERRO
  WINSOCKET_STATUS accept(tcp_winsocket &a) const;
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
  // Retorna SOCKET_OK ou SOCKET_ERRO
  WINSOCKET_STATUS include(const winsocket &a);
  // Retira um socket de uma fila de sockets
  // Retorna SOCKET_OK ou SOCKET_ERRO
  WINSOCKET_STATUS exclude(const winsocket &a);
  // Bloqueia ateh haver alguma atividade de leitura em socket da fila
  // Retorna o numero de sockets (>0) que tem dados a serem lidos,
  // em caso de sucesso; zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  WINSOCKET_STATUS wait_read(long milisec=-1);
  // Bloqueia ateh haver alguma atividade de conexao em socket da fila
  // Retorna o numero de sockets (>0) que tem conexoes a serem lidos,
  // em caso de sucesso; zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  inline WINSOCKET_STATUS wait_connect(long milisec=-1) {return wait_read(milisec);}
  // Bloqueia ateh haver alguma atividade de escrita em socket da fila
  // Retorna o numero de sockets (>0) que tiveram dados escritos,
  // em caso de sucesso; zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  WINSOCKET_STATUS wait_write(long milisec=-1);
  // Testa se houve atividade em um socket especifico da fila
  bool had_activity(const winsocket &a);
  // Impressao
  friend std::ostream& operator<<(std::ostream& os, const winsocket_queue &);
};

#endif
