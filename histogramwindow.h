#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QImageReader>
#include <QImage>
#include <QtPrintSupport/QPrinter>
#include <qwt_plot.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_renderer.h>

namespace Ui {
class HistogramWindow;
}

class HistogramWindow : public QMainWindow
{
private:
    Q_OBJECT

    Ui::HistogramWindow *ui;

    enum Color{RED, GREEN, BLUE};

    QwtPlot *plotRed = new QwtPlot;
    QwtPlot *plotGreen = new QwtPlot;
    QwtPlot *plotBlue = new QwtPlot;
    QwtPlotHistogram *histRed = new QwtPlotHistogram;
    QwtPlotHistogram *histGreen = new QwtPlotHistogram;
    QwtPlotHistogram *histBlue = new QwtPlotHistogram;

    void createHistogram(const QVector<int> &samples, QwtPlot *plot, QwtPlotHistogram *hist, Color color);
    void exportAsImage();
    bool saveImage(QString filename);
public:
    HistogramWindow(QWidget *parent, const QVector<QVector<int>> &data);
    ~HistogramWindow();

private slots:
    void on_actionAs_graphics_triggered();
};

#endif // HISTOGRAMWINDOW_H
