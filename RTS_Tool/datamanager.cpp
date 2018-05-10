#include "datamanager.h"
#include "qdebug.h"
#include <cmath>

// Constructor
DataManager::DataManager()
{

}

// Creates raw Data List from Lists of task set columns
void DataManager::AddRawData(QStringList processNameList, QStringList periodTList, QStringList computationTimeCList, QStringList deadlineDList)
{
    rawDataList.clear();
    for(int i=0; i<processNameList.size(); i++)
    {
        ProcessData processData(processNameList[i], periodTList[i].toInt(), computationTimeCList[i].toInt(), deadlineDList[i].toInt(), 0);
        rawDataList.append(processData);
    }
}

// Process raw Data List to RMS Data List
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

// Perform Rate Monotonic Scheduling
void DataManager::ScheduleRMS()
{
    RMS_Schedule.clear();
    int minorCycleLength = RMS_DataList.at(0).periodT;
    int majorCycleLength = CalculateLCM(RMS_DataList);
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

// Process raw Data List to DMS Data List
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
}

// Perform Deadline Monotonic Scheduling
void DataManager::ScheduleDMS()
{
    DMS_Schedule.clear();
    int minorCycleLength = DMS_DataList.at(0).periodT;
    int majorCycleLength = CalculateLCM(DMS_DataList);
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
        for(int i=0; i<DMS_DataList.size(); i++)
        {
            // Check if current task is available (computation finished, Period T Check)
            if(DMS_DataList.at(i).availableT <= globalT)
            {
                int scheduleDuration = minorCycleLength - currentCycleC;
                if(scheduleDuration <= 0)
                {
                    // Out of Computation Time for this minor cycle
                    break;
                }
                else if(DMS_DataList.at(i).remainingC > scheduleDuration)
                {
                    // Task can partially be scheduled in this cycle
                    currentCycleC += scheduleDuration;
                    DMS_DataList[i].remainingC -= scheduleDuration;
                }
                else
                {
                    // Task can be fully scheduled in this cycle
                    scheduleDuration = DMS_DataList.at(i).remainingC;
                    DMS_DataList[i].availableT = globalT + DMS_DataList.at(i).periodT;
                    currentCycleC += DMS_DataList.at(i).remainingC;
                    globalT += DMS_DataList.at(i).remainingC;
                    DMS_DataList[i].remainingC = DMS_DataList.at(i).computationTimeC;// Restore Computation Time to default since we completely scheduled it
                }
                ScheduleTask(DMS_Schedule, &DMS_DataList[i], scheduleDuration, j);
            }
        }
    }
}

/*
 * Performs Lui-Layland Schedulability Test to test if the task set is schedulable.
 * A Utilization U of every task in the task set is computed. The utilization of all
 * tasks is accumulated and compared to the utilization bounds. There can be three outcomes of this test
 * Test Result < 0.69: Passed, the schedule is scheduable.
 * Test Result > 0.69 and < 1: Inconclusive, the schedule might be scheduable.
 * Test Result > 1: Overload, the schedule is not scheduable.
 *
 * For clarity a calculation String is generated for display in UI
 */
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

// Adds the task inProcessData to schedule
void DataManager::ScheduleTask(QList<ScheduleInfo*>& schedule, ProcessData* inProcessData, int inDuration, int inMinorCycleIndex)
{
    schedule.append(new ScheduleInfo(inProcessData, inDuration, inMinorCycleIndex));
}

/*
 * Simplified Response Time Analysis determines the response time of each task and
 * compares it to the deadline. This analysis has two outcomes:
 * Response Time <= Deadline: Pass
 * Response Time > Deadline: Failed, the task would violate its deadline
 *
 * Ri = Ci + Sum(RoundUp(Di/Tj)*Cj)
 * If Ri < Di, then DMS is scheduable
 * Sum of all tasks with higher priority
 *
 * For clarity a calculation String is generated for display in UI
 */
void DataManager::SimplifiedResponseTimeAnalysis(QList<ProcessData> dataList, QString& rtaResultString, QString& rtaCalculationString)
{
    rtaResultString.clear();
    rtaCalculationString.clear();

    double responseTimeR = 0.0;

    // Swap order based on priority
    std::sort(dataList.begin(), dataList.end(), DataManager::lowestPriorityFirst);

    // Iterate over all tasks from lowest to highest priority
    for(int i=0; i<dataList.size(); i++)
    {
        responseTimeR = dataList.at(i).computationTimeC;

        if(i==0) rtaCalculationString.append("R" + dataList.at(i).processName + " = " + QString::number(responseTimeR) + "\n");

        // Iterate over all tasks with higher priority than process i
        for(int j=1; j<=i && j<dataList.size(); j++)
        {
            double DdividedByT = ceil((double)dataList.at(i).deadlineD/(double)dataList.at(j).periodT);
            responseTimeR += DdividedByT*(double)dataList.at(j).computationTimeC;
            rtaCalculationString.append("R" + dataList.at(i).processName +  QString::number(j) + " = " + QString::number(responseTimeR) + "\n");
        }
    }

    // Check for deadline violation
    rtaCalculationString.append("Response Time Check: " + QString::number(responseTimeR) + " <= " + QString::number(dataList.first().deadlineD));
    if(responseTimeR <= dataList.first().deadlineD)
    {
        rtaResultString = "Passed.";
    }
    else
    {
        rtaResultString = "Failed.";
    }

}

