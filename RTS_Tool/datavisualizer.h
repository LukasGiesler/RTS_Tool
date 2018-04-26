#ifndef DATAVISUALIZER_H
#define DATAVISUALIZER_H

#include "qstring.h"

class DataVisualizer
{
public:
    DataVisualizer();

    void VisualizeData();
    void ScheduleRMS();
    void ScheduleDMS();
    int CalculateGCD(int a, int b);
    int CalculateLCM();

    QString rmsTimelineString;
    QString timelineGraphAsString;

    QString dmsTimelineString;
};

#endif // DATAVISUALIZER_H
