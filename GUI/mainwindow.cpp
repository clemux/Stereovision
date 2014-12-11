#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagewidget.h"
#include <exportdialog.h>
#include <rundialog.h>
#include <qdebug.h>
#include <QMessageBox>
#include <QProcess>

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
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);



    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->actionOpenLeft, SIGNAL(triggered()), leftImage, SLOT(load()));
    connect(ui->actionOpenRight, SIGNAL(triggered()), rightImage, SLOT(load()));

    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(exportData()));
    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(runProgram()));

    connect(leftImage, SIGNAL(pointClicked(QPoint)), this, SLOT(pointClickedLeft(QPoint)));
    connect(rightImage, SIGNAL(pointClicked(QPoint)), this, SLOT(pointClickedRight(QPoint)));

    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTable()
{

    QPair<QPoint, QPoint> pair;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    foreach(pair, this->points) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itemLeft = new QTableWidgetItem(pointToString(pair.first));
        QTableWidgetItem *itemRight = new QTableWidgetItem(pointToString(pair.second));
        itemLeft->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        itemRight->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, itemLeft);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, itemRight);
    }
}

QString MainWindow::pointToString(QPoint point)
{
    return QString("(" + QString::number(point.x()) + ", " + QString::number(point.y()) + ")");
}

void MainWindow::addPoint(QPoint left, QPoint right)
{
    this->points.append(QPair<QPoint, QPoint>(left, right));
}

void MainWindow::deletePoint(int row)
{
    this->points.remove(row);
    this->updateTable();
}

void MainWindow::updatePoint(int row, QPoint left, QPoint right)
{
    this->points[row] = QPair<QPoint, QPoint>(left, right);
}

void MainWindow::pointClickedLeft(QPoint point)
{
    QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
    if (selected.count() > 0) {
        int currentRow = selected[0]->row();
        QPoint rightValue = this->points[currentRow].second;
        this->updatePoint(currentRow, point, rightValue);
        this->updateTable();
    }
    else {
        this->addPoint(point, QPoint(0, 0));
        this->updateTable();
        this->ui->tableWidget->selectRow(ui->tableWidget->rowCount() - 1);
    }
}

void MainWindow::pointClickedRight(QPoint point)
{
    QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
    if (selected.count() > 0) {
        int currentRow = selected[0]->row();
        QPoint leftValue = this->points[currentRow].first;
        this->updatePoint(currentRow, leftValue, point);
    }
    else {
        this->addPoint(QPoint(0, 0), point);
    }
    this->updateTable();
}

void MainWindow::deleteClicked()
{
    QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
    if (selected.count() > 0) {
        this->deletePoint(selected[0]->row());
    }
}

void MainWindow::exportData()
{
    ExportDialog dialog(this);
    if (!dialog.exec())
        return;

    QPair<QPoint, QPoint> point;
    QFile file(dialog.getPath());


    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setText("Erreur d'ouverture du fichier d'exportation.");
        msgBox.exec();

        return;
    }

    if (!this->leftImage->imageIsLoaded()) {
        QMessageBox msgBox;
        msgBox.setText("Aucune image n'est chargée");
        msgBox.exec();
        return;
    }

    QTextStream out(&file);
    out << QString::number(dialog.getFocal()) << endl;
    double sensorResolution = (this->leftImage->getOriginalWidth() /
                               dialog.getSensorWidth());
    out << QString::number(sensorResolution) << endl;
    out << QString::number(dialog.getBaseline()) << endl;
    out << QString::number(this->points.count()) << endl;
    foreach(point, this->points)
    {
        out << QString::number(point.first.x()) << " "
            << QString::number(point.first.y()) << " "
            << QString::number(point.second.x()) << " "
            << QString::number(point.second.y()) << " "
            << endl;
    }

    file.close();
}


void MainWindow::runProgram()
{
    RunDialog dialog(this);
    if (!dialog.exec())
        return;

    QFile dataFile(dialog.getDataPath());
    if (!dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setText("Erreur d'ouverture du fichier de données");
        msgBox.exec();
        return;
    }
    dataFile.close();



    QProcess mode;
    mode.setStandardInputFile(dialog.getDataPath());
    mode.start(dialog.getBinaryPath());

    mode.waitForFinished();

}
