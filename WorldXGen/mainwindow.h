#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <valarray>
#include "newworlddialog.h"
#include "mapbuilder.h"
#include "fullyrandommapbuilder.h"
#include "simplepeaksmoutainmapbuilder.h"
#include "peaksmountainchainmapbuilder.h"
#include "filter.h"
#include "filtermatrix.h"
#include "filteraveraging.h"
#include "editfilterdialog.h"

namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateFiltersView();

private slots:
    void on_actionNewWorld_triggered();

    void on_pushButtonGoutteLancer_clicked();

    void on_pushButtonGoutteSuivant_clicked();

    void on_pushButtonGoutteRes_clicked();

    void on_addFilterButton_clicked();

    void on_editFilterButton_clicked();

    void on_removeFilterButton_clicked();

    void on_moveUpButton_clicked();

    void on_moveDownButton_clicked();

    void on_actionUpdate_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
