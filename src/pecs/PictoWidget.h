#ifndef PICTOWIDGET_H
#define PICTOWIDGET_H

#include <QWidget>

class PictoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PictoWidget(int size, QWidget *parent = 0);
    int pieceSize () const;

signals:

private:
    //Tamaño standard del pictograma.
    int m_SizePicto;

public slots:
};

#endif // PICTOWIDGET_H
