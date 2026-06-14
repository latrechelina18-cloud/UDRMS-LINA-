#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "University.h"

class StudentDialog : public QDialog {
    Q_OBJECT
public:
    explicit StudentDialog(University* university, QWidget* parent = nullptr);

private slots:
    void onSaveClicked();

private:
    University*  university;
    QLineEdit*   idInput;
    QLineEdit*   nameInput;
    QLineEdit*   emailInput;
    QLineEdit*   passwordInput;
    QLineEdit*   yearInput;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    void setupUI();
};

#endif