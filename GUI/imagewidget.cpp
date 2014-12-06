#include "imagewidget.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QToolTip>

ImageWidget::ImageWidget(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    //this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setScaledContents(false);
    this->setBackgroundRole(QPalette::Base);
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);

}

void ImageWidget::load()
{
    qDebug() << "ouverture fichier";
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir image"),
                                                    QDir::currentPath());
    if (!path.isEmpty()) {
        this->map = new QPixmap(path);
        if (this->map->isNull()) {
            QMessageBox::information(this, tr("Stereovision"),
                                     tr("Impossible d'ouvrir %1.").arg(path));
        }
    }
    this->display();
}

void ImageWidget::display()
{
    if (this->map != NULL)
    {
        int w = this->width();
        int h = this->height();
        this->setPixmap(this->map->scaled(w, h, Qt::KeepAspectRatio));
        this->scale = (double) this->map->width() / (double) this->pixmap()->width();
        qDebug() << "New ratio:" << this->scale;
    }
}

void ImageWidget::resizeEvent(QResizeEvent*)
{
    this->display();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{

    QString posString(QString::number(event->pos().x()*this->scale) +
                      ", " +
                      QString::number(event->pos().y()*this->scale));
    QToolTip::showText(event->globalPos(), posString);
}
