#ifndef DATAVISUALIZER_H
#define DATAVISUALIZER_H

#include "qstring.h"

class DataVisualizer
{
public:
    DataVisualizer();

    void VisualizeData();
    int CalculateGCD(int a, int b);
    int CalculateLCM();

    QString timelineString;
    QString timelineGraphAsString;

    QString dmsTimelineString;
};

#endif // DATAVISUALIZER_H
