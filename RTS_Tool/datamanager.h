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
};

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

    void LuiLaylandTest();

    QList<ProcessData> rawDataList;
    QList<ProcessData> processedDataList;
    QList<ProcessData> dmsDataList;

    bool isSchedulable = false;
    float utilizationU;
    float utilizationBound;
    QString laylandCalculationString;

    static bool dataComparison(const ProcessData &s1, const ProcessData &s2)
    {
        return s1.periodT < s2.periodT;
    }

    static bool dmsComparison(const ProcessData &s1, const ProcessData &s2)
    {
        return s1.deadlineD < s2.deadlineD;
    }

};

#endif // DATAMANAGER_H
