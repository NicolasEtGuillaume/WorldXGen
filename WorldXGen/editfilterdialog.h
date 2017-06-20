#ifndef EDITFILTERDIALOG_H
#define EDITFILTERDIALOG_H

#include <QDialog>
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

    valarray<int> * getMatrix();

private:
    Ui::EditFilterDialog *ui;
};

#endif // EDITFILTERDIALOG_H
