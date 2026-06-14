#include "StudentDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFormLayout>

StudentDialog::StudentDialog(University* university, QWidget* parent)
    : QDialog(parent), university(university) {
    setWindowTitle("Add Student");
    setFixedSize(380, 380);
    setupUI();
}

void StudentDialog::setupUI() {
    setStyleSheet(R"(
        QDialog { background: #F8F0F8; }
        QLabel { font-size: 12px; color: #8B4F6F; font-weight: bold; }
        QLineEdit {
            padding: 9px 12px; border: 1px solid #E8C4D8;
            border-radius: 10px; font-size: 13px;
            background: white; color: #3D1A47;
        }
        QLineEdit:focus { border: 1.5px solid #6B2D5E; }
        QPushButton#saveBtn {
            background: #6B2D5E; color: white; border: none;
            border-radius: 20px; padding: 10px 28px;
            font-size: 13px; font-weight: bold;
        }
        QPushButton#saveBtn:hover { background: #8B3D7E; }
        QPushButton#cancelBtn {
            background: white; color: #8B4F6F;
            border: 1px solid #E8C4D8; border-radius: 20px;
            padding: 10px 28px; font-size: 13px;
        }
        QPushButton#cancelBtn:hover { background: #FDF0F8; }
    )");

    QLabel* title = new QLabel("Add New Student");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #6B2D5E;");
    title->setAlignment(Qt::AlignCenter);

    idInput       = new QLineEdit(); idInput->setPlaceholderText("e.g. STU001");
    nameInput     = new QLineEdit(); nameInput->setPlaceholderText("Full name");
    emailInput    = new QLineEdit(); emailInput->setPlaceholderText("email@ensia.edu.dz");
    passwordInput = new QLineEdit(); passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    yearInput     = new QLineEdit(); yearInput->setPlaceholderText("1 to 5");

    saveButton   = new QPushButton("Save");   saveButton->setObjectName("saveBtn");
    cancelButton = new QPushButton("Cancel"); cancelButton->setObjectName("cancelBtn");
    saveButton->setCursor(Qt::PointingHandCursor);
    cancelButton->setCursor(Qt::PointingHandCursor);

    QFormLayout* form = new QFormLayout();
    form->setSpacing(10);
    form->addRow("Student ID:",    idInput);
    form->addRow("Full Name:",     nameInput);
    form->addRow("Email:",         emailInput);
    form->addRow("Password:",      passwordInput);
    form->addRow("Academic Year:", yearInput);

    QHBoxLayout* btns = new QHBoxLayout();
    btns->addWidget(cancelButton);
    btns->addWidget(saveButton);

    QVBoxLayout* main = new QVBoxLayout(this);
    main->setContentsMargins(28, 24, 28, 24);
    main->setSpacing(14);
    main->addWidget(title);
    main->addLayout(form);
    main->addSpacing(6);
    main->addLayout(btns);

    connect(saveButton,   &QPushButton::clicked, this, &StudentDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void StudentDialog::onSaveClicked() {
    if (idInput->text().isEmpty() || nameInput->text().isEmpty() ||
        emailInput->text().isEmpty() || yearInput->text().isEmpty()) {
        QMessageBox::warning(this, "Missing fields", "Please fill in all fields.");
        return;
    }
    Student s(
        idInput->text().toStdString(),
        nameInput->text().toStdString(),
        emailInput->text().toStdString(),
        passwordInput->text().toStdString(),
        yearInput->text().toInt()
    );
    university->addStudent(s);
    QMessageBox::information(this, "Done", "Student added successfully!");
    accept();
}