#ifndef DATAVISUALIZER_H
#define DATAVISUALIZER_H

#include "qstring.h"
#include "datamanager.h"

/*
 * The DataVisualizer is responsible for drawing Timeline Graphs from scheduling data.
 */
class DataVisualizer
{
public:
    // Constructors
    DataVisualizer();
    DataVisualizer(DataManager* inDataManager);

    // Draws a Timeline graph
    void DrawTimeline(QList<ScheduleInfo*>& schedule, QString& timelineStringText, QString& timelineGraphText);

    // Reference to the current dataManager
    DataManager* dataManager;
};

#endif // DATAVISUALIZER_H
