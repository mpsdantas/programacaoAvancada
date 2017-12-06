#ifndef DADOS_CLIENTE_H
#define DADOS_CLIENTE_H

#include <string>
#include <vector>
#include <stdint.h>
#include "dados_whatsprog.h"
#include "winsocket.h"

using namespace std;

// Classe utilizada para armazenar as conversas no cliente
class Conversa
{
private:
    // Correspondente (outro participante da conversa). O "meuUsuario" (ver classe DadosCliente a seguir)
    // e o "correspondente" devem ser o remetente ou o destinatario de todas as mensagens da conversa.
    string correspondente;
    // Todas as mensagens da conversa
    vector<Mensagem> LM;
public:
    inline Conversa(): correspondente(""), LM() {}
    // Retorna o numero de mensagens da conversa
    inline unsigned size() const {return LM.size();}
    // Retorna a i-esima mensagem da conversa
    Mensagem &operator[](unsigned i);
    // Apaga todas as msgs da conversa
    inline void clearMessages() {LM.clear();}
    // Insere nova msg no final da conversa
    inline void insertMessage(const Mensagem &M) {LM.push_back(M);}
    // Retorna o numero de msgs entregues (ainda não lidas) de uma conversa
    unsigned getNumMsgsEntregues() const;
    // Funcoes de consulta/alteracao dos demais parametros
    // As funcoes de alteracao retornam false em caso de erro, true se OK
    inline const string &getCorrespondente() const {return correspondente;}
    bool setUsuario(const string &U);
};

class DadosCliente
{
private:
    // O computador (IP) onde roda o programa servidor
    string servidor;
    // O nome do usuario do cliente
    string meuUsuario;
    // O indice da conversa atualmente sendo visualizada
    // De 0 acima; se negativo, nenhuma conversa estah selecionada
    int idConversa;
    // A ultima ID utilizada em msg enviada por mim
    // Maior que zero; se igual a 0, nenhuma msg foi enviada ainda
    int32_t idMensagem;
    // Todas as conversas
    vector<Conversa> LC;
public:
    DadosCliente();
    // Funcoes de consulta dos dados principais (servidor, login do usuario)
    inline const string &getServidor() const {return servidor;}
    inline const string &getMeuUsuario() const {return meuUsuario;}
    // Limpa o servidor e o nome do usuario (deslogar)
    void clearServidorUsuario();
    // Define os parametros principais da conexao: servidor e usuario (logar)
    // Retorna false em caso de erro, true se OK
    bool setServidorUsuario(const string &IP, const string &MU);
    // Retorna o numero de conversas
    inline unsigned size() const {return LC.size();}
    // Retorna a i-esima conversa
    Conversa &operator[](unsigned i);
    // Inclui (cria) uma nova conversa com o correspondente passado como parametro
    // Retorna false em caso de erro, true se OK
    bool insertConversa(const string &U);
    // Exclui a i-esima conversas
    // Retorna false em caso de erro, true se OK
    bool eraseConversa(unsigned i);
    // Apaga todas as conversas
    inline void clearConversas() {LC.clear();}
    // Gera (incrementa) uma id valida para a proxima msg
    inline int getNovaIdMensagem() {return ++idMensagem;}
    // Funcoes de consulta/alteracao dos demais parametros
    // As funcoes de alteracao retornam false em caso de erro, true se OK
    inline int getIdConversa() const {return idConversa;}
    bool setIdConversa(int ID);
};

// Os dados das conversas do cliente serao armazenados em uma variavel global
extern DadosCliente DCliente;

// O socket do cliente serah armazenado em uma variavel global
extern tcp_winsocket s;

// O identificador da thread de leitura de dados do socket
extern HANDLE tHandle;

#endif // DADOS_CLIENTE_H
