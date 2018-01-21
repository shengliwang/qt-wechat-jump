#ifndef PICLABEL_H
#define PICLABEL_H

#include <QPoint>
#include <QLabel>
#include "status.hpp"

class PicLabel : public QLabel
{
    Q_OBJECT
public:
    explicit PicLabel(QWidget *parent = nullptr);



signals:
    void signal_swipe(size_t distance);
    void mouse_pos(int x, int y);

public slots:

private:
    int first_x;
    int first_y;

    int second_x;
    int second_y;

    int status;

public:
    void setStatus(int stat);


protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent * ev);
    void mouseReleaseEvent(QMouseEvent *ev);
};

#endif // PICLABEL_H
