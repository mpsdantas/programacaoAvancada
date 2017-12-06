#include <QMessageBox>
#include <iostream>
#include "whatsprogmain.h"
#include "ui_whatsprogmain.h"
#include "modelconversas.h"
#include "modelmensagens.h"
#include "dados_cliente.h"
#include "socket_whatsprog.h"
#include "dados_whatsprog.h"

using namespace std;

// Esta é a thread que recebe as informacoes do socket e
// armazena na variavel DCliente, de onde elas poderao ser
// exibidas pela interface visual

DWORD WINAPI le_msg(LPVOID lpParameter)
{
    WhatsProgMain *prov;
    prov = (WhatsProgMain *)lpParameter;

    int32_t cmd;
    bool conexaoOK=0;
    while (s.connected()){

        conexaoOK = (s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd));
        if(conexaoOK)
        //cout << cmd << endl;
        if(cmd==CMD_NOVA_MSG){
            //cout << cmd << endl;
            int32_t id;
            string usuario,text;
            conexaoOK = (s.read_int(id,1000*TIMEOUT_WHATSPROG) == sizeof(id));
            if(conexaoOK) conexaoOK = (s.read_string(usuario,1000*TIMEOUT_WHATSPROG));
            if(conexaoOK) conexaoOK = (s.read_string(text,1000*TIMEOUT_WHATSPROG));
            cerr<<"texto: "<<text<<"\nde: \t"<<usuario<<"\n";
            Mensagem nova;
            nova.setRemetente(usuario);
            nova.setTexto(text);
            nova.setId(id);
            nova.setStatus(MSG_RECEBIDA);
            nova.setDestinatario(DCliente.getMeuUsuario());

            bool dest_ok=0;
            for(int i = 0; i<DCliente.size(); i++){
                if(DCliente[i].getCorrespondente()==usuario){
                    DCliente[i].insertMessage(nova);
                    dest_ok =1;
                }
            }
            if (!dest_ok){
                DCliente.insertConversa(usuario);
                DCliente[DCliente.size()-1].insertMessage(nova);
            }

            emit prov->conversasModificada();
            emit prov->mensagensModificada();
            emit prov->statusModificada();
            cerr<<"emit\n";
        }
        else if(cmd==CMD_MSG_LIDA2){
            conexaoOK = (s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd));
                if(conexaoOK)
                    for(int conv=0; conv<DCliente.size(); conv++)
                        for(int mens =0; mens<DCliente[conv].size(); mens++)
                            if(cmd=DCliente[conv][mens].getId())
                                DCliente[conv][mens].setStatus(MSG_LIDA);
                                    cerr<<"lida: "<< cmd <<"\n";
        }
        else if(cmd==CMD_MSG_RECEBIDA){
            conexaoOK = (s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd));
            if(conexaoOK){
                for(int conv=0; conv<DCliente.size(); conv++)
                    for(int mens =0; mens<DCliente[conv].size(); mens++)
                        if(cmd=DCliente[conv][mens].getId())
                            DCliente[conv][mens].setStatus(MSG_RECEBIDA);
                cerr<<"Recebida: "<<cmd<<"\n";
            }
        }
        else if(cmd==CMD_MSG_ENTREGUE){
            conexaoOK = (s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd));
            if(conexaoOK){
                for(int conv=0; conv<DCliente.size(); conv++)
                    for(int mens =0; mens<DCliente[conv].size(); mens++)
                        if(cmd=DCliente[conv][mens].getId())
                            DCliente[conv][mens].setStatus(MSG_ENTREGUE);
                cerr<<"Entregue: "<<cmd<<"\n";
            }
        }
    }

  return 0;
}

