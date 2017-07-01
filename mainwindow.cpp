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
}

void MainWindow::updateImages()
{
    ui->srcImageLabel->setPixmap(QPixmap::fromImage(model->getSrcImage()));
    ui->dstImageLabel->setPixmap(QPixmap::fromImage(model->getDstImage()));
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    QFileDialog dialog(this, tr("Open File"),
                       windowFilePath());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image");

    while(dialog.exec() == QDialog::Accepted &&
          !model->loadImage(dialog.selectedFiles().first())){}
    ui->tabWidget->setCurrentIndex(0);
}
