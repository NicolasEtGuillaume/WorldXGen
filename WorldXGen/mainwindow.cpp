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
    }
    m->setSizeX(myDialog.getSizeX());
    m->setSizeY(myDialog.getSizeY());
    //((SimplePeaksMoutainMapBuilder *) m)->addGaussianCurve(new SimplePeaksMoutainMapBuilder::Gaussian3DCurve(myDialog.getSizeX()/2, myDialog.getSizeY()/2, 1., 1., 1.));
    ui->widget->setMap(m->build());
    ui->widget->updateMapView();
}
