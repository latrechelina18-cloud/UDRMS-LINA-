#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "University.h"

class SignUpDialog : public QDialog {
    Q_OBJECT
public:
    explicit SignUpDialog(University* university, QWidget* parent = nullptr);

private slots:
    void onSignUpClicked();

private:
    University*  university;
    QLineEdit*   idInput;
    QLineEdit*   nameInput;
    QLineEdit*   emailInput;
    QLineEdit*   passwordInput;
    QLineEdit*   yearInput;
    QPushButton* signUpButton;
    QPushButton* backButton;
    void setupUI();
};

#endif