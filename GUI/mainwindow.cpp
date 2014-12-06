#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagewidget.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
