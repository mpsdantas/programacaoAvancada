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
void Server::checkBuffer(Usuario &usuario){
    for (list<Mensagem>::iterator it=buffer.begin(); it != buffer.end(); ++it) {
        if ((*it).getDestinatario().compare(usuario.getLogin()) == 0){
            if ((*it).getStatus() == MSG_RECEBIDA) {
                if (enviarComando(CMD_NOVA_MSG, (*it).getId(), usuario.getLogin(), (*it).getTexto(), usuario.getSocket())) {
                    (*it).setStatus(MSG_ENTREGUE);
                    enviarComando(CMD_MSG_ENTREGUE, (*it).getId(), usuario.getSocket());
                }
            }
        }
    }
}
/*
    Metodo que verifica se um usu�rio � repetido
    Passa como parametro o seu login e retorna verdadeiro caso esse login j� exista.
*/
bool Server::usuarioRepetido(const string &l){
    for(list<Usuario>::iterator k = usuarios.begin(); k != usuarios.end();k++)
        if((*k).getLogin().compare(l)==0) return true;
    return false;
}
/*
    M�todo que verifica se a thread foi criada com sucesso.
    se existir erro ele finaliza o programa.
*/
void Server::statusThread(HANDLE tHandle){
    if (tHandle == NULL){
        cerr << "Problema na cria��o da thread: " << GetLastError() << endl;
        exit(1);
    }
}
/*
    M�todo que cria um usu�rio.
    Cadastra todas as infomra��es necess�rias para um usu�rio
    retorna verdadeiro caso ele for criado com sucesso.
*/
bool Server::criarUsuario(const string &l, const string &s,tcp_winsocket &so){
    Usuario u;
    string nome = "usuarios.txt";
    ofstream arq(nome.c_str());
    //ifstream teste(nome.c_str());
    u.setLogin(l);
    u.setSenha(s);

    if (usuarioRepetido(l) || u.tamanhoLoginValido(l) || u.tamanhoSenhaValido(s)){
        enviarComando(CMD_LOGIN_INVALIDO, so);
        return false;
    }

    u.setSocket(so);
    usuarios.push_back(u);
    salvarUsuarios(arq);
    cout << "------------------------------"<<endl;
    cout << "NOVO USUARIO CADASTRADO" << endl;
    cout << "Usuario: " << l << endl;
    cout << "Senha: ********" <<endl;
    cout << "------------------------------"<<endl;
    enviarComando(CMD_LOGIN_OK, so);
    return true;
}

