#ifndef UBCOMMUNICATIONLINE_H
#define UBCOMMUNICATIONLINE_H

#include <QWidget>
#include <QLabel>
#include <QFrame>

class UBCommunicationLine : public QWidget
{
    Q_OBJECT
public:
    explicit UBCommunicationLine(QWidget *parent = 0);
    //explicit UBCreateLinkLabel(QString labelText, QWidget* parent = 0);
    //retorna el alto de la pantalla
    // returns the height of the screen
    int screenHeight ();
    //retorna el ancho de la pantalla
    // returns the width of the screen
    int screenWidth ();

protected:
    /** Overloaded method that paints an event
    * Metodo sobrecargado que pinta un evento
    */
    void paintEvent(QPaintEvent * e);
    /** The current background brush
    * El pincel de fondo actual
    */
    QBrush mBackgroundBrush;

private:
    /** Method that returns an edge
    * Metodo que nos devuelve un borde
    */
    int border ();

    /** Method that calculates the position x in the window
     * Metodo que nos calcula la posicion x en la ventana;
     */
    int calculateX(double percent=1,int displaced =0);

    /** Method that calculates the position x in the window
     * Metodo que nos calcula la posicion x en la ventana;
     */
    int calculateY(double percent=1,int displaced =0);

    /** Method that calculates the width that the widget will have by applying a percentage of the screen,
     * by default if no parameter is passed it will be 1 which means that it is the width of the window
     * Metodo que calcula el ancho que va a tener el widget aplicandole un porcentaje de la pantalla,
     * por defecto si no se pasa ningun parametro sera 1 que significa que es el ancho de la ventana
     */
    int calculateWidth(double percent=1,int displaced =0);

    /** Method that calculates the height that the widget will have by applying a percentage of the screen,
     * by default if no parameter is passed it will be 1 which means that it is the height of the window
     * Metodo que calcula el alto que va a tener el widget aplicandole un porcentaje de la pantalla,
     * por defecto si no se pasa ningun parametro sera 1 que significa que es el alto de la ventana
     */
    int calculateHeight(double percent=1, int displaced =0);


signals:

public slots:
};

#endif // UBCOMMUNICATIONLINE_H
