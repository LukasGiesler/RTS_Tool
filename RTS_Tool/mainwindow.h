#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filemanager.h"
#include "datamanager.h"
#include "datavisualizer.h"


/*
 * MainWindow is the entry point for the application
 * and manages all UI related tasks
 */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    // UI functions
    void SetupRawDataTable();
    void SetupProcessedDataTable();
    void SetupDmsDataTable();
    void SetupSchedulabilityTest();
    void SetupDataVisualization();
    void SetupResponseTimeAnalysis();
    void Cleanup();

    // References to all application compenents
    FileManager* fileManager;
    DataManager* dataManager;
    DataVisualizer* dataVisualizer;
};

#endif // MAINWINDOW_H
