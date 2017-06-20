#ifndef EDITFILTERDIALOG_H
#define EDITFILTERDIALOG_H

#include <QDialog>
#include <QString>
#include <valarray>

namespace Ui {
class EditFilterDialog;
}

using namespace std;

class EditFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditFilterDialog(QWidget *parent = 0);
    ~EditFilterDialog();

    void setMatrix(valarray<int> * matrix);
    valarray<int> * getMatrix();

    void setCustomName(QString customName);
    QString getCustomName();

private:
    Ui::EditFilterDialog *ui;
};

#endif // EDITFILTERDIALOG_H
