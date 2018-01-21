#include "piclabel.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <math.h>

PicLabel::PicLabel(QWidget *parent) : QLabel(parent)
{
    first_x = 0;
    first_y = 0;
    second_x = 0;
    second_y = 0;

    status = -1;
}


void PicLabel::setStatus(int stat)
{
    this->status = stat;
}


void PicLabel::mousePressEvent(QMouseEvent *ev)
{
    this->first_x = ev->x();
    this->first_y = ev->y();
}

void PicLabel::mouseMoveEvent(QMouseEvent *ev)
{
    this->second_x = ev->x();
    this->second_y = ev->y();

    this->status = MOVE;
    this->update();
}

void PicLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap("./jump.png");
    int w = this->width();
    int h = this->height();
    pixmap = pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, pixmap);

    if (MOVE == status)
    {
        painter.setPen(QPen(Qt::red, 3));
        painter.drawLine(first_x, first_y, second_x, second_y);

        int r = sqrt( pow( (first_x-second_x), 2) + pow( (first_y-second_y), 2) );

        QPoint center(first_x, first_y);
        painter.drawEllipse(center, r, r);
    }
    else if(RELEASE == status)
    {
        emit signal_swipe( sqrt( pow( (first_x-second_x), 2) + pow( (first_y-second_y), 2) ) );
    }
}

void PicLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    status = RELEASE;
    this->update();
}
