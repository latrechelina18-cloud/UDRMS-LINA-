#include "SignUpDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QLabel>
SignUpDialog::SignUpDialog(University* university, QWidget* parent)
    : QDialog(parent), university(university) {
    setWindowTitle("Student Sign Up");
    setFixedSize(380, 420);
    setupUI();
}

void SignUpDialog::setupUI() {
    setStyleSheet(R"(
        QDialog { background: #F8F0F8; }
        QLabel { font-size: 12px; color: #8B4F6F; font-weight: bold; }
        QLineEdit {
            padding: 9px 12px; border: 1px solid #E8C4D8;
            border-radius: 10px; font-size: 13px;
            background: white; color: #3D1A47;
        }
        QLineEdit:focus { border: 1.5px solid #6B2D5E; }
        QPushButton#signUpBtn {
            background: #6B2D5E; color: white; border: none;
            border-radius: 20px; padding: 11px 28px;
            font-size: 13px; font-weight: bold;
        }
        QPushButton#signUpBtn:hover { background: #8B3D7E; }
        QPushButton#backBtn {
            background: white; color: #8B4F6F;
            border: 1px solid #E8C4D8; border-radius: 20px;
            padding: 11px 28px; font-size: 13px;
        }
        QPushButton#backBtn:hover { background: #FDF0F8; }
    )");

    QLabel* title = new QLabel("Create Student Account");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #6B2D5E;");
    title->setAlignment(Qt::AlignCenter);

    idInput       = new QLineEdit(); idInput->setPlaceholderText("e.g. STU010");
    nameInput     = new QLineEdit(); nameInput->setPlaceholderText("Full name");
    emailInput    = new QLineEdit(); emailInput->setPlaceholderText("email@ensia.edu.dz");
    passwordInput = new QLineEdit(); passwordInput->setPlaceholderText("Choose a password");
    passwordInput->setEchoMode(QLineEdit::Password);
    yearInput     = new QLineEdit(); yearInput->setPlaceholderText("1 to 5");

    signUpButton = new QPushButton("Create Account");
    signUpButton->setObjectName("signUpBtn");
    backButton = new QPushButton("Back to Login");
    backButton->setObjectName("backBtn");
    signUpButton->setCursor(Qt::PointingHandCursor);
    backButton->setCursor(Qt::PointingHandCursor);

    QFormLayout* form = new QFormLayout();
    form->setSpacing(10);
    form->addRow("Student ID:",    idInput);
    form->addRow("Full Name:",     nameInput);
    form->addRow("Email:",         emailInput);
    form->addRow("Password:",      passwordInput);
    form->addRow("Academic Year:", yearInput);

    QVBoxLayout* btns = new QVBoxLayout();
    btns->addWidget(signUpButton);
    btns->addWidget(backButton);

    QVBoxLayout* main = new QVBoxLayout(this);
    main->setContentsMargins(28, 24, 28, 24);
    main->setSpacing(14);
    main->addWidget(title);
    main->addLayout(form);
    main->addSpacing(6);
    main->addLayout(btns);

    connect(signUpButton, &QPushButton::clicked, this, &SignUpDialog::onSignUpClicked);
    connect(backButton,   &QPushButton::clicked, this, &QDialog::reject);
}

void SignUpDialog::onSignUpClicked() {
    if (idInput->text().isEmpty() || nameInput->text().isEmpty() ||
        emailInput->text().isEmpty() || passwordInput->text().isEmpty() ||
        yearInput->text().isEmpty()) {
        QMessageBox::warning(this, "Missing fields", "Please fill in all fields.");
        return;
    }

    // Check email doesn't already exist
    if (university->findStudentByEmail(emailInput->text().toStdString()) != nullptr) {
        QMessageBox::warning(this, "Account exists", "An account with this email already exists.");
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
    QMessageBox::information(this, "Welcome!", "Account created! You can now log in.");
    accept();
}