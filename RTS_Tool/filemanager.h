#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "qstring.h"
#include "datamanager.h"

class FileManager
{
public:
    FileManager();
    FileManager(DataManager* inDataManager);
    bool ImportFile(QString file);

    DataManager* dataManager;
};

#endif // FILEMANAGER_H
