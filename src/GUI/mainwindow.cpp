/*
    mainwindow.cpp
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "UmlClassItem.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->outputWindow->setStyleSheet // for output text

    //
    mainScene = new QGraphicsScene(this);
    mainScene->setSceneRect(-2500, -2500, 5000, 5000);

    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    
    //
    connect(ui->generateCodeBtn, &QPushButton::clicked, this, &MainWindow::handleGenerateClick);
    connect(ui->addClassBtn, &QPushButton::clicked, this, &MainWindow::handleAddClassOnScene);
    connect(mainScene, &QGraphicsScene::selectionChanged, this, &MainWindow::handleSelectionChanged);
    
    connect(ui->updateClassBtn, &QPushButton::clicked, this, &MainWindow::handleUpdateClassName);
    
    connect(ui->addAttrBtn, &QPushButton::clicked, this, &MainWindow::handleAddAttribute);
    connect(ui->removeAttrBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteAttribute);
    connect(ui->attrList, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleAttrSelection);
    // connect(ui->attrVisibilityList, &QComboBox::currentTextChanged, this, &MainWindow::handleAVisibilitySelection);
    
    connect(ui->addMethodBtn, &QPushButton::clicked, this, &MainWindow::handleAddMethod);
    connect(ui->removeMethodBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteMethod);
    connect(ui->methodList, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleMethodSelection);
    // connect(ui->methodVisibilityList, &QComboBox::currentTextChanged, this, &MainWindow::handleMVisibilitySelection);
    

    // connect(ui->editAttrBtn, &QPushButton::clicked, this, &MainWindow::handleEditAttribute);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleSelectionChanged()
{
    auto selectedItems = mainScene->selectedItems();

    if (selectedItems.isEmpty()) {
        // clears when background is clicked        
        currentSelectedItem = nullptr;
        ui->classNameEdit->clear();

        ui->attrList->clear();
        ui->attrNameEdit->clear();
        ui->attrTypeEdit->clear();
        ui->attrVisibilityList->clear();

        ui->methodList->clear();
        ui->methodNameEdit->clear();
        ui->methodTypeEdit->clear();
        ui->methodVisibilityList->clear();

        return; 
    }

    currentSelectedItem = dynamic_cast<UmlClassItem*>(selectedItems.first());

    if (currentSelectedItem != nullptr) {
        std::string className = currentSelectedItem->getBackendClass().GetName();
        ui->classNameEdit->setText(QString::fromStdString(className));

        refreshAttrList(); 
        refreshMethodList(); 
    }
}

