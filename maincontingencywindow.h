#ifndef MAINCONTINGENCYWINDOW_H
#define MAINCONTINGENCYWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QList>
#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QStringList>

#include "contingencydata.h"

#define COMBOBOX_TITLES  << "-" << "Inspection" << "Financing" << "Appraisal" << "Earnest Money" << "Final Walk-through" << "Radon Test" << "Condo Docs" << "Well & Septic" << "Comfort Letter" << "Environmental Test" << "Attorney Review" << "Home-Owner Insurance" << "Condition Report" << "Sewer" << "Zoning" << "Survey" << "Loan Rate Lock Expiration";
=======
>>>>>>> parent of 514b059... GUI labeling

namespace Ui {
class MainContingencyWindow;
}

class MainContingencyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainContingencyWindow(QWidget *parent = 0);
    ~MainContingencyWindow();

private:
    Ui::MainContingencyWindow *ui;
    void loadTitles();
    void setDefaults();
<<<<<<< HEAD
    void showRows();

    void setupComboBoxQList();
    QList <QComboBox*> m_allComboxes;
    void setupDateEditQList();
    QList <QDateEdit*> m_allDateEdit;
    void setupDaysSpinBoxQList();
    QList <QSpinBox*> m_allSpinBoxes;
    void setupAORadioButtonQList();
    QList <QRadioButton*> m_allAORadioButtons;
    void setupClosingRadioButtonQList();
    QList <QRadioButton*> m_allClosingRadioButtons;
    void setupHardDateRadioButtonQList();
    QList <QRadioButton*> m_allHardDateRadioButtons;
    void setupBusinessDaysCheckboxQList();
    QList <QCheckBox*> m_allBusinessDaysCheckBoxes;


    int     m_nRowsToShow;

=======
>>>>>>> parent of 514b059... GUI labeling
};

#endif // MAINCONTINGENCYWINDOW_H
