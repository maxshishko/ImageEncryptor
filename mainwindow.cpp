#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new ImageEncryptorModel(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::updateImages()
{
    ui->srcImageLabel->setPixmap(QPixmap::fromImage(model->getSrcImage()));
    ui->dstImageLabel->setPixmap(QPixmap::fromImage(model->getDstImage()));
}

void MainWindow::updateEvolutionEncryptionParameters()
{
    int popsize;
    double mutationRate, entropy;
    QString decryptionKey;
    model->getEvolutionEncryptorParameters(popsize, mutationRate, entropy);
    model->getEvolutionEncryptorParameters(decryptionKey);
    ui->EApopulationSpinBox->setValue(popsize);
    ui->EAmutationRateSpinBox->setValue(mutationRate);
    ui->EAenthropySpinBox->setValue(entropy);
    ui->lineEdit_EADeckey->setText(decryptionKey);
}

void MainWindow::updateParameters()
{
    try{
        switch (ui->tabWidgetEncryptionMethod->currentIndex()) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            updateEvolutionEncryptionParameters();
            break;
        }

    }
    catch(std::exception e){
        QMessageBox::critical(this, QString("Error!"), QString::fromLocal8Bit(e.what()));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog* dialog = createImageFileDialog(QFileDialog::AcceptOpen);

    bool opened = false;
    while(dialog->exec() == QDialog::Accepted &&
          !(opened= model->loadSrcImage(dialog->selectedFiles().first()))){
        if(!opened)
            QMessageBox::critical(this, tr("Error!"), tr("Can't open image."));
    }
    ui->tabWidgetImage->setCurrentIndex(0);

    delete dialog;
}

void MainWindow::on_actionSave_triggered()
{
    if(model->getDstImage().isNull()){
        QMessageBox::critical(this, tr("Error"), tr("Image is empty."));
        return;
    }

    QFileDialog* dialog = createImageFileDialog(QFileDialog::AcceptSave);

    bool saved = false;
    while(dialog->exec() == QDialog::Accepted &&
          !(saved = model->saveDstImage(dialog->selectedFiles().first()))){
        if(!saved)
            QMessageBox::critical(this, tr("Error!"), tr("Can't save image."));
    }

    delete dialog;
}

void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}

QFileDialog* MainWindow::createImageFileDialog(int acceptMode){
    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();


    QFileDialog *dialog;
    if(acceptMode == QFileDialog::AcceptSave)
        dialog = new QFileDialog(this, tr("Save Image"), windowFilePath());
    else
        dialog = new QFileDialog(this, tr("Open Image"), windowFilePath());

    dialog->setAcceptMode((QFileDialog::AcceptMode)acceptMode);
    dialog->setMimeTypeFilters(mimeTypeFilters);
    dialog->selectMimeTypeFilter("image");
    return dialog;
}

void MainWindow::encrypt()
{
    if(setupEncryptor())
        if(setupEncryptionParameters()){
            model->encrypt();
            ui->tabWidgetImage->setCurrentIndex(1);
        }
}

void MainWindow::decrypt()
{
    if(setupEncryptor())
        if(setupEncryptionParameters()){
            model->decrypt();
            ui->tabWidgetImage->setCurrentIndex(1);
        }
}

bool MainWindow::setupEncryptor()
{
    switch (ui->tabWidgetEncryptionMethod->currentIndex()) {
    case 0:
        model->changeEncryptor(ImageEncryptorModel::DNA);
        break;
    case 1:
        model->changeEncryptor(ImageEncryptorModel::Yoon);
        break;
    case 2:
        model->changeEncryptor(ImageEncryptorModel::EvolutionAlgorithm);
        break;
    }
    return true;
}

bool MainWindow::setupEncryptionParameters()
{
    try{
        switch (ui->tabWidgetEncryptionMethod->currentIndex()) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            model->setEvolutionEncryptorParameters(
                        ui->EApopulationSpinBox->value(),
                        ui->EAmutationRateSpinBox->value(),
                        ui->EAenthropySpinBox->value());
            model->setEvolutionEncryptorParameters(ui->lineEdit_EADeckey->text());
            break;
        }
    }
    catch(std::exception e){
        QMessageBox::critical(this, QString("Error!"), QString::fromLocal8Bit(e.what()));
        return false;
    }
    return true;
}

void MainWindow::on_actionPlain_Cipher_triggered()
{
    model->swapPlainCipher();
}

void MainWindow::on_buttonSetRandomParameters_clicked()
{
    model->setRandomParameters();
}

void MainWindow::on_buttotnEncrypt_clicked()
{
    encrypt();
}

void MainWindow::on_actionEncrypt_triggered()
{
    encrypt();
}

void MainWindow::on_buttonDecrypt_clicked()
{
    decrypt();
}

void MainWindow::on_actionDecrypt_triggered()
{
    decrypt();
}
