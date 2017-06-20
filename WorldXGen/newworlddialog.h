#ifndef NEWWORLDDIALOG_H
#define NEWWORLDDIALOG_H

#include <QDialog>

namespace Ui {
class NewWorldDialog;
}

class NewWorldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewWorldDialog(QWidget *parent = 0);
    ~NewWorldDialog();

    std::string getSeed();
    bool isRandom();
    int getComboIndex();
    int getSizeX();
    int getSizeY();

private:
    Ui::NewWorldDialog *ui;
};

#endif // NEWWORLDDIALOG_H
