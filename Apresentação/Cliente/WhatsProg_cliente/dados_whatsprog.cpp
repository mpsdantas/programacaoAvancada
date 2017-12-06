#include "dados_whatsprog.h"

bool Mensagem::setId(uint32_t I)
{
    if (I<=0)
    {
        id = 0;
        return false;
    }
    id=I;
    return true;
}

bool Mensagem::setRemetente(const string &R)
{
    if (R.size()<TAM_MIN_NOME_USUARIO || R.size()>TAM_MAX_NOME_USUARIO)
    {
        remetente = "";
        return false;
    }
    remetente=R;
    return true;
}

bool Mensagem::setDestinatario(const string &D)
{
    if (D.size()<TAM_MIN_NOME_USUARIO || D.size()>TAM_MAX_NOME_USUARIO)
    {
        destinatario = "";
        return false;
    }
    destinatario = D;
    return true;
}

bool Mensagem::setTexto(const string &T)
{
    if (T.size()==0)
    {
        texto = "";
        return false;
    }
    texto=T;
    return true;
}


bool Mensagem::setStatus(MsgStatus S)
{
    if (S!=MSG_ENVIADA && S!=MSG_RECEBIDA && S!=MSG_ENTREGUE && S!=MSG_LIDA && S!=MSG_INVALIDA)
    {
        status = MSG_INVALIDA;
        return false;
    }
    status=S;
    return true;
}
