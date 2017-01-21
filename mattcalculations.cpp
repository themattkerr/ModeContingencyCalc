#include "mattcalculations.h"
#include "constsants.h"
#include <qstring.h>
#include <qlocale.h>
#include <QDate>



bool doubleIsEqual (double x, double y, unsigned int nNumberOfDecimalPlaces)
{
    int nMultiplyer = 1;
    for(int iii = 1; iii <= nNumberOfDecimalPlaces; iii++)
        nMultiplyer *= 10;
    return (static_cast<int>(x*nMultiplyer + 0.5) == static_cast<int>(y*nMultiplyer + 0.5));
}

double usDollarsStringToDouble(QString qstrDollars)
{
    bool ok;
    qstrDollars.remove('$').remove(',');
    double dValue = qstrDollars.toDouble(&ok);
    if (ok)
        return dValue;
    else
        return 0;
}

QString doubleToCurrency (double dInput, unsigned int nCurrency = US_DOLLARS)
{
    QString qstrCurrency;
    switch (nCurrency)
    {
        case US_DOLLARS:     {qstrCurrency = "$ "; break;}
    }

    qstrCurrency.append(QLocale (QLocale::English).toString(dInput));
    return qstrCurrency;
}

QString millisecondsToHoursMinsSec (int nMilliseconds)
{
    int hours;
    int mins;
    int sec;

    hours = nMilliseconds / 3600000;
    nMilliseconds = nMilliseconds % 3600000;

    mins = nMilliseconds / 60000;
    nMilliseconds = nMilliseconds % 60000;

    sec = nMilliseconds / 1000;

    QString strE;
    if (mins >0)
    {
        if (hours > 0)
        {
            if (hours < 10)
                strE.append("0");
            strE = strE.number(hours, 10); strE.append("h:");}
        if (mins < 10)
            strE.append("0");
        strE.append(QString::number(mins,10)); strE.append("m:");
    }
    if (sec < 10)
        strE.append("0");
    strE.append(QString::number(sec, 10)); strE.append("s");

    return strE;
}

bool isBusinessDay(QDate dtDayToTest, QString &strReason)
{
    if(dtDayToTest.dayOfWeek() > 5)
    {
        strReason = "Weekend";
        return false;
    }
    if(isNationalHoliday(dtDayToTest, strReason))
        return false;
    return true;
}

