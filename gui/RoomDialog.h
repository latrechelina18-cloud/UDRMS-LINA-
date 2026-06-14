#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include "University.h"

class RoomDialog : public QDialog {
    Q_OBJECT
public:
    explicit RoomDialog(University* university, QWidget* parent = nullptr);
private slots:
    void onSaveClicked();
private:
    University*  university;
    QComboBox*   dormCombo;
    QLineEdit*   roomNumberInput;
    QLineEdit*   capacityInput;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    void setupUI();
};

#endif