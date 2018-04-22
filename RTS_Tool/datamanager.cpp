#include "datamanager.h"
#include "qstringlist.h"
#include "qdebug.h"

QList<RawDataRow> DataManager::rawDataList;
QList<ProcessedDataRow> DataManager::processedDataList;

DataManager::DataManager()
{

}

void DataManager::AddRawData(QStringList processNameList, QStringList periodTList, QStringList computationTimeCList)
{
    for(int i=0; i<processNameList.size(); i++)
    {
        RawDataRow newRawDataRow(processNameList[i], periodTList[i].toInt(), computationTimeCList[i].toInt());
        rawDataList.append(newRawDataRow);
    }
}

void DataManager::ProcessRawData()
{
    // Create processed data list
    for(int i=0;i<rawDataList.size();i++)
    {
        ProcessedDataRow newProcessedDataRow(rawDataList[i].processName, rawDataList[i].periodT, rawDataList[i].computationTimeC, 0);
        processedDataList.append(newProcessedDataRow);
    }

    // Sort by period T to determine priority based on rate monotonic scheduling
    std::sort(processedDataList.begin(), processedDataList.end(), DataManager::dataComparison);

    // Add priority based on sort
    for(int i=0;i<processedDataList.size();i++)
    {
        processedDataList[i].rmsPriority = i+1;
    }

    // Calculate Lui-Layland Utilization U for the task set
    utilizationU = 0;
    for(int i=0;i<processedDataList.size();i++)
    {
        utilizationU += ((float)processedDataList.at(i).computationTimeC/(float)processedDataList.at(i).periodT);
    }
    qDebug() << utilizationU;
    float otherNumber = processedDataList.size()*(std::powf(2.f,(1.f/processedDataList.size()-1.f)));
    qDebug() << otherNumber;

    // Bounds check
    isSchedulable = (utilizationU <= otherNumber);
}
