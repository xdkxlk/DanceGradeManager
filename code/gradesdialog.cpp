#include "gradesdialog.h"
#include "ui_gradesdialog.h"

GradesDialog::GradesDialog(vector<vector<double> > Grades, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GradesDialog)
{
    ui->setupUi(this);
    for(int R=0;R<Grades.size();R++)
    {
        for(int C=0;C<Grades[R].size();C++)
        {
            ui->tableWidget->setItem(R,C,new QTableWidgetItem(QString::number(Grades[R][C])));
        }
    }
}

GradesDialog::~GradesDialog()
{
    delete ui;
}
