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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionEncrypt;
    QAction *actionDecrypt;
    QAction *actionPlain_Cipher;
    QAction *actionHistogram;
    QAction *actionHorizontal;
    QAction *actionVertical;
    QAction *actionEnthropy;
    QAction *actionDiagonal;
    QAction *actionNPCR_2;
    QAction *actionUACI_2;
    QAction *actionFull_Analysis;
    QAction *actionTest_RNG;
    QAction *actionEncryption_time;
    QAction *actionSave;
    QAction *actionAbout_Image_Encryptor;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QLabel *label_20;
    QLineEdit *lineEdit_y0;
    QLabel *label_x0;
    QLineEdit *lineEdit_x0;
    QLabel *label_y0;
    QLabel *label_3;
    QLineEdit *lineEdit_z0;
    QLabel *label_4;
    QComboBox *comboBox_Encoding;
    QLabel *label_z0;
    QComboBox *comboBox_ChaoticMap;
    QLineEdit *lineEdit_key;
    QLabel *label_7;
    QWidget *tab_4;
    QGridLayout *gridLayout_6;
    QLineEdit *lineEdit_X;
    QLineEdit *lineEdit_P;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_6;
    QLineEdit *lineEdit_K;
    QLabel *label_5;
    QWidget *tab_5;
    QGridLayout *gridLayout_4;
    QLabel *label_11;
    QSpinBox *EApopulationSpinBox;
    QLabel *label_12;
    QDoubleSpinBox *EAmutationRateSpinBox;
    QDoubleSpinBox *EAenthropySpinBox;
    QLabel *label_13;
    QLineEdit *lineEdit_EADeckey;
    QLabel *label_16;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEncryption;
    QMenu *menuAnalisys;
    QMenu *menuStatistical_Analisys;
    QMenu *menuCorrelation;
    QMenu *menuDifferential_Analisys;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(550, 650);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/windowIcon"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionEncrypt = new QAction(MainWindow);
        actionEncrypt->setObjectName(QStringLiteral("actionEncrypt"));
        actionDecrypt = new QAction(MainWindow);
        actionDecrypt->setObjectName(QStringLiteral("actionDecrypt"));
        actionPlain_Cipher = new QAction(MainWindow);
        actionPlain_Cipher->setObjectName(QStringLiteral("actionPlain_Cipher"));
        actionHistogram = new QAction(MainWindow);
        actionHistogram->setObjectName(QStringLiteral("actionHistogram"));
        actionHorizontal = new QAction(MainWindow);
        actionHorizontal->setObjectName(QStringLiteral("actionHorizontal"));
        actionVertical = new QAction(MainWindow);
        actionVertical->setObjectName(QStringLiteral("actionVertical"));
        actionEnthropy = new QAction(MainWindow);
        actionEnthropy->setObjectName(QStringLiteral("actionEnthropy"));
        actionDiagonal = new QAction(MainWindow);
        actionDiagonal->setObjectName(QStringLiteral("actionDiagonal"));
        actionNPCR_2 = new QAction(MainWindow);
        actionNPCR_2->setObjectName(QStringLiteral("actionNPCR_2"));
        actionUACI_2 = new QAction(MainWindow);
        actionUACI_2->setObjectName(QStringLiteral("actionUACI_2"));
        actionFull_Analysis = new QAction(MainWindow);
        actionFull_Analysis->setObjectName(QStringLiteral("actionFull_Analysis"));
        actionTest_RNG = new QAction(MainWindow);
        actionTest_RNG->setObjectName(QStringLiteral("actionTest_RNG"));
        actionEncryption_time = new QAction(MainWindow);
        actionEncryption_time->setObjectName(QStringLiteral("actionEncryption_time"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setEnabled(false);
        actionAbout_Image_Encryptor = new QAction(MainWindow);
        actionAbout_Image_Encryptor->setObjectName(QStringLiteral("actionAbout_Image_Encryptor"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        gridLayout_7->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 506, 367));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(scrollArea);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        scrollArea_2 = new QScrollArea(tab_2);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 506, 367));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(scrollAreaWidgetContents_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(scrollArea_2);

        tabWidget->addTab(tab_2, QString());

        gridLayout_7->addWidget(tabWidget, 0, 0, 1, 1);

        tabWidget_2 = new QTabWidget(centralWidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setTabBarAutoHide(true);
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout = new QVBoxLayout(tab_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, -1, -1, 5);
        label_20 = new QLabel(tab_3);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_3->addWidget(label_20, 0, 0, 1, 4, Qt::AlignBottom);

        lineEdit_y0 = new QLineEdit(tab_3);
        lineEdit_y0->setObjectName(QStringLiteral("lineEdit_y0"));
        lineEdit_y0->setMinimumSize(QSize(90, 0));

        gridLayout_3->addWidget(lineEdit_y0, 1, 3, 1, 1);

        label_x0 = new QLabel(tab_3);
        label_x0->setObjectName(QStringLiteral("label_x0"));
        label_x0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_x0, 1, 0, 1, 1);

        lineEdit_x0 = new QLineEdit(tab_3);
        lineEdit_x0->setObjectName(QStringLiteral("lineEdit_x0"));
        lineEdit_x0->setMinimumSize(QSize(90, 0));

        gridLayout_3->addWidget(lineEdit_x0, 1, 1, 1, 1);

        label_y0 = new QLabel(tab_3);
        label_y0->setObjectName(QStringLiteral("label_y0"));
        label_y0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_y0, 1, 2, 1, 1);

        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_z0 = new QLineEdit(tab_3);
        lineEdit_z0->setObjectName(QStringLiteral("lineEdit_z0"));
        lineEdit_z0->setMinimumSize(QSize(90, 0));

        gridLayout_3->addWidget(lineEdit_z0, 1, 5, 1, 1);

        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_4, 1, 6, 1, 1);

        comboBox_Encoding = new QComboBox(tab_3);
        comboBox_Encoding->setObjectName(QStringLiteral("comboBox_Encoding"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_Encoding->sizePolicy().hasHeightForWidth());
        comboBox_Encoding->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(comboBox_Encoding, 2, 7, 1, 1);

        label_z0 = new QLabel(tab_3);
        label_z0->setObjectName(QStringLiteral("label_z0"));
        label_z0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_z0, 1, 4, 1, 1);

        comboBox_ChaoticMap = new QComboBox(tab_3);
        comboBox_ChaoticMap->setObjectName(QStringLiteral("comboBox_ChaoticMap"));

        gridLayout_3->addWidget(comboBox_ChaoticMap, 1, 7, 1, 1);

        lineEdit_key = new QLineEdit(tab_3);
        lineEdit_key->setObjectName(QStringLiteral("lineEdit_key"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(10);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit_key->sizePolicy().hasHeightForWidth());
        lineEdit_key->setSizePolicy(sizePolicy3);
        lineEdit_key->setMaxLength(64);

        gridLayout_3->addWidget(lineEdit_key, 2, 1, 1, 5);

        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(5);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy4);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_7, 2, 6, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_6 = new QGridLayout(tab_4);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        lineEdit_X = new QLineEdit(tab_4);
        lineEdit_X->setObjectName(QStringLiteral("lineEdit_X"));

        gridLayout_6->addWidget(lineEdit_X, 1, 2, 1, 1);

        lineEdit_P = new QLineEdit(tab_4);
        lineEdit_P->setObjectName(QStringLiteral("lineEdit_P"));

        gridLayout_6->addWidget(lineEdit_P, 1, 5, 1, 1);

        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(45, 0));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_9, 1, 7, 1, 1);

        label_8 = new QLabel(tab_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(45, 0));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_8, 1, 3, 1, 1);

        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(45, 0));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_K = new QLineEdit(tab_4);
        lineEdit_K->setObjectName(QStringLiteral("lineEdit_K"));

        gridLayout_6->addWidget(lineEdit_K, 1, 8, 1, 2);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_6->addWidget(label_5, 0, 0, 1, 10, Qt::AlignBottom);

        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        gridLayout_4 = new QGridLayout(tab_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_11 = new QLabel(tab_5);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 1, 0, 1, 1);

        EApopulationSpinBox = new QSpinBox(tab_5);
        EApopulationSpinBox->setObjectName(QStringLiteral("EApopulationSpinBox"));
        EApopulationSpinBox->setMaximum(10);
        EApopulationSpinBox->setSingleStep(2);
        EApopulationSpinBox->setValue(4);

        gridLayout_4->addWidget(EApopulationSpinBox, 1, 1, 1, 1);

        label_12 = new QLabel(tab_5);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 1, 2, 1, 1);

        EAmutationRateSpinBox = new QDoubleSpinBox(tab_5);
        EAmutationRateSpinBox->setObjectName(QStringLiteral("EAmutationRateSpinBox"));
        EAmutationRateSpinBox->setMaximum(1);
        EAmutationRateSpinBox->setSingleStep(0.01);
        EAmutationRateSpinBox->setValue(0.5);

        gridLayout_4->addWidget(EAmutationRateSpinBox, 1, 3, 1, 1);

        EAenthropySpinBox = new QDoubleSpinBox(tab_5);
        EAenthropySpinBox->setObjectName(QStringLiteral("EAenthropySpinBox"));
        EAenthropySpinBox->setDecimals(4);
        EAenthropySpinBox->setMinimum(0);
        EAenthropySpinBox->setMaximum(8);
        EAenthropySpinBox->setSingleStep(0.01);
        EAenthropySpinBox->setValue(7.3);

        gridLayout_4->addWidget(EAenthropySpinBox, 1, 5, 1, 1);

        label_13 = new QLabel(tab_5);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_4->addWidget(label_13, 1, 4, 1, 1);

        lineEdit_EADeckey = new QLineEdit(tab_5);
        lineEdit_EADeckey->setObjectName(QStringLiteral("lineEdit_EADeckey"));

        gridLayout_4->addWidget(lineEdit_EADeckey, 4, 1, 1, 5);

        label_16 = new QLabel(tab_5);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_16, 4, 0, 1, 1);

        tabWidget_2->addTab(tab_5, QString());

        gridLayout_7->addWidget(tabWidget_2, 1, 0, 1, 1, Qt::AlignBottom);


        horizontalLayout->addLayout(gridLayout_7);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 550, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEncryption = new QMenu(menuBar);
        menuEncryption->setObjectName(QStringLiteral("menuEncryption"));
        menuAnalisys = new QMenu(menuBar);
        menuAnalisys->setObjectName(QStringLiteral("menuAnalisys"));
        menuStatistical_Analisys = new QMenu(menuAnalisys);
        menuStatistical_Analisys->setObjectName(QStringLiteral("menuStatistical_Analisys"));
        menuCorrelation = new QMenu(menuStatistical_Analisys);
        menuCorrelation->setObjectName(QStringLiteral("menuCorrelation"));
        menuDifferential_Analisys = new QMenu(menuAnalisys);
        menuDifferential_Analisys->setObjectName(QStringLiteral("menuDifferential_Analisys"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(tabWidget_2, lineEdit_x0);
        QWidget::setTabOrder(lineEdit_x0, lineEdit_y0);
        QWidget::setTabOrder(lineEdit_y0, lineEdit_z0);
        QWidget::setTabOrder(lineEdit_z0, comboBox_ChaoticMap);
        QWidget::setTabOrder(comboBox_ChaoticMap, comboBox_Encoding);
        QWidget::setTabOrder(comboBox_Encoding, lineEdit_X);
        QWidget::setTabOrder(lineEdit_X, lineEdit_P);
        QWidget::setTabOrder(lineEdit_P, lineEdit_K);
        QWidget::setTabOrder(lineEdit_K, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, lineEdit_key);
        QWidget::setTabOrder(lineEdit_key, scrollArea);
        QWidget::setTabOrder(scrollArea, tabWidget);
        QWidget::setTabOrder(tabWidget, scrollArea_2);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuEncryption->menuAction());
        menuBar->addAction(menuAnalisys->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEncryption->addAction(actionEncrypt);
        menuEncryption->addAction(actionDecrypt);
        menuAnalisys->addAction(menuStatistical_Analisys->menuAction());
        menuAnalisys->addAction(menuDifferential_Analisys->menuAction());
        menuAnalisys->addAction(actionFull_Analysis);
        menuAnalisys->addAction(actionEncryption_time);
        menuStatistical_Analisys->addAction(actionHistogram);
        menuStatistical_Analisys->addAction(menuCorrelation->menuAction());
        menuStatistical_Analisys->addAction(actionEnthropy);
        menuStatistical_Analisys->addAction(actionTest_RNG);
        menuCorrelation->addAction(actionHorizontal);
        menuCorrelation->addAction(actionVertical);
        menuCorrelation->addAction(actionDiagonal);
        menuDifferential_Analisys->addAction(actionNPCR_2);
        menuDifferential_Analisys->addAction(actionUACI_2);
        menuEdit->addAction(actionPlain_Cipher);
        menuHelp->addAction(actionAbout_Image_Encryptor);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);
        comboBox_ChaoticMap->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Image Encryptor", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionEncrypt->setText(QApplication::translate("MainWindow", "Encrypt", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionEncrypt->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDecrypt->setText(QApplication::translate("MainWindow", "Decrypt", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionDecrypt->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionPlain_Cipher->setText(QApplication::translate("MainWindow", "Plain<->Cipher", Q_NULLPTR));
        actionHistogram->setText(QApplication::translate("MainWindow", "Histogram", Q_NULLPTR));
        actionHorizontal->setText(QApplication::translate("MainWindow", "Horizontal", Q_NULLPTR));
        actionVertical->setText(QApplication::translate("MainWindow", "Vertical", Q_NULLPTR));
        actionEnthropy->setText(QApplication::translate("MainWindow", "Enthropy", Q_NULLPTR));
        actionDiagonal->setText(QApplication::translate("MainWindow", "Diagonal", Q_NULLPTR));
        actionNPCR_2->setText(QApplication::translate("MainWindow", "NPCR", Q_NULLPTR));
        actionUACI_2->setText(QApplication::translate("MainWindow", "UACI", Q_NULLPTR));
        actionFull_Analysis->setText(QApplication::translate("MainWindow", "Full Analysis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionFull_Analysis->setToolTip(QApplication::translate("MainWindow", "Full Analysis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTest_RNG->setText(QApplication::translate("MainWindow", "Create RNG data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTest_RNG->setToolTip(QApplication::translate("MainWindow", "for sts RNG test", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionEncryption_time->setText(QApplication::translate("MainWindow", "Encryption time", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionAbout_Image_Encryptor->setText(QApplication::translate("MainWindow", "About Image Encryptor", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Random Parameters", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Encrypt", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Decrypt", Q_NULLPTR));
        label->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Source Image", Q_NULLPTR));
        label_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\241ipher", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "Initial Conditions", Q_NULLPTR));
        lineEdit_y0->setText(QApplication::translate("MainWindow", "6.21", Q_NULLPTR));
        label_x0->setText(QApplication::translate("MainWindow", "x0:", Q_NULLPTR));
        lineEdit_x0->setInputMask(QString());
        lineEdit_x0->setText(QApplication::translate("MainWindow", "10.15", Q_NULLPTR));
        label_y0->setText(QApplication::translate("MainWindow", "y0:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Hash:", Q_NULLPTR));
        lineEdit_z0->setText(QApplication::translate("MainWindow", "20.38", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Chaotic Map:", Q_NULLPTR));
        comboBox_Encoding->clear();
        comboBox_Encoding->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        comboBox_Encoding->setCurrentText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        label_z0->setText(QApplication::translate("MainWindow", "z0:", Q_NULLPTR));
        comboBox_ChaoticMap->clear();
        comboBox_ChaoticMap->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Lorenz", Q_NULLPTR)
         << QApplication::translate("MainWindow", "PWLCM", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Logistic", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Tent", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Baker", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Henon", Q_NULLPTR)
        );
        lineEdit_key->setInputMask(QString());
        lineEdit_key->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "Encoding:", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("MainWindow", "DNA Algorithm", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "K", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "P", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Parameters", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "Yoon Algorithm", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Population Size", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Mutation Rate", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Enthropy", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "Decryption Key", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("MainWindow", "EA", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuEncryption->setTitle(QApplication::translate("MainWindow", "Encryption", Q_NULLPTR));
        menuAnalisys->setTitle(QApplication::translate("MainWindow", "Analysis", Q_NULLPTR));
        menuStatistical_Analisys->setTitle(QApplication::translate("MainWindow", "Statistical Analisys", Q_NULLPTR));
        menuCorrelation->setTitle(QApplication::translate("MainWindow", "Correlation", Q_NULLPTR));
        menuDifferential_Analisys->setTitle(QApplication::translate("MainWindow", "Differential Analisys", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
