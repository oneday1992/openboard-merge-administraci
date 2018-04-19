#ifndef UBCANVASVIEW_H
#define UBCANVASVIEW_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class UBCanvasView : public QWidget
{
    Q_OBJECT

public:
    UBCanvasView(int numberOfIndepedentBoards, int toolBarHeight, QColor background, QList<QPen *> _pens, QWidget *parent);

    virtual ~UBCanvasView(){};

    bool openImage(const QString &fileName);
    bool saveImage();
    bool saveRegionImage(int region);
    QImage createSubImage(QRect *rect);

    QRect getRegion(int pos);
    int getNumberRegion(QPoint p);
    void setEraserMode(int region, bool isEraser);

    bool isModified() const { return modified; }
    QColor backgroundColor(){ return bgColor; }

public slots:
    void clearImage();
    void clearRegion(int region);
    void print();
    void drawLineTo(const QPoint &endPoint);
    void drawLineToTouch(int id, const QPoint &endPoint);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool event(QEvent *event);

public slots:
    void setupBoards(int numberOfIndependentBoards);

signals:
    void viewVisibilityChanged(bool state);

private:
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    int TBHeight;
    QPoint lastPoint;
    QList<QPen*> pens;
    QImage image;
    QList<QRect *> independentBoards;
    QHash<int, QPoint> lastPointHash;
    QColor bgColor;
    QList<bool> eraserMode;
    QCursor *cursorEraser;
    //QRect user1;
    //QRect user2;
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // UBCANVASVIEW_H
