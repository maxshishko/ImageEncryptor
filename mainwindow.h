#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>
#include <QInputDialog>
#include <memory>

#include "imageencryptormodel.h"
#include "imageencryptorpresenter.h"
#include "histogramwindow.h"
#include "correlationwindow.h"
#include "analysisresultwindow.h"
#include "fullanalisysdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public ImageEncryptorPresenter
{
    Q_OBJECT

public:
    explicit MainWindow(const std::shared_ptr<ImageEncryptorModel> &model, QWidget *parent = nullptr);
    ~MainWindow();

    void updateImages();

    void updateParameters();

    void setModel(const std::shared_ptr<ImageEncryptorModel> &value);

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

    void on_actionFull_Analysis_triggered();

private:
    Ui::MainWindow *ui;


    std::shared_ptr<ImageEncryptorModel> model;

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
