#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNouveau_monde_triggered()
{

    NouveauMondeDialog myDialog;
    myDialog.setModal(true);
    myDialog.exec();
    FullyRandomMapBuilder * m = new FullyRandomMapBuilder();
    if(!myDialog.isRandom()){
        m->setSeed(myDialog.getSeed());
    }
    m->setSizeX(6);
    m->setSizeY(7);
    ui->widget->setMap(m->build());
    ui->widget->updateMapView();
}
