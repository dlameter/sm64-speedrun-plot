#ifndef INTERACTIVE_QCHAT_H
#define INTERACTIVE_QCHAT_H

#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneMouseEvent>

#include <QtCharts>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QGraphicsSceneWheelEvent;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_USE_NAMESPACE

class InteractiveQChart: public QtCharts::QChart {
public:
    InteractiveQChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

protected:
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool m_buttonPressed;
    QPointF m_lastMousePos;
};

#endif
