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

void MainWindow::on_actionNewWorld_triggered()
{
    NewWorldDialog myDialog;
    myDialog.setModal(true);
    myDialog.exec();

    if (myDialog.result() == myDialog.Rejected) return;

    MapBuilder * m;
    switch (myDialog.getComboIndex())
    {
        case 0 :
            m = new FullyRandomMapBuilder();
            break;
        case 1 :
            m = new SimplePeaksMoutainMapBuilder();
            break;
        case 2 :
            m = new PeaksMountainChainMapBuilder();
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

    ui->widget->setMap(m->build());
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

void MainWindow::on_addFilterButton_clicked()
{
    EditFilterDialog editFilterDialog;
    editFilterDialog.setModal(true);
    editFilterDialog.exec();

    if (editFilterDialog.result() == editFilterDialog.Rejected) return;

    FilterMatrix * filter = new FilterMatrix();
    valarray<int> * matrix = editFilterDialog.getMatrix(); // vector<line<int>>
    filter->setMatrix(matrix);

    ui->widget->addMapFilter(filter);
    updateFiltersView();
}

void MainWindow::on_removeFilterButton_clicked()
{
    QModelIndexList indexesList = ui->filterListWidget->selectionModel()->selectedIndexes();
    for (QModelIndex index : indexesList)
    {
        ui->widget->removeMapFilter(index.row());
    }
    updateFiltersView();
}

void MainWindow::updateFiltersView()
{
    ui->filterListWidget->clear();
    int count = ui->widget->getMapFiltersCount();
    for (int i = 0; i < count; ++i)
    {
        QString name = "Filter : matrix " + QString::number(i);
        ui->filterListWidget->addItem(name);
    }
}
