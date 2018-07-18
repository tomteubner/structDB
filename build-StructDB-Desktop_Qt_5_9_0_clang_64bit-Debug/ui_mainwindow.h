/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *msgBoard;
    QPushButton *checkButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *showInput;
    QPushButton *setInput;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *showLog;
    QPushButton *setLog;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *showXYZ;
    QPushButton *setXYZ;
    QTableWidget *tableWidget;
    QPushButton *uploadButton;
    QLabel *label;
    QFrame *line;
    QFrame *line_2;
    QLineEdit *searchString;
    QPushButton *updateTable;
    QComboBox *boxRuntype;
    QLabel *label_2;
    QLineEdit *password;
    QLineEdit *username;
    QLineEdit *database;
    QLineEdit *ipaddress;
    QLineEdit *port;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1232, 730);
        MainWindow->setMinimumSize(QSize(1232, 730));
        MainWindow->setMaximumSize(QSize(1232, 730));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        msgBoard = new QPlainTextEdit(centralWidget);
        msgBoard->setObjectName(QStringLiteral("msgBoard"));
        msgBoard->setGeometry(QRect(850, 200, 371, 521));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(msgBoard->sizePolicy().hasHeightForWidth());
        msgBoard->setSizePolicy(sizePolicy);
        msgBoard->setAutoFillBackground(false);
        msgBoard->setTabChangesFocus(true);
        msgBoard->setUndoRedoEnabled(false);
        msgBoard->setReadOnly(true);
        msgBoard->setTextInteractionFlags(Qt::TextSelectableByMouse);
        checkButton = new QPushButton(centralWidget);
        checkButton->setObjectName(QStringLiteral("checkButton"));
        checkButton->setGeometry(QRect(850, 170, 101, 21));
        checkButton->setMinimumSize(QSize(91, 21));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(850, 20, 371, 139));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        showInput = new QLineEdit(layoutWidget);
        showInput->setObjectName(QStringLiteral("showInput"));
        showInput->setReadOnly(false);
        showInput->setClearButtonEnabled(true);

        horizontalLayout->addWidget(showInput);

        setInput = new QPushButton(layoutWidget);
        setInput->setObjectName(QStringLiteral("setInput"));
        setInput->setMinimumSize(QSize(101, 35));
        setInput->setMaximumSize(QSize(101, 35));

        horizontalLayout->addWidget(setInput);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        showLog = new QLineEdit(layoutWidget);
        showLog->setObjectName(QStringLiteral("showLog"));
        showLog->setReadOnly(false);
        showLog->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(showLog);

        setLog = new QPushButton(layoutWidget);
        setLog->setObjectName(QStringLiteral("setLog"));
        setLog->setMinimumSize(QSize(101, 35));
        setLog->setMaximumSize(QSize(101, 35));

        horizontalLayout_2->addWidget(setLog);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        showXYZ = new QLineEdit(layoutWidget);
        showXYZ->setObjectName(QStringLiteral("showXYZ"));
        showXYZ->setReadOnly(false);
        showXYZ->setClearButtonEnabled(true);

        horizontalLayout_3->addWidget(showXYZ);

        setXYZ = new QPushButton(layoutWidget);
        setXYZ->setObjectName(QStringLiteral("setXYZ"));
        setXYZ->setMinimumSize(QSize(101, 35));
        setXYZ->setMaximumSize(QSize(101, 35));

        horizontalLayout_3->addWidget(setXYZ);


        verticalLayout->addLayout(horizontalLayout_3);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(230, 10, 601, 711));
        tableWidget->setMinimumSize(QSize(381, 631));
        uploadButton = new QPushButton(centralWidget);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));
        uploadButton->setGeometry(QRect(950, 170, 271, 21));
        uploadButton->setMinimumSize(QSize(141, 21));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 91, 21));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(210, -30, 20, 821));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(830, -50, 20, 821));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        searchString = new QLineEdit(centralWidget);
        searchString->setObjectName(QStringLiteral("searchString"));
        searchString->setGeometry(QRect(10, 100, 191, 21));
        searchString->setAutoFillBackground(false);
        searchString->setClearButtonEnabled(true);
        updateTable = new QPushButton(centralWidget);
        updateTable->setObjectName(QStringLiteral("updateTable"));
        updateTable->setGeometry(QRect(10, 130, 191, 21));
        boxRuntype = new QComboBox(centralWidget);
        boxRuntype->setObjectName(QStringLiteral("boxRuntype"));
        boxRuntype->setGeometry(QRect(70, 70, 131, 26));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 58, 21));
        password = new QLineEdit(centralWidget);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(10, 700, 201, 21));
        password->setEchoMode(QLineEdit::Password);
        username = new QLineEdit(centralWidget);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(10, 670, 201, 21));
        database = new QLineEdit(centralWidget);
        database->setObjectName(QStringLiteral("database"));
        database->setGeometry(QRect(10, 640, 201, 21));
        ipaddress = new QLineEdit(centralWidget);
        ipaddress->setObjectName(QStringLiteral("ipaddress"));
        ipaddress->setGeometry(QRect(10, 610, 131, 21));
        port = new QLineEdit(centralWidget);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(150, 610, 61, 21));
        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(ipaddress, port);
        QWidget::setTabOrder(port, database);
        QWidget::setTabOrder(database, username);
        QWidget::setTabOrder(username, password);
        QWidget::setTabOrder(password, showInput);
        QWidget::setTabOrder(showInput, showLog);
        QWidget::setTabOrder(showLog, showXYZ);
        QWidget::setTabOrder(showXYZ, checkButton);
        QWidget::setTabOrder(checkButton, msgBoard);
        QWidget::setTabOrder(msgBoard, boxRuntype);
        QWidget::setTabOrder(boxRuntype, searchString);
        QWidget::setTabOrder(searchString, updateTable);
        QWidget::setTabOrder(updateTable, tableWidget);
        QWidget::setTabOrder(tableWidget, setXYZ);
        QWidget::setTabOrder(setXYZ, setLog);
        QWidget::setTabOrder(setLog, setInput);
        QWidget::setTabOrder(setInput, uploadButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        checkButton->setText(QApplication::translate("MainWindow", "Check", Q_NULLPTR));
        showInput->setText(QApplication::translate("MainWindow", "/Users/Tom/Sandbox/data/P4O10.inp", Q_NULLPTR));
        setInput->setText(QApplication::translate("MainWindow", "Input file", Q_NULLPTR));
        showLog->setText(QApplication::translate("MainWindow", "/Users/Tom/Sandbox/data/P4O10.log", Q_NULLPTR));
        setLog->setText(QApplication::translate("MainWindow", "Log file", Q_NULLPTR));
        showXYZ->setText(QApplication::translate("MainWindow", "/Users/Tom/Sandbox/data/", Q_NULLPTR));
        setXYZ->setText(QApplication::translate("MainWindow", "XYZ Path", Q_NULLPTR));
        uploadButton->setText(QApplication::translate("MainWindow", "Upload", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Filter Options", Q_NULLPTR));
        searchString->setText(QString());
        searchString->setPlaceholderText(QApplication::translate("MainWindow", "Atome", Q_NULLPTR));
        updateTable->setText(QApplication::translate("MainWindow", "Refresh", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Run Type", Q_NULLPTR));
        password->setPlaceholderText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        username->setPlaceholderText(QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        database->setPlaceholderText(QApplication::translate("MainWindow", "Database", Q_NULLPTR));
        ipaddress->setPlaceholderText(QApplication::translate("MainWindow", "IP Address", Q_NULLPTR));
        port->setPlaceholderText(QApplication::translate("MainWindow", "Port", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
