#include <QApplication>
#include "LoginDialog.h"
#include "MainWindow.h"
#include "University.h"
#include "DataManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    University university("ENSIA");

    // Load saved data on startup
    DataManager::loadData(university);

    LoginDialog login;
    if (login.exec() != QDialog::Accepted) return 0;

    MainWindow window(&university, login.getUserType());
    window.show();

    int result = app.exec();

    // Save data when app closes
    DataManager::saveData(university);

    return result;
}