#include "MainWindow.h"
#include "StudentDialog.h"
#include "DormDialog.h"
#include "RoomDialog.h"
#include "RestaurantDialog.h"
#include "AssignRoomDialog.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QGridLayout>

MainWindow::MainWindow(University* university, QString userType, QWidget* parent)
    : QMainWindow(parent), university(university), userType(userType) {
    setWindowTitle("UDRMS — " + userType);
    setMinimumSize(1000, 650);
    setupUI();
    applyGlobalStyles();
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* root = new QHBoxLayout(centralWidget);
    root->setSpacing(0);
    root->setContentsMargins(0, 0, 0, 0);

    setupSidebar();
    root->addWidget(sidebar);

    contentArea = new QStackedWidget();
    contentArea->setStyleSheet("background: #F8F0F8;");
    setupStudentsPage();
    setupDormsPage();
    setupRoomsPage();
    setupRestaurantPage();
    root->addWidget(contentArea);
}

void MainWindow::setupSidebar() {
    sidebar = new QWidget();
    sidebar->setFixedWidth(200);
    sidebar->setStyleSheet("background-color: #6B2D5E;");

    QVBoxLayout* layout = new QVBoxLayout(sidebar);
    layout->setContentsMargins(14, 28, 14, 20);
    layout->setSpacing(6);

    QLabel* appName = new QLabel("UDRMS");
    appName->setAlignment(Qt::AlignCenter);
    appName->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");

    QLabel* school = new QLabel("ENSIA 2025–2026");
    school->setAlignment(Qt::AlignCenter);
    school->setStyleSheet("font-size: 10px; color: #E8A0BF; letter-spacing: 1px;");

    QFrame* div1 = new QFrame();
    div1->setFrameShape(QFrame::HLine);
    div1->setStyleSheet("color: rgba(255,255,255,0.2); margin: 8px 0;");

    QLabel* userLabel = new QLabel(userType);
    userLabel->setAlignment(Qt::AlignCenter);
    userLabel->setWordWrap(true);
    userLabel->setStyleSheet("font-size: 11px; color: #E8A0BF; margin-bottom: 10px;");

    btnStudents   = new QPushButton("  Students");
    btnDorms      = new QPushButton("  Dormitories");
    btnRooms      = new QPushButton("  Rooms");
    btnRestaurant = new QPushButton("  Restaurant");

    QString navStyle = R"(
        QPushButton {
            text-align: left;
            padding: 11px 16px;
            border-radius: 10px;
            font-size: 13px;
            color: #E8C4D8;
            background: transparent;
            border: none;
        }
        QPushButton:hover {
            background: rgba(255,255,255,0.12);
            color: white;
        }
    )";

    btnStudents->setStyleSheet(navStyle);
    btnDorms->setStyleSheet(navStyle);
    btnRooms->setStyleSheet(navStyle);
    btnRestaurant->setStyleSheet(navStyle);
    btnStudents->setCursor(Qt::PointingHandCursor);
    btnDorms->setCursor(Qt::PointingHandCursor);
    btnRooms->setCursor(Qt::PointingHandCursor);
    btnRestaurant->setCursor(Qt::PointingHandCursor);

    layout->addWidget(appName);
    layout->addWidget(school);
    layout->addWidget(div1);
    layout->addWidget(userLabel);
    layout->addWidget(btnStudents);
    layout->addWidget(btnDorms);
    layout->addWidget(btnRooms);
    layout->addWidget(btnRestaurant);
    layout->addStretch();

    QLabel* footer = new QLabel("University Dormitory\n& Restaurant System");
    footer->setAlignment(Qt::AlignCenter);
    footer->setWordWrap(true);
    footer->setStyleSheet("font-size: 10px; color: rgba(232,160,191,0.6); line-height: 1.5;");
    layout->addWidget(footer);

    connect(btnStudents,   &QPushButton::clicked, this, &MainWindow::showStudentsPage);
    connect(btnDorms,      &QPushButton::clicked, this, &MainWindow::showDormsPage);
    connect(btnRooms,      &QPushButton::clicked, this, &MainWindow::showRoomsPage);
    connect(btnRestaurant, &QPushButton::clicked, this, &MainWindow::showRestaurantPage);
}

