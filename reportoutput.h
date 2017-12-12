#ifndef REPORTOUTPUT_H
#define REPORTOUTPUT_H

#include <QDialog>
#include <QString>
#include <QFont>
#include "contingencydata.h"

#define ADDITIONALCONTINGENCIES 2

enum reportTargetAudience {
    BUYERS          = 1,
    SELLERS         = 2,
    MILESTONES_ONLY = 3,
};

namespace Ui {
class ReportOutput;
}

class ReportOutput : public QDialog
{
    Q_OBJECT

public:
    explicit ReportOutput(QWidget *parent = 0, ContingencyData *contData = 0, int *nReportType = 0);
    ~ReportOutput();

private slots:
    void on_pushButton_Close_clicked();
    void on_radioButton_Buyers_clicked();
    void on_radioButton_Sellers_clicked();
    void on_radioButton_Milestones_clicked();

private:
    Ui::ReportOutput *ui;

    ContingencyData m_OutData;

    Contingency m_contOutputArray[MAX_NUM_CONTINGENCIES+2];
    QString m_strOutputText;
    int *m_nReportType = 0;

    void setupGUI();
    void copyContingenciesToArray();
    void sortAscending();
    void shiftArrayItems(int nStartIndex, int nNumOfItemToBeMoved);
    void generateText();
    QString AddBlankLine(QString strInputText);

};

#endif // REPORTOUTPUT_H
