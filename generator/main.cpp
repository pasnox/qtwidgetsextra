#include <QApplication>

#include "MainWindow.h"

int main(int argc, char** argv) {
    QSharedPointer<QApplication> app(new QApplication(argc, argv));

    MainWindow w;
    w.showMaximized();

    return app->exec();
}
