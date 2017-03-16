#ifndef CONTINGENCYDATA_H
#define CONTINGENCYDATA_H

#define CURRENT_VERSION "2.0.0"
#define LONG_DATE_FORMAT "dddd  MMMM d, yyyy"
#define FROM_CLOSING_MESSAGE "From Closing"
#define FROM_AO_MESSAGE ""

#define MAX_NUM_CONTINGENCIES 20

#include <QDate>
#include <QString>
#include <QTime>
#include "textforcontingencies.h"

#define HARD_DATE_TEXT "Hard Date"
#define CALC_FROM_AO_TEXT "Days From AO"
#define CALC_FROM_CLOSING_TEXT "Days To Closing"
#define CALC_FROM_CONTINGENCY_TEXT "Tied to"

enum CalculateFrom {

    CALC_FROM_AO        = 0,
    CALC_FROM_CLOSING   = 1,
    HARD_DATE           = 2,
    OTHER_CONT          = 3,
};

class Contingency{
public:

    Contingency();
    ~Contingency();

    QString m_strContingencyTitle;
    int     m_nCalcFrom;
    bool    m_bUseBusinessDays;
    QString m_strBusinessDayReasons;
    QDate   m_dtDateOfContingency;
    int     m_nNumOfDays;
    QString m_strReportInfoBuyer;
    QString m_strReportInfoSeller;
    QString m_strCustomText;
    QString m_strDependantContingecyTitle;
};

class ContingencyData
{
public:
    ContingencyData();
    ~ContingencyData();

//-----------------------------------------------------------------------------------------
    void enterAODate(QDate dtAODate);
    void enterClosingDate(QDate dtClosingDate);
    void enterDaysClosing(int nDaysClosing);

    void enterListingBrokerTrustName(QString strListingBrokerTrustName);
    void enterEarnestMoneyAmount(QString strEarnestMoneyAmout);
    void enterMLSNumber(QString strMLSNumber);
    void enterPropertyAddress(QString strPropertyAddress);

    void enterContingencyTitle(QString strContingencyTitle, int nContingencyNum);
    void enterCustomText(QString strCustomText, int nContingencyNum);
    void enterDateOfContingency(QDate dtDateOfContingency,int nContingencyNum );
    void enterTimeOfDay(QTime TimeOfDay, int nContingencyNum);
    void enterDays(int nDays, int nContingencyNum);

    void enterDependantContingencyTitle(QString DepContTitle, int nContingencyNum);

    void setCalcType(int nCalcType, int nContingencyNum);
    void setUseBusinessDays(bool BusinessDays, int nContingencyNum);



//-----------------------------------------------------------------------------------------   


    QDate   getAODate();
    QDate   getClosingDate();
    int     getDaysClosing();

    QString getListingBrokerTrustName();
    QString getEarnestMoneyAmout();
    QString getMLSNumber();
    QString getPropertyAddress();

    QString getContingencyTitle(int nContingencyNum);
    QString getCustomText(int nContingencyNum);
    QDate   getDateOfContingency(int nContingencyNum);
    QTime   getTimeOfDay(int nContingencyNum);
    int     getNumOfDays(int nContingencyNum);
    QString getReportInfoBuyer(int nContingencyNum);
    QString getReportInfoSeller(int nContingencyNum);

    QString getDependantContingencyTitle(int nContingencyNum);

    int     getCalcFrom(int nContingencyNum);
    bool    getUseBusinessDays(int nContingencyNum);
    
//-----------------------------------------------------------------------------------------


    void setDefaults();
    void resetContingency(int nContingencyNum);
    void sortContingenciesAcending();
    void sortContingenciesDecending();
    
private:


    QDate m_dtAODate;
    QDate m_dtClosingDate;
    int m_nDaysClosing;

    QString m_strListingBrokerTrustName;
    QString m_strEarnestMoneyAmout;
    QString m_strMLSNumber;
    QString m_strPropertyAddress;

    Contingency m_Contingency[MAX_NUM_CONTINGENCIES];


    void setContingencyReportText(int nContingencyNum);


    void calculateDaysFromDate(int nContingencyNum );
    void calculateDateFromDays(int nContingencyNum , QString &strReasons);

    void refreshData();



};



#endif // CONTINGENCYDATA_H
