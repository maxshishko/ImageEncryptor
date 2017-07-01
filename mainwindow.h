#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>

#include "imageencryptormodel.h"
#include "imageencryptorpresenter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public ImageEncryptorPresenter
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateImages();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionQuit_triggered();

    void on_actionPlain_Cipher_triggered();

private:
    Ui::MainWindow *ui;

    ImageEncryptorModel *model;

    QFileDialog *createImageFileDialog(int acceptMode);
};

#endif // MAINWINDOW_H