WhatsProgMain::WhatsProgMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WhatsProgMain)
{
    ui->setupUi(this);

    // A lista da esquerda (conversas)
    modelConversas = new ModelConversas(this);
    ui->tableViewConversas->setModel( modelConversas );
    ui->tableViewConversas->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableViewConversas->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableViewConversas->horizontalHeader()->setSectionsClickable(false);
    ui->tableViewConversas->setShowGrid(false);
    ui->tableViewConversas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewConversas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewConversas->setTabKeyNavigation(false);

    // A lista da direita (mensagens)
    modelMensagens = new ModelMensagens(this);
    ui->tableViewMensagens->setModel( modelMensagens );
    ui->tableViewMensagens->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableViewMensagens->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableViewMensagens->horizontalHeader()->setSectionsClickable(false);
    ui->tableViewMensagens->setShowGrid(true);
    ui->tableViewMensagens->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableViewMensagens->setTabKeyNavigation(false);

    // A barra de status
    statusBar()->insertWidget(0,new QLabel("SERVIDOR: "));
    if (DCliente.getServidor() == "")
    {
        ipServidor = new QLabel("---");
    }
    else
    {
        ipServidor = new QLabel(DCliente.getServidor().c_str());
    }
    statusBar()->insertWidget(1,ipServidor);

    statusBar()->insertWidget(2,new QLabel("   USUÁRIO: "));
    if (DCliente.getMeuUsuario() == "")
    {
        nomeUsuario = new QLabel("---");
    }
    else
    {
        nomeUsuario = new QLabel(DCliente.getMeuUsuario().c_str());
    }
    statusBar()->insertWidget(3,nomeUsuario);

    statusBar()->insertWidget(4,new QLabel("   CONVERSA: "));
    if (DCliente.getIdConversa() < 0)
    {
        nomeConversa = new QLabel("---");
    }
    else
    {
        nomeConversa = new QLabel(DCliente[DCliente.getIdConversa()].getCorrespondente().c_str());
    }
    statusBar()->insertWidget(5,nomeConversa);

    // A caixa de dialogo de login
    loginDialog = new LoginDialog(this);
    novamsg = new nova_msg(this);

    // As conexoes
    connect(this, SIGNAL (conversasModificada()),
            modelConversas, SLOT (slotAtualizaConversas()));
    connect(this, SIGNAL (numMsgConversaModificado(unsigned)),
            modelConversas, SLOT (slotAtualizaNumMsgConversa(unsigned)));
    connect(this, SIGNAL (mensagensModificada()),
            modelMensagens, SLOT (slotAtualizaMensagens()));
    connect(this, SIGNAL (statusModificada()),
            this, SLOT (slotAtualizaBarraStatus()));
    connect(loginDialog, SIGNAL (aceitaUsuario(const string, const string, const string, bool)),
            this, SLOT (slotAceitaUsuario(const string, const string, const string, bool)));
    connect(this, SIGNAL (removerUsuario()),
            this, SLOT (slotRemoverUsuario()));
    connect(novamsg, SIGNAL (aceitaDestinatario(const string)),
            this, SLOT (slotAceitarDestinatario(const string)));
    connect(this, SIGNAL (mensagemClienteServidor(int32_t, const string, const string, const string, MsgStatus)),
            this, SLOT (slotMensagemClienteServidor(int32_t, const string, const string, const string, MsgStatus)));
}

WhatsProgMain::~WhatsProgMain()
{
    delete ui;
}

void WhatsProgMain::slotRemoverUsuario()
{
    s.write_int(CMD_LOGOUT_USER);
    ui->actionNovo->setEnabled(true);
    ui->actionConectar->setEnabled(true);
    ui->actionDesconectar->setDisabled(true);
    s.close();
}

void WhatsProgMain::slotAtualizaBarraStatus()
{
    if (DCliente.getServidor() == "")
    {
        ipServidor->setText("---");
    }
    else
    {
        ipServidor->setText(DCliente.getServidor().c_str());
    }

    if (DCliente.getMeuUsuario() == "")
    {
        nomeUsuario->setText("---");
    }
    else
    {
        nomeUsuario->setText(DCliente.getMeuUsuario().c_str());
    }

    if (DCliente.getIdConversa() < 0)
    {
        nomeConversa->setText("---");
    }
    else
    {
        nomeConversa->setText(DCliente[DCliente.getIdConversa()].getCorrespondente().c_str());
    }
}

