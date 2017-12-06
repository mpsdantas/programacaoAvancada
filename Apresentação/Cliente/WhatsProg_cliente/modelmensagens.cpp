#include <QFont>
#include <QBrush>
#include <iostream>
#include "modelmensagens.h"
#include "dados_whatsprog.h"
#include "dados_cliente.h"

using namespace std;

ModelMensagens::ModelMensagens(QObject *parent)
    : QAbstractTableModel(parent)
{
    QString dir = "..\\WhatsProg_cliente\\";
    QString pixfile;

    pixfile = dir+"tickOneGray.png";
    if (!pixRecebida.load(pixfile,"PNG"))
    {
        cerr << "Erro na leitura do pixmap " << pixfile.toStdString() << endl;
    }
    pixfile = dir+"tickTwoGray.png";
    if (!pixEntregue.load(pixfile,"PNG"))
    {
        cerr << "Erro na leitura do pixmap " << pixfile.toStdString() << endl;
    }
    pixfile = dir+"tickTwoBlue.png";
    if (!pixLida.load(pixfile,"PNG"))
    {
        cerr << "Erro na leitura do pixmap " << pixfile.toStdString() << endl;
    }
}

QVariant ModelMensagens::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FEITO POR MIM:

    // Os cabecalhos horizontais
    if (orientation == Qt::Horizontal) switch(role)
    {
    case Qt::DisplayRole:
        switch(section)
        {
        case 0:
            return QString("Mensagens");
        case 1:
            return QString("St");
        }
        break;
    case Qt::FontRole:
    {
        QFont boldFont;
        boldFont.setBold(true);
        return boldFont;
    }
    case Qt::ForegroundRole:
        break;
    case Qt::BackgroundRole:
        // BUG: Qt nao respeita o background no header!!!
        return QBrush(Qt::yellow);
    case Qt::TextAlignmentRole:
    {
        return Qt::AlignCenter + Qt::AlignVCenter;
    }
    case Qt::CheckStateRole:
        break;
    }

    return QVariant();
}

int ModelMensagens::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FEITO POR MIM:
    if (DCliente.getIdConversa() < 0) return 0;
    return DCliente[DCliente.getIdConversa()].size();
}

int ModelMensagens::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FEITO POR MIM:
    return 2;
}

QVariant ModelMensagens::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FEITO POR MIM:
    if (DCliente.getIdConversa() < 0)
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            return QString(DCliente[DCliente.getIdConversa()][index.row()].getTexto().c_str());
            break;
        case 1:
            if (DCliente[DCliente.getIdConversa()][index.row()].getRemetente() == DCliente.getMeuUsuario())
            {
                switch(DCliente[DCliente.getIdConversa()][index.row()].getStatus())
                {
                case MSG_ENVIADA:
                    return QString("?");
                case MSG_INVALIDA:
                    return QString("X");
                default:
                    break;
                }
            }
            break;
        }
        break;
    case Qt::FontRole:
        break;
    case Qt::ForegroundRole:
        if (index.column() == 1 &&
            DCliente[DCliente.getIdConversa()][index.row()].getRemetente() == DCliente.getMeuUsuario() &&
            DCliente[DCliente.getIdConversa()][index.row()].getStatus() == MSG_LIDA )
        {
            return QBrush(QColor("#0000FF"));
        }
        break;
    case Qt::BackgroundRole:
        switch(index.column())
        {
        case 0:
            if (DCliente[DCliente.getIdConversa()][index.row()].getRemetente() == DCliente.getMeuUsuario())
            {
                return QBrush(QColor("#EEFFEE"));
            }
            break;
        case 1:
            if (DCliente[DCliente.getIdConversa()][index.row()].getRemetente() == DCliente.getMeuUsuario())
            {
                return QBrush(QColor("#EEFFEE"));
            }
            break;
        }
        break;
    case Qt::TextAlignmentRole:
        if (index.column()==0)
        {
            if (DCliente[DCliente.getIdConversa()][index.row()].getRemetente() == DCliente.getMeuUsuario())
            {
                return (Qt::AlignRight + Qt::AlignVCenter);
            }
            if (DCliente[DCliente.getIdConversa()][index.row()].getRemetente() == DCliente[DCliente.getIdConversa()].getCorrespondente())
            {
                return (Qt::AlignLeft + Qt::AlignVCenter);
            }
            break;
        }
        if (index.column()==1)
        {
            return Qt::AlignCenter;
        }
        break;
    case Qt::DecorationRole:
        if (index.column()==1 &&
            DCliente[DCliente.getIdConversa()][index.row()].getRemetente() == DCliente.getMeuUsuario())
        {
            switch(DCliente[DCliente.getIdConversa()][index.row()].getStatus())
            {
            case MSG_RECEBIDA:
                return pixRecebida;
            case MSG_ENTREGUE:
                return pixEntregue;
            case MSG_LIDA:
                return pixLida;
            default:
                break;
            }
        }
        break;
    case Qt::CheckStateRole:
        break;
    }

    return QVariant();
}

void ModelMensagens::slotAtualizaMensagens()
{
    // Avisa que os dados da lista de mensagens vao mudar
    beginResetModel();
    // Avisa que todos os dados do modelo de mensagens devem ser lidos novamente
    endResetModel();
}

