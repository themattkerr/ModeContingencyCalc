#include "saveandloadfunctions.h"

bool openMilestoneFile(QString strFileName ,ContingencyData &openData, int *pnReportType , int *pnRowsToShow)

{
    QFile file (strFileName);
    file.open(QIODevice::ReadOnly);

        QDataStream stream (&file);

    QDate dtAODate;
    QDate dtClosingDate;
    int nDaysClosing;

    QString strListingBrokerTrustName;
    QString strEarnestMoneyAmout;
    QString strMLSNumber;
    QString strPropertyAddress;

    Contingency aContingency[MAX_NUM_CONTINGENCIES];

    QString strSoftwareVer;

    stream >> strSoftwareVer;
    if( strSoftwareVer == CURRENT_VERSION)
    {
        stream >> *pnReportType;
        stream >> *pnRowsToShow;
        stream >> dtAODate;
        stream >> dtClosingDate;
        stream >> nDaysClosing;

        stream >> strListingBrokerTrustName;
        stream >> strEarnestMoneyAmout;
        stream >> strMLSNumber;
        stream >> strPropertyAddress;

        Contingency *x = 0;
        for (int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
        {
            x = &aContingency[iii];
            stream >> x->m_bUseBusinessDays;
            stream >> x->m_dtDateOfContingency;
            stream >> x->m_nCalcFrom;
            stream >> x->m_nNumOfDays;
            stream >> x->m_strContingencyTitle;
            stream >> x->m_strCustomText;
            stream >> x->m_strDependantContingecyTitle;
        }
        x=0;

        openData.enterAODate(dtAODate);
        openData.enterClosingDate(dtClosingDate);
        openData.enterDaysClosing(nDaysClosing);
        openData.enterListingBrokerTrustName(strListingBrokerTrustName);
        openData.enterEarnestMoneyAmount(strEarnestMoneyAmout);
        openData.enterMLSNumber(strMLSNumber);
        openData.enterPropertyAddress(strPropertyAddress);

        for (int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
        {
            x = &aContingency[iii];
            openData.setUseBusinessDays( x->m_bUseBusinessDays, iii);
            openData.enterDateOfContingency( x->m_dtDateOfContingency, iii );
            openData.setCalcType( x->m_nCalcFrom, iii );

            openData.enterContingencyTitle( x->m_strContingencyTitle, iii);
            openData.enterCustomText( x->m_strCustomText, iii );
            openData.enterDependantContingencyTitle(x->m_strDependantContingecyTitle, iii);
            openData.enterDays(  x->m_nNumOfDays, iii );

        }
        return true;
    }



    if( strSoftwareVer == "2.0.0")
    {
        stream >> *pnReportType;
        stream >> *pnRowsToShow;
        stream >> dtAODate;
        stream >> dtClosingDate;
        stream >> nDaysClosing;

        stream >> strListingBrokerTrustName;
        stream >> strEarnestMoneyAmout;
        stream >> strMLSNumber;
        stream >> strPropertyAddress;

        Contingency *x = 0;
        for (int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
        {
            x = &aContingency[iii];
            stream >> x->m_bUseBusinessDays;
            stream >> x->m_dtDateOfContingency;
            stream >> x->m_nCalcFrom;
            stream >> x->m_nNumOfDays;
            stream >> x->m_strContingencyTitle;
            stream >> x->m_strCustomText;
        }
        x=0;

        openData.enterAODate(dtAODate);
        openData.enterClosingDate(dtClosingDate);
        openData.enterDaysClosing(nDaysClosing);
        openData.enterListingBrokerTrustName(strListingBrokerTrustName);
        openData.enterEarnestMoneyAmount(strEarnestMoneyAmout);
        openData.enterMLSNumber(strMLSNumber);
        openData.enterPropertyAddress(strPropertyAddress);

        for (int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
        {
            x = &aContingency[iii];
            openData.setUseBusinessDays( x->m_bUseBusinessDays, iii);
            openData.enterDateOfContingency( x->m_dtDateOfContingency, iii );
            openData.setCalcType( x->m_nCalcFrom, iii );
            openData.enterDays(  x->m_nNumOfDays, iii );
            openData.enterContingencyTitle( x->m_strContingencyTitle, iii);
            openData.enterCustomText( x->m_strCustomText, iii );
        }
        return true;
    }
    return false;
}

bool saveMilestoneFile(QString strFileName ,ContingencyData &saveData, int *pnReportType , int *pnRowsToShow)
{
    QFile file (strFileName);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QDataStream stream (&file);
        QString strSoftwareVersion = CURRENT_VERSION;
        stream << strSoftwareVersion;
        stream << *pnReportType;
        stream << *pnRowsToShow;

        stream << saveData.getAODate();
        stream << saveData.getClosingDate();
        stream << saveData.getDaysClosing();

        stream << saveData.getListingBrokerTrustName();
        stream << saveData.getEarnestMoneyAmout();
        stream << saveData.getMLSNumber();
        stream << saveData.getPropertyAddress();

        for (int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
        {
            stream << saveData.getUseBusinessDays(iii);
            stream << saveData.getDateOfContingency(iii);
            stream << saveData.getCalcFrom(iii);
            stream << saveData.getNumOfDays(iii);
            stream << saveData.getContingencyTitle(iii);
            stream << saveData.getCustomText(iii);
            stream << saveData.getDependantContingencyTitle(iii);
        }
        return true;
    }
    return false;
}
