#include "datavisualizer.h"
#include "datamanager.h"
#include "qdebug.h"
#include <numeric>

DataVisualizer::DataVisualizer()
{

}

void DataVisualizer::VisualizeData()
{

    CalculateLCM();
    // Cleanup
    timelineString.clear();

    /* RMS Scheduling Concept
     * 1. Lowest Common Multiple of period T of sorted task list to determine Major Cycle Length
     * 2. Minor Cycle Length is the smallest period T
     * 3. Each Minor Cycle Loop
     * 3.1 Check Task with highest priority (lowest period T)
     * 3.2 If task is currently not computing, start the task.
     * 3.3 If it is computing, go to next task.
     */

    // todo: Create Timeline string
    int minorCycleLength = DataManager::processedDataList.at(0).periodT;
    int majorCycleLength = CalculateLCM();
    int minorCyclesPerMajorCycle = majorCycleLength/minorCycleLength;
    int globalT = 0;
    int currentCycleC = 0;

    // Debug Graph
    QList<QString> timelineGraphStrings;
    for(int i=0; i<DataManager::processedDataList.size(); i++)
    {
        timelineGraphStrings.append(DataManager::processedDataList.at(i).processName);
    }

    // Schedule a major cycle
    for(int j=0; j<minorCyclesPerMajorCycle; j++)
    {
        // At the start of each minor cycle, the current t is known
        globalT = j*minorCycleLength;
        // Schedule a minor cycle
        for(int i=0; i<DataManager::processedDataList.size(); i++)
        {
            // Check if current task is available (computation finished)
            if(DataManager::processedDataList.at(i).availableT <= globalT)
            {
                qDebug() << "If: " << (currentCycleC + DataManager::processedDataList.at(i).computationTimeC);
                // Check if the current task fits into the current minor cycle
                if((currentCycleC + DataManager::processedDataList.at(i).computationTimeC) <= minorCycleLength)
                {//Fit
                    ProcessedDataRow newProcessedDataRow = DataManager::processedDataList.at(i);
                    currentCycleC += DataManager::processedDataList.at(i).computationTimeC;
                    newProcessedDataRow.availableT = globalT + DataManager::processedDataList.at(i).periodT;// todo: Consider what happens if minor cycle length is exceeded here
                    globalT += DataManager::processedDataList.at(i).computationTimeC;
                    timelineString.append(newProcessedDataRow.processName);
                    DataManager::processedDataList.removeAt(i);
                    DataManager::processedDataList.insert(i, newProcessedDataRow);

                    // Debug Graph
                    for(int k=0; k<timelineGraphStrings.size(); k++)
                    {
                        for(int l=0; l<DataManager::processedDataList.at(i).computationTimeC; l++)
                        {
                            if(k == i)
                            {
                                timelineGraphStrings[k].append("-");
                            }
                            else
                            {
                                timelineGraphStrings[k].append(".");
                            }
                        }
                    }

                    //qDebug() << DataManager::processedDataList.at(i).processName << " executes for " << DataManager::processedDataList.at(i).computationTimeC << " and will finish at t = " << DataManager::processedDataList.at(i).availableT;
                }
                else
                {//Doesn't fit
                    break;
                }
            }
        }
        qDebug() << minorCycleLength-currentCycleC;
        // Debug Graph
        for(int k=0; k<timelineGraphStrings.size(); k++)
        {
            for(int l=0; l<minorCycleLength-currentCycleC; l++)
            {
                timelineGraphStrings[k].append(".");
            }
        }
        currentCycleC = 0;
        timelineString.append(" ");

        for(int k=0; k<timelineGraphStrings.size(); k++)
        {
            timelineGraphStrings[k].append(" ");
        }
    }

    // Debug Graph End
    for(int i=0; i<timelineGraphStrings.size(); i++)
    {
        timelineGraphStrings[i].append("\n");
        timelineGraphAsString.append(timelineGraphStrings.at(i));
    }
    for(int i=0; i<timelineGraphStrings[0].size(); i++)
    {
        if(i > majorCycleLength)
        {
            break;
        }
        if(i==0)
        {
             timelineGraphAsString.append(" ");
        }
        else if(i%5==0)
        {
            timelineGraphAsString.append(QString::number(i));
            if(i%(minorCycleLength)==0)
            {
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

    /* String Concept
     * abcabdeabcabd
     *
     */

    /* Chart Concept
     *
     *  ^
     * a| -   -   -  -
     * b|  -   -   -  -
     * c|   -       -
     * d|       -      -
     * e|        -
     * *0----5----10----15->
     */
}


// Calculates Lowest Common Mulitple
int DataVisualizer::CalculateLCM()
{
    int outLCM = DataManager::processedDataList.at(0).periodT;
    for(int i=0; i<DataManager::processedDataList.size(); i++)
    {
        outLCM = (((DataManager::processedDataList.at(i).periodT * outLCM))/(CalculateGCD(DataManager::processedDataList.at(i).periodT, outLCM)));

    }
    qDebug() << QString::number(outLCM);
    return outLCM;
}

int DataVisualizer::CalculateGCD(int a, int b)
{
    if (b == 0)
        return a;
    return CalculateGCD(b, a % b);
}
