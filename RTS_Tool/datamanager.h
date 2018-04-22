#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "qstring.h"
#include "qlist.h"

struct RawDataRow
{
    QString processName;
    int periodT;
    int computationTimeC;

    RawDataRow(QString inProcessName, int inPeriodT, int inComputationTimeC)
    {
        processName = inProcessName;
        periodT = inPeriodT;
        computationTimeC = inComputationTimeC;
    }
};

struct ProcessedDataRow
{
    QString processName;
    int periodT;
    int computationTimeC;
    int rmsPriority;

    ProcessedDataRow(QString inProcessName, int inPeriodT, int inComputationTimeC, int inRmsPriority)
    {
        processName = inProcessName;
        periodT = inPeriodT;
        computationTimeC = inComputationTimeC;
        rmsPriority = inRmsPriority;
    }
};

class DataManager
{
public:
    DataManager();

    // Adds raw data to the data manager
    void AddRawData(QStringList processNameList, QStringList periodTList, QStringList computationTimeCList);

    // Processes the raw data
    void ProcessRawData();

    // Resets the data manager
    void Cleanup();

    static QList<RawDataRow> rawDataList;
    static QList<ProcessedDataRow> processedDataList;

    bool isSchedulable = false;
    float utilizationU;

    static bool dataComparison(const ProcessedDataRow &s1, const ProcessedDataRow &s2)
    {
        return s1.periodT < s2.periodT;
    }
};

#endif // DATAMANAGER_H
