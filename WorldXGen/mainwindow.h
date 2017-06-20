#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "newworlddialog.h"
#include "mapbuilder.h"
#include "fullyrandommapbuilder.h"
#include "simplepeaksmoutainmapbuilder.h"
#include "peaksmountainchainmapbuilder.h"
#include "filter.h"
#include "filteraveraging.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNewWorld_triggered();

    void on_pushButtonGoutteLancer_clicked();

    void on_pushButtonGoutteSuivant_clicked();

    void on_pushButtonGoutteRes_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
