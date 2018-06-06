#include "PictoWidget.h"
#include <QtWidgets>

PictoWidget::PictoWidget(int size, QWidget *parent) : QWidget(parent), m_SizePicto(size)
{
    setAcceptDrops(true);
    setMinimumSize(m_SizePicto,m_SizePicto);
    setMaximumSize(m_SizePicto,m_SizePicto);
}

int PictoWidget::pieceSize() const
{
    return m_SizePicto;
}
