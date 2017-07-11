#include "analysisresultwindow.h"
#include "ui_analysisresultwindow.h"

AnalysisResultWindow::AnalysisResultWindow(QWidget *parent, QVector<double> data) :
    QMainWindow(parent),
    ui(new Ui::AnalysisResultWindow)
{
    ui->setupUi(this);

    if(data.size() == 3){
        ui->lineEdit_1->setText(data[0]);
        ui->lineEdit_2->setText(data[1]);
        ui->lineEdit_3->setText(data[2]);
    }
}

AnalysisResultWindow::~AnalysisResultWindow()
{
    delete ui;
}
