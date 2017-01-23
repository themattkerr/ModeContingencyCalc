#ifndef CONTINGENCYDATA_H
#define CONTINGENCYDATA_H

#define CURRENT_VERSION "2.0.0"
#define LONG_DATE_FORMAT "ddd MMMM d, yyyy"
#define FROM_CLOSING_MESSAGE "From Closing"
#define FROM_AO_MESSAGE ""
#define MAX_NUM_CONTINGENCIES 16

#include <QDate>
#include <QString>
#include <QTime>

enum CalculateFrom {

    HARD_DATE           = 0,
    CALC_FROM_AO        = 1,
    CALC_FROM_CLOSING   = 2,

};

class Contingency{

    Contingency();
    ~Contingency();

    QString m_strContingencyTitle;
    QDate   m_dtDateOfContingency;
    QTime   m_tTimeOfDay;
    int     m_nNumOfDays;
    QString m_strReportInfo;

    int     m_nCalcFrom;
    bool    m_bUseBusinessDays;
};

class ContingencyData
{
public:
    ContingencyData() {}

    ~ContingencyData(){}

//-----------------------------------------------------------------------------------------
    void enterAODate(QDate dtAODate);
    void enterClosingDate(QDate dtClosingDate);
    void enterDaysClosing(int nDaysClosing);

    void enterListingBrokerTrustName(QString strListingBrokerTrustName);
    void enterEarnestMoneyAmount(QString strEarnestMoneyAmout);
    void enterMLSNumber(QString strMLSNumber);
    void enterPropertyAddress(QString strPropertyAddress);

    void enterContingencyTitle(QString strContingencyTitle, int nContingencyNum);   
    void enterDateOfContingency(QDate dtDateOfContingency,int nContingencyNum );
    void enterTimeOfDay(QTime TimeOfDay, int nContingencyNum);
    void enterDays(int nDays, int nContingencyNum);

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
    QDate   getDateOfContingency(int nContingencyNum);
    QTime   getTimeOfDay(int nContingencyNum);
    int     getNumOfDays(int nContingencyNum);
    QString getReportInfo(int nContingencyNum);

    int     getCalcFrom(int nContingencyNum);
    bool    getUseBusinessDays(int nContingencyNum);
    
//-----------------------------------------------------------------------------------------
    //void enterContingencyText(QString strContingencyText);

    void sortContingenciesAcending();
    void sortContingenciesDecending();

    void refreshData();

    QString generateReport();
    
private:

    QDate m_dtAODate;
    QDate m_dtClosingDate;
    int m_nDaysClosing;

    QString m_strListingBrokerTrustName;
    QString m_strEarnestMoneyAmout;
    QString m_strMLSNumber;
    QString m_strPropertyAddress;

    Contingency m_Contingency[MAX_NUM_CONTINGENCIES];


    QString setContingencyReportText(QString strContingencyTitle);

   /* QStringList m_strlCustomItems;
    strlCustomItems << "-" << "Final Walk-through" << "Radon Test" << "Condo Docs" <<
                       "Well & Septic" << "Comfort Letter" << "Environmental Test" <<
                       "Attorney Review" << "Home-Owner Insurance" << "Condition Report" <<
                       "Sewer" << "Zoning" << "Survey" << "Loan Rate Lock Expiration";*/
    void calculateDaysFromDate(int nContingencyNum );
};



#endif // CONTINGENCYDATA_H
