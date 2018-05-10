#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qdebug.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    dataManager = new DataManager();
    fileManager = new FileManager(dataManager);
    dataVisualizer = new DataVisualizer(dataManager);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * The Import File Button kicks off most of the Application Code
 */
void MainWindow::on_pushButton_clicked()
{
    // Make sure everything is reset
    Cleanup();

    // Import the .csv file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import task set"), "", tr("Task set (*.csv)"));

    if(!fileManager->ImportFile(fileName))
    {
        ui->importErrorText->setPlainText("Import failed.");
        return;
    }

    ui->importNameText->setPlainText(fileName);
    ui->importErrorText->setPlainText("");

    // Process task set
    dataManager->ProcessRmsData();
    dataManager->ProcessDmsData();

    // Setup raw task set table
    SetupRawDataTable();

    // Setup processed task set table
    SetupProcessedDataTable();

    // Setup Schedulability Test
    SetupSchedulabilityTest();

    // Process DMS Data
    dataManager->ProcessDmsData();

    // Setup dms task set table
    SetupDmsDataTable();

    // Setup Response Time Analysis and Optimal Priority Assignment using RTA for the DMS Schedule
    SetupResponseTimeAnalysis();
}

// Setup the raw task set UI
void MainWindow::SetupRawDataTable()
{
    ui->rawTaskSetTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Process Name"), QTableWidgetItem::Type));
    ui->rawTaskSetTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Period T"), QTableWidgetItem::Type));
    ui->rawTaskSetTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Computation Time C"), QTableWidgetItem::Type));
    ui->rawTaskSetTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Deadline D"), QTableWidgetItem::Type));

    for(int i=0;i<dataManager->rawDataList.size();i++)
    {
        ui->rawTaskSetTable->insertRow(ui->rawTaskSetTable->rowCount());
        ui->rawTaskSetTable->setItem(i, 0, new QTableWidgetItem(dataManager->rawDataList.at(i).processName));
        ui->rawTaskSetTable->setItem(i, 1, new QTableWidgetItem(QString::number(dataManager->rawDataList.at(i).periodT)));
        ui->rawTaskSetTable->setItem(i, 2, new QTableWidgetItem(QString::number(dataManager->rawDataList.at(i).computationTimeC)));
        ui->rawTaskSetTable->setItem(i, 3, new QTableWidgetItem(QString::number(dataManager->rawDataList.at(i).deadlineD)));
    }
}

// Setup the RMS task set UI
void MainWindow::SetupProcessedDataTable()
{
    ui->processedTaskSetTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Process Name"), QTableWidgetItem::Type));
    ui->processedTaskSetTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Period T"), QTableWidgetItem::Type));
    ui->processedTaskSetTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Computation Time C"), QTableWidgetItem::Type));
    ui->processedTaskSetTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("RMS Priority"), QTableWidgetItem::Type));
    ui->processedTaskSetTable->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Utilization U"), QTableWidgetItem::Type));

    for(int i=0;i<dataManager->rawDataList.size();i++)
    {
        ui->processedTaskSetTable->insertRow(ui->processedTaskSetTable->rowCount());
        ui->processedTaskSetTable->setItem(i, 0, new QTableWidgetItem(dataManager->RMS_DataList.at(i).processName));
        ui->processedTaskSetTable->setItem(i, 1, new QTableWidgetItem(QString::number(dataManager->RMS_DataList.at(i).periodT)));
        ui->processedTaskSetTable->setItem(i, 2, new QTableWidgetItem(QString::number(dataManager->RMS_DataList.at(i).computationTimeC)));
        ui->processedTaskSetTable->setItem(i, 3, new QTableWidgetItem(QString::number(dataManager->RMS_DataList.at(i).priority)));
        ui->processedTaskSetTable->setItem(i, 4, new QTableWidgetItem(QString::number(dataManager->RMS_DataList.at(i).utilizationU)));
    }

    ui->tabWidget->setCurrentIndex(1);
}

// Setup the DMS Table task set UI
void MainWindow::SetupDmsDataTable()
{
    ui->dmsTaskSetTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Process Name"), QTableWidgetItem::Type));
    ui->dmsTaskSetTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Period T"), QTableWidgetItem::Type));
    ui->dmsTaskSetTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Computation Time C"), QTableWidgetItem::Type));
    ui->dmsTaskSetTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Deadline D"), QTableWidgetItem::Type));
    ui->dmsTaskSetTable->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("DMS Priority"), QTableWidgetItem::Type));

    for(int i=0;i<dataManager->rawDataList.size();i++)
    {
        ui->dmsTaskSetTable->insertRow(ui->dmsTaskSetTable->rowCount());
        ui->dmsTaskSetTable->setItem(i, 0, new QTableWidgetItem(dataManager->DMS_DataList.at(i).processName));
        ui->dmsTaskSetTable->setItem(i, 1, new QTableWidgetItem(QString::number(dataManager->DMS_DataList.at(i).periodT)));
        ui->dmsTaskSetTable->setItem(i, 2, new QTableWidgetItem(QString::number(dataManager->DMS_DataList.at(i).computationTimeC)));
        ui->dmsTaskSetTable->setItem(i, 3, new QTableWidgetItem(QString::number(dataManager->DMS_DataList.at(i).deadlineD)));
        ui->dmsTaskSetTable->setItem(i, 4, new QTableWidgetItem(QString::number(dataManager->DMS_DataList.at(i).priority)));
    }
}

