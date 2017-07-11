#ifndef FULLANALISYSDIALOG_H
#define FULLANALISYSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class FullAnalisysDialog;
}

class FullAnalisysDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FullAnalisysDialog(QWidget *parent = 0);
    ~FullAnalisysDialog();

    QString getFilePath();
    int getNumSimulations();
    bool useRandomParameters();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FullAnalisysDialog *ui;
};

#endif // FULLANALISYSDIALOG_H