/*
 * See Simplified Response Time Analysis. The exact response time analysis will additionaly
 * consider the previous response time and loop the response time calculation
 * until the response time no longer grows.
 *
 * For clarity a calculation String is generated for display in UI
 */
void DataManager::ExactResponseTimeAnalysis(QList<ProcessData> dataList, QString& rtaResultString, QString& rtaCalculationString)
{
    rtaResultString.clear();
    rtaCalculationString.clear();

    double responseTimeR = 0.0;

    // Iterate over all tasks from highest to lowest
    for(int i=0; i<dataList.size(); i++)
    {
        // Set default values for task i
        responseTimeR = dataList.at(i).computationTimeC;
        double previousResponseTime = 0.0;

        // First task or task with equal computation time to first
        if(dataList.at(i).computationTimeC == dataList.at(0).computationTimeC)
        {
            rtaCalculationString.append("R" + dataList.at(i).processName + " = " + QString::number(responseTimeR) + "\n");
            previousResponseTime = responseTimeR;// This is R0
            if(i==0) continue;
        }

        // Response Time Iteration Loop
        int rIndex = 1;
        while(true)
        {
            // Set default values for rIndex iteration
            double currentIterationResult = 0.0;
            responseTimeR = dataList.at(i).computationTimeC;
            rtaCalculationString.append("R" + dataList.at(i).processName +  QString::number(rIndex) + " = " + QString::number(dataList.at(i).computationTimeC));

            // Iterate over all tasks with higher priority than process i
            for(int j=1; j<=i && j<dataList.size(); j++)
            {
                if(previousResponseTime != 0.0)
                {
                    rtaCalculationString.append("+ [" + QString::number(previousResponseTime) + "/" + QString::number((double)dataList.at(j-1).periodT) + "] * " + QString::number((double)dataList.at(j-1).computationTimeC));
                }

                double DdividedByT = ceil(previousResponseTime/(double)dataList.at(j-1).periodT);
                currentIterationResult += DdividedByT * (double)dataList.at(j-1).computationTimeC;
            }

            // Accumlate the response time of all rIndex loops
            responseTimeR += currentIterationResult;
            rtaCalculationString.append(" = " + QString::number(responseTimeR) + "\n");

            // Stop Response Time Iteration if result doesn't change anymore
            if(responseTimeR == previousResponseTime)
            {
                rIndex = 1;
                break;
            }
            previousResponseTime = responseTimeR;
            rIndex++;
        }
    }

    // Response Time Check for deadline violation
    rtaCalculationString.append("Response Time Check: " + QString::number(responseTimeR) + " < " + QString::number(dataList.last().deadlineD));
    if(responseTimeR < dataList.last().deadlineD)
    {
        rtaResultString = "Passed.";
    }
    else
    {
        rtaResultString = "Failed.";
    }
}

/*
 * Executes exact RTA for one task.
 * See Exact Response Time Analysis for more information.
 */
bool DataManager::ExactResponseTimeAnalysisOfTask(QList<ProcessData> dataList, int index)
{
    double responseTimeR = dataList.at(index).computationTimeC;
    double previousResponseTime = responseTimeR;

    // Response Time Iteration Loop
    int rIndex = 1;
    while(true)
    {
        // Set default values for rIndex iteration
        double currentIterationResult = 0.0;
        responseTimeR = dataList.at(index).computationTimeC;

        // Iterate over all tasks
        for(int j=0; j<dataList.size(); j++)
        {
            if(j == index) continue; // ignore the same task, e.g. A==A

            // Special Case, first task will always have result of computation time. The +1 simulates round up within the calculation.
            if(j == 0) {
                currentIterationResult += (double)dataList.at(j).computationTimeC + 1;
                continue;
            }

            //
            double DdividedByT = ceil(previousResponseTime/(double)dataList.at(j-1).periodT);
            currentIterationResult += DdividedByT * (double)dataList.at(j-1).computationTimeC;
        }

        // Accumulate Response Time of all loop iterations
        responseTimeR += currentIterationResult;

        // Stop Response Time Iteration if result doesn't change anymore
        if(responseTimeR == previousResponseTime)
        {
            rIndex = 1;
            break;
        }
        previousResponseTime = responseTimeR;
        rIndex++;
    }

    // Deadline violation check
    if(responseTimeR < dataList.at(index).deadlineD)
    {
        return true;
    }

    return false;
}

/*
 * Optimal Priority Assignment using Exact Response Time Analysis.
 * Close to copy&paste from RTS script page 38
 */
void DataManager::OptimalPriorityAssignment(QList<ProcessData>& dataList)
{
    for(int k=0; k<dataList.size(); k++)
    {
        bool ok = false;
        for(int next=k; next<dataList.size(); next++)
        {
            // Swap Priorities of k and next
            int tmpPriority = dataList[k].priority;
            dataList[k].priority = dataList[next].priority;
            dataList[next].priority = tmpPriority;

            ok = ExactResponseTimeAnalysisOfTask(dataList, k);
            // RTA of k
            if(ok)
            {
                break; // exit loop
            }
        }
    }
}

// Calculates Lowest Common Mulitple of dataList
int DataManager::CalculateLCM(QList<ProcessData>& dataList)
{
    int outLCM = dataList.at(0).periodT;
    for(int i=0; i<dataList.size(); i++)
    {
        outLCM = (((dataList.at(i).periodT * outLCM))/(CalculateGCD(dataList.at(i).periodT, outLCM)));

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
