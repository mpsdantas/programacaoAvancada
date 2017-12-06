#ifndef DADOS_WHATSPROG_H
#define DADOS_WHATSPROG_H

#include <string>
#include <stdint.h>

using namespace std;

// Numero de bytes das informacoes a serem enviadas
#define TAM_MIN_NOME_USUARIO 6
#define TAM_MAX_NOME_USUARIO 12
#define TAM_MIN_SENHA 6
#define TAM_MAX_SENHA 12
#define TAM_MAX_MSG 255

// Timeout (em segundos) para esperar o envio de um dado obrigatorio pelo socket
#define TIMEOUT_WHATSPROG 30

// Os possiveis estados de uma mensagem
enum MsgStatus
{
    MSG_ENVIADA=1,
    MSG_RECEBIDA=2,
    MSG_ENTREGUE=3,
    MSG_LIDA=4,
    MSG_INVALIDA=-1
};

// Os campos que compoem uma mensagem armazenada no cliente ou no servidor
class Mensagem
{
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

enum ComandoWhatsProg
{
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
    //CMD_CRIAR_CONVERSA=1014,
    //CMD_CRIAR_CONVERSA_OK=1015
};

#endif // DADOS_WHATSPROG_H
