#ifndef CORRELATIONWINDOW_H
#define CORRELATIONWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>
#include <qwt_plot_renderer.h>
#include "qwt_plot.h"
#include "qwt_plot_curve.h"

namespace Ui {
class CorrelationWindow;
}

class CorrelationWindow : public QMainWindow
{
    Q_OBJECT

    enum class Color{RED, GREEN, BLUE};

    QwtPlot *plotRed = new QwtPlot;
    QwtPlot *plotGreen = new QwtPlot;
    QwtPlot *plotBlue = new QwtPlot;
    QwtPlotCurve *curveRed = new QwtPlotCurve;
    QwtPlotCurve *curveGreen = new QwtPlotCurve;
    QwtPlotCurve *curveBlue = new QwtPlotCurve;

    void initScatter(QwtPlot *plot, QwtPlotCurve *curve, Color color);
    void exportAsImage();
    bool saveImage(QString filename);
public:
    explicit CorrelationWindow(QWidget *parent, const QVector<QVector<QVector<double>>> &dataSet, const QVector<double> &correlation);
    ~CorrelationWindow();

private slots:
    void on_actionAs_graphics_triggered();

private:
    Ui::CorrelationWindow *ui;
};

#endif // CORRELATIONWINDOW_H
