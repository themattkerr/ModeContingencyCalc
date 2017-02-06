#ifndef SAVEANDLOADFUNCTIONS_H
#define SAVEANDLOADFUNCTIONS_H

#include "contingencydata.h"
#include <QDataStream>
#include <QString>
#include <QFile>


bool openMilestoneFile(QString strFileName , ContingencyData &openData , int *pnReportType = 0, int *pnRowsToShow = 0);
bool saveMilestoneFile(QString strFileName ,ContingencyData &saveData, int *pnReportType = 0, int *pnRowsToShow = 0);

#endif // SAVEANDLOADFUNCTIONS_H
