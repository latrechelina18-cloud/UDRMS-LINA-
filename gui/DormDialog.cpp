#include "DormDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

DormDialog::DormDialog(University* university, QWidget* parent)
    : QDialog(parent), university(university) {
    setWindowTitle("Add Dormitory");
    setFixedSize(320, 200);
    setupUI();
}

void DormDialog::setupUI() {
    nameInput     = new QLineEdit();
    locationInput = new QLineEdit();
    nameInput->setPlaceholderText("e.g. Dorm A");
    locationInput->setPlaceholderText("e.g. North Campus");

    saveButton   = new QPushButton("Save");
    cancelButton = new QPushButton("Cancel");

    QFormLayout* form = new QFormLayout();
    form->addRow("Name:",     nameInput);
    form->addRow("Location:", locationInput);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(cancelButton);
    btnLayout->addWidget(saveButton);

    QVBoxLayout* main = new QVBoxLayout(this);
    main->addLayout(form);
    main->addSpacing(10);
    main->addLayout(btnLayout);

    connect(saveButton,   &QPushButton::clicked, this, &DormDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void DormDialog::onSaveClicked() {
    if (nameInput->text().isEmpty() || locationInput->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all fields.");
        return;
    }
    Dormitory d(nameInput->text().toStdString(),
                locationInput->text().toStdString());
    university->addDormitory(d);
    QMessageBox::information(this, "Success", "Dormitory added!");
    accept();
}