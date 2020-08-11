#include "interactive_qchart.h"

InteractiveQChart::InteractiveQChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags) 
{
    m_buttonPressed = false;
    m_zoom = 1.0;
}

void InteractiveQChart::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (event->buttons() | Qt::MidButton) {
        int delta = event->delta();
        if (delta > 0) {
            zoom(1.1);
        }
        else if (delta < 0) {
            zoom(0.9);
        }
    }
    else {
        event->ignore();
    }
}

void InteractiveQChart::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() | Qt::MidButton) {
        zoomReset();
    }
    else {
        event->ignore();
    }
}
