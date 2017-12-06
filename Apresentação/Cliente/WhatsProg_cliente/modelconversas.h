#ifndef MODELCONVERSAS_H
#define MODELCONVERSAS_H

#include <QAbstractTableModel>

class ModelConversas : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ModelConversas(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void slotAtualizaConversas();
    void slotAtualizaNumMsgConversa(unsigned I);

private:
};

#endif // MODELCONVERSAS_H
