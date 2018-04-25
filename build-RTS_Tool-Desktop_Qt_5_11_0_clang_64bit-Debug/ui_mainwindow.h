/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImport_File_csv;
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QTextEdit *importNameText;
    QPushButton *pushButton;
    QTextEdit *importErrorText;
    QWidget *tab_2;
    QTableWidget *rawTaskSetTable;
    QWidget *tab_5;
    QTableWidget *processedTaskSetTable;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *utilizationUText;
    QPlainTextEdit *plainTextEdit_2;
    QPlainTextEdit *schedulabilityStatusText;
    QPlainTextEdit *plainTextEdit_4;
    QPlainTextEdit *laylandCalculationText;
    QTextEdit *textEdit;
    QWidget *tab_6;
    QTextEdit *timelineStringText;
    QTextEdit *TextEdit;
    QTextEdit *timelineGraphAsStringText;
    QTextEdit *TextEdit_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1292, 673);
        actionImport_File_csv = new QAction(MainWindow);
        actionImport_File_csv->setObjectName(QStringLiteral("actionImport_File_csv"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        formLayoutWidget = new QWidget(tab);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 720, 90));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        importNameText = new QTextEdit(formLayoutWidget);
        importNameText->setObjectName(QStringLiteral("importNameText"));
        importNameText->setMinimumSize(QSize(500, 30));
        importNameText->setMaximumSize(QSize(500, 30));
        importNameText->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, importNameText);

        pushButton = new QPushButton(formLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 30));
        pushButton->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, pushButton);

        importErrorText = new QTextEdit(formLayoutWidget);
        importErrorText->setObjectName(QStringLiteral("importErrorText"));
        importErrorText->setMinimumSize(QSize(0, 30));
        importErrorText->setMaximumSize(QSize(16777215, 30));
        importErrorText->setStyleSheet(QLatin1String("color: rgb(255, 0, 0);\n"
"background-color: rgba(255, 255, 255, 0);\n"
" border: 0px solid black;"));
        importErrorText->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::LabelRole, importErrorText);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        rawTaskSetTable = new QTableWidget(tab_2);
        if (rawTaskSetTable->columnCount() < 3)
            rawTaskSetTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        rawTaskSetTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        rawTaskSetTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        rawTaskSetTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        rawTaskSetTable->setObjectName(QStringLiteral("rawTaskSetTable"));
        rawTaskSetTable->setEnabled(true);
        rawTaskSetTable->setGeometry(QRect(10, 10, 421, 311));
        rawTaskSetTable->setMaximumSize(QSize(421, 16777215));
        rawTaskSetTable->horizontalHeader()->setDefaultSectionSize(120);
        rawTaskSetTable->horizontalHeader()->setHighlightSections(true);
        rawTaskSetTable->horizontalHeader()->setMinimumSectionSize(39);
        rawTaskSetTable->horizontalHeader()->setStretchLastSection(true);
        rawTaskSetTable->verticalHeader()->setVisible(false);
        rawTaskSetTable->verticalHeader()->setDefaultSectionSize(30);
        rawTaskSetTable->verticalHeader()->setMinimumSectionSize(23);
        rawTaskSetTable->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        rawTaskSetTable->verticalHeader()->setStretchLastSection(false);
        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        processedTaskSetTable = new QTableWidget(tab_5);
        if (processedTaskSetTable->columnCount() < 5)
            processedTaskSetTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        processedTaskSetTable->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        processedTaskSetTable->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        processedTaskSetTable->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        processedTaskSetTable->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        processedTaskSetTable->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        processedTaskSetTable->setObjectName(QStringLiteral("processedTaskSetTable"));
        processedTaskSetTable->setEnabled(true);
        processedTaskSetTable->setGeometry(QRect(10, 10, 611, 311));
        processedTaskSetTable->setMaximumSize(QSize(800, 16777215));
        processedTaskSetTable->horizontalHeader()->setDefaultSectionSize(120);
        processedTaskSetTable->horizontalHeader()->setHighlightSections(true);
        processedTaskSetTable->horizontalHeader()->setMinimumSectionSize(39);
        processedTaskSetTable->horizontalHeader()->setStretchLastSection(false);
        processedTaskSetTable->verticalHeader()->setVisible(false);
        processedTaskSetTable->verticalHeader()->setDefaultSectionSize(30);
        processedTaskSetTable->verticalHeader()->setMinimumSectionSize(23);
        processedTaskSetTable->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        processedTaskSetTable->verticalHeader()->setStretchLastSection(false);
        gridLayoutWidget = new QWidget(tab_5);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(640, 10, 321, 152));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        utilizationUText = new QPlainTextEdit(gridLayoutWidget);
        utilizationUText->setObjectName(QStringLiteral("utilizationUText"));
        utilizationUText->setMinimumSize(QSize(0, 30));
        utilizationUText->setMaximumSize(QSize(16777215, 30));
        utilizationUText->setReadOnly(true);

        gridLayout->addWidget(utilizationUText, 1, 1, 1, 1);

        plainTextEdit_2 = new QPlainTextEdit(gridLayoutWidget);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setMinimumSize(QSize(0, 30));
        plainTextEdit_2->setMaximumSize(QSize(16777215, 30));
        plainTextEdit_2->setReadOnly(true);

        gridLayout->addWidget(plainTextEdit_2, 1, 0, 1, 1);

        schedulabilityStatusText = new QPlainTextEdit(gridLayoutWidget);
        schedulabilityStatusText->setObjectName(QStringLiteral("schedulabilityStatusText"));
        schedulabilityStatusText->setMinimumSize(QSize(0, 30));
        schedulabilityStatusText->setMaximumSize(QSize(16777215, 30));
        schedulabilityStatusText->setReadOnly(true);

        gridLayout->addWidget(schedulabilityStatusText, 2, 1, 1, 1);

        plainTextEdit_4 = new QPlainTextEdit(gridLayoutWidget);
        plainTextEdit_4->setObjectName(QStringLiteral("plainTextEdit_4"));
        plainTextEdit_4->setMinimumSize(QSize(0, 30));
        plainTextEdit_4->setMaximumSize(QSize(16777215, 30));
        plainTextEdit_4->setReadOnly(true);

        gridLayout->addWidget(plainTextEdit_4, 2, 0, 1, 1);

        laylandCalculationText = new QPlainTextEdit(gridLayoutWidget);
        laylandCalculationText->setObjectName(QStringLiteral("laylandCalculationText"));
        laylandCalculationText->setMinimumSize(QSize(0, 30));
        laylandCalculationText->setMaximumSize(QSize(16777215, 30));
        laylandCalculationText->setReadOnly(true);

        gridLayout->addWidget(laylandCalculationText, 3, 0, 1, 2);

        textEdit = new QTextEdit(gridLayoutWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(0, 30));
        textEdit->setMaximumSize(QSize(16777215, 30));

        gridLayout->addWidget(textEdit, 0, 0, 1, 2);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        timelineStringText = new QTextEdit(tab_6);
        timelineStringText->setObjectName(QStringLiteral("timelineStringText"));
        timelineStringText->setGeometry(QRect(10, 40, 500, 30));
        timelineStringText->setMinimumSize(QSize(500, 30));
        timelineStringText->setMaximumSize(QSize(500, 30));
        timelineStringText->setReadOnly(true);
        TextEdit = new QTextEdit(tab_6);
        TextEdit->setObjectName(QStringLiteral("TextEdit"));
        TextEdit->setGeometry(QRect(10, 10, 256, 30));
        TextEdit->setMinimumSize(QSize(0, 30));
        TextEdit->setMaximumSize(QSize(16777215, 30));
        TextEdit->setStyleSheet(QLatin1String("background-color: rgba(255, 255, 255, 0);\n"
"border: 0px solid black;"));
        TextEdit->setReadOnly(true);
        timelineGraphAsStringText = new QTextEdit(tab_6);
        timelineGraphAsStringText->setObjectName(QStringLiteral("timelineGraphAsStringText"));
        timelineGraphAsStringText->setGeometry(QRect(10, 110, 1001, 341));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        font.setPointSize(15);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        timelineGraphAsStringText->setFont(font);
        timelineGraphAsStringText->setStyleSheet(QStringLiteral("font: 15pt \"Courier\";"));
        timelineGraphAsStringText->setReadOnly(true);
        TextEdit_2 = new QTextEdit(tab_6);
        TextEdit_2->setObjectName(QStringLiteral("TextEdit_2"));
        TextEdit_2->setGeometry(QRect(10, 80, 256, 30));
        TextEdit_2->setMinimumSize(QSize(0, 30));
        TextEdit_2->setMaximumSize(QSize(16777215, 30));
        TextEdit_2->setStyleSheet(QLatin1String("background-color: rgba(255, 255, 255, 0);\n"
"border: 0px solid black;"));
        TextEdit_2->setReadOnly(true);
        tabWidget->addTab(tab_6, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionImport_File_csv->setText(QApplication::translate("MainWindow", "Import File (.csv)", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        tab->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        pushButton->setText(QApplication::translate("MainWindow", "Import task set (.csv)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Import File", nullptr));
        QTableWidgetItem *___qtablewidgetitem = rawTaskSetTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Process name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = rawTaskSetTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Period T", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = rawTaskSetTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Computation Time T", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Raw task set", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = processedTaskSetTable->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Process name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = processedTaskSetTable->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Period T", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = processedTaskSetTable->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Computation Time T", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = processedTaskSetTable->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "RMS Priority", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = processedTaskSetTable->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Utilization U", nullptr));
        plainTextEdit_2->setPlainText(QApplication::translate("MainWindow", "Utilization U:", nullptr));
        plainTextEdit_4->setPlainText(QApplication::translate("MainWindow", "Status:", nullptr));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\">Schedulability Check</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Processed task set", nullptr));
        TextEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\">Timeline string</span></p></body></html>", nullptr));
        timelineGraphAsStringText->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier'; font-size:15pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        TextEdit_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\">Timeline graph</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "Timeline", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
