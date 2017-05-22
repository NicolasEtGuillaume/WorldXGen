#include "nouveaumondedialog.h"
#include "ui_nouveaumondedialog.h"

NouveauMondeDialog::NouveauMondeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NouveauMondeDialog)
{
    ui->setupUi(this);
}

NouveauMondeDialog::~NouveauMondeDialog()
{
    delete ui;
}

std::string NouveauMondeDialog::getSeed()
{
    return ui->seed->text().toLocal8Bit().constData();
}

bool NouveauMondeDialog::isRandom()
{
    return ui->checkBox->isChecked();
}
