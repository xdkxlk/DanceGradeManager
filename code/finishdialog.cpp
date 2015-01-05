#include "finishdialog.h"
#include "ui_finishdialog.h"
#include "CPeople.h"
#include "CProblem.h"
#include <QTableWidgetItem>
#include <QVariant>

FinishDialog::FinishDialog(CExam * Exam,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinishDialog)
{
    ui->setupUi(this);
    ui->tableWidgetCulPro->setVisible(false);
    ui->tableWidgetDanPro->setVisible(false);

    m_Exam = Exam;
    vector<QString> Names = m_Exam->GetPeopleNames();
    for(int i=0;i<Names.size();i++)
    {
        ui->tableWidgetPeople->insertRow(ui->tableWidgetPeople->rowCount());
        CPeople* people = m_Exam->GetPeople(Names[i]);
        ui->tableWidgetPeople->setItem(i,0,new QTableWidgetItem(Names[i]));
        ui->tableWidgetPeople->setItem(i,1,m_SaveAsNum(people->GetAge()));
        ui->tableWidgetPeople->setItem(i,2,new QTableWidgetItem(people->GetSex()));
        ui->tableWidgetPeople->setItem(i,3,new QTableWidgetItem(people->GetAddress()));
        ui->tableWidgetPeople->setItem(i,4,m_SaveAsNum(people->GetDanceSingleA()));
        ui->tableWidgetPeople->setItem(i,5,m_SaveAsNum(people->GetAnswerA()));
        ui->tableWidgetPeople->setItem(i,6,m_SaveAsNum(people->GetDanceOrdA()));
        ui->tableWidgetPeople->setItem(i,7,m_SaveAsNum(people->GetDanceSingleA() * 0.7 + people->GetAnswerA() * 0.1 + people->GetDanceOrdA() * 0.2));
    }
    ui->tableWidgetPeople->setHorizontalHeaderItem(2,new QTableWidgetItem(
                                                       QString::fromUtf8("\xE6\x80\xA7\xE5\x88\xAB  ")+m_Exam->GetPeoSexPercent()));
    //性别（"\xE6\x80\xA7\xE5\x88\xAB  "）
    ui->tableWidgetPeople->setSortingEnabled(true);

    map<QString,vector<double> > DancGradAnalyse = m_Exam->GetDanOrderAnalyse();
    for(map<QString,vector<double> >::iterator index = DancGradAnalyse.begin();index!=DancGradAnalyse.end();index++)
    {
        int Row=ui->tableWidgetDanPro->rowCount();
        ui->tableWidgetDanPro->insertRow(Row);
        ui->tableWidgetDanPro->setItem(Row,0,new QTableWidgetItem(index->first));
        for(int j=0; j<3; j++)
        {
             ui->tableWidgetDanPro->setItem(Row,j+1,m_SaveAsNum(index->second[j]));
        }
    }
    ui->tableWidgetDanPro->setSortingEnabled(true);

    map<QString,vector<double> > CulAnalyse = m_Exam->GetCulAnalyse();
    for(map<QString,vector<double> >::iterator index = CulAnalyse.begin();index!=CulAnalyse.end();index++)
    {
        int Row=ui->tableWidgetCulPro->rowCount();
        ui->tableWidgetCulPro->insertRow(Row);
        ui->tableWidgetCulPro->setItem(Row,0,new QTableWidgetItem(index->first));
        for(int j=0; j<3; j++)
        {
             ui->tableWidgetCulPro->setItem(Row,j+1,m_SaveAsNum(index->second[j]));
        }
    }
    ui->tableWidgetCulPro->setSortingEnabled(true);
}

FinishDialog::~FinishDialog()
{
    delete ui;
}

void FinishDialog::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        ui->tableWidgetPeople->setVisible(true);
        ui->tableWidgetDanPro->setVisible(false);
        ui->tableWidgetCulPro->setVisible(false);
        break;
    case 1:
        ui->tableWidgetPeople->setVisible(false);
        ui->tableWidgetDanPro->setVisible(false);
        ui->tableWidgetCulPro->setVisible(true);
        break;
    case 2:
        ui->tableWidgetPeople->setVisible(false);
        ui->tableWidgetDanPro->setVisible(true);
        ui->tableWidgetCulPro->setVisible(false);
        break;
    default:
        break;
    }
}

QTableWidgetItem * FinishDialog::m_SaveAsNum(double item)
{
    QTableWidgetItem *data = new QTableWidgetItem;
    data->setData(Qt::EditRole,QVariant(item));
    return data;
}

QTableWidgetItem * FinishDialog::m_SaveAsNum(int item)
{
    QTableWidgetItem *data = new QTableWidgetItem;
    data->setData(Qt::EditRole,QVariant(item));
    return data;
}
