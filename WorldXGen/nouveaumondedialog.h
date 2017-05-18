#ifndef NOUVEAUMONDEDIALOG_H
#define NOUVEAUMONDEDIALOG_H

#include <QDialog>

namespace Ui {
class NouveauMondeDialog;
}

class NouveauMondeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NouveauMondeDialog(QWidget *parent = 0);
    ~NouveauMondeDialog();

    std::string getSeed();
    bool isRandom();

private:
    Ui::NouveauMondeDialog *ui;
};

#endif // NOUVEAUMONDEDIALOG_H
