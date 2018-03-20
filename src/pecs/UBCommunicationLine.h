#ifndef UBCOMMUNICATIONLINE_H
#define UBCOMMUNICATIONLINE_H

#include <QWidget>

class UBCommunicationLine : public QWidget
{
    Q_OBJECT
public:
    explicit UBCommunicationLine(QWidget *parent = 0);
    //retorna el alto de la pantalla
    // returns the height of the screen
    int screenheight ();
    //retorna el ancho de la pantalla
    // returns the width of the screen
    int screenwidth ();

protected:
    void paintEvent(QPaintEvent * e);
    /** The current background brush
    * El pincel de fondo actual
    */
    QBrush mBackgroundBrush;

signals:

public slots:
};

#endif // UBCOMMUNICATIONLINE_H
