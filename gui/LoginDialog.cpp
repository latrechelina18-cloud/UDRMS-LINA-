#include "LoginDialog.h"
#include "SignUpDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

// Hardcoded staff/admin accounts (realistic: staff accounts aren't self-service)
struct StaffAccount { QString email, password, role; };
static QVector<StaffAccount> staffAccounts = {
    {"admin@ensia.edu.dz",   "admin123",   "System Administrator"},
    {"dormadmin@ensia.edu.dz", "dorm123",  "Dorm Administrator"},
    {"chef@ensia.edu.dz",    "rest123",    "Restaurant Staff"}
};

LoginDialog::LoginDialog(University* university, QWidget* parent)
    : QDialog(parent), university(university) {
    setWindowTitle("UDRMS - Login");
    setFixedSize(420, 540);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setupUI();
}

void LoginDialog::setupUI() {
    setStyleSheet(R"(
        QDialog { background-color: #F8F0F8; }
        QLabel#title { font-size: 22px; font-weight: bold; color: #6B2D5E; }
        QLabel#subtitle { font-size: 12px; color: #A06080; letter-spacing: 1px; }
        QLabel#fieldLabel { font-size: 12px; color: #8B4F6F; font-weight: bold; }
        QLineEdit, QComboBox {
            padding: 10px 14px; border: 1px solid #E8C4D8;
            border-radius: 10px; font-size: 13px;
            background: white; color: #3D1A47; min-height: 20px;
        }
        QLineEdit:focus, QComboBox:focus { border: 1.5px solid #6B2D5E; }
        QPushButton#loginBtn {
            background-color: #6B2D5E; color: white; border: none;
            border-radius: 24px; font-size: 14px; font-weight: bold;
            padding: 13px; margin-top: 8px;
        }
        QPushButton#loginBtn:hover { background-color: #8B3D7E; }
        QPushButton#signUpLink {
            background: transparent; color: #6B2D5E;
            border: none; font-size: 12px; text-decoration: underline;
        }
    )");

    QVBoxLayout* outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);

    QWidget* topStrip = new QWidget();
    topStrip->setFixedHeight(8);
    topStrip->setStyleSheet("background-color: #6B2D5E;");
    outer->addWidget(topStrip);

    QWidget* card = new QWidget();
    card->setStyleSheet("background: white;");
    QVBoxLayout* layout = new QVBoxLayout(card);
    layout->setContentsMargins(44, 32, 44, 36);
    layout->setSpacing(6);

    QLabel* ensia = new QLabel("ENSIA 2025–2026");
    ensia->setObjectName("subtitle");
    ensia->setAlignment(Qt::AlignCenter);

    titleLabel = new QLabel("Welcome back");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);

    subtitleLabel = new QLabel("University Dormitory & Restaurant System");
    subtitleLabel->setObjectName("subtitle");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setWordWrap(true);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color: #F0D0E4; margin: 10px 0;");

    QLabel* roleLabel = new QLabel("Login as");
    roleLabel->setObjectName("fieldLabel");
    userTypeCombo = new QComboBox();
    userTypeCombo->addItem("Student");
    userTypeCombo->addItem("Dorm Administrator");
    userTypeCombo->addItem("Restaurant Staff");
    userTypeCombo->addItem("System Administrator");

    QLabel* emailLabel = new QLabel("Email");
    emailLabel->setObjectName("fieldLabel");
    emailInput = new QLineEdit();
    emailInput->setPlaceholderText("your@ensia.edu.dz");

    QLabel* passLabel = new QLabel("Password");
    passLabel->setObjectName("fieldLabel");
    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("••••••••");
    passwordInput->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Sign in");
    loginButton->setObjectName("loginBtn");
    loginButton->setCursor(Qt::PointingHandCursor);

    signUpLink = new QPushButton("New student? Create an account");
    signUpLink->setObjectName("signUpLink");
    signUpLink->setCursor(Qt::PointingHandCursor);

    layout->addWidget(ensia);
    layout->addSpacing(4);
    layout->addWidget(titleLabel);
    layout->addWidget(subtitleLabel);
    layout->addWidget(line);
    layout->addWidget(roleLabel);
    layout->addWidget(userTypeCombo);
    layout->addSpacing(6);
    layout->addWidget(emailLabel);
    layout->addWidget(emailInput);
    layout->addSpacing(6);
    layout->addWidget(passLabel);
    layout->addWidget(passwordInput);
    layout->addSpacing(8);
    layout->addWidget(loginButton);
    layout->addSpacing(4);
    layout->addWidget(signUpLink, 0, Qt::AlignCenter);

    outer->addWidget(card);

    QWidget* bottomStrip = new QWidget();
    bottomStrip->setFixedHeight(8);
    bottomStrip->setStyleSheet("background-color: #E8A0BF;");
    outer->addWidget(bottomStrip);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(signUpLink,  &QPushButton::clicked, this, &LoginDialog::onSignUpClicked);
}

void LoginDialog::onSignUpClicked() {
    SignUpDialog dlg(university, this);
    dlg.exec(); // After signing up, they come back to login screen
}

void LoginDialog::onLoginClicked() {
    QString email = emailInput->text();
    QString password = passwordInput->text();
    QString role = userTypeCombo->currentText();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Missing fields", "Please enter your email and password.");
        return;
    }

    if (role == "Student") {
        Student* s = university->findStudentByEmail(email.toStdString());
        if (s == nullptr || QString::fromStdString(s->getPassword()) != password) {
            QMessageBox::warning(this, "Login failed", "Incorrect email or password.");
            return;
        }
        loggedInStudent = s;
        accept();
        return;
    }

    // Staff / Admin accounts
    for (const StaffAccount& acc : staffAccounts) {
        if (acc.role == role && acc.email == email && acc.password == password) {
            accept();
            return;
        }
    }

    QMessageBox::warning(this, "Login failed", "Incorrect email or password for this role.");
}

QString LoginDialog::getEmail() const     { return emailInput->text(); }
QString LoginDialog::getUserType() const  { return userTypeCombo->currentText(); }
Student* LoginDialog::getLoggedInStudent() const { return loggedInStudent; }