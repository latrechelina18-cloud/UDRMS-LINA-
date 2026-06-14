#ifndef DORMDIALOG_H
#define DORMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "University.h"

class DormDialog : public QDialog {
    Q_OBJECT
public:
    explicit DormDialog(University* university, QWidget* parent = nullptr);

private slots:
    void onSaveClicked();

private:
    University*  university;
    QLineEdit*   nameInput;
    QLineEdit*   locationInput;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    void setupUI();
};

#endif