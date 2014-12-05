#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include <QPixmap>

class ImageWidget : public QLabel
{
    Q_OBJECT
private:
    QPixmap map;
public:
    explicit ImageWidget(QWidget *parent = 0);
signals:

public slots:
    void load();
    void display();
};

#endif // IMAGEWIDGET_H
