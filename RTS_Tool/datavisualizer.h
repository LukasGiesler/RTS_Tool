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
    void DrawRMS();
    void DrawDMS();

    QString RMS_ScheduleString;
    QString timelineGraphAsString;

    QString dmsTimelineString;

    DataManager* dataManager;
};

#endif // DATAVISUALIZER_H
