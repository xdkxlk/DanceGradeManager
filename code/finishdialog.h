#ifndef FINISHDIALOG_H
#define FINISHDIALOG_H

#include <QTableWidgetItem>
#include <QDialog>
#include "CExam.h"

namespace Ui {
class FinishDialog;
}

class FinishDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FinishDialog(CExam * Exam,QWidget *parent = 0);
    ~FinishDialog();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::FinishDialog *ui;
    CExam *m_Exam;

    /*由于QTableWidgetItem默认是以QString的方式保存数据的，如果
     * 数据为数字则进行大小比较时则不准确，需要专门定制数据保存方式
     * 以下两个函数就完成此功能
    */
    QTableWidgetItem * m_SaveAsNum(double item);
    QTableWidgetItem * m_SaveAsNum(int item);
};

#endif // FINISHDIALOG_H
