#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filemanager.h"
#include "datamanager.h"
#include "datavisualizer.h"

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

    void SetupRawDataTable();
    void SetupProcessedDataTable();
    void SetupDmsDataTable();
    void SetupSchedulabilityTest();
    void SetupDataVisualization();
    void Cleanup();
    void DrawTimelineGraph();

    FileManager* fileManager;
    DataManager* dataManager;
    DataVisualizer* dataVisualizer;
};

#endif // MAINWINDOW_H
