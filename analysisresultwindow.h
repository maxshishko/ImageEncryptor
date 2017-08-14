#ifndef ANALYSISRESULTWINDOW_H
#define ANALYSISRESULTWINDOW_H

#include <QMainWindow>

namespace Ui {
class AnalysisResultWindow;
}

class AnalysisResultWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnalysisResultWindow(QWidget *parent, const QVector<double> &data);
    ~AnalysisResultWindow();

private:
    Ui::AnalysisResultWindow *ui;
};

#endif // ANALYSISRESULTWINDOW_H
