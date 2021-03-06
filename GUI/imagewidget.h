#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include <QPoint>
#include <QPixmap>
#include <QMouseEvent>

class ImageWidget : public QLabel
{
    Q_OBJECT
private:
    QPixmap *loadedImage = NULL;
    QPoint realCoords(QPoint pos);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    QPoint getCenter();
public:
    explicit ImageWidget(QWidget *parent = 0);
    int getOriginalWidth();
    bool imageIsLoaded();
signals:
    void pointClicked(QPoint point);
public slots:
    void load();
    void display();
};

#endif // IMAGEWIDGET_H