QWidget* MainWindow::makeStatCard(QString label, QString value) {
    QWidget* card = new QWidget();
    card->setStyleSheet(R"(
        QWidget {
            background: white;
            border-radius: 12px;
            border: 1px solid #F0D0E4;
        }
    )");
    QVBoxLayout* l = new QVBoxLayout(card);
    l->setContentsMargins(16, 14, 16, 14);

    QLabel* lbl = new QLabel(label);
    lbl->setStyleSheet("font-size: 11px; color: #A06080; border: none; background: transparent;");

    QLabel* val = new QLabel(value);
    val->setStyleSheet("font-size: 26px; font-weight: bold; color: #6B2D5E; border: none; background: transparent;");

    l->addWidget(lbl);
    l->addWidget(val);
    return card;
}

void MainWindow::setupStudentsPage() {
    QWidget* page = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 28, 28, 28);
    layout->setSpacing(16);

    QHBoxLayout* header = new QHBoxLayout();
    QLabel* title = new QLabel("Students");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #3D1A47;");

    QPushButton* addBtn = new QPushButton("+ Add Student");
    QPushButton* assignBtn = new QPushButton("Assign Room");

    QString filledBtnStyle = R"(
        QPushButton {
            background: #6B2D5E;
            color: white;
            border: none;
            border-radius: 20px;
            padding: 9px 22px;
            font-size: 13px;
            font-weight: bold;
        }
        QPushButton:hover { background: #8B3D7E; }
    )";
    QString outlineBtnStyle = R"(
        QPushButton {
            background: white;
            color: #6B2D5E;
            border: 1.5px solid #6B2D5E;
            border-radius: 20px;
            padding: 9px 22px;
            font-size: 13px;
            font-weight: bold;
        }
        QPushButton:hover { background: #FDF0F8; }
    )";

    addBtn->setStyleSheet(filledBtnStyle);
    assignBtn->setStyleSheet(outlineBtnStyle);
    addBtn->setCursor(Qt::PointingHandCursor);
    assignBtn->setCursor(Qt::PointingHandCursor);

    header->addWidget(title);
    header->addStretch();
    header->addWidget(assignBtn);
    header->addWidget(addBtn);
    layout->addLayout(header);

    QHBoxLayout* stats = new QHBoxLayout();
    stats->setSpacing(12);
    stats->addWidget(makeStatCard("Total Students",
        QString::number(university->getStudents().size())));
    stats->addWidget(makeStatCard("Assigned", "0"));
    stats->addWidget(makeStatCard("Unassigned", "0"));
    layout->addLayout(stats);

    QWidget* tableCard = new QWidget();
    tableCard->setStyleSheet("background: white; border-radius: 14px; border: 1px solid #F0D0E4;");
    QVBoxLayout* tableLayout = new QVBoxLayout(tableCard);
    tableLayout->setContentsMargins(0, 0, 0, 0);

    studentsTable = new QTableWidget();
    studentsTable->setColumnCount(6);
    studentsTable->setHorizontalHeaderLabels({"ID","Name","Email","Year","Room","Status"});
    studentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentsTable->setAlternatingRowColors(true);
    studentsTable->verticalHeader()->setVisible(false);
    studentsTable->setShowGrid(false);
    studentsTable->setStyleSheet(R"(
        QTableWidget {
            background: white;
            border: none;
            border-radius: 14px;
            font-size: 13px;
            color: #3D1A47;
        }
        QTableWidget::item {
            padding: 10px 16px;
            border-bottom: 1px solid #FBF0F8;
        }
        QTableWidget::item:selected {
            background: #F8E8F4;
            color: #6B2D5E;
        }
        QHeaderView::section {
            background: #FDF0F8;
            color: #8B4F6F;
            font-weight: bold;
            font-size: 12px;
            padding: 10px 16px;
            border: none;
            border-bottom: 1px solid #F0D0E4;
        }
        QTableWidget::item:alternate {
            background: #FEFBFE;
        }
    )");

    tableLayout->addWidget(studentsTable);
    layout->addWidget(tableCard);

    connect(addBtn, &QPushButton::clicked, this, [this]() {
        StudentDialog dlg(university, this);
        if (dlg.exec() == QDialog::Accepted) refreshStudentsTable();
    });

    connect(assignBtn, &QPushButton::clicked, this, [this]() {
        AssignRoomDialog dlg(university, this);
        if (dlg.exec() == QDialog::Accepted) refreshStudentsTable();
    });

    contentArea->addWidget(page);
    refreshStudentsTable();
}

