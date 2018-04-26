#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "qstring.h"
#include "qlist.h"

struct RawDataRow
{
    QString processName;
    int periodT;
    int computationTimeC;
    int deadlineD;

    RawDataRow(QString inProcessName, int inPeriodT, int inComputationTimeC, int inDeadlineD)
    {
        processName = inProcessName;
        periodT = inPeriodT;
        computationTimeC = inComputationTimeC;
        deadlineD = inDeadlineD;
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

struct dmsDataRow
{
    QString processName;
    int periodT;
    int computationTimeC;
    int dmsPriority;
    float utilizationU;
    float availableT;

    dmsDataRow(QString inProcessName, int inPeriodT, int inComputationTimeC, int inDmsPriority, float inUtilizationU)
    {
        processName = inProcessName;
        periodT = inPeriodT;
        computationTimeC = inComputationTimeC;
        dmsPriority = inDmsPriority;
        utilizationU = inUtilizationU;
        availableT = 0;
    }

    dmsDataRow(const dmsDataRow& inDmsDataRow)
    {
        processName = inDmsDataRow.processName;
        periodT = inDmsDataRow.periodT;
        computationTimeC = inDmsDataRow.computationTimeC;
        dmsPriority = inDmsDataRow.dmsPriority;
        utilizationU = inDmsDataRow.utilizationU;
        availableT = inDmsDataRow.availableT;
    }
};

class DataManager
{
public:
    DataManager();

    // Adds raw data to the data manager
    void AddRawData(QStringList processNameList, QStringList periodTList, QStringList computationTimeCList, QStringList deadlineDList);

    // Turns raw data to rms data
    void ProcessRawData();

    // Turns raw data to dms data
    void ProcessDmsData();

    // Resets the data manager
    void Cleanup();

    void LuiLaylandTest();

    static QList<RawDataRow> rawDataList;
    static QList<ProcessedDataRow> processedDataList;
    static QList<dmsDataRow> dmsDataList;

    bool isSchedulable = false;
    float utilizationU;
    float utilizationBound;
    QString laylandCalculationString;

    static bool dataComparison(const ProcessedDataRow &s1, const ProcessedDataRow &s2)
    {
        return s1.periodT < s2.periodT;
    }

    static bool dmsComparison(const dmsDataRow &s1, const dmsDataRow &s2)
    {
        return s1.periodT < s2.periodT;
    }

};

#endif // DATAMANAGER_H
