#ifndef MATTCALCULATIONS
#define MATTCALCULATIONS

#define VERSION_OF_MATTCALCULATIONS "1.2.0"

#include <qstring.h>
#include <QDate>

enum curency{
    US_DOLLARS = 0,
};
enum dayOfWeek{
    MONDAY = 1,
    TUESDAY = 2,
    WEDNESDAY = 3,
    THURSDAY = 4,
    FRIDAY = 5,
    SATURDAY = 6,
    SUNDAY = 7

};

bool doubleIsEqual (double x, double y, unsigned int nNumberOfDecimalPlaces);

double  usDollarsStringToDouble(QString qstrDollars);
QString doubleToCurrency (double dInput, unsigned int nCurrency);
QString millisecondsToHoursMinsSec (int nMilliseconds);

bool  isBusinessDay(QDate dtDayToTest, QString &strReason);
bool  isNationalHoliday(QDate dtDayToTest, QString &strHolidayName);
void  dayOfWeekStats(QDate dtDay, int &nDayOfWeek, int &nHowManyOfDayOfWeekInMonth, int &occuranceOfDayOfWeekInMonth);
QDate dateBusinessDaysAway(QDate dtInputDate, int nNumOfBusinessDays, QString &strListOfDaysOff);

#endif // MATTCALCULATIONS