void MainWindow::setupDormsPage() {
    QWidget* page = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 28, 28, 28);
    layout->setSpacing(16);

    QHBoxLayout* header = new QHBoxLayout();
    QLabel* title = new QLabel("Dormitories");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #3D1A47;");

    QPushButton* addBtn = new QPushButton("+ Add Dormitory");
    addBtn->setStyleSheet(R"(
        QPushButton {
            background: #6B2D5E; color: white; border: none;
            border-radius: 20px; padding: 9px 22px;
            font-size: 13px; font-weight: bold;
        }
        QPushButton:hover { background: #8B3D7E; }
    )");
    addBtn->setCursor(Qt::PointingHandCursor);
    header->addWidget(title);
    header->addStretch();
    header->addWidget(addBtn);
    layout->addLayout(header);

    QWidget* tableCard = new QWidget();
    tableCard->setStyleSheet("background: white; border-radius: 14px; border: 1px solid #F0D0E4;");
    QVBoxLayout* tl = new QVBoxLayout(tableCard);
    tl->setContentsMargins(0, 0, 0, 0);

    dormsTable = new QTableWidget();
    dormsTable->setColumnCount(4);
    dormsTable->setHorizontalHeaderLabels({"Name","Location","Rooms","Occupancy"});
    dormsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dormsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dormsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    dormsTable->verticalHeader()->setVisible(false);
    dormsTable->setShowGrid(false);
    dormsTable->setAlternatingRowColors(true);
    dormsTable->setStyleSheet(R"(
        QTableWidget {
            background: white; border: none; border-radius: 14px;
            font-size: 13px; color: #3D1A47;
        }
        QTableWidget::item { padding: 10px 16px; border-bottom: 1px solid #FBF0F8; }
        QTableWidget::item:selected { background: #F8E8F4; color: #6B2D5E; }
        QHeaderView::section {
            background: #FDF0F8; color: #8B4F6F; font-weight: bold;
            font-size: 12px; padding: 10px 16px; border: none;
            border-bottom: 1px solid #F0D0E4;
        }
        QTableWidget::item:alternate { background: #FEFBFE; }
    )");
    tl->addWidget(dormsTable);
    layout->addWidget(tableCard);

    connect(addBtn, &QPushButton::clicked, this, [this]() {
        DormDialog dlg(university, this);
        if (dlg.exec() == QDialog::Accepted) refreshDormsTable();
    });

    contentArea->addWidget(page);
    refreshDormsTable();
}

void MainWindow::setupRoomsPage() {
    QWidget* page = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 28, 28, 28);
    layout->setSpacing(16);

    QHBoxLayout* header = new QHBoxLayout();
    QLabel* title = new QLabel("Rooms");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #3D1A47;");
    QPushButton* addBtn = new QPushButton("+ Add Room");
    addBtn->setStyleSheet(R"(
        QPushButton {
            background: #6B2D5E; color: white; border: none;
            border-radius: 20px; padding: 9px 22px;
            font-size: 13px; font-weight: bold;
        }
        QPushButton:hover { background: #8B3D7E; }
    )");
    addBtn->setCursor(Qt::PointingHandCursor);
    header->addWidget(title);
    header->addStretch();
    header->addWidget(addBtn);
    layout->addLayout(header);

    QWidget* tableCard = new QWidget();
    tableCard->setStyleSheet("background: white; border-radius: 14px; border: 1px solid #F0D0E4;");
    QVBoxLayout* tl = new QVBoxLayout(tableCard);
    tl->setContentsMargins(0, 0, 0, 0);

    roomsTable = new QTableWidget();
    roomsTable->setColumnCount(4);
    roomsTable->setHorizontalHeaderLabels({"Dormitory","Room No.","Capacity","Occupancy"});
    roomsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    roomsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    roomsTable->verticalHeader()->setVisible(false);
    roomsTable->setShowGrid(false);
    roomsTable->setAlternatingRowColors(true);
    roomsTable->setStyleSheet(R"(
        QTableWidget {
            background: white; border: none; border-radius: 14px;
            font-size: 13px; color: #3D1A47;
        }
        QTableWidget::item { padding: 10px 16px; border-bottom: 1px solid #FBF0F8; }
        QTableWidget::item:selected { background: #F8E8F4; color: #6B2D5E; }
        QHeaderView::section {
            background: #FDF0F8; color: #8B4F6F; font-weight: bold;
            font-size: 12px; padding: 10px 16px; border: none;
            border-bottom: 1px solid #F0D0E4;
        }
        QTableWidget::item:alternate { background: #FEFBFE; }
    )");
    tl->addWidget(roomsTable);
    layout->addWidget(tableCard);

    connect(addBtn, &QPushButton::clicked, this, [this]() {
        RoomDialog dlg(university, this);
        if (dlg.exec() == QDialog::Accepted) refreshRoomsTable();
    });

    contentArea->addWidget(page);
}

void MainWindow::setupRestaurantPage() {
    QWidget* page = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 28, 28, 28);
    layout->setSpacing(16);

    QHBoxLayout* header = new QHBoxLayout();
    QLabel* title = new QLabel("Restaurant Menus");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #3D1A47;");
    QPushButton* updateBtn = new QPushButton("Update Menu");
    updateBtn->setStyleSheet(R"(
        QPushButton {
            background: #6B2D5E; color: white; border: none;
            border-radius: 20px; padding: 9px 22px;
            font-size: 13px; font-weight: bold;
        }
        QPushButton:hover { background: #8B3D7E; }
    )");
    updateBtn->setCursor(Qt::PointingHandCursor);
    header->addWidget(title);
    header->addStretch();
    header->addWidget(updateBtn);
    layout->addLayout(header);

    QWidget* tableCard = new QWidget();
    tableCard->setStyleSheet("background: white; border-radius: 14px; border: 1px solid #F0D0E4;");
    QVBoxLayout* tl = new QVBoxLayout(tableCard);
    tl->setContentsMargins(0, 0, 0, 0);

    restaurantTable = new QTableWidget();
    restaurantTable->setColumnCount(4);
    restaurantTable->setHorizontalHeaderLabels({"Dormitory","Breakfast","Lunch","Dinner"});
    restaurantTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    restaurantTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    restaurantTable->verticalHeader()->setVisible(false);
    restaurantTable->setShowGrid(false);
    restaurantTable->setAlternatingRowColors(true);
    restaurantTable->setStyleSheet(R"(
        QTableWidget {
            background: white; border: none; border-radius: 14px;
            font-size: 13px; color: #3D1A47;
        }
        QTableWidget::item { padding: 10px 16px; border-bottom: 1px solid #FBF0F8; }
        QTableWidget::item:selected { background: #F8E8F4; color: #6B2D5E; }
        QHeaderView::section {
            background: #FDF0F8; color: #8B4F6F; font-weight: bold;
            font-size: 12px; padding: 10px 16px; border: none;
            border-bottom: 1px solid #F0D0E4;
        }
        QTableWidget::item:alternate { background: #FEFBFE; }
    )");
    tl->addWidget(restaurantTable);
    layout->addWidget(tableCard);

    connect(updateBtn, &QPushButton::clicked, this, [this]() {
        RestaurantDialog dlg(university, this);
        if (dlg.exec() == QDialog::Accepted) refreshRestaurantTable();
    });

    contentArea->addWidget(page);
}

void MainWindow::refreshStudentsTable() {
    auto& students = university->getStudents();
    studentsTable->setRowCount(students.size());
    for (int i = 0; i < (int)students.size(); i++) {
        studentsTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(students[i].getId())));
        studentsTable->setItem(i,1,new QTableWidgetItem(QString::fromStdString(students[i].getFullName())));
        studentsTable->setItem(i,2,new QTableWidgetItem(QString::fromStdString(students[i].getEmail())));
        studentsTable->setItem(i,3,new QTableWidgetItem(QString::number(students[i].getAcademicYear())));
        studentsTable->setItem(i,4,new QTableWidgetItem(QString::fromStdString(students[i].getRoomNumber())));
        QString status = students[i].isAssigned() ? "Assigned" : "Unassigned";
        QTableWidgetItem* statusItem = new QTableWidgetItem(status);
        statusItem->setForeground(students[i].isAssigned() ? QColor("#6B2D5E") : QColor("#888"));
        studentsTable->setItem(i,5,statusItem);
        studentsTable->setRowHeight(i, 44);
    }
}

void MainWindow::refreshDormsTable() {
    auto& dorms = university->getDormitories();
    dormsTable->setRowCount(dorms.size());
    for (int i = 0; i < (int)dorms.size(); i++) {
        dormsTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(dorms[i].getName())));
        dormsTable->setItem(i,1,new QTableWidgetItem(QString::fromStdString(dorms[i].getLocation())));
        dormsTable->setItem(i,2,new QTableWidgetItem(QString::number(dorms[i].getRooms().size())));
        dormsTable->setItem(i,3,new QTableWidgetItem(
            QString::number(dorms[i].getTotalOccupancy()) + " / " +
            QString::number(dorms[i].getTotalCapacity())));
        dormsTable->setRowHeight(i, 44);
    }
}

void MainWindow::refreshRoomsTable() {
    roomsTable->setRowCount(0);
    int row = 0;
    for (auto& dorm : university->getDormitories()) {
        for (auto& room : dorm.getRooms()) {
            roomsTable->insertRow(row);
            roomsTable->setItem(row,0,new QTableWidgetItem(QString::fromStdString(dorm.getName())));
            roomsTable->setItem(row,1,new QTableWidgetItem(QString::fromStdString(room.getRoomNumber())));
            roomsTable->setItem(row,2,new QTableWidgetItem(QString::number(room.getCapacity())));
            roomsTable->setItem(row,3,new QTableWidgetItem(
                QString::number(room.getCurrentOccupancy()) + " / " +
                QString::number(room.getCapacity())));
            roomsTable->setRowHeight(row, 44);
            row++;
        }
    }
}

void MainWindow::refreshRestaurantTable() {
    auto& dorms = university->getDormitories();
    restaurantTable->setRowCount(dorms.size());
    for (int i = 0; i < (int)dorms.size(); i++) {
        auto& r = dorms[i].getRestaurant();
        restaurantTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(dorms[i].getName())));
        restaurantTable->setItem(i,1,new QTableWidgetItem(QString::fromStdString(r.getBreakfast())));
        restaurantTable->setItem(i,2,new QTableWidgetItem(QString::fromStdString(r.getLunch())));
        restaurantTable->setItem(i,3,new QTableWidgetItem(QString::fromStdString(r.getDinner())));
        restaurantTable->setRowHeight(i, 44);
    }
}

void MainWindow::setSidebarActive(QPushButton* active) {
    QString activeStyle = R"(
        QPushButton {
            text-align: left; padding: 11px 16px;
            border-radius: 10px; font-size: 13px;
            color: white; background: rgba(255,255,255,0.2);
            border: none; font-weight: bold;
        }
    )";
    QString normalStyle = R"(
        QPushButton {
            text-align: left; padding: 11px 16px;
            border-radius: 10px; font-size: 13px;
            color: #E8C4D8; background: transparent; border: none;
        }
        QPushButton:hover { background: rgba(255,255,255,0.12); color: white; }
    )";
    btnStudents->setStyleSheet(normalStyle);
    btnDorms->setStyleSheet(normalStyle);
    btnRooms->setStyleSheet(normalStyle);
    btnRestaurant->setStyleSheet(normalStyle);
    active->setStyleSheet(activeStyle);
}

void MainWindow::showStudentsPage() {
    contentArea->setCurrentIndex(0);
    refreshStudentsTable();
    setSidebarActive(btnStudents);
}
void MainWindow::showDormsPage() {
    contentArea->setCurrentIndex(1);
    refreshDormsTable();
    setSidebarActive(btnDorms);
}
void MainWindow::showRoomsPage() {
    contentArea->setCurrentIndex(2);
    refreshRoomsTable();
    setSidebarActive(btnRooms);
}
void MainWindow::showRestaurantPage() {
    contentArea->setCurrentIndex(3);
    refreshRestaurantTable();
    setSidebarActive(btnRestaurant);
}

void MainWindow::applyGlobalStyles() {
    setStyleSheet("QMainWindow { background: #F8F0F8; }");
    showStudentsPage();
}