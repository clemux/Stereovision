#ifndef RUNDIALOG_H
#define RUNDIALOG_H

#include <QDialog>

namespace Ui {
class RunDialog;
}

class RunDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RunDialog(QWidget *parent = 0);
    ~RunDialog();

   QString getBinaryPath();
   QString getDataPath();
private slots:
    void browsePathBinary();
    void browsePathData();

private:
    Ui::RunDialog *ui;
};

#endif // RUNDIALOG_H
