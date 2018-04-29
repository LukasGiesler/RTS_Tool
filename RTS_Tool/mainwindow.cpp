#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qvariant.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "qdebug.h"

using namespace QtCharts;

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Cleanup();

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

    // Setup raw task set table
    SetupRawDataTable();

    // Setup processed task set table
    SetupProcessedDataTable();

    // Setup Schedulability Test
    SetupSchedulabilityTest();

    // Setup dms task set
    dataManager->ProcessDmsData();
    SetupDmsDataTable();
}

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
        ui->processedTaskSetTable->setItem(i, 0, new QTableWidgetItem(dataManager->processedDataList.at(i).processName));
        ui->processedTaskSetTable->setItem(i, 1, new QTableWidgetItem(QString::number(dataManager->processedDataList.at(i).periodT)));
        ui->processedTaskSetTable->setItem(i, 2, new QTableWidgetItem(QString::number(dataManager->processedDataList.at(i).computationTimeC)));
        ui->processedTaskSetTable->setItem(i, 3, new QTableWidgetItem(QString::number(dataManager->processedDataList.at(i).priority)));
        ui->processedTaskSetTable->setItem(i, 4, new QTableWidgetItem(QString::number(dataManager->processedDataList.at(i).utilizationU)));
    }

    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::SetupDmsDataTable()
{
    ui->dmsTaskSetTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Process Name"), QTableWidgetItem::Type));
    ui->dmsTaskSetTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Period T"), QTableWidgetItem::Type));
    ui->dmsTaskSetTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Computation Time C"), QTableWidgetItem::Type));
    ui->dmsTaskSetTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Deadline D"), QTableWidgetItem::Type));
    ui->dmsTaskSetTable->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("DMS Priority"), QTableWidgetItem::Type));

    for(int i=0;i<dataManager->rawDataList.size();i++)
    {
        qDebug() << dataManager->dmsDataList.size();
        ui->dmsTaskSetTable->insertRow(ui->dmsTaskSetTable->rowCount());
        ui->dmsTaskSetTable->setItem(i, 0, new QTableWidgetItem(dataManager->dmsDataList.at(i).processName));
        ui->dmsTaskSetTable->setItem(i, 1, new QTableWidgetItem(QString::number(dataManager->dmsDataList.at(i).periodT)));
        ui->dmsTaskSetTable->setItem(i, 2, new QTableWidgetItem(QString::number(dataManager->dmsDataList.at(i).computationTimeC)));
        ui->dmsTaskSetTable->setItem(i, 3, new QTableWidgetItem(QString::number(dataManager->dmsDataList.at(i).deadlineD)));
        ui->dmsTaskSetTable->setItem(i, 4, new QTableWidgetItem(QString::number(dataManager->dmsDataList.at(i).priority)));
    }

}

void MainWindow::SetupSchedulabilityTest()
{
    ui->utilizationUText->setPlainText(QString::number(dataManager->utilizationU));
    ui->utilizationBound->setPlainText(QString::number(dataManager->utilizationBound));
    ui->laylandCalculationText->setPlainText(dataManager->laylandCalculationString);

    if(dataManager->utilizationU <= dataManager->utilizationBound)
    {
        ui->schedulabilityStatusText->setPlainText("Success.");
        ui->schedulabilityStatusText->setStyleSheet("color:green;");
        SetupDataVisualization();
    }
    else if((dataManager->utilizationBound < dataManager->utilizationU) && (dataManager->utilizationU <= 1))
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
    dataVisualizer->VisualizeData();
    ui->rmsTimelineStringText->setPlainText(dataVisualizer->rmsTimelineString);
    ui->timelineGraphAsStringText->setPlainText(dataVisualizer->timelineGraphAsString);
    ui->dmsTimelineStringText->setPlainText(dataVisualizer->dmsTimelineString);
}

void MainWindow::Cleanup()
{
    ui->rawTaskSetTable->clear();
    ui->rawTaskSetTable->setRowCount(0);
    ui->processedTaskSetTable->clear();
    ui->processedTaskSetTable->setRowCount(0);
    ui->timelineGraphAsStringText->setPlainText("");
    ui->rmsTimelineStringText->setPlainText("");
    ui->dmsTimelineStringText->setPlainText("");
    ui->dmsTaskSetTable->clear();
    ui->dmsTaskSetTable->setRowCount(0);
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
