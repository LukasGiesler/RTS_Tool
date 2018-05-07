#include "datamanager.h"
#include "qstringlist.h"
#include "qdebug.h"
#include <cmath>

DataManager::DataManager()
{

}

void DataManager::AddRawData(QStringList processNameList, QStringList periodTList, QStringList computationTimeCList, QStringList deadlineDList)
{
    rawDataList.clear();
    for(int i=0; i<processNameList.size(); i++)
    {
        ProcessData processData(processNameList[i], periodTList[i].toInt(), computationTimeCList[i].toInt(), deadlineDList[i].toInt(), 0);
        rawDataList.append(processData);
    }
}

void DataManager::ProcessRmsData()
{
    RMS_DataList.clear();
    // Create processed data list
    for(int i=0;i<rawDataList.size();i++)
    {
        ProcessData processData(rawDataList[i].processName, rawDataList[i].periodT, rawDataList[i].computationTimeC, 0, 0);
        RMS_DataList.append(processData);
    }

    // Sort by period T to determine priority based on rate monotonic scheduling
    std::sort(RMS_DataList.begin(), RMS_DataList.end(), DataManager::dataComparison);

    // Add priority based on sort
    for(int i=0;i<RMS_DataList.size();i++)
    {
        RMS_DataList[i].priority = RMS_DataList.size() - i;
    }

    // Test schedulability
    LuiLaylandTest();
}

void DataManager::ScheduleRMS()
{
    RMS_Schedule.clear();
    int minorCycleLength = RMS_DataList.at(0).periodT;
    int majorCycleLength = CalculateLCM();
    int minorCyclesPerMajorCycle = majorCycleLength/minorCycleLength;
    int globalT = 0;
    int currentCycleC = 0;

    // Schedule a major cycle
    for(int j=0; j<minorCyclesPerMajorCycle; j++)
    {
        // At the start of each minor cycle, the current t is known
        globalT = j*minorCycleLength;
        currentCycleC = 0;

        // Schedule a minor cycle
        for(int i=0; i<RMS_DataList.size(); i++)
        {
            // Check if current task is available (computation finished, Period T Check)
            if(RMS_DataList.at(i).availableT <= globalT)
            {
                int scheduleDuration = minorCycleLength - currentCycleC;
                if(scheduleDuration <= 0)
                {
                    // Out of Computation Time for this minor cycle
                    break;
                }
                else if(RMS_DataList.at(i).remainingC > scheduleDuration)
                {
                    // Task can partially be scheduled in this cycle
                    currentCycleC += scheduleDuration;
                    RMS_DataList[i].remainingC -= scheduleDuration;
                }
                else
                {
                    // Task can be fully scheduled in this cycle
                    scheduleDuration = RMS_DataList.at(i).remainingC;
                    RMS_DataList[i].availableT = globalT + RMS_DataList.at(i).periodT;
                    currentCycleC += RMS_DataList.at(i).remainingC;
                    globalT += RMS_DataList.at(i).remainingC;
                    RMS_DataList[i].remainingC = RMS_DataList.at(i).computationTimeC;// Restore Computation Time to default since we completely scheduled it
                }
                ScheduleTask(RMS_Schedule, &RMS_DataList[i], scheduleDuration, j);
            }
        }
    }
}

void DataManager::ProcessDmsData()
{
    DMS_DataList.clear();
    // Create processed data list
    for(int i=0;i<rawDataList.size();i++)
    {
        ProcessData processData(rawDataList[i].processName, rawDataList[i].periodT, rawDataList[i].computationTimeC, rawDataList[i].deadlineD, 0);
        DMS_DataList.append(processData);
    }

    // Sort by period T to determine priority based on deadline monotonic scheduling
    std::sort(DMS_DataList.begin(), DMS_DataList.end(), DataManager::dmsComparison);

    // Add priority based on sort
    for(int i=0;i<DMS_DataList.size();i++)
    {
        DMS_DataList[i].priority = DMS_DataList.size() - i;
    }

    // Test schedulability
    //LuiLaylandTest();
}

void DataManager::ScheduleDMS()
{

}

void DataManager::LuiLaylandTest()
{
    // Calculate Lui-Layland Utilization U for the task set
    laylandCalculationString.clear();
    laylandCalculationString.append("U=");
    utilizationU = 0;
    for(int i=0;i<RMS_DataList.size();i++)
    {
        float currentUtilizationU = ((float)RMS_DataList.at(i).computationTimeC/(float)RMS_DataList.at(i).periodT);
        utilizationU += currentUtilizationU;
        RMS_DataList[i].utilizationU = currentUtilizationU;
        if(i>0) laylandCalculationString.append(" + ");
        laylandCalculationString.append(QString::number(RMS_DataList.at(i).computationTimeC) + "/" + QString::number(RMS_DataList.at(i).periodT));
    }
    laylandCalculationString.append(" = " + QString::number(utilizationU));

    utilizationBound = RMS_DataList.size()*(std::pow(2.f,1.f/RMS_DataList.size())-1.f);
}

// Calculates Lowest Common Mulitple
int DataManager::CalculateLCM()
{
    int outLCM = RMS_DataList.at(0).periodT;
    for(int i=0; i<RMS_DataList.size(); i++)
    {
        outLCM = (((RMS_DataList.at(i).periodT * outLCM))/(CalculateGCD(RMS_DataList.at(i).periodT, outLCM)));

    }
    return outLCM;
}

// Calculates Greatest Common Divider
int DataManager::CalculateGCD(int a, int b)
{
    if (b == 0)
        return a;
    return CalculateGCD(b, a % b);
}

void DataManager::ScheduleTask(QList<ScheduleInfo*>& schedule, ProcessData* inProcessData, int inDuration, int inMinorCycleIndex)
{
    schedule.append(new ScheduleInfo(inProcessData, inDuration, inMinorCycleIndex));
}

