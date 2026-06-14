#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "University.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(University* university,
                        QString userType,
                        QWidget* parent = nullptr);

private slots:
    void showStudentsPage();
    void showDormsPage();
    void showRoomsPage();
    void showRestaurantPage();
    void setSidebarActive(QPushButton* active);

private:
    University*     university;
    QString         userType;

    QWidget*        centralWidget;
    QWidget*        sidebar;
    QStackedWidget* contentArea;

    QPushButton*    btnStudents;
    QPushButton*    btnDorms;
    QPushButton*    btnRooms;
    QPushButton*    btnRestaurant;

    QTableWidget*   studentsTable;
    QTableWidget*   dormsTable;
    QTableWidget*   roomsTable;
    QTableWidget*   restaurantTable;

    void setupUI();
    void setupSidebar();
    void setupStudentsPage();
    void setupDormsPage();
    void setupRoomsPage();
    void setupRestaurantPage();
    void applyGlobalStyles();
    void refreshStudentsTable();
    void refreshDormsTable();
    void refreshRoomsTable();
    void refreshRestaurantTable();

    QWidget* makeStatCard(QString label, QString value);
};

#endif