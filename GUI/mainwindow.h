#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ImageWidget *leftImage;
    ImageWidget *rightImage;
    QVector<QPair<QPoint, QPoint> > points;
    void updateTable();
    QString pointToString(QPoint point);

private slots:
    void addPoint(QPoint point);
};

#endif // MAINWINDOW_H
