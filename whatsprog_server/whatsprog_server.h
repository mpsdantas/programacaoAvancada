//INÍCIO INCLUDE
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdint.h>
#include "winsocket.h"
//FIM INCLUDE

//INICIO DEFINIÇÕES DE CONSTANTES DO PROGRAMA
#define PORTA "23456"
#define TAM_MIN_LOGIN 6
#define TAM_MAX_LOGIN 12
#define TAM_MIN_SENHA 6
#define TAM_MAX_SENHA 12
#define TAM_MAX_MSG 255
#define TIMEOUT 60
//FIM DEFINIÇÕES DE CONSTANTES DO PROGRAMA

//INICIO ENUM'S
enum MsgStatus{
    MSG_ENVIADA=1,
    MSG_RECEBIDA=2,
    MSG_ENTREGUE=3,
    MSG_LIDA=4,
    MSG_INVALIDA=-1
};
enum CommandWhatsProg{
    CMD_NEW_USER=1001,
    CMD_LOGIN_USER=1002,
    CMD_LOGIN_OK=1003,
    CMD_LOGIN_INVALIDO=1004,
    CMD_NOVA_MSG=1005,
    CMD_MSG_RECEBIDA=1006,
    CMD_MSG_ENTREGUE=1007,
    CMD_MSG_LIDA1=1008,
    CMD_MSG_LIDA2=1009,
    CMD_ID_INVALIDA=1010,
    CMD_USER_INVALIDO=1011,
    CMD_MSG_INVALIDA=1012,
    CMD_LOGOUT_USER=1013
};
//FIM ENUM'S

//INCIO CLASSES

//CLASSE MENSAGEM
class Mensagem{
private:
    // Identificador da mensagem
    int32_t id;
    // Nomes do remetente e do destinatario
    string remetente;
    string destinatario;
    // Texto da mensagem
    string texto;
    // Estado (status) da mensagem
    MsgStatus status;
public:
    inline Mensagem(): id(0), remetente(""), destinatario(""),
                       texto(""), status(MSG_INVALIDA) {}
    // Funcoes de consulta/alteracao de parametros
    // As funcoes de alteracao retornam false em caso de erro, true se OK
    inline uint32_t getId() const {return id;}
    bool setId(uint32_t I);
    inline const string &getRemetente() const {return remetente;}
    bool setRemetente(const string &R);
    inline const string &getDestinatario() const {return destinatario;}
    bool setDestinatario(const string &D);
    inline const string &getTexto() const {return texto;}
    bool setTexto(const string &T);
    inline MsgStatus getStatus() const {return status;}
    bool setStatus(MsgStatus S);
};
//CLASSE MENSAGEM

//CLASSE USUARIO
class Usuario{
private:
    uint32_t id;
    string login;
    string senha;
    tcp_winsocket s;
    list<Mensagem> conversa;
public:
    inline Usuario(): id(0),login(""),senha(""),s(){}
    inline string getLogin(){return login;}
    inline string getSenha(){return senha;}
    inline tcp_winsocket getSocket(){return s;}
    inline tcp_winsocket setSocket(tcp_winsocket so){s = so;}
    inline void setLogin(const string &l){login = l;}
    inline void setSenha(const string &s){senha = s;}
    bool tamanhoLoginValido(const string &l);
    bool tamanhoSenhaValido(const string &l);
};
//CLASSE USUARIO

//CLASSE SERVER
class Server{
private:
    tcp_winsocket t;
    winsocket_queue f;
    tcp_winsocket_server server; // Socket do servidor
    WINSOCKET_STATUS iResult;
    list<Usuario> usuarios;
    list<Mensagem> buffer;
public:
    bool criarUsuario(const string &l, const string &s, tcp_winsocket so);
    bool usuarioRepetido(const string &l);
    void abrirConexao(WINSOCKET_STATUS iResult);
    void statusThread(HANDLE tHandle);
    void monitorarChegada(bool fim);
    bool socketAceito();
    void enviarComando(CommandWhatsProg comando, tcp_winsocket socket);
    void enviarComando(CommandWhatsProg comando,int32_t param1, tcp_winsocket socket);
    bool loginUsuario(string login, string password, tcp_winsocket socket);
    bool enviarMensagem();
    void aguardarAcao();
    void enviarMensagemCliente(Usuario usuario);
    void cmd_msg_lida1(Usuario usuario);
    bool enviarComando(CommandWhatsProg comando, int32_t param1, string param2, string param3, tcp_winsocket socket);
    void checkBuffer(Usuario usuario);
};
//CLASSE SERVER
