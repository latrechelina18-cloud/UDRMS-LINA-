#include "AssignRoomDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

AssignRoomDialog::AssignRoomDialog(University* university, QWidget* parent)
    : QDialog(parent), university(university) {
    setWindowTitle("Assign Student to Room");
    setFixedSize(380, 340);
    setupUI();
}

void AssignRoomDialog::setupUI() {
    setStyleSheet(R"(
        QDialog { background: #F8F0F8; }
        QLabel { font-size: 12px; color: #8B4F6F; font-weight: bold; }
        QComboBox {
            padding: 9px 12px; border: 1px solid #E8C4D8;
            border-radius: 10px; font-size: 13px;
            background: white; color: #3D1A47;
        }
        QComboBox:focus { border: 1.5px solid #6B2D5E; }
        QPushButton#assignBtn {
            background: #6B2D5E; color: white; border: none;
            border-radius: 20px; padding: 10px 28px;
            font-size: 13px; font-weight: bold;
        }
        QPushButton#assignBtn:hover { background: #8B3D7E; }
        QPushButton#cancelBtn {
            background: white; color: #8B4F6F;
            border: 1px solid #E8C4D8; border-radius: 20px;
            padding: 10px 28px; font-size: 13px;
        }
        QPushButton#cancelBtn:hover { background: #FDF0F8; }
    )");

    QLabel* title = new QLabel("Assign Student to Room");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #6B2D5E;");
    title->setAlignment(Qt::AlignCenter);

    studentCombo = new QComboBox();
    dormCombo    = new QComboBox();
    roomCombo    = new QComboBox();

    // Fill students (only unassigned ones)
    for (Student& s : university->getStudents()) {
        if (!s.isAssigned()) {
            studentCombo->addItem(
                QString::fromStdString(s.getFullName() + " (" + s.getId() + ")"),
                QString::fromStdString(s.getId())
            );
        }
    }

    // Fill dormitories
    for (Dormitory& d : university->getDormitories()) {
        dormCombo->addItem(QString::fromStdString(d.getName()));
    }

    assignButton = new QPushButton("Assign");
    assignButton->setObjectName("assignBtn");
    cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("cancelBtn");
    assignButton->setCursor(Qt::PointingHandCursor);
    cancelButton->setCursor(Qt::PointingHandCursor);

    QFormLayout* form = new QFormLayout();
    form->setSpacing(12);
    form->addRow("Student:",   studentCombo);
    form->addRow("Dormitory:", dormCombo);
    form->addRow("Room:",      roomCombo);

    QHBoxLayout* btns = new QHBoxLayout();
    btns->addWidget(cancelButton);
    btns->addWidget(assignButton);

    QVBoxLayout* main = new QVBoxLayout(this);
    main->setContentsMargins(28, 24, 28, 24);
    main->setSpacing(16);
    main->addWidget(title);
    main->addLayout(form);
    main->addSpacing(6);
    main->addLayout(btns);

    connect(dormCombo,     &QComboBox::currentTextChanged, this, &AssignRoomDialog::onDormChanged);
    connect(assignButton,  &QPushButton::clicked, this, &AssignRoomDialog::onAssignClicked);
    connect(cancelButton,  &QPushButton::clicked, this, &QDialog::reject);

    refreshRoomCombo(); // populate rooms for the first dorm
}

void AssignRoomDialog::onDormChanged() {
    refreshRoomCombo();
}

void AssignRoomDialog::refreshRoomCombo() {
    roomCombo->clear();
    if (dormCombo->currentText().isEmpty()) return;

    string dormName = dormCombo->currentText().toStdString();
    Dormitory* dorm = university->findDormitory(dormName);
    if (dorm == nullptr) return;

    for (Room& r : dorm->getRooms()) {
        QString label = QString::fromStdString(r.getRoomNumber()) +
            "  (" + QString::number(r.getCurrentOccupancy()) + "/" +
            QString::number(r.getCapacity()) + ")";
        roomCombo->addItem(label, QString::fromStdString(r.getRoomNumber()));
        // Disable if full
        if (r.isFull()) {
            int idx = roomCombo->count() - 1;
            roomCombo->setItemData(idx, QVariant(0), Qt::UserRole - 1); // visually mark, basic approach
        }
    }
}

void AssignRoomDialog::onAssignClicked() {
    if (studentCombo->count() == 0) {
        QMessageBox::warning(this, "No students", "There are no unassigned students.");
        return;
    }
    if (dormCombo->count() == 0 || roomCombo->count() == 0) {
        QMessageBox::warning(this, "No rooms", "No dormitory/room available. Add one first.");
        return;
    }

    string studentId = studentCombo->currentData().toString().toStdString();
    string dormName   = dormCombo->currentText().toStdString();
    string roomNumber = roomCombo->currentData().toString().toStdString();

    Dormitory* dorm = university->findDormitory(dormName);
    Student* student = university->findStudent(studentId);

    if (dorm == nullptr || student == nullptr) {
        QMessageBox::warning(this, "Error", "Could not find student or dormitory.");
        return;
    }

    try {
        dorm->assignStudent(student, roomNumber);
        QMessageBox::information(this, "Success",
            QString::fromStdString(student->getFullName()) + " has been assigned to room " +
            QString::fromStdString(roomNumber) + " in " + QString::fromStdString(dormName) + "!");
        accept();
    } catch (const exception& e) {
        QMessageBox::warning(this, "Cannot assign", QString::fromStdString(e.what()));
    }
}