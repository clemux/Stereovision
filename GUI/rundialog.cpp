#include "rundialog.h"
#include "ui_rundialog.h"
#include <QFileDialog>
#include <QDir>

RunDialog::RunDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunDialog)
{
    ui->setupUi(this);

    connect(ui->binaryButton, SIGNAL(clicked()), this, SLOT(browsePathBinary()));
    connect(ui->dataButton, SIGNAL(clicked()), this, SLOT(browsePathData()));
}

RunDialog::~RunDialog()
{
    delete ui;
}

void RunDialog::browsePathBinary()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir programme"),
                                                QDir::currentPath());
    ui->binaryPathEdit->setText(path);
}

void RunDialog::browsePathData()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir données"),
                                                QDir::currentPath());
    ui->dataPathEdit->setText(path);
}

QString RunDialog::getBinaryPath()
{
    return ui->binaryPathEdit->text();
}

QString RunDialog::getDataPath()
{
    return ui->dataPathEdit->text();
}
