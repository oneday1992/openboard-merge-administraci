#ifndef PINTALINEACOMUNICACION_H
#define PINTALINEACOMUNICACION_H

#include <QWidget>

class PintaLineaComunicacion : public QWidget
{
    Q_OBJECT
public:
    explicit PintaLineaComunicacion(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent * e);

signals:

public slots:
};

#endif // PINTALINEACOMUNICACION_H
