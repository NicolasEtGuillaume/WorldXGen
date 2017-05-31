#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "nouveaumondedialog.h"
#include "mapbuilder.h"
#include "fullyrandommapbuilder.h"
#include "simplepeaksmoutainmapbuilder.h"
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
    void on_actionNouveau_monde_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
