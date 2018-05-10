#include "filemanager.h"
#include "qfile.h"
#include "qdebug.h"
#include "datamanager.h"

FileManager::FileManager()
{

}

FileManager::FileManager(DataManager* inDataManager)
{
    dataManager = inDataManager;
}

// Reads a .csv file and stores it in the dataManger
bool FileManager::ImportFile(QString inFile)
{
    QFile file(inFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return false;
    }

    // Temp lists to store each column
    QStringList processNameList;
    QStringList periodTList;
    QStringList computationTimeCList;
    QStringList deadlineDList;

    // Iterate over columns
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        processNameList.append(line.split(',').at(0));
        periodTList.append(line.split(',').at(1));
        computationTimeCList.append(line.split(',').at(2));

        // If deadline column is empty, set the deadline to 0
        if(line.split(',').at(3) != nullptr)
        {
            deadlineDList.append(line.split(',').at(3));
        }
        else
        {
            deadlineDList.append(0);
        }
    }

    // Add imported data to the data manager list
    dataManager->AddRawData(processNameList, periodTList, computationTimeCList, deadlineDList);

    return true;
}
