#include "UBMainPanelPecs.h"
#include <qevent.h>
#include <QDebug>

UBMainPanelPecs::UBMainPanelPecs(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
}

void UBMainPanelPecs::dragEnterEvent(QDragEnterEvent *event)
{
    qWarning() << "Entrando en panel principal de Pecs para drops";
    event->accept();
}

void UBMainPanelPecs::dropEvent(QDropEvent *event)
{

}


