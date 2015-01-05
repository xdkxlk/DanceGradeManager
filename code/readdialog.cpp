#include "readdialog.h"
#include "ui_readdialog.h"
#include <QFileDialog>

ReadDialog::ReadDialog(QString *PathPeo, int *JudgeNum,
                       QString *PathCult, QString *PathDan, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadDialog)
{
    ui->setupUi(this);
    m_PathPeo=PathPeo;
    m_JudgeNum=JudgeNum;
    m_PathCult=PathCult;
    m_PathDan=PathDan;
    ui->groupBoxRead->setVisible(false);
    setFixedSize(sizeHint().width(),sizeHint().height());
}

ReadDialog::~ReadDialog()
{
    delete ui;
}

QString ReadDialog::m_LookFile()
{
    return (QFileDialog::getOpenFileName(
                        this,QString("Open  File"),"/home",
                        QString("Excel (*.csv)") ));
}

void ReadDialog::m_EnableDone()
{
    if(ui->spinBox->value()!=0 && ui->lineEdit_2->text()!=""
            && ui->lineEdit_4->text()!="" && ui->lineEdit_5->text()!="")
        ui->pushButton->setEnabled(true);
}

void ReadDialog::on_pushButton_2_clicked()
{
    (*m_PathPeo) = m_LookFile();
    ui->lineEdit_2->setText(*m_PathPeo);
    m_EnableDone();
}

void ReadDialog::on_pushButton_4_clicked()
{
    (*m_PathCult) = m_LookFile();
    ui->lineEdit_4->setText(*m_PathCult);
    m_EnableDone();
}

void ReadDialog::on_pushButton_5_clicked()
{
    (*m_PathDan) = m_LookFile();
    ui->lineEdit_5->setText(*m_PathDan);
    m_EnableDone();
}

void ReadDialog::on_spinBox_valueChanged(int arg1)
{
    (*m_JudgeNum) = arg1;
    if(arg1==0)
        ui->pushButton->setEnabled(false);
    else
    {
        if( ui->lineEdit_2->text()!=""
                && ui->lineEdit_4->text()!="" && ui->lineEdit_5->text()!="")
            ui->pushButton->setEnabled(true);
    }
}

void ReadDialog::on_pushButton_3_clicked()
{
    ui->groupBoxHelp->setVisible(false);
    ui->groupBoxRead->setVisible(true);
    setFixedSize(sizeHint().width(),sizeHint().height());
}
