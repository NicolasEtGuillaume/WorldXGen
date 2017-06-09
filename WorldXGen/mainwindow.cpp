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
    MapBuilder * m;
    switch (myDialog.getComboIndex())
    {
        case 0 :
            m = new FullyRandomMapBuilder();
            break;
        case 1 :
            m = new SimplePeaksMoutainMapBuilder();
            break;
        default :
            m = new SimplePeaksMoutainMapBuilder();
    }

    if(!myDialog.isRandom()){
        m->setSeed(myDialog.getSeed());
    } else {
        m->setSeed(new Seed());
    }
    m->setSizeX(myDialog.getSizeX())
        ->setSizeY(myDialog.getSizeY());

    Filter * filter = new FilterAveraging();

    ui->widget->setMap(filter->apply(m->build()));
    ui->widget->updateMapView();
}

void MainWindow::on_pushButtonGoutteLancer_clicked()
{
    //Ajout d'une goutte
    ui->widget->getMap()->addGoutte((float)ui->doubleSpinBoxGoutteX->value(),(float)ui->doubleSpinBoxGoutteY->value());
    ui->widget->updateMapView();
}

void MainWindow::on_pushButtonGoutteSuivant_clicked()
{
    //appel d'une itération de euler
    ui->widget->getMap()->iterationEuler(0.1);
    ui->widget->updateMapView();
}

void MainWindow::on_pushButtonGoutteRes_clicked()
{
    //appel de euler jusqu'à la fin de la rivière
    bool done = true;
    while (done) {
        done = ui->widget->getMap()->iterationEuler(0.1);
    }
    ui->widget->updateMapView();
}
