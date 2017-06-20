#include "newworlddialog.h"
#include "ui_newworlddialog.h"

NewWorldDialog::NewWorldDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewWorldDialog)
{
    ui->setupUi(this);
}

NewWorldDialog::~NewWorldDialog()
{
    delete ui;
}

std::string NewWorldDialog::getSeed()
{
    return ui->seed->text().toLocal8Bit().constData();
}

bool NewWorldDialog::isRandom()
{
    return ui->checkBox->isChecked();
}

int NewWorldDialog::getComboIndex()
{
    return ui->comboBox->currentIndex();
}

int NewWorldDialog::getSizeX()
{
    return ui->sizeX->value();
}

int NewWorldDialog::getSizeY()
{
    return ui->sizeY->value();
}
