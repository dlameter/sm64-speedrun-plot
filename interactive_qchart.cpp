#include "interactive_qchart.h"

InteractiveQChart::InteractiveQChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags) 
{
    m_buttonPressed = false;
    m_lastMousePos = QPointF(0,0);
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

        event->accept();
    }
    else {
        event->ignore();
    }
}

void InteractiveQChart::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() == Qt::MidButton) {
        zoomReset();

        event->accept();
    }
    else if (event->buttons() == Qt::RightButton) {
        m_buttonPressed = true;
        m_lastMousePos = event->pos();

        event->accept();
    }
    else {
        event->ignore();
    }
}

void InteractiveQChart::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_buttonPressed) {
        auto deltaPos = event->pos() - m_lastMousePos;
        scroll(-deltaPos.x(), deltaPos.y());

        m_lastMousePos = event->pos();

        event->accept();
    }
    else {
        event->ignore();
    }
}

void InteractiveQChart::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() == Qt::RightButton) {
        m_buttonPressed = false;
        m_lastMousePos = QPointF(0,0);

        event->accept();
    }
    else {
        event->ignore();
    }
}
