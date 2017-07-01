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

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog* dialog = createImageFileDialog(QFileDialog::AcceptOpen);

    bool opened = false;
    while(dialog->exec() == QDialog::Accepted &&
          !(opened= model->loadSrcImage(dialog->selectedFiles().first()))){
        if(!opened)
            QMessageBox::critical(this, tr("Error!"), tr("Can't open image."));
    }
    ui->tabWidget->setCurrentIndex(0);

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

void MainWindow::on_actionPlain_Cipher_triggered()
{
    model->swapPlainCipher();
}
