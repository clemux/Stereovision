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
    void updatePoint(int row, QPoint left, QPoint right);
    void addPoint(QPoint left, QPoint right);
    void deletePoint(int row);
private slots:
    void pointClickedLeft(QPoint point);
    void pointClickedRight(QPoint point);
    void deleteClicked();
    void exportData();
};

#endif // MAINWINDOW_H
