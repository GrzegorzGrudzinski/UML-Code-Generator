#include <iostream>
#include <memory> // dla make_unique
#include <vector>

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {  
    ///////////////

    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();

    return 0;
}
