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
    cout << myDialog.getComboIndex() << endl;
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
