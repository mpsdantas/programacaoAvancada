#ifndef MODELMENSAGENS_H
#define MODELMENSAGENS_H

#include <QAbstractTableModel>
#include <QPixmap>

class ModelMensagens : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ModelMensagens(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void slotAtualizaMensagens();

private:
    QPixmap pixRecebida;
    QPixmap pixEntregue;
    QPixmap pixLida;
};

#endif // MODELMENSAGENS_H
