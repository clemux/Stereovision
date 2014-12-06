#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

class ImageWidget : public QLabel
{
    Q_OBJECT
private:
    QPixmap *map = NULL;
    double scale;
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
public:
    explicit ImageWidget(QWidget *parent = 0);
signals:

public slots:
    void load();
    void display();
};

#endif // IMAGEWIDGET_H