void WhatsProgMain::slotAceitaUsuario(const string &IP, const string &login,
                                      const string &senha, bool novoUsuario )
{
    if (IP == "")
    {
        QMessageBox::warning(this, "Login", "IP inválido.");
        return;
    }
    if (login.size()<TAM_MIN_NOME_USUARIO || login.size()>TAM_MAX_NOME_USUARIO)
    {
        QMessageBox::warning(this, "Login", "Usuário inválido.");
        return;
    }
    if (login == DCliente.getMeuUsuario())
    {
        QMessageBox::warning(this, "Login", "Usuário já conectado.");
        return;
    }
    if (senha.size()<TAM_MIN_SENHA || senha.size()>TAM_MAX_SENHA)
    {
        QMessageBox::warning(this, "Login", "Senha inválida.");
        return;
    }

    // Desconecta o socket, encerra a thread de leitura de dados,
    // limpa o servidor e usuario atuais, limpa todas as conversas,
    // redesenha todas as janelas
    on_actionDesconectar_triggered();

    // Conecta o socket
    if (s.connect(IP.c_str(), PORTA_WHATSPROG) != SOCKET_OK)
    {
        cout << IP.c_str();
        cout << PORTA_WHATSPROG;
        if(s.connected())
        {
            cout << "Conectou";
        }
        string msg = "Impossivel conectar com servidor "+IP+" na porta "+PORTA_WHATSPROG;
        QMessageBox::warning(this, "Erro de conexão", msg.c_str());
        return;
    }

    // Envia a msg de conexao para o servidor, atraves do socket
    bool conexaoOK = true;
    if (novoUsuario)
    {
        // Testa se eh possivel cadastrar um novo usuario com esses ip, login e senha
        // Envia o comando CMD_NEW_USER
        if (conexaoOK) conexaoOK = (s.write_int(CMD_NEW_USER) != SOCKET_ERROR);
    }
    else
    {
        // Testa se eh possivel se conectar com esses ip, login e senha
        // Envia o comando CMD_LOGIN_USER
        if (conexaoOK) conexaoOK = (s.write_int(CMD_LOGIN_USER) != SOCKET_ERROR);
    }
    // Envia os parametros do comando (login, senha)
    if (conexaoOK) conexaoOK = (s.write_string(login) != SOCKET_ERROR);
    if (conexaoOK) conexaoOK = (s.write_string(senha) != SOCKET_ERROR);
    if (!conexaoOK)
    {
        QMessageBox::warning(this, "Erro de conexão", "Erro no envio da conexão.");
        return;
    }

    /*int32_t cmd;
    conexaoOK = (s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd));
    if (conexaoOK) conexaoOK = (cmd == CMD_LOGIN_OK);
    if (!conexaoOK)
    {
        QMessageBox::warning(this, "Erro de conexão", "Erro na leitura da resposta à conexão.");
        return;
    }*/

    // Lanca a thread de leitura dos dados do socket
    // Cria a thread que escreve as mensagens recebidas
    tHandle = CreateThread(NULL, 0, le_msg, this , 0, NULL);
    if (tHandle == NULL)
    {
        s.close();
        QMessageBox::warning(this, "Erro de conexão", "Erro na criação da thread de leitura do socket.");
        return;
    }
    // Armazena o novo nome do servidor e do usuário
    DCliente.setServidorUsuario(IP,login);

    // Redesenha todas as janelas
    emit conversasModificada();
    emit mensagensModificada();
    emit statusModificada();

    // Informa que o novo usuario estah conectado
    QMessageBox::information(this, "Login", "Usuário conectado.");
    ui->actionNovo->setDisabled(true);
    ui->actionConectar->setDisabled(true);
    ui->actionDesconectar->setEnabled(true);
}

void WhatsProgMain::on_actionNovo_triggered()
{
    loginDialog->setUsuario(true);
}

void WhatsProgMain::on_actionConectar_triggered()
{
    loginDialog->setUsuario(false);
}

// Desconecta o socket, encerra a thread de leitura de dados,
// limpa o servidor e usuario atuais, limpa todas as conversas,
// redesenha todas as janelas
void WhatsProgMain::on_actionDesconectar_triggered()
{
    if (s.connected())
    {
        // Envia o comando de logout
        emit removerUsuario();
        QMessageBox::information(this, "Logout", "Usuário desconectado.");
        // Fecha o socket e, consequentemente,
        // encerra a thread de leitura de dados do socket
        //s.close();
    }

    // Limpa os nomes do servidor e usuario
    DCliente.clearServidorUsuario();

    // Redesenha todas as janelas
    emit conversasModificada();
    emit mensagensModificada();
    emit statusModificada();
}

void WhatsProgMain::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

void WhatsProgMain::on_tableViewConversas_activated(const QModelIndex &index)
{
    on_tableViewConversas_clicked(index);
}

void WhatsProgMain::on_tableViewConversas_clicked(const QModelIndex &index)
{
    if (index.row() >= (int)DCliente.size())
    {
        cerr << "ID de conversa invalida.\n";
        return;
    }

    if (index.row() != DCliente.getIdConversa())
    {
        DCliente.setIdConversa(index.row());

        // Muda o status de todas as msgs que foram enviadas para mim de RECEBIDA -> LIDA
        bool houve_leitura = false;
        for (unsigned i=0; i<DCliente[DCliente.getIdConversa()].size(); i++)
        {
            if (DCliente[DCliente.getIdConversa()][i].getRemetente() == DCliente[DCliente.getIdConversa()].getCorrespondente() &&
                DCliente[DCliente.getIdConversa()][i].getStatus() == MSG_ENTREGUE)
            {
                DCliente[DCliente.getIdConversa()][i].setStatus(MSG_LIDA);
                // Envia msg ao servidor informando que a msg foi lida

                houve_leitura = true;
            }
        }
        if (houve_leitura)
        {
            emit numMsgConversaModificado(DCliente.getIdConversa());
        }

        // Sinaliza para atualizar a janela de mensagens e a barra de status
        emit mensagensModificada();
        emit statusModificada();
    }
}