// Setup the Lui-Layland Schedulability Test UI
void MainWindow::SetupSchedulabilityTest()
{
    ui->utilizationUText->setPlainText(QString::number(dataManager->utilizationU));
    ui->utilizationBound->setPlainText(QString::number(dataManager->utilizationBound));
    ui->laylandCalculationText->setPlainText(dataManager->laylandCalculationString);

    if(dataManager->utilizationU <= dataManager->utilizationBound)
    {
        ui->schedulabilityStatusText->setPlainText("Success.");
        ui->schedulabilityStatusText->setStyleSheet("color:green;border: 0px solid black;");
        SetupDataVisualization();
    }
    else if((dataManager->utilizationBound < dataManager->utilizationU) && (dataManager->utilizationU <= 1))
    {
        ui->schedulabilityStatusText->setPlainText("Inconclusive.");
        ui->schedulabilityStatusText->setStyleSheet("color:DarkOrange;border: 0px solid black;");
        SetupDataVisualization();
    }
    else
    {
        ui->schedulabilityStatusText->setPlainText("Overload.");
        ui->schedulabilityStatusText->setStyleSheet("color:red;border: 0px solid black;");
    }
}

// Setup the Timeline Graph for RMS and DMS
void MainWindow::SetupDataVisualization()
{
    // Visualize data
    dataManager->ScheduleRMS();
    dataManager->ScheduleDMS();

    QString scheduleAsString;
    QString scheduleAsGraph;

    dataVisualizer->DrawTimeline(dataManager->RMS_Schedule, scheduleAsString, scheduleAsGraph);
    ui->rmsTimelineStringText->setPlainText(scheduleAsString);
    ui->rmsTimelineText->setPlainText(scheduleAsGraph);

    dataVisualizer->DrawTimeline(dataManager->DMS_Schedule, scheduleAsString, scheduleAsGraph);
    ui->dmsTimelineStringText->setPlainText(scheduleAsString);
    ui->dmsTimelineText->setPlainText(scheduleAsGraph);
}

// Setup Response Time Analysis and Optimal Priority Assignment using RTA for the DMS Schedule
void MainWindow::SetupResponseTimeAnalysis()
{
    QString rtaResultString;
    QString rtaCalculationString;

    dataManager->SimplifiedResponseTimeAnalysis(dataManager->DMS_DataList, rtaResultString, rtaCalculationString);
    ui->simplifiedRTAResultText->setPlainText(rtaResultString);
    ui->simplifiedRTAStringText->setPlainText(rtaCalculationString);

    dataManager->ExactResponseTimeAnalysis(dataManager->DMS_DataList, rtaResultString, rtaCalculationString);
    ui->exactRTAResultText->setPlainText(rtaResultString);
    ui->exactRTAStringText->setPlainText(rtaCalculationString);

    dataManager->OptimalPriorityAssignment(dataManager->DMS_DataList);

    // Update DMS task set table with new priorities. NOTE: Other UI elements will not be updated to reflect the priority changes
    for(int i=0;i<dataManager->DMS_DataList.size();i++)
    {
        ui->dmsTaskSetTable->setItem(i, 4, new QTableWidgetItem(QString::number(dataManager->DMS_DataList.at(i).priority)));
    }
}

// Restore the UI to default setup
void MainWindow::Cleanup()
{
    ui->rawTaskSetTable->clear();
    ui->rawTaskSetTable->setRowCount(0);
    ui->processedTaskSetTable->clear();
    ui->processedTaskSetTable->setRowCount(0);
    ui->rmsTimelineText->setPlainText("");
    ui->rmsTimelineStringText->setPlainText("");
    ui->dmsTimelineStringText->setPlainText("");
    ui->dmsTaskSetTable->clear();
    ui->dmsTaskSetTable->setRowCount(0);
    ui->dmsTimelineText->setPlainText("");
    ui->laylandCalculationText->setPlainText("");
    ui->utilizationBound->setPlainText("");
    ui->utilizationUText->setPlainText("");
    ui->simplifiedRTAResultText->setPlainText("");
    ui->simplifiedRTAStringText->setPlainText("");
    ui->exactRTAResultText->setPlainText("");
    ui->exactRTAStringText->setPlainText("");
}
