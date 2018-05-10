#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "qstring.h"
#include "datamanager.h"

/*
 * The FileManager handles importing of .csv task sets.
 */
class FileManager
{
public:
    // Constructors
    FileManager();
    FileManager(DataManager* inDataManager);

    // Imports a .csv file and stores it using the Data Manager
    bool ImportFile(QString file);

    // Reference to the current Data Manager
    DataManager* dataManager;
};

#endif // FILEMANAGER_H
