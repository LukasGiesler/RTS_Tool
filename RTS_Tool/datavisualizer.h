#ifndef DATAVISUALIZER_H
#define DATAVISUALIZER_H

#include "qstring.h"
#include "datamanager.h"

class DataVisualizer
{
public:
    DataVisualizer();
    DataVisualizer(DataManager* inDataManager);

    void DrawTimeline(QList<ScheduleInfo*>& schedule, QString& timelineStringText, QString& timelineGraphText);

    DataManager* dataManager;
};

#endif // DATAVISUALIZER_H
