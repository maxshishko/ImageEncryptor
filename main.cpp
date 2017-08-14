#include <QApplication>
//#include <memory>
#include "imageencryptormodel.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto model = std::make_shared<ImageEncryptorModel>();
    auto window = std::make_shared<MainWindow>(model);

    model->setPresenter(window);
    window->show();

    return a.exec();
}
