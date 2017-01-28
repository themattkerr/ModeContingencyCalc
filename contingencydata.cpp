
#include <QDate>
#include <QString>
#include <QTime>
#include "contingencydata.h"
#include "mattcalculations.h"

Contingency::Contingency(){}
Contingency::~Contingency(){}

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
//----Public functions ------------------------------------------------------------------------------------
void ContingencyData::setDefaults()
{
     m_dtAODate = QDate::currentDate();

     m_nDaysClosing = 60;
     m_dtClosingDate = m_dtAODate.addDays(m_nDaysClosing);

     m_strListingBrokerTrustName = "";
     m_strEarnestMoneyAmout = "";
     m_strMLSNumber = "";
     m_strPropertyAddress = "";

     Contingency *x =  &m_Contingency[0];
     x->m_strContingencyTitle = EARNEST_MONEY_TITLE;
     x->m_nNumOfDays = 5;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfo.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

     x =  &m_Contingency[1];
     x->m_strContingencyTitle = FINANCING_TITLE;
     x->m_nNumOfDays = 45;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfo.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

     x =  &m_Contingency[2];
     x->m_strContingencyTitle = APPRAISAL_TITLE;
     x->m_nNumOfDays = 40;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfo.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

     x =  &m_Contingency[3];
     x->m_strContingencyTitle = INSPECTION_TITLE;
     x->m_nNumOfDays = 14;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfo.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

     x =  &m_Contingency[4];
     x->m_strContingencyTitle = RADON_TITLE;
     x->m_nNumOfDays = 14;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfo.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

    for(int iii = 5; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        x =  &m_Contingency[iii];
        x->m_strContingencyTitle = "-";
        x->m_nNumOfDays = 0;
        x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
        x->m_nCalcFrom = CALC_FROM_AO;
        x->m_strReportInfo.clear();
        x->m_bUseBusinessDays = false;
        x->m_strBusinessDayReasons.clear();
    }


    x=0;

}

//----Private Fucntions-------------------------------------------------------------------------------------
void ContingencyData::setContingencyReportText(int nContingencyNum)
{
    Contingency *x = &m_Contingency[nContingencyNum];
    x->m_strReportInfo.clear();

    if(x->m_strContingencyTitle == BLANK)                     {x->m_strReportInfo.clear(); }
    if(x->m_strContingencyTitle == EARNEST_MONEY_TITLE)       {x->m_strReportInfo.append(EARNEST_MONEY1).append(m_strListingBrokerTrustName).append(EARNEST_MONEY2).append(m_strEarnestMoneyAmout).append(EARNEST_MONEY3);  }
    if(x->m_strContingencyTitle == CONDITION_REPORT_TITLE)    {x->m_strReportInfo.append(CONDITION_REPORT ); }
    if(x->m_strContingencyTitle == FINANCING_TITLE)           {x->m_strReportInfo.append(FINANCING );}
    if(x->m_strContingencyTitle == APPRAISAL_TITLE)           {x->m_strReportInfo.append(APPRAISAL ); }
    if(x->m_strContingencyTitle == INSPECTION_TITLE)          {x->m_strReportInfo.append(INSPECTION ); }
    if(x->m_strContingencyTitle == RADON_TITLE)               {x->m_strReportInfo.append(RADON ); }
    if(x->m_strContingencyTitle == WELL_SEPTIC_TITLE)         {x->m_strReportInfo.append(WELL_SEPTIC ); }
    if(x->m_strContingencyTitle == FINAL_WALKTHROUGH_TITLE)   {x->m_strReportInfo.append(FINAL_WALKTHROUGH ); }
    if(x->m_strContingencyTitle == HOME_INSURENCE_TITLE)      {x->m_strReportInfo.append(HOME_OWNER_INSSURENCE ); }
    if(x->m_strContingencyTitle == CONDO_DOCS_TITLE)          {x->m_strReportInfo.append(CONDO_DOCS ); }
    if(x->m_strContingencyTitle == COMFORT_LETTER_TITLE)      {x->m_strReportInfo.append(COMFORT_LETTER ); }
    if(x->m_strContingencyTitle == ENVIRONMENTAL_TEST_TITLE)  {x->m_strReportInfo.append(ENVIRONMENTAL_TEST ); }
    if(x->m_strContingencyTitle == ATTORNEY_REVIEW_TITLE)     {x->m_strReportInfo.append(ATTORNEY_REVIEW ); }
    if(x->m_strContingencyTitle == SEWER_TITLE)               {x->m_strReportInfo.append(SEWER ); }
    if(x->m_strContingencyTitle == ZONING_TITLE)              {x->m_strReportInfo.append(ZONING ); }
    if(x->m_strContingencyTitle == SURVEY_TITLE)              {x->m_strReportInfo.append(SURVEY ); }
    if(x->m_strContingencyTitle == RATE_LOCK_TITLE)           {x->m_strReportInfo.append(RATE_LOCK ); }
    if(x->m_strContingencyTitle == CUSTOM_TITLE)              {}
    x = 0;

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
    Contingency *x =0;
    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        x = &m_Contingency[iii];
        switch (x->m_nCalcFrom) {
        case CALC_FROM_AO:          {x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);        break;}
        case CALC_FROM_CLOSING:     {x->m_dtDateOfContingency = m_dtClosingDate.addDays(x->m_nNumOfDays);   break;}
        case HARD_DATE:             {x->m_nNumOfDays = m_dtAODate.daysTo(x->m_dtDateOfContingency);         break;}

            break;
        default:
            break;
        }
        setContingencyReportText(iii);
    }


}

QString ContingencyData::generateReport()
{

}
