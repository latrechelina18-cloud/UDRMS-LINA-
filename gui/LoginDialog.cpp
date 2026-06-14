#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("UDRMS - Login");
    setFixedSize(420, 500);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setupUI();
}

void LoginDialog::setupUI() {
    setStyleSheet(R"(
        QDialog {
            background-color: #F8F0F8;
        }
        QLabel#title {
            font-size: 22px;
            font-weight: bold;
            color: #6B2D5E;
        }
        QLabel#subtitle {
            font-size: 12px;
            color: #A06080;
            letter-spacing: 1px;
        }
        QLabel#fieldLabel {
            font-size: 12px;
            color: #8B4F6F;
            font-weight: bold;
        }
        QLineEdit, QComboBox {
            padding: 10px 14px;
            border: 1px solid #E8C4D8;
            border-radius: 10px;
            font-size: 13px;
            background: white;
            color: #3D1A47;
            min-height: 20px;
        }
        QLineEdit:focus, QComboBox:focus {
            border: 1.5px solid #6B2D5E;
        }
        QComboBox::drop-down {
            border: none;
            padding-right: 10px;
        }
        QPushButton#loginBtn {
            background-color: #6B2D5E;
            color: white;
            border: none;
            border-radius: 24px;
            font-size: 14px;
            font-weight: bold;
            padding: 13px;
            margin-top: 8px;
        }
        QPushButton#loginBtn:hover {
            background-color: #8B3D7E;
        }
        QPushButton#loginBtn:pressed {
            background-color: #4A1D3E;
        }
    )");

    QVBoxLayout* outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);

    // Top decorative strip
    QWidget* topStrip = new QWidget();
    topStrip->setFixedHeight(8);
    topStrip->setStyleSheet("background-color: #6B2D5E; border-radius: 0px;");
    outer->addWidget(topStrip);

    // Card
    QWidget* card = new QWidget();
    card->setStyleSheet("background: white; border-radius: 0px;");
    QVBoxLayout* layout = new QVBoxLayout(card);
    layout->setContentsMargins(44, 36, 44, 44);
    layout->setSpacing(6);

    // Header
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

    // Divider
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color: #F0D0E4; margin: 12px 0;");

    // Fields
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

    layout->addWidget(ensia);
    layout->addSpacing(4);
    layout->addWidget(titleLabel);
    layout->addWidget(subtitleLabel);
    layout->addWidget(line);
    layout->addSpacing(4);
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

    outer->addWidget(card);

    // Bottom strip
    QWidget* bottomStrip = new QWidget();
    bottomStrip->setFixedHeight(8);
    bottomStrip->setStyleSheet("background-color: #E8A0BF;");
    outer->addWidget(bottomStrip);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
}

void LoginDialog::onLoginClicked() {
    if (emailInput->text().isEmpty() || passwordInput->text().isEmpty()) {
        QMessageBox::warning(this, "Missing fields", "Please enter your email and password.");
        return;
    }
    accept();
}

QString LoginDialog::getEmail() const    { return emailInput->text(); }
QString LoginDialog::getPassword() const { return passwordInput->text(); }
QString LoginDialog::getUserType() const { return userTypeCombo->currentText(); }