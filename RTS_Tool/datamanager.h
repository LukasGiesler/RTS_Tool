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
    float utilizationU;
    float availableT;

    ProcessedDataRow(QString inProcessName, int inPeriodT, int inComputationTimeC, int inRmsPriority, float inUtilizationU)
    {
        processName = inProcessName;
        periodT = inPeriodT;
        computationTimeC = inComputationTimeC;
        rmsPriority = inRmsPriority;
        utilizationU = inUtilizationU;
        availableT = 0;
    }

    ProcessedDataRow(const ProcessedDataRow& inProcessedDataRow)
    {
        processName = inProcessedDataRow.processName;
        periodT = inProcessedDataRow.periodT;
        computationTimeC = inProcessedDataRow.computationTimeC;
        rmsPriority = inProcessedDataRow.rmsPriority;
        utilizationU = inProcessedDataRow.utilizationU;
        availableT = inProcessedDataRow.availableT;
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
    float utilizationBound;
    QString laylandCalculationString;

    static bool dataComparison(const ProcessedDataRow &s1, const ProcessedDataRow &s2)
    {
        return s1.periodT < s2.periodT;
    }
};

#endif // DATAMANAGER_H
