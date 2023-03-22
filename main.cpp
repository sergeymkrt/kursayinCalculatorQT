#include <QApplication>
#include "Widgets/MainWindow/MainWindow.h"
#include "Widgets/Authentication/AuthenticationWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //auto *w = new MainWindow();
    //w->show();
    auto *w = new AuthenticationWidget();
    w->show();
    return QApplication::exec();
}
