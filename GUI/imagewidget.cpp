#include "imagewidget.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

ImageWidget::ImageWidget(QWidget *parent) :
    QLabel(parent)
{
}

void ImageWidget::load()
{
    qDebug() << "ouverture fichier";
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir image"),
                                                    QDir::currentPath());
    if (!path.isEmpty()) {
        this->map = QPixmap(path);
        if (this->map.isNull()) {
            QMessageBox::information(this, tr("Stereovision"),
                                     tr("Impossible d'ouvrir %1.").arg(path));
        }
    }
}

void ImageWidget::display()
{
    this->setPixmap(this->map);
}
