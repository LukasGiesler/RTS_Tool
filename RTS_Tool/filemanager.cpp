#include "filemanager.h"
#include "qfile"
#include "qdebug.h"
#include "datamanager.h"

FileManager::FileManager()
{

}

// Reads a .csv file
bool FileManager::ImportFile(QString inFile)
{
    QFile file(inFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return false;
    }

    QStringList processNameList;
    QStringList periodTList;
    QStringList computationTimeCList;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        processNameList.append(line.split(',').at(0));
        periodTList.append(line.split(',').at(1));
        computationTimeCList.append(line.split(',').at(2));
    }

    // Add imported data to the static data manager list
    DataManager dataManager;
    dataManager.AddRawData(processNameList, periodTList, computationTimeCList);


    // Debug Output
    qDebug() << processNameList;
    qDebug() << periodTList;
    qDebug() << computationTimeCList;
    return true;
}
