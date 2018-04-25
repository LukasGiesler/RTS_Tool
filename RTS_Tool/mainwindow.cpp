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
    ui->utilizationUText->setPlainText(QString::number(dataManager.utilizationU));
    ui->laylandCalculationText->setPlainText(dataManager.laylandCalculationString);
    if(dataManager.isSchedulable)
    {
        ui->schedulabilityStatusText->setPlainText("Passed.");
        ui->schedulabilityStatusText->setStyleSheet("color:green;");

        // Visualize data
        DataVisualizer dataVisualizer;
        dataVisualizer.VisualizeData();
        ui->timelineStringText->setPlainText(dataVisualizer.timelineString);
        ui->timelineGraphAsStringText->setPlainText(dataVisualizer.timelineGraphAsString);
        //DrawTimelineGraph();
    }
    else
    {
        ui->schedulabilityStatusText->setPlainText("Failed.");
        ui->schedulabilityStatusText->setStyleSheet("color:red;");
    }

    // Setup processed task set table
    SetupProcessedDataTable();
}

void MainWindow::SetupRawDataTable()
{
    ui->rawTaskSetTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Process Name"), QTableWidgetItem::Type));
    ui->rawTaskSetTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Period T"), QTableWidgetItem::Type));
    ui->rawTaskSetTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Computation Time C"), QTableWidgetItem::Type));

    for(int i=0;i<DataManager::rawDataList.size();i++)
    {
        ui->rawTaskSetTable->insertRow(ui->rawTaskSetTable->rowCount());
        ui->rawTaskSetTable->setItem(i, 0, new QTableWidgetItem(DataManager::rawDataList.at(i).processName));
        ui->rawTaskSetTable->setItem(i, 1, new QTableWidgetItem(QString::number(DataManager::rawDataList.at(i).periodT)));
        ui->rawTaskSetTable->setItem(i, 2, new QTableWidgetItem(QString::number(DataManager::rawDataList.at(i).computationTimeC)));
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

void MainWindow::Cleanup()
{
    DataManager::rawDataList.clear();
    DataManager::processedDataList.clear();

    ui->rawTaskSetTable->clear();
    ui->rawTaskSetTable->setRowCount(0);
    ui->processedTaskSetTable->clear();
    ui->processedTaskSetTable->setRowCount(0);
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
