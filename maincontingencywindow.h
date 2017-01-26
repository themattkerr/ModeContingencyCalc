#ifndef MAINCONTINGENCYWINDOW_H
#define MAINCONTINGENCYWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QStringList>
#include "contingencydata.h"

#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QRadioButton>
#include <QCheckBox>

namespace Ui {
class MainContingencyWindow;
}

class MainContingencyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainContingencyWindow(QWidget *parent = 0);
    ~MainContingencyWindow();

private slots:
    void on_pushButton_Show_5_More_clicked();

    void on_pushButton_Show_5_Fewer_clicked();

private:
    Ui::MainContingencyWindow *ui;
    void loadTitles();
    void setDefaults();
    void showRows();
    //void setupComboBoxQList();
    //QList <QComboBox*> m_allComboxes;
    int     m_nRowsToShow;

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

};

#endif // MAINCONTINGENCYWINDOW_H
