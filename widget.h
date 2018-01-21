#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_connectButton_clicked();

    void on_startButton_clicked();

    void slot_swipe(size_t distance);

private:
    Ui::Widget *ui;
    QTimer * timer;
};

#endif // WIDGET_H