bool Server::loginUsuario(string login, string senha, tcp_winsocket &socket){
    for (list<Usuario>::iterator it=usuarios.begin(); it != usuarios.end(); ++it){
        if ((*it).getLogin().compare(login) + (*it).getSenha().compare(senha) == 0) {
            cout << "------------------------------"<<endl;
            cout << "NOVO LOGIN" << endl;
            cout << "Usuario: " << login << endl;
            cout << "------------------------------"<<endl;
            (*it).setSocket(socket);
            enviarComando(CMD_LOGIN_OK, socket);
            return true;
        }
    }
    enviarComando(CMD_LOGIN_INVALIDO, socket);
    return false;
}
/*
    Metodo que verifica se existem erros na abertura da conex�o do main
    finaliza o programa caso ocorram erros.
*/
void Server::abrirConexao(WINSOCKET_STATUS iR){
    if (iR != 0){
        cerr << "WSAStartup failed: " << iR << endl;
        exit(1);
    }
    if (server.listen(PORTA) != SOCKET_OK){
        cerr << "Não foi poss�vel abrir o socket de controle\n";
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
    if (server.accepting()){
      f.include(server);
      for (list<Usuario>::iterator i=usuarios.begin(); i!=usuarios.end(); i++){
    	  if ((*i).getSocket().connected())
    	  {
	        f.include((*i).getSocket());
    	  }else{
            (*i).getSocket().close();
    	  }
      }
    }
    iResult = f.wait_read(TIMEOUT*1000);
    if (iResult==SOCKET_ERROR){
        cerr << "Erro na espera por alguma atividade\n";
    }
}
ostream& Server::salvarUsuarios(ostream &O){
    O << "USUARIOS " << usuarios.size()<<"\n";
    for(list<Usuario>::iterator i = usuarios.begin(); i!=usuarios.end(); i++){
        O << (*i).getLogin() << "," << (*i).getSenha() << ";\n";
    }
}
istream& Server::recuperarUsuarios(istream &I){
    int n;
    string cabecalho,login,senha;
    getline(I,cabecalho,' ');
    I >> n;
    Usuario usuario;
    for(int i=0; i<n;i++){
        I.ignore(255,'\n');
        getline(I,login,',');
        usuario.setLogin(login);
        getline(I,senha,';');
        usuario.setSenha(senha);
        usuarios.push_back(usuario);
    }
}
void Server::carregarUsuarios(){
    string nome = "usuarios.txt";
    ifstream arq(nome.c_str());
    if (arq.is_open()){
        recuperarUsuarios(arq);
    }
}

/*
    Metodo que realiza fun��es caso o socket for aceito.
*/

bool Server::socketAceito(){
   int32_t cmd;
    string login, password;
    tcp_winsocket temp_socket;
    if (f.had_activity(server)){
        if (server.accept(temp_socket) != SOCKET_OK){
            cerr << "Nao foi possivel estabelecer uma conexao (Método socketAceito).\n";
            return false;
        } else {
            iResult = temp_socket.read_int(cmd,TIMEOUT*1000);
            if (iResult == SOCKET_ERROR){
              cerr << "Erro na leitura do codigo (Método socketAceito).\n";
              temp_socket.close();
            } else {
                iResult = temp_socket.read_string(login,TIMEOUT*1000);
                if (iResult == SOCKET_ERROR){
                    cerr << "Erro na leitura do login de um cliente que se conectou (Método socketAceito).\n";
                    temp_socket.close();
                }

                iResult = temp_socket.read_string(password,TIMEOUT*1000);
                if (iResult == SOCKET_ERROR){
                    cerr << "Erro na leitura da senha de um cliente que se conectou (Método socketAceito).\n";
                    temp_socket.close();
                }

                if (cmd == CMD_NEW_USER) {
                    criarUsuario(login, password, temp_socket);
                } else if (cmd == CMD_LOGIN_USER) {
                    loginUsuario(login, password, temp_socket);
                    //checar se tem msg no buffer
                } else {
                    cout << "ERRO (Método socketAceito)" << endl;
                }
            }
        }
    }
}
void Server::enviarComando(CommandWhatsProg comando, tcp_winsocket &socket){
    WINSOCKET_STATUS iResult;
    iResult = socket.write_int(comando);
    if ( iResult == SOCKET_ERROR ) {
        cerr << "Problema ao enviar mensagem para o cliente. (Metodo enviarComando)" << endl;
        socket.close();
    }
}
void Server::enviarComando(CommandWhatsProg comando,int32_t param1, tcp_winsocket &socket){
    WINSOCKET_STATUS iResult;
    iResult = socket.write_int(comando);
    if ( iResult == SOCKET_ERROR ) {
        cerr << "Problema ao enviar mensagem para o cliente (Metodo enviarComando)." << endl;
        socket.close();
    }else{
        iResult = socket.write_int(param1);
        if ( iResult == SOCKET_ERROR ) {
            cerr << "Problema ao enviar mensagem para o cliente (Metodo enviarComando)." << endl;
            socket.close();
        }
    }
}
bool Server::enviarComando(CommandWhatsProg comando, int32_t param1, string param2, string param3, tcp_winsocket &socket){
    iResult = socket.write_int(comando);
    if ( iResult == SOCKET_ERROR ) {
        cerr << "Problema ao enviar mensagem para o cliente (Metodo enviarComando)." << endl;
        socket.close();
    } else {
        iResult = socket.write_int(param1);

        if ( iResult == SOCKET_ERROR ) {
            cerr << "Problema ao enviar mensagem para o cliente (Metodo enviarComando)." << endl;
            socket.close();
        } else {
            iResult = socket.write_string(param2);

            if ( iResult == SOCKET_ERROR ) {
                cerr << "Problema ao enviar mensagem para o cliente (Metodo enviarComando)." << endl;
                socket.close();
            } else {
                iResult = socket.write_string(param3);

                if ( iResult == SOCKET_ERROR ) {
                    cerr << "Problema ao enviar mensagem para o cliente (Metodo enviarComando)." << endl;
                    socket.close();
                } else {
                    return true;
                }
            }
        }
    }

    return false;
}
void Server::aguardarAcao(){
    int32_t comando;

    for(list<Usuario>::iterator i = usuarios.begin(); i!=usuarios.end(); i++){
          if ((*i).getSocket().connected() && f.had_activity((*i).getSocket())){
            iResult = (*i).getSocket().read_int(comando,TIMEOUT*1000);
            if (iResult == SOCKET_ERROR){
              cerr << "Erro na comunicação (Metodo aguardarACAO).\n";
              (*i).getSocket().close();
            }else{
                switch(comando){
                    case CMD_NOVA_MSG:
                        enviarMensagemCliente((*i));
                        break;
                    case CMD_MSG_LIDA1:
                        cmd_msg_lida1((*i));
                        break;
                    case CMD_LOGOUT_USER:
                        (*i).getSocket().close();
                        cout << "---------------------" << endl;
                        cout << "Usuario " << (*i).getLogin() << " saiu."<<endl;
                        cout << "---------------------" << endl;
                        break;
                    default:
                        (*i).getSocket().close();
                        break;
                }
            }
          }
    }
}
void Server::enviarMensagemCliente(Usuario &usuario){
    int32_t param1;
    string param2, param3;
    Mensagem mensagem;
    iResult = usuario.getSocket().read_int(param1, TIMEOUT*1000);
    if (iResult == SOCKET_ERROR){
        cerr << "Erro na comunicacao (Metodo enviarMensagemCliente). \n";
        usuario.getSocket().close();
    } else{
        iResult = usuario.getSocket().read_string(param2, TIMEOUT*1000);

        if (iResult == SOCKET_ERROR){
            cerr << "Erro na comunicacao (Metodo enviarMensagemCliente) \n";
            usuario.getSocket().close();
        } else {
            iResult = usuario.getSocket().read_string(param3, TIMEOUT*1000);
            if (iResult == SOCKET_ERROR){
                cerr << "Erro na comunicacao (Metodo enviarMensagemCliente) \n";
                usuario.getSocket().close();
            } else {
                if (mensagem.setRemetente(usuario.getLogin())) {
                    if (mensagem.setId(param1)) {
                        for (list<Mensagem>::iterator it=buffer.begin(); it != buffer.end(); ++it) {
                            if ((*it).getRemetente().compare(usuario.getLogin()) == 0) {
                                if ((*it).getId() == param1) {
                                    enviarComando(CMD_ID_INVALIDA, param1, usuario.getSocket());
                                    return ;
                                }
                            }
                        }
                        if (mensagem.setDestinatario(param2)) {
                            for(list<Usuario>::iterator k = usuarios.begin(); k != usuarios.end(); k++){
                                if((*k).getLogin().compare(param2)==0){
                                    if (mensagem.setTexto(param3)) {
                                        mensagem.setStatus(MSG_RECEBIDA);
                                        enviarComando(CMD_MSG_RECEBIDA,param1,usuario.getSocket());
                                        buffer.push_back(mensagem);
                                        if((*k).getSocket().connected()){
                                            if (enviarComando(CMD_NOVA_MSG, param1, mensagem.getRemetente(), param3, (*k).getSocket())) {
                                                mensagem.setStatus(MSG_ENTREGUE);
                                                enviarComando(CMD_MSG_ENTREGUE, param1, usuario.getSocket());
                                            } else {
                                                return ;
                                            }
                                        }
                                        //Armazenar no buffer
                                    }else{
                                        enviarComando(CMD_MSG_INVALIDA,param1,usuario.getSocket());
                                        return;
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
                    usuario.getSocket().close();
                }
            }
        }
    }
}
void Server::cmd_msg_lida1(Usuario &usuario){
    int32_t param1;
    string param2;//remetente
    Mensagem mensagem;
    iResult = usuario.getSocket().read_int(param1, TIMEOUT*1000);
    if (iResult == SOCKET_ERROR){
        cerr << "Erro na comunicacao \n";
        usuario.getSocket().close();
    } else{
        iResult = usuario.getSocket().read_string(param2, TIMEOUT*1000);

        if (iResult == SOCKET_ERROR){
            cerr << "Erro na comunicacao \n";
            usuario.getSocket().close();
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
            usuario.getSocket().close();
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
    M�todo responsavel por verificar o tamanho da string de usu�rio.
    Retorna verdadeiro quando o tamanho � inv�lido.
*/
bool Usuario::tamanhoLoginValido(const string &l){
    if((!(l.size()>=TAM_MIN_LOGIN && l.size()<=TAM_MAX_LOGIN))) return true;
    return false;
}

/*
    M�todo responsavel por verificar o tamanho da string de senha.
    Retorna verdadeiro quando o tamanho � inv�lido.
*/
bool Usuario::tamanhoSenhaValido(const string &l){
    if((!(l.size()>=TAM_MIN_SENHA && l.size()<=TAM_MAX_SENHA))) return true;
    return false;
}

/*
##############-----FIM METODOS CLASSE UUSUARIO-----##############
*/
