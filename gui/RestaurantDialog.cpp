#include "RestaurantDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

RestaurantDialog::RestaurantDialog(University* university, QWidget* parent)
    : QDialog(parent), university(university) {
    setWindowTitle("Update Restaurant Menu");
    setFixedSize(350, 250);
    setupUI();
}

void RestaurantDialog::setupUI() {
    dormCombo      = new QComboBox();
    breakfastInput = new QLineEdit();
    lunchInput     = new QLineEdit();
    dinnerInput    = new QLineEdit();

    for (auto& d : university->getDormitories())
        dormCombo->addItem(QString::fromStdString(d.getName()));

    breakfastInput->setPlaceholderText("e.g. Bread, eggs, juice");
    lunchInput->setPlaceholderText("e.g. Rice, chicken, salad");
    dinnerInput->setPlaceholderText("e.g. Soup, pasta");

    saveButton   = new QPushButton("Update Menu");
    cancelButton = new QPushButton("Cancel");

    QFormLayout* form = new QFormLayout();
    form->addRow("Dormitory:",  dormCombo);
    form->addRow("Breakfast:",  breakfastInput);
    form->addRow("Lunch:",      lunchInput);
    form->addRow("Dinner:",     dinnerInput);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(cancelButton);
    btnLayout->addWidget(saveButton);

    QVBoxLayout* main = new QVBoxLayout(this);
    main->addLayout(form);
    main->addSpacing(10);
    main->addLayout(btnLayout);

    connect(saveButton,   &QPushButton::clicked, this, &RestaurantDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void RestaurantDialog::onSaveClicked() {
    if (dormCombo->count() == 0) {
        QMessageBox::warning(this, "Error", "No dormitories exist yet.");
        return;
    }
    string dormName = dormCombo->currentText().toStdString();
    Dormitory* dorm = university->findDormitory(dormName);
    if (dorm) {
        dorm->getRestaurant().updateMenu(
            breakfastInput->text().toStdString(),
            lunchInput->text().toStdString(),
            dinnerInput->text().toStdString()
        );
        QMessageBox::information(this, "Success", "Menu updated!");
        accept();
    }
}