void WhatsProgMain::on_lineEditMensagem_returnPressed()
{
    if (DCliente.getMeuUsuario().size() < TAM_MIN_NOME_USUARIO)
    {
        QMessageBox::warning(this, "Usuário inválido", "Usuário não definido.");
        return;
    }
    if (DCliente.getIdConversa()<0 || DCliente.getIdConversa()>=(int)DCliente.size())
    {
        QMessageBox::warning(this, "Conversa inválida", "Conversa não selecionada.");
        return;
    }
    string arg1 = ui->lineEditMensagem->text().toStdString();
    if (arg1.size()==0 || arg1.size()>TAM_MAX_MSG)
    {
        QMessageBox::warning(this, "Msg inválida", "Tamanho da mensagem inválido.");
        return;
    }
    ui->lineEditMensagem->clear();

    Mensagem M;
    // Define os campos da msg
    M.setId(DCliente.getNovaIdMensagem());
    // Nome do remetente
    M.setRemetente(DCliente.getMeuUsuario());
    // Nome do destinatario
    M.setDestinatario(DCliente[DCliente.getIdConversa()].getCorrespondente());
    // Texto da mensagem
    M.setTexto(arg1);
    // Estado (status) da mensagem
    M.setStatus(MSG_ENVIADA);

    emit mensagemClienteServidor(M.getId(), M.getRemetente(), M.getDestinatario(), M.getTexto(), M.getStatus());
    // Inclui a msg na base de dados local
    // Acrescenta no final da conversa
    DCliente[DCliente.getIdConversa()].insertMessage(M);
    // Sinaliza que houve alteracao no numero de msgs de uma conversa na janela de conversas
    emit numMsgConversaModificado(DCliente.getIdConversa());
    // Sinaliza que houve alteracao na janela de Mensagens
    emit mensagensModificada();
}

//FAZENDO JANELA PARA CRIAR UMA NOVA MENSAGEMconst string &id, const string &rem, const string &dest, const string &txt, MsgStatus status
void WhatsProgMain::on_actionNova_conversa_triggered()
{
    novamsg->setNova();
}

void WhatsProgMain::slotAceitarDestinatario(const string &dest)
{
    DCliente.insertConversa(dest);
    emit conversasModificada();
}

void WhatsProgMain::slotMensagemClienteServidor(int32_t id, const string &rem, const string &dest, const string &txt, MsgStatus status)
{
    emit conversasModificada();
    bool conexaoOK = true;
    if(s.connected())
    {
        conexaoOK = (s.write_int(CMD_NOVA_MSG) != SOCKET_ERROR);
        if(conexaoOK) conexaoOK = (s.write_int(id) != SOCKET_ERROR);
        if(conexaoOK) conexaoOK = (s.write_string(dest) != SOCKET_ERROR);
        if(conexaoOK) conexaoOK = (s.write_string(txt) != SOCKET_ERROR);
        if (!conexaoOK) {
            QMessageBox::warning(this, "Erro de conexão", "Erro no envio da conexão.");
            on_actionDesconectar_triggered();
            return;
        }
        conexaoOK = false;
        int32_t cmd;
        conexaoOK = (s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd)); //TAVA DANDO CONEXÃO INVALIDA PORQUE
        //s.read_int(cmd,1000*TIMEOUT_WHATSPROG) != sizeof(cmd) ERA FALSO JÁ QUE OS DOIS VALORES RETORNAM 4
        //ENTÃO TIVE QUE TROCAR != POR == '-'
        //QMessageBox::warning(this, "RECEBEU DO SERVIDOR", QString::number(cmd));
        if(conexaoOK)
        {
            switch(cmd)
            {
                case CMD_ID_INVALIDA:
                    QMessageBox::warning(this, "Erro de envio", "ID inválido.");
                    if(s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd)) id = cmd;
                    return;
                case CMD_USER_INVALIDO:
                    QMessageBox::warning(this, "Erro de envio", "Usuário inválido.");
                    if(s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd)) id = cmd;
                    return;
                case CMD_MSG_INVALIDA:
                    QMessageBox::warning(this, "Erro de envio", "Mensagem inválida.");
                    if(s.read_int(cmd,1000*TIMEOUT_WHATSPROG) == sizeof(cmd)) id = cmd;
                    return;
                case CMD_MSG_RECEBIDA:
                    emit conversasModificada();
                    //QMessageBox::warning(this, "Erro de envio", "Mensagem inválida.");
                    return;
            }
        }
        else
        {
            QMessageBox::warning(this, "Erro", "Erro ao coletar resposta do servidor.");
            return;
        }
    }
}

void WhatsProgMain::on_actionApagar_mensagens_triggered()
{
    DCliente[DCliente.getIdConversa()].clearMessages();
}

void WhatsProgMain::on_actionRemover_conversa_triggered()
{
    //DCliente.clearConversas(); // todas as conversas
    DCliente.eraseConversa(DCliente.getIdConversa()); //Uma conversa em particular
}
