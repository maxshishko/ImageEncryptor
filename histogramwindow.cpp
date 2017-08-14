#include "histogramwindow.h"
#include "ui_histogramwindow.h"

void HistogramWindow::createHistogram(const QVector<int> &data,
                                      QwtPlot *plot,
                                      QwtPlotHistogram *hist,
                                      HistogramWindow::Color color)
{
    QVector<QwtIntervalSample> samples;
    for(int i = 0; i < data.size(); i++)
        samples.append(QwtIntervalSample(data[i],i, i+1));

    hist->setSamples(samples);
    hist->attach(plot);
    QColor penColor, brushColor;
    switch (color) {
    case RED:
        penColor = QColor(255, 0, 0, 100);
        brushColor = QColor(255, 0, 0, 255);
        break;
    case GREEN:
        penColor = QColor(0, 255, 0, 100);
        brushColor = QColor(0, 255, 0, 255);
        break;
    case BLUE:
        penColor = QColor(0, 0, 255, 100);
        brushColor = QColor(0, 0, 255, 255);
        break;
    }
    hist->setPen(QPen(penColor));
    hist->setBrush(QBrush(brushColor));
    plot->setAxisScale(2, 0, 255);
    plot->setSizePolicy(this->sizePolicy());
    plot->replot();
}

void HistogramWindow::exportAsImage()
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

bool HistogramWindow::saveImage(QString filename)
{
    QImage redPlotImage(2*plotRed->size(), QImage::Format_RGBA8888);
    QImage greenPlotImage(2*plotGreen->size(), QImage::Format_RGBA8888);
    QImage bluePlotImage(2*plotBlue->size(), QImage::Format_RGBA8888);
    QwtPlotRenderer renderer;
    renderer.renderTo(plotRed, redPlotImage);
    renderer.renderTo(plotGreen, greenPlotImage);
    renderer.renderTo(plotBlue, bluePlotImage);

    QImage result(redPlotImage.width(),
                  redPlotImage.height()+greenPlotImage.height()+bluePlotImage.height(),
                  QImage::Format_RGBA8888);
    QPainter painter(&result);
    painter.drawImage(0, 0, redPlotImage);
    painter.drawImage(0, redPlotImage.height(), greenPlotImage);
    painter.drawImage(0, redPlotImage.height()+greenPlotImage.height(), bluePlotImage);

    return result.save(filename);
}

HistogramWindow::HistogramWindow(QWidget *parent, const QVector<QVector<int> > &data) :
    QMainWindow(parent),
    ui(new Ui::HistogramWindow)
{
    ui->setupUi(this);

    createHistogram(data[0], plotRed, histRed, RED);
    createHistogram(data[1], plotGreen, histGreen, GREEN);
    createHistogram(data[2], plotBlue, histBlue, BLUE);

    ui->verticalLayout->addWidget(plotRed);
    ui->verticalLayout->addWidget(plotGreen);
    ui->verticalLayout->addWidget(plotBlue);
}

HistogramWindow::~HistogramWindow()
{
    delete histRed;
    delete histGreen;
    delete histBlue;
    delete plotRed;
    delete plotGreen;
    delete plotBlue;
    delete ui;
}

void HistogramWindow::on_actionAs_graphics_triggered()
{
    exportAsImage();
}
