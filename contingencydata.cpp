
#include <QDate>
#include <QString>
#include <QTime>
#include <QMessageBox>
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
    refreshData();
}
void ContingencyData::enterEarnestMoneyAmount(QString strEarnestMoneyAmout)
{
    double dTemp;
    dTemp = usDollarsStringToDouble(strEarnestMoneyAmout);
    m_strEarnestMoneyAmout = doubleToCurrency(dTemp, US_DOLLARS);
    refreshData();
}
void ContingencyData::enterMLSNumber(QString strMLSNumber)
{
    m_strMLSNumber = strMLSNumber;
    refreshData();
}
void ContingencyData::enterPropertyAddress(QString strPropertyAddress)
{
    m_strPropertyAddress = strPropertyAddress;
    refreshData();
}

void ContingencyData::enterContingencyTitle(QString strContingencyTitle, int nContingencyNum)
{
    m_Contingency[nContingencyNum].m_strContingencyTitle.clear();
    m_Contingency[nContingencyNum].m_strReportInfoBuyer.clear();
    m_Contingency[nContingencyNum].m_strReportInfoSeller.clear();
    m_Contingency[nContingencyNum].m_strContingencyTitle = strContingencyTitle;
    if (strContingencyTitle == BLANK)
        resetContingency(nContingencyNum);
    //m_Contingency[nContingencyNum].m_strReportInfoBuyer = setContingencyReportText(strContingencyTitle);
    refreshData();
}
void ContingencyData::enterCustomText(QString strCustomText, int nContingencyNum)
{
    m_Contingency[nContingencyNum].m_strCustomText.clear();
    m_Contingency[nContingencyNum].m_strCustomText.append(strCustomText);
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
void ContingencyData::enterDependantContingencyTitle(QString DepContTitle, int nContingencyNum)
{
    m_Contingency[nContingencyNum].m_strDependantContingecyTitle = DepContTitle;
}

void ContingencyData::setCalcType(int nCalcType, int nContingencyNum)
{
    if(nCalcType == HARD_DATE || nCalcType == CALC_FROM_AO || nCalcType == CALC_FROM_CLOSING || nCalcType == OTHER_CONT)
        m_Contingency[nContingencyNum].m_nCalcFrom = nCalcType;
    else {
        m_Contingency[nContingencyNum].m_nCalcFrom = -1;
    }
    refreshData();
}
void ContingencyData::setUseBusinessDays(bool BusinessDays, int nContingencyNum)
{
    m_Contingency[nContingencyNum].m_bUseBusinessDays = BusinessDays;
    refreshData();
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
QString ContingencyData::getCustomText(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_strCustomText;
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
QString ContingencyData::getReportInfoBuyer(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_strReportInfoBuyer;
}
QString ContingencyData::getReportInfoSeller(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_strReportInfoSeller;
}
QString ContingencyData::getDependantContingencyTitle(int nContingencyNum)
{
    return m_Contingency[nContingencyNum].m_strDependantContingecyTitle;
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
     x->m_strReportInfoBuyer.clear();
     x->m_strReportInfoSeller.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

     x =  &m_Contingency[1];
     x->m_strContingencyTitle = FINANCING_TITLE;
     x->m_nNumOfDays = 45;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfoBuyer.clear();
     x->m_strReportInfoSeller.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

     x =  &m_Contingency[2];
     x->m_strContingencyTitle = APPRAISAL_TITLE;
     x->m_nNumOfDays = 40;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfoBuyer.clear();
     x->m_strReportInfoSeller.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

     x =  &m_Contingency[3];
     x->m_strContingencyTitle = INSPECTION_TITLE;
     x->m_nNumOfDays = 14;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfoBuyer.clear();
     x->m_strReportInfoSeller.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

     x =  &m_Contingency[4];
     x->m_strContingencyTitle = RADON_TITLE;
     x->m_nNumOfDays = 14;
     x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
     x->m_nCalcFrom = CALC_FROM_AO;
     x->m_strReportInfoBuyer.clear();
     x->m_strReportInfoSeller.clear();
     x->m_bUseBusinessDays = false;
     x->m_strBusinessDayReasons.clear();

    for(int iii = 5; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        resetContingency(iii);
//        x =  &m_Contingency[iii];
//        x->m_strContingencyTitle = "-";
//        x->m_nNumOfDays = 0;
//        x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
//        x->m_nCalcFrom = CALC_FROM_AO;
//        x->m_strReportInfoBuyer.clear();
//        x->m_bUseBusinessDays = false;
//        x->m_strBusinessDayReasons.clear();
    }


    x=0;

}
void ContingencyData::resetContingency(int nContingencyNum)
{
    Contingency *x =  &m_Contingency[nContingencyNum];
    x->m_strContingencyTitle = "-";
    x->m_nNumOfDays = 0;
    x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
    x->m_nCalcFrom = CALC_FROM_AO;
    x->m_strReportInfoBuyer.clear();
    x->m_strReportInfoSeller.clear();
    x->m_bUseBusinessDays = false;
    x->m_strBusinessDayReasons.clear();
    x->m_strCustomText.clear();
}
void ContingencyData::sortContingenciesAcending()
{
    Contingency Temp;

    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES;iii++)
    {
        for(int jjj = 0; jjj < MAX_NUM_CONTINGENCIES;jjj++)
        {
            //if(m_Contingency[iii].m_dtDateOfContingency != m_Contingency[jjj].m_dtDateOfContingency)
            if(m_Contingency[iii].m_strContingencyTitle != BLANK && m_Contingency[jjj].m_strContingencyTitle == BLANK)
            {
                Temp = m_Contingency[iii];
                m_Contingency[iii] = m_Contingency[jjj];
                m_Contingency[jjj] = Temp;
            }

            if((m_Contingency[iii].m_dtDateOfContingency < m_Contingency[jjj].m_dtDateOfContingency)
               && ( m_Contingency[iii].m_strContingencyTitle != BLANK))
            {
                Temp = m_Contingency[iii];
                m_Contingency[iii] = m_Contingency[jjj];
                m_Contingency[jjj] = Temp;
//                if(m_Contingency[iii].m_dtDateOfContingency == m_Contingency[jjj].m_dtDateOfContingency
//                        && (m_Contingency[iii].m_strContingencyTitle < m_Contingency[jjj].m_strContingencyTitle ) )
//                {
//                    Temp = m_Contingency[iii];
//                    m_Contingency[iii] = m_Contingency[jjj];
//                    m_Contingency[jjj] = Temp;
//                }
            }


        }
    }

}
void ContingencyData::sortContingenciesDecending()
{

}

//----Private Functions-------------------------------------------------------------------------------------
void ContingencyData::setContingencyReportText(int nContingencyNum)
{
    Contingency *x = &m_Contingency[nContingencyNum];
    x->m_strReportInfoBuyer.clear();
    x->m_strReportInfoSeller.clear();

    if(x->m_strContingencyTitle == BLANK)                     {x->m_strReportInfoBuyer.clear();
                                                               x->m_strReportInfoSeller.clear();
    }
    if(x->m_strContingencyTitle == EARNEST_MONEY_TITLE)         {//---Set Buyer Info---
                                                                x->m_strReportInfoBuyer.append(EARNEST_MONEY1_BUYER);
                                                                if(m_strListingBrokerTrustName == "")
                                                                     x->m_strReportInfoBuyer.append(EARNEST_MONEY_SUB1_BUYER);
                                                                 else
                                                                     x->m_strReportInfoBuyer.append("'").append(m_strListingBrokerTrustName).append("'");
                                                                x->m_strReportInfoBuyer.append(EARNEST_MONEY2_BUYER);
                                                                if (m_strEarnestMoneyAmout == "" || m_strEarnestMoneyAmout == doubleToCurrency(0,US_DOLLARS ) )
                                                                    x->m_strReportInfoBuyer.append(EARNEST_MONEY_SUB2_BUYER);
                                                                else
                                                                    x->m_strReportInfoBuyer.append(m_strEarnestMoneyAmout);
                                                                x->m_strReportInfoBuyer.append(EARNEST_MONEY3_BUYER);
                                                                if(m_strPropertyAddress == "")
                                                                    x->m_strReportInfoBuyer.append(EARNEST_MONEY_SUB3_BUYER);
                                                                else
                                                                    x->m_strReportInfoBuyer.append("'").append(m_strPropertyAddress).append("'");
                                                                x->m_strReportInfoBuyer.append(EARNEST_MONEY4_BUYER);

                                                               //---Set seller info ---
                                                               x->m_strReportInfoSeller.append(EARNEST_MONEY1_SELLER);
                                                               if (m_strEarnestMoneyAmout != "" || m_strEarnestMoneyAmout != "$ 0")
                                                                   x->m_strReportInfoSeller.append(EARNEST_MONEY2_SELLER).append(m_strEarnestMoneyAmout).append(" ");
                                                               x->m_strReportInfoSeller.append(EARNEST_MONEY3_SELLER);
                                                               if(m_strListingBrokerTrustName != "" )
                                                                   x->m_strReportInfoSeller.append("'").append(m_strListingBrokerTrustName).append("'");
                                                               else {
                                                                   x->m_strReportInfoSeller.append(EARNEST_MONEY4_SELLER);
                                                                     }
                                                               x->m_strReportInfoSeller.append(EARNEST_MONEY5_SELLER);
                                                               }

    if(x->m_strContingencyTitle == CONDITION_REPORT_TITLE)    {x->m_strReportInfoBuyer.append(CONDITION_REPORT_BUYER );
                                                               x->m_strReportInfoSeller.append(CONDITION_REPORT_SELLER ); }

    if(x->m_strContingencyTitle == FINANCING_TITLE)           {x->m_strReportInfoBuyer.append(FINANCING_BUYER );
                                                               x->m_strReportInfoSeller.append(FINANCING_SELLER ); }

    if(x->m_strContingencyTitle == APPRAISAL_TITLE)           {x->m_strReportInfoBuyer.append(APPRAISAL_BUYER );
                                                               x->m_strReportInfoSeller.append(APPRAISAL_SELLER ); }

    if(x->m_strContingencyTitle == INSPECTION_TITLE)          {x->m_strReportInfoBuyer.append(INSPECTION_BUYER );
                                                               x->m_strReportInfoSeller.append(INSPECTION_SELLER ); }

    if(x->m_strContingencyTitle == RADON_TITLE)               {x->m_strReportInfoBuyer.append(RADON_BUYER );
                                                               x->m_strReportInfoSeller.append(RADON_SELLER );}

    if(x->m_strContingencyTitle == WELL_SEPTIC_TITLE)         {x->m_strReportInfoBuyer.append(WELL_SEPTIC_BUYER );
                                                               x->m_strReportInfoSeller.append(WELL_SEPTIC_SELLER );  }

    if(x->m_strContingencyTitle == FINAL_WALKTHROUGH_TITLE)   {x->m_strReportInfoBuyer.append(FINAL_WALKTHROUGH_BUYER );
                                                               x->m_strReportInfoSeller.append(FINAL_WALKTHROUGH_SELLER ); }

    if(x->m_strContingencyTitle == HOME_INSURENCE_TITLE)      {x->m_strReportInfoBuyer.append(HOME_OWNER_INSSURENCE_BUYER );
                                                               x->m_strReportInfoSeller.append(HOME_OWNER_INSSURENCE_SELLER ); }

    if(x->m_strContingencyTitle == CONDO_DOCS_TITLE)          {x->m_strReportInfoBuyer.append(CONDO_DOCS_BUYER );
                                                               x->m_strReportInfoSeller.append(CONDO_DOCS_SELLER ); }

    if(x->m_strContingencyTitle == COMFORT_LETTER_TITLE)      {x->m_strReportInfoBuyer.append(COMFORT_LETTER_BUYER );
                                                               x->m_strReportInfoSeller.append(COMFORT_LETTER_SELLER ); }

    if(x->m_strContingencyTitle == ENVIRONMENTAL_TEST_TITLE)  {x->m_strReportInfoBuyer.append(ENVIRONMENTAL_TEST_BUYER );
                                                               x->m_strReportInfoSeller.append(ENVIRONMENTAL_TEST_SELLER ); }

    if(x->m_strContingencyTitle == ATTORNEY_REVIEW_TITLE)     {x->m_strReportInfoBuyer.append(ATTORNEY_REVIEW_BUYER );
                                                               x->m_strReportInfoSeller.append(ATTORNEY_REVIEW_SELLER ); }

    if(x->m_strContingencyTitle == SEWER_TITLE)               {x->m_strReportInfoBuyer.append(SEWER_BUYER );
                                                               x->m_strReportInfoSeller.append(SEWER_SELLER ); }

    if(x->m_strContingencyTitle == ZONING_TITLE)              {x->m_strReportInfoBuyer.append(ZONING_BUYER );
                                                               x->m_strReportInfoSeller.append(ZONING_SELLER ); }

    if(x->m_strContingencyTitle == SURVEY_TITLE)              {x->m_strReportInfoBuyer.append(SURVEY_BUYER );
                                                               x->m_strReportInfoSeller.append(SURVEY_SELLER ); }

    if(x->m_strContingencyTitle == RATE_LOCK_TITLE)           {x->m_strReportInfoBuyer.append(RATE_LOCK_BUYER );
                                                               x->m_strReportInfoSeller.append(RATE_LOCK_SELLER ); } 

    if(x->m_strContingencyTitle == ORDER_TITLE_TITLE)         {x->m_strReportInfoBuyer.append(ORDER_TITLE_BUYER );
                                                               x->m_strReportInfoSeller.append(ORDER_TITLE_SELLER ); }

    if(x->m_strContingencyTitle == HOA_DOCS_DELIVERY_TITLE)   {x->m_strReportInfoBuyer.append(HOA_DOCS_DELIVERY_BUYER );
                                                               x->m_strReportInfoSeller.append(HOA_DOCS_DELIVERY_SELLER ); }

    if(x->m_strContingencyTitle == HOA_DOCS_REVIEW_TITLE)     {x->m_strReportInfoBuyer.append(HOA_DOCS_REVIEW_BUYER );
                                                               x->m_strReportInfoSeller.append(HOA_DOCS_REVIEW_SELLER ); }

    if(x->m_strContingencyTitle == COVENANTS_RESTRICTIONS_DELIVERY_TITLE)
                                                              {x->m_strReportInfoBuyer.append(COVENANTS_RESTRICTIONS_DELIVERY_BUYER );
                                                               x->m_strReportInfoSeller.append(COVENANTS_RESTRICTIONS_DELIVERY_SELLER ); }

    if(x->m_strContingencyTitle == COVENANTS_RESTRICTIONS_REVIEW_TITLE)
                                                              {x->m_strReportInfoBuyer.append(COVENANTS_RESTRICTIONS_REVIEW_BUYER );
                                                               x->m_strReportInfoSeller.append(COVENANTS_RESTRICTIONS_REVIEW_SELLER ); }

    if(x->m_strContingencyTitle == CUSTOM_TITLE)              {}
    x = 0;

}



void ContingencyData::calculateDaysFromDate(int nContingencyNum)
{
    QString strBusinessDayList;
    Contingency *x = &m_Contingency[nContingencyNum];

    if(x->m_nCalcFrom == HARD_DATE || x->m_nCalcFrom == CALC_FROM_AO  )
    {
        if(!(x->m_bUseBusinessDays))
        {
            x->m_nNumOfDays = m_dtAODate.daysTo(x->m_dtDateOfContingency);
            return;
        }
        if(x->m_bUseBusinessDays)
        {
            x->m_nNumOfDays = numOfBusinessDaysBetween(m_dtAODate,x->m_dtDateOfContingency,strBusinessDayList);
            return;
        }
    }
    if(x->m_nCalcFrom == CALC_FROM_CLOSING)
    {
        if(!(x->m_bUseBusinessDays))
        {
            x->m_nNumOfDays = m_dtClosingDate.daysTo(x->m_dtDateOfContingency);
            return;
        }
        if(x->m_bUseBusinessDays)
        {
            x->m_nNumOfDays = numOfBusinessDaysBetween(m_dtClosingDate, x->m_dtDateOfContingency,  strBusinessDayList);
            return;
        }
    }
    else { x->m_nNumOfDays = 0;}
}
void ContingencyData::calculateDateFromDays(int nContingencyNum, QString &strReasons )
{
    Contingency *x = &m_Contingency[nContingencyNum];

    if(x->m_nCalcFrom == HARD_DATE) // since Date is a set point the only thing that can change is the count of days
    {
        if(x->m_bUseBusinessDays)
           x->m_nNumOfDays = numOfBusinessDaysBetween(m_dtAODate, x->m_dtDateOfContingency, strReasons );
        else
            x->m_nNumOfDays = m_dtAODate.daysTo(x->m_dtDateOfContingency);
        return;
    }
    if(x->m_nCalcFrom == CALC_FROM_AO)
        {
            if(x->m_bUseBusinessDays)
                x->m_dtDateOfContingency =  dateBusinessDaysAway (m_dtAODate,x->m_nNumOfDays,strReasons  );
            else
                x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays);
        }
    if(x->m_nCalcFrom == CALC_FROM_CLOSING)
       {
            if(x->m_bUseBusinessDays)
                 x->m_dtDateOfContingency = dateBusinessDaysAway(m_dtClosingDate, x->m_nNumOfDays, strReasons);
            else
                x->m_dtDateOfContingency = m_dtClosingDate.addDays(x->m_nNumOfDays);
        }
    if(x->m_nCalcFrom == OTHER_CONT )
        {
            return;
        }
     if(x->m_nCalcFrom != HARD_DATE && x->m_nCalcFrom != CALC_FROM_AO && x->m_nCalcFrom != CALC_FROM_CLOSING && x->m_nCalcFrom != OTHER_CONT)
     {
         x->m_nNumOfDays = 0;
     }
     return;
}

void ContingencyData::refreshData()
{
    QString strNonWorkDays;
    Contingency *x =0;
    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        x = &m_Contingency[iii];
        switch (x->m_nCalcFrom) {
        case CALC_FROM_AO:          {if(!(x->m_bUseBusinessDays))
                                        {x->m_dtDateOfContingency = m_dtAODate.addDays(x->m_nNumOfDays); break;}
                                     if(x->m_bUseBusinessDays)
                                        {x->m_dtDateOfContingency = dateBusinessDaysAway(m_dtAODate,x->m_nNumOfDays,strNonWorkDays); break;}
                                    }
        case CALC_FROM_CLOSING:     {if(!(x->m_bUseBusinessDays))
                                        {x->m_dtDateOfContingency = m_dtClosingDate.addDays(x->m_nNumOfDays); break;}
                                     if(x->m_bUseBusinessDays)
                                        {x->m_dtDateOfContingency = dateBusinessDaysAway(m_dtClosingDate, x->m_nNumOfDays, strNonWorkDays); break;}
                                    }
        case HARD_DATE:             {if(!(x->m_bUseBusinessDays))
                                        {x->m_nNumOfDays = m_dtAODate.daysTo(x->m_dtDateOfContingency);         break;}
                                     if(x->m_bUseBusinessDays)
                                        {x->m_nNumOfDays = numOfBusinessDaysBetween(m_dtAODate, x->m_dtDateOfContingency, strNonWorkDays ); break;}
                                    }
        case OTHER_CONT:            {
                                        x->m_nNumOfDays; break;
                                    }
            break;
        default:
            break;
        }
        setContingencyReportText(iii);
    }


}

//QString ContingencyData::generateReport()
//{

//}
