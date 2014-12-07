#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = 0);
    double getSensorWidth();
    double getBaseline();
    double getFocal();
    QString getPath();
    ~ExportDialog();

private:
    Ui::ExportDialog *ui;

private slots:
    void browsePath();
};

#endif // EXPORTDIALOG_H
