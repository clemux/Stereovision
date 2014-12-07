#include "exportdialog.h"
#include "ui_exportdialog.h"
#include <qfiledialog.h>
#include <qdir.h>
#include <qdebug.h>

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);

    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browsePath()));
}

double ExportDialog::getSensorWidth()
{
    return ui->sensorWidthBox->value();
}

double ExportDialog::getBaseline()
{
    return ui->baselineBox->value();
}

double ExportDialog::getFocal()
{
    return ui->focalBox->value();
}

QString ExportDialog::getPath()
{
    return ui->pathEdit->text();
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::browsePath()
{
    qDebug() << "PROUUUUUT" << endl;
    QString path = QFileDialog::getOpenFileName(this, tr("Exporter sous"),
                                                QDir::currentPath());
    ui->pathEdit->setText(path);
}
