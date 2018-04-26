#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qvariant.h"
#include "filemanager.h"
#include "datamanager.h"
#include "datavisualizer.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Cleanup();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Import task set"), "", tr("Task set (*.csv)"));
    FileManager fileManager;

    if(!fileManager.ImportFile(fileName))
    {
        ui->importErrorText->setPlainText("Import failed.");
        return;
    }

    ui->importNameText->setPlainText(fileName);
    ui->importErrorText->setPlainText("");

    // Setup raw task set table
    SetupRawDataTable();

    // Process task set
    DataManager dataManager;
    dataManager.ProcessRawData();

    // Setup processed task set table
    SetupProcessedDataTable();

    // Setup Schedulability Test
    SetupSchedulabilityTest(dataManager);
}

void MainWindow::SetupRawDataTable()
{
    ui->rawTaskSetTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Process Name"), QTableWidgetItem::Type));
    ui->rawTaskSetTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Period T"), QTableWidgetItem::Type));
    ui->rawTaskSetTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Computation Time C"), QTableWidgetItem::Type));
    ui->rawTaskSetTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Deadline D"), QTableWidgetItem::Type));

    for(int i=0;i<DataManager::rawDataList.size();i++)
    {
        ui->rawTaskSetTable->insertRow(ui->rawTaskSetTable->rowCount());
        ui->rawTaskSetTable->setItem(i, 0, new QTableWidgetItem(DataManager::rawDataList.at(i).processName));
        ui->rawTaskSetTable->setItem(i, 1, new QTableWidgetItem(QString::number(DataManager::rawDataList.at(i).periodT)));
        ui->rawTaskSetTable->setItem(i, 2, new QTableWidgetItem(QString::number(DataManager::rawDataList.at(i).computationTimeC)));
        ui->rawTaskSetTable->setItem(i, 3, new QTableWidgetItem(QString::number(DataManager::rawDataList.at(i).deadlineD)));
    }
}

void MainWindow::SetupProcessedDataTable()
{
    ui->processedTaskSetTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Process Name"), QTableWidgetItem::Type));
    ui->processedTaskSetTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Period T"), QTableWidgetItem::Type));
    ui->processedTaskSetTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Computation Time C"), QTableWidgetItem::Type));
    ui->processedTaskSetTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("RMS Priority"), QTableWidgetItem::Type));
    ui->processedTaskSetTable->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Utilization U"), QTableWidgetItem::Type));

    for(int i=0;i<DataManager::rawDataList.size();i++)
    {
        ui->processedTaskSetTable->insertRow(ui->processedTaskSetTable->rowCount());
        ui->processedTaskSetTable->setItem(i, 0, new QTableWidgetItem(DataManager::processedDataList.at(i).processName));
        ui->processedTaskSetTable->setItem(i, 1, new QTableWidgetItem(QString::number(DataManager::processedDataList.at(i).periodT)));
        ui->processedTaskSetTable->setItem(i, 2, new QTableWidgetItem(QString::number(DataManager::processedDataList.at(i).computationTimeC)));
        ui->processedTaskSetTable->setItem(i, 3, new QTableWidgetItem(QString::number(DataManager::processedDataList.at(i).rmsPriority)));
        ui->processedTaskSetTable->setItem(i, 4, new QTableWidgetItem(QString::number(DataManager::processedDataList.at(i).utilizationU)));
    }

    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::SetupSchedulabilityTest(DataManager& dataManager)
{
    ui->utilizationUText->setPlainText(QString::number(dataManager.utilizationU));
    ui->utilizationBound->setPlainText(QString::number(dataManager.utilizationBound));
    ui->laylandCalculationText->setPlainText(dataManager.laylandCalculationString);

    if(dataManager.utilizationU <= dataManager.utilizationBound)
    {
        ui->schedulabilityStatusText->setPlainText("Success.");
        ui->schedulabilityStatusText->setStyleSheet("color:green;");
        SetupDataVisualization();
    }
    else if((dataManager.utilizationBound < dataManager.utilizationU) && (dataManager.utilizationU < 1))
    {
        ui->schedulabilityStatusText->setPlainText("Inconclusive.");
        ui->schedulabilityStatusText->setStyleSheet("color:DarkOrange;");
        SetupDataVisualization();
    }
    else
    {
        ui->schedulabilityStatusText->setPlainText("Overload.");
        ui->schedulabilityStatusText->setStyleSheet("color:red;");
    }
}

void MainWindow::SetupDataVisualization()
{
    // Visualize data
    DataVisualizer dataVisualizer;
    dataVisualizer.VisualizeData();
    ui->rmsTimelineStringText->setPlainText(dataVisualizer.rmsTimelineString);
    ui->timelineGraphAsStringText->setPlainText(dataVisualizer.timelineGraphAsString);
    ui->dmsTimelineStringText->setPlainText(dataVisualizer.dmsTimelineString);
}

void MainWindow::Cleanup()
{
    DataManager::rawDataList.clear();
    DataManager::processedDataList.clear();

    ui->rawTaskSetTable->clear();
    ui->rawTaskSetTable->setRowCount(0);
    ui->processedTaskSetTable->clear();
    ui->processedTaskSetTable->setRowCount(0);
    ui->timelineGraphAsStringText->setPlainText("");
    ui->rmsTimelineStringText->setPlainText("");
    ui->dmsTimelineStringText->setPlainText("");
}

void MainWindow::DrawTimelineGraph()
{

    /*
    QLineSeries *series = new QLineSeries();

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
    */
}
