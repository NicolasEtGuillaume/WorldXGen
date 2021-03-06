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

    ui->widget->setCursor(Qt::WaitCursor);
    ui->widget->setMap(m->build());
    ui->widget->updateMapView();
    ui->widget->setCursor(Qt::ArrowCursor);
}

void MainWindow::on_pushButtonGoutteLancer_clicked()
{
    //Ajout d'une goutte
    if(ui->doubleSpinBoxGoutteX->value() < ui->widget->getMap()->getSizeX() && ui->doubleSpinBoxGoutteY->value() < ui->widget->getMap()->getSizeY()){
        ui->widget->getFilteredMap()->addGoutte((float)ui->doubleSpinBoxGoutteX->value(),(float)ui->doubleSpinBoxGoutteY->value());
    } else {
        QMessageBox msg;
        msg.warning(0, "Warning !", "The entered coordinates are not within the map");
    }


}

void MainWindow::on_pushButtonGoutteSuivant_clicked()
{
    //appel d'une itération de euler
    ui->widget->setCursor(Qt::WaitCursor);
    for(int i = 0; i <= 50 ; i++) ui->widget->getFilteredMap()->iterationEuler(0.01f);
    ui->widget->updateMapView();
    ui->widget->setCursor(Qt::ArrowCursor);
}

void MainWindow::on_pushButtonGoutteRes_clicked()
{
    //appel de euler jusqu'à la fin de la rivière
    ui->widget->setCursor(Qt::WaitCursor);
    bool done = true;
    while (done) {
        done = ui->widget->getFilteredMap()->iterationEuler(0.01f);
    }
    ui->widget->updateMapView();
    ui->widget->setCursor(Qt::ArrowCursor);
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

void MainWindow::on_actionUpdate_triggered()
{
    ui->widget->setCursor(Qt::WaitCursor);
    if (ui->widget->isMapSet()){
        ui->widget->filterMap();
        ui->widget->updateMapView();
    }

}

void MainWindow::on_actionCenter_triggered()
{
    ui->widget->setX_rot(0);
    ui->widget->setY_rot(0);
    ui->widget->setZ_rot(0);
    ui->widget->setCameraAimX(0);
    ui->widget->setCameraAimY(0);
    ui->widget->updateGL();
}

void MainWindow::on_pushButtonGoutteDynamic_clicked()
{
    ui->widget->setCursor(Qt::WaitCursor);
    bool notDone = true;
    int i =0;
    while (notDone) {
        if(i%50 == 0){
            ui->widget->updateMapView();
            ui->widget->updateGL();
        }
        notDone = ui->widget->getFilteredMap()->iterationEuler(0.01f);
        i++;
    }

    ui->widget->setCursor(Qt::ArrowCursor);
}
