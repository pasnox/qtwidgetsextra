#include <QApplication>

#include <memory>

#include "MainWindow.h"

int main(int argc, char** argv) {
    std::unique_ptr<QApplication> app(new QApplication(argc, argv));

    MainWindow w;
    w.showMaximized();

    return app->exec();
}
