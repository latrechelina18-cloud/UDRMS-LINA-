#ifndef ASSIGNROOMDIALOG_H
#define ASSIGNROOMDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "University.h"

class AssignRoomDialog : public QDialog {
    Q_OBJECT
public:
    explicit AssignRoomDialog(University* university, QWidget* parent = nullptr);

private slots:
    void onDormChanged();
    void onAssignClicked();

private:
    University*  university;
    QComboBox*   studentCombo;
    QComboBox*   dormCombo;
    QComboBox*   roomCombo;
    QPushButton* assignButton;
    QPushButton* cancelButton;
    void setupUI();
    void refreshRoomCombo();
};

#endif