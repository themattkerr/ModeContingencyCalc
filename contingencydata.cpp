#include "contingencydata.h"
#include <QDate>
#include <QString>
#include <QTime>

ContingencyData() {}

~ContingencyData(){}

//-----------------------------------------------------------------------------------------
void ContingencyData::enterAODate(QDate dtAODate)
{

}

void ContingencyData::enterClosingDate(QDate dtClosingDate)
{

}

void ContingencyData::enterDaysClosing(int nDaysClosing)
{

}

void ContingencyData::enterListingBrokerTrustName(QString strListingBrokerTrustName)
{

}

void ContingencyData::enterEarnestMoneyAmount(QString strEarnestMoneyAmout);
void ContingencyData::enterMLSNumber(QString strMLSNumber);
void ContingencyData::enterPropertyAddress(QString strPropertyAddress);

void ContingencyData::enterContingencyTitle(QString strContingencyTitle, int nContingencyNum);
void ContingencyData::enterDateOfContingency(QDate dtDateOfContingency,int nContingencyNum );
void ContingencyData::enterTimeOfDay(QTime TimeOfDay, int nContingencyNum);
void ContingencyData::enterDays(int nDays, int nContingencyNum);

void ContingencyData::setCalcType(int nCalcType, int nContingencyNum);
void ContingencyData::setUseBusinessDays(bool BusinessDays, int nContingencyNum);

//-----------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------
void ContingencyData::enterContingencyText(QString strContingencyText);

void ContingencyData::sortContingenciesAcending();
void ContingencyData::sortContingenciesDecending();

void ContingencyData::refreshData();

QString ContingencyData::generateReport();