bool isNationalHoliday(QDate dtDayToTest, QString &strHolidayName)
{
    if(strHolidayName != 0)
            strHolidayName.clear();
    int nTestYear;
    int nTestMonth;
    int nTestDay;
    dtDayToTest.getDate(&nTestYear, &nTestMonth, &nTestDay);

    QDate dtChristmas, dtVeteransDay, dtIndependenceDay, dtNewYearsDay;

    dtChristmas.setDate(nTestYear, 12, 25);
    dtVeteransDay.setDate(nTestYear, 11, 11);
    dtIndependenceDay.setDate(nTestYear, 7, 4);
    dtNewYearsDay.setDate(nTestYear, 1, 1);

    if(dtDayToTest==dtChristmas)
        {strHolidayName = "Christmas"; return true;}
    if(dtDayToTest==dtVeteransDay)
        {strHolidayName = "Veteran's Day"; return true;}
    if(dtDayToTest==dtIndependenceDay)
        {strHolidayName = "Independence Day"; return true;}
    if(dtDayToTest==dtNewYearsDay)
        {strHolidayName = "New Year's Day"; return true;}

    int nDayOfWeek, nHowManyOfDayOfWeekInMonth, occuranceOfDayOfWeekInMonth;
    dayOfWeekStats(dtDayToTest, nDayOfWeek, nHowManyOfDayOfWeekInMonth, occuranceOfDayOfWeekInMonth);

    if(nDayOfWeek == MONDAY)
    {
        if(dtChristmas.addDays(1) == dtDayToTest) //If holidays are on a sunday
            {strHolidayName = "Christmas Holiday"; return true;}
        if(dtVeteransDay.addDays(1) == dtDayToTest)
            {strHolidayName = "Veteran's Day Holiday"; return true;}
        if(dtIndependenceDay.addDays(1) == dtDayToTest)
            {strHolidayName = "Independence Day Holiday"; return true;}
        if(dtNewYearsDay.addDays(1) == dtDayToTest)
            {strHolidayName = "New Year's Day Holiday"; return true;}

        if(nTestMonth == 1 && occuranceOfDayOfWeekInMonth == 3) //Martin Luther King Jr Day (3rd Monday In Jan)
            {strHolidayName = "Martin Luther King Jr Day Holiday"; return true;}
        if(nTestMonth == 2 && occuranceOfDayOfWeekInMonth == 3) // George Washington's Birthday (3rd Monday In Feb)
            {strHolidayName = "George Washington's Birthday Holiday"; return true;}
        if(nTestMonth == 9 && occuranceOfDayOfWeekInMonth == 1) // Labor Day (1st Mon in Sept)
            {strHolidayName = "Labor Day Holiday"; return true;}
        if(nTestMonth == 10 && occuranceOfDayOfWeekInMonth == 2) //Columbus Day (2nd Mon in Oct)
            {strHolidayName = "Columbus Day Holiday"; return true;}
        if(nTestMonth == 5)                                      //Memorial Day (last Mon in May)
        {
            if(nHowManyOfDayOfWeekInMonth == occuranceOfDayOfWeekInMonth)
               {strHolidayName = "Memorial Day Holiday"; return true;}
        }
    }
    if(nDayOfWeek == THURSDAY)
    {
        if(nTestMonth == 11 && occuranceOfDayOfWeekInMonth == 4)    //Thanksgiving (4th Thursday in Nov)
            {strHolidayName = "Thanksgiving Holiday"; return true;}
    }
    if(nDayOfWeek == FRIDAY)
    {
        if(dtChristmas.addDays(-1) == dtDayToTest) //If holidays are on a Saturday
            {strHolidayName = "Christmas Holiday"; return true;}
        if(dtVeteransDay.addDays(-1) == dtDayToTest)
            {strHolidayName = "Veteran's Day Holiday"; return true;}
        if(dtIndependenceDay.addDays(-1) == dtDayToTest)
            {strHolidayName = "Independence Day Holiday"; return true;}
        if(dtNewYearsDay.addDays(-1) == dtDayToTest)
            {strHolidayName = "New Year's Day Holiday"; return true;}
    }
    return false;
}

void dayOfWeekStats(QDate dtDay, int &nDayOfWeek, int &nHowManyOfDayOfWeekInMonth, int &occuranceOfDayOfWeekInMonth)
{
    int nTestYear;
    int nTestMonth;
    int nTestDay;
    dtDay.getDate(&nTestYear, &nTestMonth, &nTestDay);
    QDate dtTemp;

    nDayOfWeek = dtDay.dayOfWeek();
    int nDaysInMonth = dtDay.daysInMonth();
    occuranceOfDayOfWeekInMonth = 0;
    nHowManyOfDayOfWeekInMonth =0;
    for(int iii = 1; iii <= nDaysInMonth; iii++)
    {
        dtTemp.setDate(nTestYear, nTestMonth, iii );
        if (nDayOfWeek == dtTemp.dayOfWeek())
            nHowManyOfDayOfWeekInMonth++;
        if (dtTemp == dtDay)
            occuranceOfDayOfWeekInMonth = nHowManyOfDayOfWeekInMonth;
    }
}

QDate dateBusinessDaysAway(QDate dtInputDate, int nNumOfBusinessDays, QString &strListOfDaysOff)
{
    QString strTemp;
    strListOfDaysOff.clear();
    int nNumberOfActualDays = 0;

    if(nNumOfBusinessDays > 0)
    {
        for(int iii = 1; iii <= nNumOfBusinessDays; iii++)
        {
            nNumberOfActualDays++;
            if(!(isBusinessDay(dtInputDate.addDays(nNumberOfActualDays), strTemp)))
                {iii--; strListOfDaysOff.append(dtInputDate.addDays(nNumberOfActualDays).toString()).append("\t").append(strTemp).append("\n");}
        }
     }
    if(nNumOfBusinessDays < 0)
    {
        for(int iii = nNumOfBusinessDays; iii < 0 ; iii++)
        {
            nNumberOfActualDays--;
            if(!(isBusinessDay(dtInputDate.addDays(nNumberOfActualDays), strTemp)))
                {iii--; strListOfDaysOff.append(dtInputDate.addDays(nNumberOfActualDays).toString()).append("\t").append(strTemp).append("\n");}
        }
     }
    return dtInputDate.addDays(nNumberOfActualDays);
}



