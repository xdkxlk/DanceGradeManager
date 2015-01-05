#ifndef GRADESDIALOG_H
#define GRADESDIALOG_H

#include <QDialog>
#include <vector>
using std::vector;

namespace Ui {
class GradesDialog;
}

class GradesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GradesDialog(vector<vector<double> > Grades,QWidget *parent = 0);
    ~GradesDialog();

private:
    Ui::GradesDialog *ui;
};

#endif // GRADESDIALOG_H
