#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>

#include "imageencryptormodel.h"
#include "imageencryptorpresenter.h"
#include "histogramwindow.h"
#include "correlationwindow.h"
#include "analysisresultwindow.h"

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

    void updateParameters();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionQuit_triggered();

    void on_actionPlain_Cipher_triggered();

    void on_buttonSetRandomParameters_clicked();

    void on_buttotnEncrypt_clicked();

    void on_actionEncrypt_triggered();

    void on_buttonDecrypt_clicked();

    void on_actionDecrypt_triggered();

    void on_actionHistogram_triggered();

    void on_actionHorizontal_triggered();

    void on_actionVertical_triggered();

    void on_actionDiagonal_triggered();

    void on_actionEnthropy_triggered();

    void on_actionNPCR_triggered();

    void on_actionUACI_triggered();

    void on_actionEncryption_time_triggered();

private:
    Ui::MainWindow *ui;

    ImageEncryptorModel *model;

    QFileDialog *createImageFileDialog(int acceptMode);

    void encrypt();
    void decrypt();
    bool setupEncryptor();
    bool setupEncryptionParameters();
    void updateEvolutionEncryptionParameters();
    void updateYoonEncryptionParameters();
    void updateDNAEncryptionParameters();
    void showCorrelation(int type);
};

#endif // MAINWINDOW_H
