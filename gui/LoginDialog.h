#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);
    QString getEmail() const;
    QString getPassword() const;
    QString getUserType() const;

private slots:
    void onLoginClicked();

private:
    QLabel*      titleLabel;
    QLabel*      subtitleLabel;
    QLineEdit*   emailInput;
    QLineEdit*   passwordInput;
    QComboBox*   userTypeCombo;
    QPushButton* loginButton;
    void setupUI();
};

#endif