#include "datamanager.h"
#include "qstringlist.h"
#include "qdebug.h"
#include <cmath>

DataManager::DataManager()
{

}

void DataManager::AddRawData(QStringList processNameList, QStringList periodTList, QStringList computationTimeCList, QStringList deadlineDList)
{
    for(int i=0; i<processNameList.size(); i++)
    {
        ProcessData processData(processNameList[i], periodTList[i].toInt(), computationTimeCList[i].toInt(), deadlineDList[i].toInt(), 0);
        qDebug() << processData.deadlineD;
        rawDataList.append(processData);
    }
}

void DataManager::ProcessRmsData()
{
    // Create processed data list
    for(int i=0;i<rawDataList.size();i++)
    {
        ProcessData processData(rawDataList[i].processName, rawDataList[i].periodT, rawDataList[i].computationTimeC, 0, 0);
        processedDataList.append(processData);
    }

    // Sort by period T to determine priority based on rate monotonic scheduling
    std::sort(processedDataList.begin(), processedDataList.end(), DataManager::dataComparison);

    // Add priority based on sort
    for(int i=0;i<processedDataList.size();i++)
    {
        processedDataList[i].priority = processedDataList.size() - i;
    }

    // Test schedulability
    LuiLaylandTest();
}

void DataManager::ProcessDmsData()
{
    // Create processed data list
    for(int i=0;i<rawDataList.size();i++)
    {
        ProcessData processData(rawDataList[i].processName, rawDataList[i].periodT, rawDataList[i].computationTimeC, rawDataList[i].deadlineD, 0);
        dmsDataList.append(processData);
    }

    // Sort by period T to determine priority based on deadline monotonic scheduling
    std::sort(dmsDataList.begin(), dmsDataList.end(), DataManager::dmsComparison);

    // Add priority based on sort
    for(int i=0;i<dmsDataList.size();i++)
    {
        dmsDataList[i].priority = dmsDataList.size() - i;
    }

    // Test schedulability
    //LuiLaylandTest();
}

void DataManager::LuiLaylandTest()
{
    // Calculate Lui-Layland Utilization U for the task set
    laylandCalculationString.clear();
    laylandCalculationString.append("U=");
    utilizationU = 0;
    for(int i=0;i<processedDataList.size();i++)
    {
        float currentUtilizationU = ((float)processedDataList.at(i).computationTimeC/(float)processedDataList.at(i).periodT);
        utilizationU += currentUtilizationU;
        processedDataList[i].utilizationU = currentUtilizationU;
        if(i>0) laylandCalculationString.append(" + ");
        laylandCalculationString.append(QString::number(processedDataList.at(i).computationTimeC) + "/" + QString::number(processedDataList.at(i).periodT));
    }
    laylandCalculationString.append(" = " + QString::number(utilizationU));

    utilizationBound = processedDataList.size()*(std::pow(2.f,1.f/processedDataList.size())-1.f);
}

