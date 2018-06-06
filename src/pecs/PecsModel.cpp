#include "PecsModel.h"

PecsModel::PecsModel(int pieceSize, QObject *parent)
    :QAbstractListModel(parent), m_PieceSize(pieceSize)
{

}
