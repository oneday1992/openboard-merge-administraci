#ifndef UBMAINPANELPECS_H
#define UBMAINPANELPECS_H

#include <QWidget>
#include <QGraphicsScene>

class UBMainPanelPecs : public QWidget
{
    Q_OBJECT
public:
    UBMainPanelPecs(QWidget *parent = 0, QGraphicsScene *scene=0);
private:
    QGraphicsScene *mScene;
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
signals:

public slots:
};

#endif // UBMAINPANELPECS_H
