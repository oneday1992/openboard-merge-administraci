#ifndef UBMAINPANELPECS_H
#define UBMAINPANELPECS_H

#include <QWidget>

class UBMainPanelPecs : public QWidget
{
    Q_OBJECT
public:
    explicit UBMainPanelPecs(QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
signals:

public slots:
};

#endif // UBMAINPANELPECS_H
