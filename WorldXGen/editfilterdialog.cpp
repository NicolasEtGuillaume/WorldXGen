#include "editfilterdialog.h"
#include "ui_editfilterdialog.h"

EditFilterDialog::EditFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFilterDialog)
{
    ui->setupUi(this);
}

EditFilterDialog::~EditFilterDialog()
{
    delete ui;
}

valarray<int> * EditFilterDialog::getMatrix()
{
    valarray<int> * matrix = new valarray<int>(25);

    (*matrix)[0]   = ui->spinBox->value();
    (*matrix)[1]   = ui->spinBox_2->value();
    (*matrix)[2]   = ui->spinBox_3->value();
    (*matrix)[3]   = ui->spinBox_4->value();
    (*matrix)[4]   = ui->spinBox_5->value();
    (*matrix)[5]   = ui->spinBox_6->value();
    (*matrix)[6]   = ui->spinBox_7->value();
    (*matrix)[7]   = ui->spinBox_8->value();
    (*matrix)[8]   = ui->spinBox_9->value();
    (*matrix)[9]   = ui->spinBox_10->value();
    (*matrix)[10]  = ui->spinBox_11->value();
    (*matrix)[11]  = ui->spinBox_12->value();
    (*matrix)[12]  = ui->spinBox_13->value();
    (*matrix)[13]  = ui->spinBox_14->value();
    (*matrix)[14]  = ui->spinBox_15->value();
    (*matrix)[15]  = ui->spinBox_16->value();
    (*matrix)[16]  = ui->spinBox_17->value();
    (*matrix)[17]  = ui->spinBox_18->value();
    (*matrix)[18]  = ui->spinBox_19->value();
    (*matrix)[19]  = ui->spinBox_20->value();
    (*matrix)[20]  = ui->spinBox_21->value();
    (*matrix)[21]  = ui->spinBox_22->value();
    (*matrix)[22]  = ui->spinBox_23->value();
    (*matrix)[23]  = ui->spinBox_24->value();
    (*matrix)[24]  = ui->spinBox_25->value();

    return matrix;
}

QString EditFilterDialog::getCustomName()
{
    return ui->customNameLineEdit->text();
}
