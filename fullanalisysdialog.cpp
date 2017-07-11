#include "fullanalisysdialog.h"
#include "ui_fullanalisysdialog.h"


FullAnalisysDialog::FullAnalisysDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullAnalisysDialog)
{
    ui->setupUi(this);
}

FullAnalisysDialog::~FullAnalisysDialog()
{
    delete ui;
}

QString FullAnalisysDialog::getFilePath()
{
    return ui->lineEditFilename->text();
}

int FullAnalisysDialog::getNumSimulations()
{
    return ui->spinBoxNumSim->value();
}

bool FullAnalisysDialog::useRandomParameters()
{
    return ui->checkBoxUseRandomParam->isChecked();
}

void FullAnalisysDialog::on_pushButton_clicked()
{
    QStringList mimeTypeFilters;
    mimeTypeFilters << "text/csv";

    QFileDialog *dialog = new QFileDialog(this, tr("Choose file to write data"), windowFilePath());
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    dialog->setMimeTypeFilters(mimeTypeFilters);
    dialog->selectMimeTypeFilter("text");

    if(dialog->exec() == QDialog::Accepted){
        ui->lineEditFilename->setText(dialog->selectedFiles().first());
    }
}
