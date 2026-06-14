#include "RoomDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

RoomDialog::RoomDialog(University* university, QWidget* parent)
    : QDialog(parent), university(university) {
    setWindowTitle("Add Room");
    setFixedSize(320, 230);
    setupUI();
}

void RoomDialog::setupUI() {
    dormCombo       = new QComboBox();
    roomNumberInput = new QLineEdit();
    capacityInput   = new QLineEdit();

    for (auto& d : university->getDormitories())
        dormCombo->addItem(QString::fromStdString(d.getName()));

    roomNumberInput->setPlaceholderText("e.g. 101");
    capacityInput->setPlaceholderText("e.g. 2");

    saveButton   = new QPushButton("Save");
    cancelButton = new QPushButton("Cancel");

    QFormLayout* form = new QFormLayout();
    form->addRow("Dormitory:", dormCombo);
    form->addRow("Room No.:", roomNumberInput);
    form->addRow("Capacity:", capacityInput);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(cancelButton);
    btnLayout->addWidget(saveButton);

    QVBoxLayout* main = new QVBoxLayout(this);
    main->addLayout(form);
    main->addSpacing(10);
    main->addLayout(btnLayout);

    connect(saveButton,   &QPushButton::clicked, this, &RoomDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void RoomDialog::onSaveClicked() {
    if (dormCombo->count() == 0) {
        QMessageBox::warning(this, "Error", "No dormitories exist yet. Add a dormitory first.");
        return;
    }
    if (roomNumberInput->text().isEmpty() || capacityInput->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all fields.");
        return;
    }
    string dormName = dormCombo->currentText().toStdString();
    Dormitory* dorm = university->findDormitory(dormName);
    if (dorm) {
        dorm->addRoom(roomNumberInput->text().toStdString(),
                      capacityInput->text().toInt());
        QMessageBox::information(this, "Success", "Room added!");
        accept();
    }
}