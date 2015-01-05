#ifndef READDIALOG_H
#define READDIALOG_H

#include <QDialog>

namespace Ui {
class ReadDialog;
}

class ReadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReadDialog(QString *PathPeo, int *JudgeNum,
                        QString *PathCult, QString *PathDan,QWidget *parent = 0);
    ~ReadDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_3_clicked();

private:
    Ui::ReadDialog *ui;
    QString *m_PathPeo;
    int *m_JudgeNum;
    QString *m_PathCult;
    QString *m_PathDan;

    QString m_LookFile();
    void m_EnableDone();
};

#endif // READDIALOG_H
