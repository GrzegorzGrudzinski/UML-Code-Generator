#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
// #include <QGraphicsItem>

#include "UmlClassItem.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void handleGenerateClick(); 
    void handleSelectionChanged(); 
    
    void handleAddClassOnScene();
    void handleUpdateClassName();
    
    
    void handleAddAttribute();
    void refreshAttrList();                 
    void handleAttrSelection(int currentRow); 
    void handleEditAttribute();             
    void handleDeleteAttribute();           
    
    void handleAddMethod();
    void refreshMethodList();                 
    void handleMethodSelection(int currentRow); 
    void handleEditMethod();             
    void handleDeleteMethod();           
    
private:
    Ui::MainWindow *ui;

    QGraphicsScene *mainScene;

    UmlClassItem* currentSelectedItem = nullptr;
};
#endif // MAINWINDOW_H
