#include <QApplication>
#include "LoginDialog.h"
#include "MainWindow.h"
#include "University.h"
#include "DataManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    University university("ENSIA");
    DataManager::loadData(university);

    bool keepRunning = true;

    while (keepRunning) {
        LoginDialog login(&university);
        if (login.exec() != QDialog::Accepted) {
            keepRunning = false;
            break;
        }

        MainWindow window(&university, login.getUserType());

        bool loggedOut = false;
        QObject::connect(&window, &MainWindow::logoutRequested, [&]() {
            loggedOut = true;
        });

        window.show();
        app.exec();

        DataManager::saveData(university);

        if (!loggedOut) {
            keepRunning = false;
        }
    }

    return 0;
}
