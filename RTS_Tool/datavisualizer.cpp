#include "datavisualizer.h"
#include "qdebug.h"
#include <numeric>

// Constructor
DataVisualizer::DataVisualizer()
{

}

DataVisualizer::DataVisualizer(DataManager* inDataManager)
{
    dataManager = inDataManager;
}

/*
 *  Draws a Time Line Graph based on schedule
 *  timelineStringText will have the format: ABC BCD ABC ...
 *  timelineGraphText will be the actual graph as String
 */
void DataVisualizer::DrawTimeline(QList<ScheduleInfo*>& schedule, QString& timelineStringText, QString& timelineGraphText)
{
    timelineStringText.clear();
    timelineGraphText.clear();
    // Timeline String
    int currentMinorCycle = -1;
    for(int i=0; i<schedule.size(); i++)
    {
        // Draw space after every minor cycle
        if(schedule[i]->minorCycleIndex != currentMinorCycle)
        {
            timelineStringText.append(" ");
            currentMinorCycle = schedule[i]->minorCycleIndex;
        }

        // Draw process name
        timelineStringText.append(schedule[i]->processData->processName);
    }

    // Timeline Graph
    currentMinorCycle = 0;
    int minorCycleLength = schedule.at(0)->processData->periodT;
    int majorCycleLength = dataManager->CalculateLCM(dataManager->rawDataList);
    int leftOverLength = 0;
    int usedCycleLength = 0;

    // Draw Y Axis
    QList<QString> timelineRowStrings;
    for(int i=0; i<dataManager->rawDataList.size(); i++)
    {
        timelineRowStrings.append(dataManager->RMS_DataList.at(i).processName);//todo: change RMS to current data list, axis labeling for DMS  might be wrong
    }

    // Draw process status
    for(int i=0; i<schedule.size(); i++)
    {//Every process
        // Draw end of minor cycle
        if(schedule[i]->minorCycleIndex != currentMinorCycle)
        {
            for(int m=0; m<timelineRowStrings.size(); m++)
            {// Every string row
                for(int l=0; l<leftOverLength; l++)
                {
                    timelineRowStrings[m].append(".");
                }
                timelineRowStrings[m].append(" ");
            }
            usedCycleLength = 0;
        }

        for(int j=0; j<timelineRowStrings.size(); j++)
        {// Every string row
            for(int k=0; k<schedule[i]->scheduledDuration; k++)
            {// Every string row character
                if(schedule[i]->processData->processName==timelineRowStrings[j].at(0))
                {
                    timelineRowStrings[j].append("-");
                }
                else
                {
                    timelineRowStrings[j].append(".");
                }
            }

        }
        currentMinorCycle = schedule[i]->minorCycleIndex;
        usedCycleLength += schedule[i]->scheduledDuration;
        leftOverLength = minorCycleLength - usedCycleLength;
    }

    // Draw newlines on each row and combine the rows to one string
    for(int i=0; i<timelineRowStrings.size(); i++)
    {
        for(int l=0; l<leftOverLength; l++)
        {
            timelineRowStrings[i].append(".");
        }
        timelineRowStrings[i].append("\n");
        timelineGraphText.append(timelineRowStrings.at(i));
    }

    // Timeline Graph, draw X axis
    for(int i=0; i<timelineRowStrings[0].size(); i++)
    {
        if(i > majorCycleLength) break;
        if(i==0) {
             timelineGraphText.append(" ");
        }
        else if(i%5==0) {
            timelineGraphText.append(QString::number(i));
            if(i%(minorCycleLength)==0) {
                timelineGraphText.append(" ");
                continue;
            }
        }
        else
        {
            if(i>=98 && (i+2)%5 == 0)
            {
                continue;
            }
            else if(i>=9 && (i+1)%5 == 0)
            {
                continue;
            }
            timelineGraphText.append(".");
        }
        qDebug() << i;
    }
}

