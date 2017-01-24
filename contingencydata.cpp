
#include <QDate>
#include <QString>
#include <QTime>
#include "contingencydata.h"
#include "mattcalculations.h"

//ContingencyData() {}

//~ContingencyData(){}

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
    double dTemp;
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
//void ContingencyData::enterTimeOfDay(QTime TimeOfDay, int nContingencyNum);
void ContingencyData::enterDays(int nDays, int nContingencyNum)
{
    m_Contingency[nContingencyNum].m_nNumOfDays = nDays;
    calculateDateFromDays(nContingencyNum, m_Contingency[nContingencyNum].m_strBusinessDayReasons);
}
void ContingencyData::setCalcType(int nCalcType, int nContingencyNum)
{
    if(nCalcType == HARD_DATE || nCalcType == CALC_FROM_AO || nCalcType == CALC_FROM_CLOSING)
        m_Contingency[nContingencyNum].m_nCalcFrom = nCalcType;
    else {
        m_Contingency[nContingencyNum].m_nCalcFrom = -1;
    }
}
void ContingencyData::setUseBusinessDays(bool BusinessDays, int nContingencyNum)
{
    m_Contingency[nContingencyNum].m_bUseBusinessDays = BusinessDays;
}

//-----Public Get Functions------------------------------------------------------------------------------------
QDate   ContingencyData::getAODate()
{
    return m_dtAODate;
}
QDate   ContingencyData::getClosingDate()
{
    return m_dtClosingDate;
}
int     ContingencyData::getDaysClosing()
{
    return m_nDaysClosing;
}

QString ContingencyData::getListingBrokerTrustName()
{
    return m_strListingBrokerTrustName;
}
QString ContingencyData::getEarnestMoneyAmout()
{
    return m_strEarnestMoneyAmout;
}
QString ContingencyData::getMLSNumber()
{
    return m_strMLSNumber;
}
QString ContingencyData::getPropertyAddress()
{
    return m_strPropertyAddress;
}

QString ContingencyData::getContingencyTitle(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_strContingencyTitle;
}
QDate   ContingencyData::getDateOfContingency(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_dtDateOfContingency;
}
//QTime   ContingencyData::getTimeOfDay(int nContingencyNum)

int     ContingencyData::getNumOfDays(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_nNumOfDays;
}
QString ContingencyData::getReportInfo(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_strReportInfo;
}

int     ContingencyData::getCalcFrom(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_nCalcFrom;
}
bool    ContingencyData::getUseBusinessDays(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_bUseBusinessDays;
}

//----Private Fucntions-------------------------------------------------------------------------------------
QString ContingencyData::setContingencyReportText(QString strContingencyTitle)
{

}

void ContingencyData::sortContingenciesAcending()
{

}
void ContingencyData::sortContingenciesDecending()
{

}

void ContingencyData::calculateDaysFromDate(int nContingencyNum)
{
    if(m_Contingency[nContingencyNum].m_nCalcFrom == HARD_DATE || m_Contingency[nContingencyNum].m_nCalcFrom == CALC_FROM_AO  )
        {m_Contingency[nContingencyNum].m_nNumOfDays = m_dtAODate.daysTo(m_Contingency[nContingencyNum].m_dtDateOfContingency);
        return;}
    if(m_Contingency[nContingencyNum].m_nCalcFrom == CALC_FROM_CLOSING)
        {m_Contingency[nContingencyNum].m_nNumOfDays = m_dtClosingDate.daysTo(m_Contingency[nContingencyNum].m_dtDateOfContingency);
        return;}
    else { m_Contingency[nContingencyNum].m_nNumOfDays = 0;}
}
void ContingencyData::calculateDateFromDays(int nContingencyNum, QString &strReasons )
{
    if(m_Contingency[nContingencyNum].m_nCalcFrom == HARD_DATE)
        {m_Contingency[nContingencyNum].m_nNumOfDays = m_dtAODate.daysTo(m_Contingency[nContingencyNum].m_dtDateOfContingency);
        return;}
    if(m_Contingency[nContingencyNum].m_nCalcFrom == CALC_FROM_AO)
        {
            if(m_Contingency[nContingencyNum].m_bUseBusinessDays)
            {
                m_Contingency[nContingencyNum].m_dtDateOfContingency =  dateBusinessDaysAway (m_dtAODate,m_Contingency[nContingencyNum].m_nNumOfDays,strReasons  );
                return;
            }
            else
            {
                m_Contingency[nContingencyNum].m_dtDateOfContingency = m_dtAODate.addDays(m_Contingency[nContingencyNum].m_nNumOfDays);
                return;
            }
        }
    if(m_Contingency[nContingencyNum].m_nCalcFrom == CALC_FROM_CLOSING)
       {
            if(m_Contingency[nContingencyNum].m_bUseBusinessDays)
            {
                 m_Contingency[nContingencyNum].m_dtDateOfContingency = dateBusinessDaysAway(m_dtClosingDate, m_Contingency[nContingencyNum].m_nNumOfDays, strReasons);
                 return;
            }
            else
            {
                m_Contingency[nContingencyNum].m_dtDateOfContingency = m_dtClosingDate.addDays(m_Contingency[nContingencyNum].m_nNumOfDays);
                return;
            }
        }
    else { m_Contingency[nContingencyNum].m_nNumOfDays = 0;}
}

void ContingencyData::refreshData()
{
    //run calculations
    //set contingency text

}

QString ContingencyData::generateReport()
{

}
