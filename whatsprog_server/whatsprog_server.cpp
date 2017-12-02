#include "whatsprog_server.h"
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
    if (R.size()<TAM_MIN_LOGIN || R.size()>TAM_MAX_LOGIN)
    {
        remetente = "";
        return false;
    }
    remetente=R;
    return true;
}

bool Mensagem::setDestinatario(const string &D)
{
    if (D.size()<TAM_MIN_LOGIN || D.size()>TAM_MAX_LOGIN)
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
/*
##############-----METODOS CLASSE SERVER-----##############
*/

/*
    Metodo que verifica se um usuário é repetido
    Passa como parametro o seu login e retorna verdadeiro caso esse login já exista.
*/
bool Server::usuarioRepetido(const string &l){
    for(list<Usuario>::iterator k = usuarios.begin(); k != usuarios.end();k++)
        if((*k).getLogin().compare(l)==0) return true;
    return false;
}
/*
    Método que verifica se a thread foi criada com sucesso.
    se existir erro ele finaliza o programa.
*/
void Server::statusThread(HANDLE tHandle){
    if (tHandle == NULL){
        cerr << "Problema na criação da thread: " << GetLastError() << endl;
        exit(1);
    }
}
/*
    Método que cria um usuário.
    Cadastra todas as infomrações necessárias para um usuário
    retorna verdadeiro caso ele for criado com sucesso.
*/
bool Server::criarUsuario(const string &l, const string &s,tcp_winsocket so){
    Usuario u;
    if(u.tamanhoLoginValido(l) && u.tamanhoSenhaValido(s)){
        enviarComando(CMD_LOGIN_INVALIDO, so);
        return false;
    }
    if(usuarioRepetido(l)){
        enviarComando(CMD_LOGIN_INVALIDO, so);
        return false;
    }
    u.setLogin(l);
    u.setSenha(s);
    u.setSocket(so);
    usuarios.push_back(u);
    enviarComando(CMD_LOGIN_OK, so);
    cout<<"Usuário Cadastrado"<<endl;
    return true;
}

bool Server::loginUsuario(string login, string senha, tcp_winsocket socket){
    for (list<Usuario>::iterator it=usuarios.begin(); it != usuarios.end(); ++it){
        if ((*it).getLogin().compare(login) + (*it).getSenha().compare(senha) == 0) {
            enviarComando(CMD_LOGIN_OK, socket);
            cout << login << " logou" << endl;
            return true;
        }
    }
    enviarComando(CMD_LOGIN_INVALIDO, socket);
    cout<<"Usuário Logado"<<endl;
    return false;
}
/*
    Metodo que verifica se existem erros na abertura da conexão do main
    finaliza o programa caso ocorram erros.
*/
void Server::abrirConexao(WINSOCKET_STATUS iR){
    if (iR != 0){
        cerr << "WSAStartup failed: " << iR << endl;
        exit(1);
    }
    if (server.listen(PORTA) != SOCKET_OK){
        cerr << "Não foi possível abrir o socket de controle\n";
        exit(1);
    }
}
/*
    Metodo que monitora a chegada de sockets novos no servidor.
*/
void Server::monitorarChegada(bool fim){
    // Inclui na fila de sockets para o select todos os sockets que eu
    // quero monitorar para ver se houve chegada de dados
    f.clean();
    if (!(fim = !server.accepting())){
      f.include(server);
      for (list<Usuario>::iterator i=usuarios.begin(); i!=usuarios.end(); i++){
    	  if ((*i).getSocket().connected())
    	  {
	        f.include((*i).getSocket());
    	  }
      }
    }
    iResult = f.wait_read(TIMEOUT*1000);
    if (iResult==SOCKET_ERROR){
        cerr << "Erro na espera por alguma atividade\n";
        exit(1);
    }
}
/*
    Metodo que realiza funções caso o socket for aceito.
*/
bool Server::socketAceito(){
    int32_t comando;
    string login, senha;
    tcp_winsocket temp_socket;

    if (f.had_activity(server)){
        if (server.accept(temp_socket) != SOCKET_OK){
            cerr << "Não foi possivel estabelecer conexão.\n";
            return false;
        }else{
            iResult = temp_socket.read_int(comando,TIMEOUT*1000);
            if (iResult == SOCKET_ERROR){
              cerr << "Erro na leitura do nome de login de um cliente que se conectou.\n";
              temp_socket.close();
            }else{
                iResult = temp_socket.read_string(login,TIMEOUT*1000);
                cout << iResult;
                if (iResult == SOCKET_ERROR){
                    cerr << "Erro na leitura do login de um cliente que se conectou.\n";
                    temp_socket.close();
                }
                iResult = temp_socket.read_string(senha,TIMEOUT*1000);
                if (iResult == SOCKET_ERROR){
                    cerr << "Erro na leitura da senha de um cliente que se conectou.\n";
                    temp_socket.close();
                }
                if (comando == CMD_NEW_USER) {
                    criarUsuario(login, senha, temp_socket);

                } else if (comando == CMD_LOGIN_USER) {
                    loginUsuario(login,senha,temp_socket);
                    //Checar se tem usuário no buffer.
                } else {
                    cout << "nera p ta aq n migo" << endl;
                }
            }
        }
    }
}

void Server::enviarComando(CommandWhatsProg comando, tcp_winsocket socket){
    WINSOCKET_STATUS iResult;
    iResult = socket.write_int(comando);
    if ( iResult == SOCKET_ERROR ) {
        cerr << "Problema ao enviar mensagem para o cliente " << endl;
        socket.shutdown();
    }
}

void Server::enviarComando(CommandWhatsProg comando,int32_t param1, tcp_winsocket socket){
    WINSOCKET_STATUS iResult;
    iResult = socket.write_int(comando);
    if ( iResult == SOCKET_ERROR ) {
        cerr << "Problema ao enviar mensagem para o cliente " << endl;
        socket.shutdown();
    }else{
        iResult = socket.write_int(param1);
        if ( iResult == SOCKET_ERROR ) {
            cerr << "Problema ao enviar mensagem para o cliente " << endl;
            socket.shutdown();
        }
    }
}
void Server::aguardarAcao(){
    int32_t comando;

    for (list<Usuario>::iterator i = usuarios.begin(); i!=usuarios.end(); i++){
          if ((*i).getSocket().connected() && f.had_activity((*i).getSocket())){
            iResult = (*i).getSocket().read_int(comando,TIMEOUT*1000);
            if (iResult == SOCKET_ERROR){
              cerr << "Erro na comunicação\n";
              (*i).getSocket().shutdown();
            }else{
                switch(comando){
                    case CMD_NOVA_MSG:
                        enviarMensagemCliente((*i));
                        break;
                    case CMD_MSG_LIDA1:

                        break;
                    default:
                        cout << "Operação inválida.";
                        break;
                }
            }
          }
    }
}
void Server::enviarMensagemCliente(Usuario usuario){
    int32_t param1;
    string param2, param3;
    Mensagem mensagem;
    iResult = usuario.getSocket().read_int(param1, TIMEOUT*1000);
    if (iResult == SOCKET_ERROR){
        cerr << "Erro na comunicacao \n";
        usuario.getSocket().shutdown();
    } else{
        iResult = usuario.getSocket().read_string(param2, TIMEOUT*1000);

        if (iResult == SOCKET_ERROR){
            cerr << "Erro na comunicacao \n";
            usuario.getSocket().shutdown();
        } else {
            iResult = usuario.getSocket().read_string(param3, TIMEOUT*1000);
            if (iResult == SOCKET_ERROR){
                cerr << "Erro na comunicacao \n";
                usuario.getSocket().shutdown();
            } else {
                if (mensagem.setRemetente(usuario.getLogin())) {
                    if (mensagem.setId(param1)) {
                        //verificar se o id é válido
                            //iterar o buffer de mensagens desse determinado usuário
                                //checando se tem id igual
                        if (mensagem.setDestinatario(param2)) {
                            for(list<Mensagem>::iterator k = buffer.begin(); k != buffer.end();k++){
                                if((*k).getDestinatario().compare(param2)==0){
                                    if (mensagem.setTexto(param3)) {
                                        // verificar se user ta on
                                            //se sim eviar msg
                                        enviarComando(CMD_MSG_RECEBIDA,param1,usuario.getSocket());
                                        //Armazenar no buffer
                                    }else{
                                        enviarComando(CMD_MSG_INVALIDA,param1,usuario.getSocket());
                                    }
                                }else{
                                    enviarComando(CMD_USER_INVALIDO, param1, usuario.getSocket());
                                }
                            }
                        } else {
                            enviarComando(CMD_USER_INVALIDO,param1,usuario.getSocket());
                        }
                    } else {
                        enviarComando(CMD_ID_INVALIDA,param1,usuario.getSocket());
                    }
                }else{
                    usuario.getSocket().shutdown();
                }
            }
        }
    }
}
void Server::cmg_msg_lida1(Usuario usuario){
    int32_t param1;
    string param2;//remetente
    Mensagem mensagem;
    iResult = usuario.getSocket().read_int(param1, TIMEOUT*1000);
    if (iResult == SOCKET_ERROR){
        cerr << "Erro na comunicacao \n";
        usuario.getSocket().shutdown();
    } else{
        iResult = usuario.getSocket().read_string(param2, TIMEOUT*1000);

        if (iResult == SOCKET_ERROR){
            cerr << "Erro na comunicacao \n";
            usuario.getSocket().shutdown();
        }else{
            for (list<Mensagem>::iterator it=buffer.begin(); it != buffer.end(); ++it) {
                if((*it).getRemetente().compare(param2) == 0){
                    if ((*it).getId() == param1){
                        (*it).setStatus(MSG_LIDA);

                        for (list<Usuario>::iterator a=usuarios.begin(); a != usuarios.end(); ++a) {

                            if ((*a).getLogin().compare(param2) == 0){
                                enviarComando(CMD_MSG_LIDA2, param1, (*a).getSocket());
                                buffer.erase(it);
                                return;
                            }

                        }
                    }
                }
            }
            usuario.getSocket().shutdown();
        }
    }
}
/*
##############-----FIM METODOS CLASSE SERVER-----##############
*/


/*
##############-----METODOS CLASSE USUARIO-----##############
*/

/*
    Método responsavel por verificar o tamanho da string de usuário.
    Retorna verdadeiro quando o tamanho é inválido.
*/
bool Usuario::tamanhoLoginValido(const string &l){
    if((!(l.size()>=TAM_MIN_LOGIN && l.size()<=TAM_MAX_LOGIN))) return true;
    return false;
}

/*
    Método responsavel por verificar o tamanho da string de senha.
    Retorna verdadeiro quando o tamanho é inválido.
*/
bool Usuario::tamanhoSenhaValido(const string &l){
    if((!(l.size()>=TAM_MIN_SENHA && l.size()<=TAM_MAX_SENHA))) return true;
    return false;
}

/*
##############-----FIM METODOS CLASSE UUSUARIO-----##############
*/
