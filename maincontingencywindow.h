#ifndef MAINCONTINGENCYWINDOW_H
#define MAINCONTINGENCYWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QStringList>
#include "contingencydata.h"
#include "textforcontingencies.h"

#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>
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

    void on_dateEditAODate_userDateChanged(const QDate &date);

    void on_pushButtonSetToToday_clicked();

    void on_spinBoxDaysToClosing_valueChanged(int arg1);

    void on_dateEditClosingDate_userDateChanged(const QDate &date);

    void on_lineEditPropertyAddress_editingFinished();

    void on_lineEditMLSNum_editingFinished();

    void on_lineEditEarnestMoney_editingFinished();

    void on_lineEditListingBrokerTrustName_editingFinished();

    void on_cont1TitleComboBox_activated(const QString &arg1);

    void on_cont2TitleComboBox_activated(const QString &arg1);

    void on_cont3TitleComboBox_activated(const QString &arg1);

    void on_cont4TitleComboBox_activated(const QString &arg1);

    void on_cont5TitleComboBox_activated(const QString &arg1);

    void on_cont6TitleComboBox_activated(const QString &arg1);

    void on_cont7TitleComboBox_activated(const QString &arg1);

    void on_cont8TitleComboBox_activated(const QString &arg1);

    void on_cont9TitleComboBox_activated(const QString &arg1);

    void on_cont10TitleComboBox_activated(const QString &arg1);

    void on_cont11TitleComboBox_activated(const QString &arg1);

    void on_cont12TitleComboBox_activated(const QString &arg1);

    void on_cont13TitleComboBox_activated(const QString &arg1);

    void on_cont14TitleComboBox_activated(const QString &arg1);

    void on_cont15TitleComboBox_activated(const QString &arg1);

    void on_cont16TitleComboBox_activated(const QString &arg1);

    void on_cont17TitleComboBox_activated(const QString &arg1);

    void on_cont18TitleComboBox_activated(const QString &arg1);

    void on_cont19TitleComboBox_activated(const QString &arg1);

    void on_cont20TitleComboBox_activated(const QString &arg1);

    void on_cont1dateEdit_userDateChanged(const QDate &date);

    void on_cont2dateEdit_userDateChanged(const QDate &date);

    void on_cont3dateEdit_userDateChanged(const QDate &date);

    void on_cont4dateEdit_userDateChanged(const QDate &date);

    void on_cont5dateEdit_userDateChanged(const QDate &date);

    void on_cont6dateEdit_userDateChanged(const QDate &date);

    void on_cont7dateEdit_userDateChanged(const QDate &date);

    void on_cont8dateEdit_userDateChanged(const QDate &date);

    void on_cont9dateEdit_userDateChanged(const QDate &date);

    void on_cont10dateEdit_userDateChanged(const QDate &date);

    void on_cont11dateEdit_userDateChanged(const QDate &date);

    void on_cont12dateEdit_userDateChanged(const QDate &date);

    void on_cont13dateEdit_userDateChanged(const QDate &date);

    void on_cont14dateEdit_userDateChanged(const QDate &date);

    void on_cont15dateEdit_userDateChanged(const QDate &date);

    void on_cont16dateEdit_userDateChanged(const QDate &date);

    void on_cont17dateEdit_userDateChanged(const QDate &date);

    void on_cont18dateEdit_userDateChanged(const QDate &date);

    void on_cont19dateEdit_userDateChanged(const QDate &date);

    void on_cont20dateEdit_userDateChanged(const QDate &date);

    void on_cont6DaysSpinBox_valueChanged(int arg1);

    void on_cont1DaysSpinBox_valueChanged(int arg1);

    void on_cont2DaysSpinBox_valueChanged(int arg1);

    void on_cont3DaysSpinBox_valueChanged(int arg1);

    void on_cont4DaysSpinBox_valueChanged(int arg1);

    void on_cont5DaysSpinBox_valueChanged(int arg1);

    void on_cont7DaysSpinBox_valueChanged(int arg1);

    void on_cont8DaysSpinBox_valueChanged(int arg1);

    void on_cont9DaysSpinBox_valueChanged(int arg1);

    void on_cont10DaysSpinBox_valueChanged(int arg1);

    void on_cont11DaysSpinBox_valueChanged(int arg1);

    void on_cont12DaysSpinBox_valueChanged(int arg1);

    void on_cont13DaysSpinBox_valueChanged(int arg1);

    void on_cont14DaysSpinBox_valueChanged(int arg1);

    void on_cont15DaysSpinBox_valueChanged(int arg1);

    void on_cont16DaysSpinBox_valueChanged(int arg1);

    void on_cont17DaysSpinBox_valueChanged(int arg1);

    void on_cont18DaysSpinBox_valueChanged(int arg1);

    void on_cont19DaysSpinBox_valueChanged(int arg1);

    void on_cont20DaysSpinBox_valueChanged(int arg1);

private:

    Ui::MainContingencyWindow *ui;
    ContingencyData m_contData;
    void setupGUI();
    void hideCustomLineEdits();
    void loadTitles();
    void loadDefaults();
    void showRows();
    void refreshFields();
    void loadDateLabels();



    void setupComboBoxQList();
    QList <QComboBox*> m_allComboxes;
    void setupCustomLineEditQList();
    QList <QLineEdit*> m_allCustomLineEdits;
    void setupDateEditQList();
    QList <QDateEdit*> m_allDateEdit;
    void setupDateLabelQList();
    QList <QLabel*> m_allDateLabels;
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
    //Contingency m_contData;
};

#endif // MAINCONTINGENCYWINDOW_H
