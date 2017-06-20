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

}

void MainWindow::on_pushButtonGoutteSuivant_clicked()
{
    //appel d'une itération de euler
    for(int i = 0; i <= 50 ; i++) ui->widget->getMap()->iterationEuler(0.01f);
    ui->widget->updateMapView();
}

void MainWindow::on_pushButtonGoutteRes_clicked()
{
    //appel de euler jusqu'à la fin de la rivière
    bool done = true;
    while (done) {
        done = ui->widget->getMap()->iterationEuler(0.01f);
    }
    ui->widget->updateMapView();
}

void MainWindow::on_addFilterButton_clicked()
{
    EditFilterDialog editFilterDialog;
    editFilterDialog.setModal(true);
    editFilterDialog.exec();

    if (editFilterDialog.result() == editFilterDialog.Rejected) return;

    QString filterCustomName = editFilterDialog.getCustomName();
    FilterMatrix * filter;
    if (filterCustomName.length() > 0) {
        filter = new FilterMatrix(filterCustomName);
    } else {
        filter = new FilterMatrix();
    }

    valarray<int> * matrix = editFilterDialog.getMatrix(); // vector<line<int>>
    filter->setMatrix(matrix);

    ui->widget->addMapFilter(filter);
    updateFiltersView();
}

void MainWindow::on_editFilterButton_clicked()
{
    QModelIndexList indexesList = ui->filterListWidget->selectionModel()->selectedIndexes();
    for (QModelIndex index : indexesList)
    {
        FilterMatrix * filter = ui->widget->getMapFilter(index.row());

        EditFilterDialog editFilterDialog;
        editFilterDialog.setMatrix(filter->getMatrix());
        editFilterDialog.setCustomName(filter->customName);

        editFilterDialog.setModal(true);
        editFilterDialog.exec();

        filter->setMatrix(editFilterDialog.getMatrix());
        filter->customName = editFilterDialog.getCustomName();
    }
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

void MainWindow::on_moveUpButton_clicked()
{
    QModelIndexList indexesList = ui->filterListWidget->selectionModel()->selectedIndexes();
    for (QModelIndex index : indexesList)
    {
        ui->widget->moveMapFilterUp(index.row());
    }
    updateFiltersView();
}

void MainWindow::on_moveDownButton_clicked()
{
    QModelIndexList indexesList = ui->filterListWidget->selectionModel()->selectedIndexes();
    for (QModelIndex index : indexesList)
    {
        ui->widget->moveMapFilterDown(index.row());
    }
    updateFiltersView();
}

void MainWindow::updateFiltersView()
{
    ui->filterListWidget->clear();
    int count = ui->widget->getMapFiltersCount();
    for (int i = 0; i < count; ++i)
    {
        QString name = QString::number(i) + ". " + ui->widget->getMapFilterName(i);
        ui->filterListWidget->addItem(name);
    }
}
