#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagewidget.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    leftImage = new ImageWidget();
    rightImage = new ImageWidget();
    ui->horizontalLayout->insertWidget(0, leftImage);
    ui->horizontalLayout->insertWidget(1, rightImage);

    ui->tableWidget->setMinimumWidth(150);
    ui->tableWidget->setMaximumWidth(200);



    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->actionOpenLeft, SIGNAL(triggered()), leftImage, SLOT(load()));
    connect(ui->actionOpenRight, SIGNAL(triggered()), rightImage, SLOT(load()));

    connect(leftImage, SIGNAL(pointClicked(QPoint)), this, SLOT(addPoint(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTable()
{

    QPair<QPoint, QPoint> pair;
    qDebug() << "Tableau: ";
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    foreach(pair, this->points) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itemLeft = new QTableWidgetItem(pointToString(pair.first));
        QTableWidgetItem *itemRight = new QTableWidgetItem(pointToString(pair.second));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, itemLeft);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, itemRight);
        qDebug() << pointToString(pair.first) << " - " << pointToString(pair.second);
    }
}

QString MainWindow::pointToString(QPoint point)
{
    return QString("(" + QString::number(point.x()) + ", " + QString::number(point.y()) + ")");
}

void MainWindow::addPoint(QPoint point)
{
    this->points.append(QPair<QPoint, QPoint>(point, QPoint(0, 0)));
    this->updateTable();
}
