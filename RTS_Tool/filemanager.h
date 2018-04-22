#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "qstring.h"

class FileManager
{
public:
    FileManager();

    bool ImportFile(QString file);
};

#endif // FILEMANAGER_H
