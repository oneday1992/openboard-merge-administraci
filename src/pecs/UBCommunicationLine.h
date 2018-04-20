#ifndef UBCOMMUNICATIONLINE_H
#define UBCOMMUNICATIONLINE_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QPainterPath>
#include <QHBoxLayout>
#include <QList>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class pictoCommunicationLine;

class UBCommunicationLine : public QWidget
{
    Q_OBJECT
public:
    explicit UBCommunicationLine(QWidget *parent = 0, QGraphicsScene *scene=0);
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
    //void paintEvent(QPaintEvent * e);

    /** The current background brush
    * El pincel de fondo actual
    */
    QBrush mBackgroundBrush;

    /** Overloaded method that manages the drag and drop in the communication line.
    * Metodo sobrecargado que gestiona el drag and drop en la linea de comunicacion.
    */
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dragEnterEvent(QDragEnterEvent *event);

private:
    QHBoxLayout *layout;
    QList<pictoCommunicationLine*> listPath;
    QGraphicsScene *mScene;

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


    /**
     * Method that returns in standard width of a pictogram.
     * Metodo que devuelve en ancho estandar de un pictograma.
     */
    int pictoWidth ();

    /**
     * Method that returns in standard height of a pictogram.
     * Metodo que devuelve el alto estandar de un pictograma.
     */
    int pictoHeight ();

    /**
     * Method that returns the standard separation between pictogram.
     * Metodo que devuelve la separacion estandar entre pictograma.
     */
    int separatorPicto ();

    /**
     * Method that calculates the starting position where to place the pictograms in the communication line.
     * Metodo que calcula la posicion de inicio donde colocar los pictogramas en la linea de comunicacion.
     */
    int posInit (int ancho);



signals:

public slots:
};

class pictoCommunicationLine : public QGraphicsPixmapItem
{
    //Q_OBJECT
 public:
     pictoCommunicationLine (QGraphicsPixmapItem *parent=0, int i=0, QGraphicsScene *scene=0);
     //~pictoCommunicationLine();


 private:
   int numero;
   QGraphicsScene *mScene;
   int width;
   int height;


 protected:
   void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
   void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
   void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
   void dropEvent(QGraphicsSceneDragDropEvent *event);

   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};



#endif // UBCOMMUNICATIONLINE_H
