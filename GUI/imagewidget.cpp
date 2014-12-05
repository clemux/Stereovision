#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
    QLabel(parent)
{
}

void ImageWidget::load()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir image"),
                                                    QDir::currentPath());
    if (!fileName.isEmpty()) {
        this->map = QPixmap(path);
        if (this->map.isNull()) {
            QMessageBox::information(this, tr("Stereovision"),
                                     tr("Impossible d'ouvrir %1.").arg(fileName));
        }
    }
}

void ImageWidget::display()
{
    this->setPixmap(this->map);
}
