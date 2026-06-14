#include <QApplication>
#include "LoginDialog.h"
#include "MainWindow.h"
#include "University.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    University university("ENSIA");

    LoginDialog login;
    if (login.exec() != QDialog::Accepted) return 0;

    MainWindow window(&university, login.getUserType());
    window.show();

    return app.exec();
}
