#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamanager.h"

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
    void SetupSchedulabilityTest(DataManager& dataManager);
    void SetupDataVisualization();
    void Cleanup();
    void DrawTimelineGraph();
};

#endif // MAINWINDOW_H
