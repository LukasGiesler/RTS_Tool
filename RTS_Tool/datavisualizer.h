#ifndef DATAVISUALIZER_H
#define DATAVISUALIZER_H

#include "qstring.h"
#include "datamanager.h"

class DataVisualizer
{
public:
    DataVisualizer();
    DataVisualizer(DataManager* inDataManager);

    void VisualizeData();
    void ScheduleRMS();
    void ScheduleDMS();
    int CalculateGCD(int a, int b);
    int CalculateLCM();

    QString rmsTimelineString;
    QString timelineGraphAsString;

    QString dmsTimelineString;

    DataManager* dataManager;
};

#endif // DATAVISUALIZER_H
