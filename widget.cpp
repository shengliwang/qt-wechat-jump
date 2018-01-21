#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QDebug>
#include <unistd.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include "status.hpp"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    connect(ui->pictureLabel, PicLabel::signal_swipe, this, slot_swipe);
    connect(this->timer, &QTimer::timeout,
            [this](){
        this->timer->stop();
        this->on_startButton_clicked();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_connectButton_clicked()
{
    QProcess adb(this);
    QStringList adbList;
    adbList.append("devices");

    adb.start("adb", adbList);
    adb.waitForStarted();
    adb.waitForFinished();

    QString list = QString::fromLocal8Bit( adb.readAllStandardOutput() );

    ui->devListLabel->setText(list);

}

void Widget::on_startButton_clicked()
{
    QProcess capture;
    QStringList captureList;
    captureList.append("shell");
    captureList.append("screencap");
    captureList.append("-p");
    captureList.append("/sdcard/jump.png");
    capture.start("adb", captureList);
    capture.waitForStarted();
    capture.waitForFinished();

    QProcess pull;
    QStringList pullCommand;
    pullCommand.append("pull");
    pullCommand.append("/sdcard/jump.png");
    pullCommand.append(".");
    pull.start("adb", pullCommand);
    pull.waitForStarted();
    pull.waitForFinished();

    ui->pictureLabel->setStatus(INIT);
    ui->pictureLabel->update();
}


void Widget::slot_swipe(size_t distance)
{
    QProcess swipe;

    double xishu = ui->xishu->text().toDouble();

    QStringList swipeList;
    swipeList.append("shell");
    swipeList.append("input");
    swipeList.append("swipe");
    swipeList.append("250");
    swipeList.append("250");
    swipeList.append("255");
    swipeList.append("255");

    QString time = QString("%1").arg((int)((double)distance*xishu));
    QString info = QString("距离： %1\r\n按压时间： %2ms").arg(distance).arg(time);
    ui->infoLabel->setText(info);
    swipeList.append(time);
    qDebug() << swipeList;

    swipe.start("adb", swipeList);
    swipe.waitForStarted();
    swipe.waitForFinished();

    timer->start(1000);

}
