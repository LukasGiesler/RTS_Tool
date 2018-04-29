#include "datavisualizer.h"
#include "datamanager.h"
#include "qdebug.h"
#include <numeric>

DataVisualizer::DataVisualizer()
{

}


DataVisualizer::DataVisualizer(DataManager* inDataManager)
{
    dataManager = inDataManager;
}

void DataVisualizer::VisualizeData()
{
    DrawRMS();
    DrawDMS();
}

void DataVisualizer::DrawRMS()
{
    RMS_ScheduleString.clear();
    timelineGraphAsString.clear();
    // Timeline String
    int currentMinorCycle = -1;
    for(int i=0; i<dataManager->RMS_Schedule.size(); i++)
    {
        // Draw space after every minor cycle
        if(dataManager->RMS_Schedule[i]->minorCycleIndex != currentMinorCycle)
        {
            RMS_ScheduleString.append(" ");
            currentMinorCycle = dataManager->RMS_Schedule[i]->minorCycleIndex;
        }

        // Draw process name
        RMS_ScheduleString.append(dataManager->RMS_Schedule[i]->processData->processName);
    }

    // Timeline Graph
    currentMinorCycle = 0;
    int minorCycleLength = dataManager->RMS_Schedule.at(0)->processData->periodT;
    int majorCycleLength = dataManager->CalculateLCM();
    int leftOverLength = 0;
    int usedCycleLength = 0;

    // Draw Y Axis
    QList<QString> timelineRowStrings;
    for(int i=0; i<dataManager->RMS_DataList.size(); i++)
    {
        timelineRowStrings.append(dataManager->RMS_DataList.at(i).processName);
    }

    // Draw process status
    for(int i=0; i<dataManager->RMS_Schedule.size(); i++)
    {//Every process
        // Draw end of minor cycle
        if(dataManager->RMS_Schedule[i]->minorCycleIndex != currentMinorCycle)
        {
            qDebug() << leftOverLength;
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
            for(int k=0; k<dataManager->RMS_Schedule[i]->scheduledDuration; k++)
            {// Every string row character
                if(dataManager->RMS_Schedule[i]->processData->processName==timelineRowStrings[j].at(0))
                {
                    timelineRowStrings[j].append("-");
                }
                else
                {
                    timelineRowStrings[j].append(".");
                }
            }

        }
        currentMinorCycle = dataManager->RMS_Schedule[i]->minorCycleIndex;
        usedCycleLength += dataManager->RMS_Schedule[i]->scheduledDuration;
        leftOverLength = minorCycleLength - usedCycleLength;
    }

    // Draw newlines on each row and combine the rows to one string
    for(int i=0; i<timelineRowStrings.size(); i++)
    {
        timelineRowStrings[i].append("\n");
        timelineGraphAsString.append(timelineRowStrings.at(i));
    }

    // RMS Timeline Graph, draw X axis
    for(int i=0; i<timelineRowStrings[0].size(); i++)
    {
        if(i > majorCycleLength) break;
        if(i==0) {
             timelineGraphAsString.append(" ");
        }
        else if(i%5==0) {
            timelineGraphAsString.append(QString::number(i));
            if(i%(minorCycleLength)==0) {
                timelineGraphAsString.append(" ");
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
            timelineGraphAsString.append(".");
        }
    }
}

void DataVisualizer::DrawDMS()
{

}
