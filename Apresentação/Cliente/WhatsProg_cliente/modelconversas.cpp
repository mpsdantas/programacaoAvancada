#include <QFont>
#include <QBrush>
#include "modelconversas.h"
#include "dados_whatsprog.h"
#include "dados_cliente.h"

using namespace std;

ModelConversas::ModelConversas(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant ModelConversas::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FEITO POR MIM:

    // Os cabecalhos horizontais
    if (orientation == Qt::Horizontal) switch(role)
    {
    case Qt::DisplayRole:
        switch(section)
        {
        case 0:
            return QString("Msgs");
        case 1:
            return QString("Usuário");
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

int ModelConversas::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FEITO POR MIM:
    return DCliente.size();
}

int ModelConversas::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FEITO POR MIM:
    return 2;
}

QVariant ModelConversas::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FEITO POR MIM:
    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            return QString("%1/%2")
                    .arg(DCliente[index.row()].getNumMsgsEntregues())
                    .arg(DCliente[index.row()].size());
        case 1:
            return QString(DCliente[index.row()].getCorrespondente().c_str());
            break;
        }
        break;
    case Qt::FontRole:
        break;
    case Qt::ForegroundRole:
        break;
    case Qt::BackgroundRole:
        if (index.column()==0 && DCliente[index.row()].getNumMsgsEntregues() > 0) return QBrush(Qt::green);
        break;
    case Qt::TextAlignmentRole:
        if (index.column()==0)
        {
            return Qt::AlignCenter;
        }
        break;
    case Qt::CheckStateRole:
        break;
    }

    return QVariant();
}

void ModelConversas::slotAtualizaConversas()
{
    // Avisa que os dados da lista de conversas vao mudar
    beginResetModel();
    // Avisa que todos os dados do modelo de conversas devem ser lidos novamente
    endResetModel();
}

void ModelConversas::slotAtualizaNumMsgConversa(unsigned I)
{
    QModelIndex topLeft = index(I,0);
    emit dataChanged(topLeft, topLeft);
}

