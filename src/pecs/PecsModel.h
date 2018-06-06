#ifndef PECSMODEL_H
#define PECSMODEL_H

#include <QAbstractListModel>


class PecsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    PecsModel(int pieceSize, QObject *parent = 0);


private:
    int m_PieceSize;

};

#endif // PECSMODEL_H
