#ifndef RESTAURANTDIALOG_H
#define RESTAURANTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include "University.h"

class RestaurantDialog : public QDialog {
    Q_OBJECT
public:
    explicit RestaurantDialog(University* university, QWidget* parent = nullptr);
private slots:
    void onSaveClicked();
private:
    University*  university;
    QComboBox*   dormCombo;
    QLineEdit*   breakfastInput;
    QLineEdit*   lunchInput;
    QLineEdit*   dinnerInput;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    void setupUI();
};

#endif