#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ImageWidget leftImage(this);
    ui->horizontalLayout->addWidget(&leftImage);


    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->actionOpenLeft, SIGNAL(triggered()), &leftImage, SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
