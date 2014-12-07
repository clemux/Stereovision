#include "imagewidget.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QToolTip>
#include <QMouseEvent>

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
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir image"),
                                                    QDir::currentPath());
    if (!path.isEmpty()) {
        if (this->loadedImage != NULL)
            delete this->loadedImage;
        this->loadedImage = new QPixmap(path);
        if (this->loadedImage->isNull())
            QMessageBox::information(this, tr("Stereovision"),
                                     tr("Impossible d'ouvrir %1.").arg(path));
    }
    this->display();
}

void ImageWidget::display()
{
    if (this->loadedImage != NULL)
    {
        int w = this->width();
        int h = this->height();
        this->setPixmap(this->loadedImage->scaled(w, h, Qt::KeepAspectRatio));
    }
}

void ImageWidget::resizeEvent(QResizeEvent*)
{
    this->display();
}

QPoint ImageWidget::realCoords(QPoint pos)
{
    return pos*(this->loadedImage->width() / this->pixmap()->width());
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (this->loadedImage == NULL)
        return;

    QPoint pos = realCoords(event->pos());

    if (pos.x() > this->loadedImage->width()
        || pos.y() > this->loadedImage->height())
        return ;

    QString posString(QString::number(pos.x()) +
                      ", " +
                      QString::number(pos.y()));
    QToolTip::showText(event->globalPos(), posString);

}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    if (this->loadedImage == NULL)
        return;
    this->pointClicked(realCoords(event->pos()));
}
