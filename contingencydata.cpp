
#include <QDate>
#include <QString>
#include <QTime>
#include "contingencydata.h"
#include "mattcalculations.h"

ContingencyData::ContingencyData() {}

ContingencyData::~ContingencyData(){}

//----Public Enter Functions-------------------------------------------------------------------------------------
void ContingencyData::enterAODate(QDate dtAODate)
{
    m_dtAODate = dtAODate;
    m_nDaysClosing = m_dtAODate.daysTo(m_dtClosingDate);
    refreshData();
}
void ContingencyData::enterClosingDate(QDate dtClosingDate)
{
    m_dtClosingDate = dtClosingDate;
    m_nDaysClosing = m_dtAODate.daysTo(m_dtClosingDate);
    refreshData();
}
void ContingencyData::enterDaysClosing(int nDaysClosing)
{
    m_nDaysClosing = nDaysClosing;
    m_dtClosingDate = m_dtAODate.addDays(m_nDaysClosing);
    refreshData();
}
void ContingencyData::enterListingBrokerTrustName(QString strListingBrokerTrustName)
{
    m_strListingBrokerTrustName = strListingBrokerTrustName;
}
void ContingencyData::enterEarnestMoneyAmount(QString strEarnestMoneyAmout)
{
    double = dTemp;
    dTemp = usDollarsStringToDouble(strEarnestMoneyAmout);
    m_strEarnestMoneyAmout = doubleToCurrency(dTemp, US_DOLLARS);
}
void ContingencyData::enterMLSNumber(QString strMLSNumber)
{
    m_strMLSNumber = strMLSNumber;
}
void ContingencyData::enterPropertyAddress(QString strPropertyAddress)
{
    m_strPropertyAddress = strPropertyAddress;
}

void ContingencyData::enterContingencyTitle(QString strContingencyTitle, int nContingencyNum)
{
    m_Contingency[nContingencyNum].m_strContingencyTitle.clear();
    m_Contingency[nContingencyNum].m_strReportInfo.clear();
    m_Contingency[nContingencyNum].m_strContingencyTitle = strContingencyTitle;
    //m_Contingency[nContingencyNum].m_strReportInfo = setContingencyReportText(strContingencyTitle);
    refreshData();
}

void ContingencyData::enterDateOfContingency(QDate dtDateOfContingency,int nContingencyNum )
{
    m_Contingency[nContingencyNum].m_dtDateOfContingency = dtDateOfContingency;
    calculateDaysFromDate(nContingencyNum );
}

void ContingencyData::enterTimeOfDay(QTime TimeOfDay, int nContingencyNum);
void ContingencyData::enterDays(int nDays, int nContingencyNum);

void ContingencyData::setCalcType(int nCalcType, int nContingencyNum);
void ContingencyData::setUseBusinessDays(bool BusinessDays, int nContingencyNum);

//-----Public Get Functions------------------------------------------------------------------------------------
QDate   ContingencyData::getAODate();
QDate   ContingencyData::getClosingDate();
int     ContingencyData::getDaysClosing();

QString ContingencyData::getListingBrokerTrustName();
QString ContingencyData::getEarnestMoneyAmout();
QString ContingencyData::getMLSNumber();
QString ContingencyData::getPropertyAddress();

QString ContingencyData::getContingencyTitle(int nContingencyNum);
QDate   ContingencyData::getDateOfContingency(int nContingencyNum);
QTime   ContingencyData::getTimeOfDay(int nContingencyNum);
int     ContingencyData::getNumOfDays(int nContingencyNum);
QString ContingencyData::getReportInfo(int nContingencyNum);

int     ContingencyData::getCalcFrom(int nContingencyNum);
bool    ContingencyData::getUseBusinessDays(int nContingencyNum);

//----Private Fucntions-------------------------------------------------------------------------------------
QString ContingencyData::setContingencyReportText(QString strContingencyTitle);

void ContingencyData::sortContingenciesAcending();
void ContingencyData::sortContingenciesDecending();

void ContingencyData::calculateDaysFromDate(int nContingencyNum)
{
    if(m_Contingency[nContingencyNum].m_nCalcFrom == HARD_DATE || m_Contingency[nContingencyNum].m_nCalcFrom == CALC_FROM_AO  )
        m_Contingency[nContingencyNum].m_nNumOfDays = m_dtAODate.daysTo(m_Contingency[nContingencyNum].m_dtDateOfContingency);
    if(m_Contingency[nContingencyNum].m_nCalcFrom == CALC_FROM_CLOSING)
        m_Contingency[nContingencyNum].m_nNumOfDays = m_dtClosingDate.daysTo(m_Contingency[nContingencyNum].m_dtDateOfContingency);
    else { m_Contingency[nContingencyNum].m_nNumOfDays = 0;}
}

void ContingencyData::refreshData()
{
    //run calculations
    //set contingency text

}

QString ContingencyData::generateReport();
