#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "qstring.h"
#include "qlist.h"

struct ProcessData
{
    QString processName;
    int periodT;
    int computationTimeC;
    int deadlineD;
    int priority;
    float utilizationU;
    int availableT;
    float remainingC;

    ProcessData(QString inProcessName, int inPeriodT, int inComputationTimeC, int inDeadlineD, float inUtilizationU)
    {
        processName = inProcessName;
        periodT = inPeriodT;
        computationTimeC = inComputationTimeC;
        deadlineD = inDeadlineD;
        priority = 0;
        utilizationU = inUtilizationU;
        availableT = 0;
        remainingC = computationTimeC;
    }

    ProcessData(const ProcessData& inProcessData)
    {
        processName = inProcessData.processName;
        periodT = inProcessData.periodT;
        computationTimeC = inProcessData.computationTimeC;
        deadlineD = inProcessData.deadlineD;
        priority = inProcessData.priority;
        utilizationU = inProcessData.utilizationU;
        availableT = inProcessData.utilizationU;
        remainingC = inProcessData.remainingC;
    }
};

struct ScheduleInfo
{
    ProcessData* processData;
    int scheduledDuration;
    int minorCycleIndex;

    ScheduleInfo(ProcessData* inProcessData, int inScheduledDuration, int inMinorCycleIndex)
    {
        processData = inProcessData;
        scheduledDuration = inScheduledDuration;
        minorCycleIndex = inMinorCycleIndex;
    }
};

/*
 * The DataManager is the core of the application. It stores all scheduling data and
 * performs several operations on that data.
 */
class DataManager
{
public:
    DataManager();

    // Adds raw data to the data manager
    void AddRawData(QStringList processNameList, QStringList periodTList, QStringList computationTimeCList, QStringList deadlineDList);

    // Turns raw data to rms data
    void ProcessRmsData();

    // Turns raw data to dms data
    void ProcessDmsData();

    // Resets the data manager
    void Cleanup();

    // Executes the Lui Layland schedulability Test
    void LuiLaylandTest();

    // Executes Simplified Response Time Analysis
    void SimplifiedResponseTimeAnalysis(QList<ProcessData> dataList, QString& rtaResultString, QString& rtaCalculationString);

    // Executes Exact Response Time Analysis
    void ExactResponseTimeAnalysis(QList<ProcessData> dataList, QString& rtaResultString, QString& rtaCalculationString);

    // Executes Exact Response Time Analysis of one Task
    bool ExactResponseTimeAnalysisOfTask(QList<ProcessData> dataList, int index);

    // Executes Optimal Priority Assignment
    void OptimalPriorityAssignment(QList<ProcessData>& dataList);

    // Schedules a task
    void ScheduleTask(QList<ScheduleInfo*>& schedule, ProcessData* inProcessData, int inDuration, int inMinorCycleIndex);

    // Creates RMS Schedule
    void ScheduleRMS();

    // Creates DMS Schedule
    void ScheduleDMS();

    // Calculates Greatest Common Divider
    int CalculateGCD(int a, int b);

    // Calculates Lowest Common Multiple
    int CalculateLCM(QList<ProcessData>& dataList);

    // Process Data Lists
    QList<ProcessData> rawDataList;
    QList<ProcessData> RMS_DataList;
    QList<ProcessData> DMS_DataList;

    // Schedule Lists
    QList<ScheduleInfo*> RMS_Schedule;
    QList<ScheduleInfo*> DMS_Schedule;

    // Other. todo: replace them
    bool isSchedulable = false;
    float utilizationU;
    float utilizationBound;
    QString laylandCalculationString;
    QString optimalPriorityAssignmentString;

    // Comparision Operators used for sorting
    static bool dataComparison(const ProcessData &s1, const ProcessData &s2)
    {
        return s1.periodT < s2.periodT;
    }

    static bool dmsComparison(const ProcessData &s1, const ProcessData &s2)
    {
        return s1.deadlineD < s2.deadlineD;
    }

    static bool lowestPriorityFirst(const ProcessData &s1, const ProcessData &s2)
    {
        return s1.priority < s2.priority;
    }

};

#endif // DATAMANAGER_H
