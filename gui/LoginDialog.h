#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include "University.h"

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(University* university, QWidget* parent = nullptr);
    QString getEmail() const;
    QString getUserType() const;
    Student* getLoggedInStudent() const;

private slots:
    void onLoginClicked();
    void onSignUpClicked();

private:
    University*  university;
    Student*     loggedInStudent = nullptr;

    QLabel*      titleLabel;
    QLabel*      subtitleLabel;
    QLineEdit*   emailInput;
    QLineEdit*   passwordInput;
    QComboBox*   userTypeCombo;
    QPushButton* loginButton;
    QPushButton* signUpLink;
    void setupUI();
};

#endif