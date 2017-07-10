#include "correlationwindow.h"
#include "ui_correlationwindow.h"


void CorrelationWindow::initScatter(QwtPlot *plot, QwtPlotCurve *curve, CorrelationWindow::Color color)
{
    QColor penColor;
    switch (color) {
    case RED:
        penColor = QColor(255, 0, 0);
        break;
    case GREEN:
        penColor = QColor(0, 255, 0);
        break;
    case BLUE:
        penColor= QColor(0, 0, 255);
        break;
    }
    curve->setStyle(QwtPlotCurve::Dots);
    curve->setPen(penColor, 3);
    curve->attach(plot);
    plot->setSizePolicy(this->sizePolicy());
}

void CorrelationWindow::exportAsImage()
{
    QFileDialog dialog(this, QString("Save image"), windowFilePath());

    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();

    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image");

    bool saved = false;
    while(dialog.exec() == QDialog::Accepted &&
          !(saved= saveImage(dialog.selectedFiles().first()))){
        if(!saved)
            QMessageBox::critical(this, tr("Error!"), tr("Can't save image."));
    }
}

bool CorrelationWindow::saveImage(QString filename)
{
    QImage redPlotImage(plotRed->size(), QImage::Format_RGBA8888);
    QImage greenPlotImage(plotGreen->size(), QImage::Format_RGBA8888);
    QImage bluePlotImage(plotBlue->size(), QImage::Format_RGBA8888);
    QwtPlotRenderer renderer;
    renderer.renderTo(plotRed, redPlotImage);
    renderer.renderTo(plotGreen, greenPlotImage);
    renderer.renderTo(plotBlue, bluePlotImage);

    QImage result(redPlotImage.width()+greenPlotImage.width()+bluePlotImage.width(),
                  redPlotImage.height(),
                  QImage::Format_RGBA8888);
    QPainter painter(&result);
    painter.drawImage(0, 0, redPlotImage);
    painter.drawImage(redPlotImage.width(), 0, greenPlotImage);
    painter.drawImage(redPlotImage.width()+greenPlotImage.width(), 0, bluePlotImage);

    return result.save(filename);
}

CorrelationWindow::CorrelationWindow(QWidget *parent, QVector<QVector<QVector<double> > > dataSet, QVector<double> correlation) :
    QMainWindow(parent),
    ui(new Ui::CorrelationWindow)
{
    ui->setupUi(this);

    ui->lineEditCorrR->setText(QString::number(correlation[0]));
    ui->lineEditCorrG->setText(QString::number(correlation[1]));
    ui->lineEditCorrB->setText(QString::number(correlation[2]));

    curveRed->setSamples(dataSet[0][0], dataSet[0][1]);
    curveGreen->setSamples(dataSet[1][0], dataSet[1][1]);
    curveBlue->setSamples(dataSet[2][0], dataSet[2][1]);

    initScatter(plotRed, curveRed, RED);
    initScatter(plotGreen, curveGreen, GREEN);
    initScatter(plotBlue, curveBlue, BLUE);

    ui->horizontalLayoutScatters->addWidget(plotRed);
    ui->horizontalLayoutScatters->addWidget(plotGreen);
    ui->horizontalLayoutScatters->addWidget(plotBlue);
}

CorrelationWindow::~CorrelationWindow()
{
    delete ui;
}

void CorrelationWindow::on_actionAs_graphics_triggered()
{
    exportAsImage();
}
