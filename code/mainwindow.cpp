#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->MgroupBoxPro->setVisible(false);
    ui->LookPeoplegroupBox->setEnabled(false);
    ui->pushButtonAgain->setEnabled(false);
    connect(ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(StartNewSlot()));
    connect(ui->pushButtonAgain,SIGNAL(clicked()),this,SLOT(StartAgainSlot()));
    connect(ui->MButtonGrade,SIGNAL(clicked()),this,SLOT(StartCultSlot()));
    m_Exam=NULL;
    IsTheFirstRurnning=true;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Exam;
}

void MainWindow::StartNewSlot()
{
    int JudgeNum;
    QString FilePathName,FilePathCulture,FilePathDance;
    ReadDialog ReadIn(&FilePathName,&JudgeNum,&FilePathCulture,&FilePathDance,this);
    if(ReadIn.exec()==QDialog::Accepted)
    {
        CPeople *FirstPeople;
        if(IsTheFirstRurnning)
        {
            m_Exam = new CExam(FilePathName,JudgeNum,FilePathCulture,FilePathDance);
            FirstPeople = m_Exam->GetFirstPeo();
        }
        else
            FirstPeople = m_Exam->StartNew(FilePathName,JudgeNum,FilePathCulture,FilePathDance);

        ui->pushButtonAgain->setEnabled(false);
        ui->MgroupBoxPro->setVisible(false);

        //为了防止 QComboBox->clear(); 莫名崩溃（原因还不明），需要先disconnect再connect
        disconnect(ui->LookPeoplecomboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_LookPeoplecomboBox_currentTextChanged(QString)));
        ui->LookPeoplecomboBox->clear();
        connect(ui->LookPeoplecomboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_LookPeoplecomboBox_currentTextChanged(QString)));

        ui->LookPeoplegroupBox->setEnabled(true);
        //下一名选手
        ui->pushButtonControl->setText(QString::fromUtf8("\xE4\xB8\x8B\xE4\xB8\x80\xE5\x90\x8D\xE9\x80\x89\xE6\x89\x8B"));
        ui->pushButtonControl->setEnabled(false);
        ui->Mlabel->setEnabled(true);
        ui->MlabelPeopel->setEnabled(true);
        ui->MarchButtonDanceSin->setEnabled(true);

        vector<QString> Names = m_Exam->GetPeopleNames();
        for(int i=0;i<Names.size();i++)
        {
            ui->LookPeoplecomboBox->addItem(Names[i]);
        }
        CPeople *people = m_Exam->GetPeople(ui->LookPeoplecomboBox->currentText());
        ui->LooKPeolplelabel->setText(people->GetName()+QString("\n\n")+QString::number(people->GetAge())
                                      +QString("\n\n")+people->GetSex()+QString("\n\n")+people->GetAddress());
        ui->MlabelPeopel->setText(FirstPeople->GetName());

        connect(ui->MButtonGrade,SIGNAL(clicked()),this,SLOT(StartCultSlot()));
        disconnect(this->ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(StartNewSlot()));
        connect(this->ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(TheNextPeopleSlot()));
    }
}

void MainWindow::StartAgainSlot()
{
    CPeople *FirstPeople = m_Exam->StartAgain();

    ui->pushButtonAgain->setEnabled(false);
    ui->MgroupBoxPro->setVisible(false);
    ui->LookPeoplegroupBox->setEnabled(true);
    //下一名选手
    ui->pushButtonControl->setText(QString::fromUtf8("\xE4\xB8\x8B\xE4\xB8\x80\xE5\x90\x8D\xE9\x80\x89\xE6\x89\x8B"));
    ui->pushButtonControl->setEnabled(false);
    ui->Mlabel->setEnabled(true);
    ui->MlabelPeopel->setEnabled(true);
    ui->MarchButtonDanceSin->setEnabled(true);

    CPeople *people = m_Exam->GetPeople(ui->LookPeoplecomboBox->currentText());
    ui->LooKPeolplelabel->setText(people->GetName()+QString("\n\n")+QString::number(people->GetAge())
                                  +QString("\n\n")+people->GetSex()+QString("\n\n")+people->GetAddress());
    ui->MlabelPeopel->setText(FirstPeople->GetName());

    connect(ui->MButtonGrade,SIGNAL(clicked()),this,SLOT(StartCultSlot()));
    disconnect(this->ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(StartNewSlot()));
    connect(this->ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(TheNextPeopleSlot()));
}

void MainWindow::TheNextPeopleSlot()
{
    CPeople *people = m_Exam->GetNextPeople();
    ui->pushButtonControl->setEnabled(false);
    if(people!=NULL)
    {
        if(m_Exam->IsTheLastPeople())
        {
            //结束比赛
            ui->pushButtonControl->setText(QString::fromUtf8("\xE7\xBB\x93\xE6\x9D\x9F\xE6\xAF\x94\xE8\xB5\x9B"));
            disconnect(ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(TheNextPeopleSlot()));
            connect(ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(FinishSlot()));
        }
        ui->MgroupBoxPro->setVisible(false);
        ui->MarchButtonDanceSin->setEnabled(true);
        ui->MlabelPeopel->setText(people->GetName());
    }
}

void MainWindow::FinishSlot()
{
    IsTheFirstRurnning=false;
    FinishDialog Dialog(m_Exam, this);
    Dialog.exec();

    ui->pushButtonAgain->setEnabled(true);
    //新的比赛
    ui->pushButtonControl->setText(QString::fromUtf8("\xE6\x96\xB0\xE7\x9A\x84\xE6\xAF\x94\xE8\xB5\x9B"));
    disconnect(ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(FinishSlot()));
    connect(ui->pushButtonControl,SIGNAL(clicked()),this,SLOT(StartNewSlot()));
}

void MainWindow::on_MarchButtonDanceSin_clicked()
{
    ui->MarchButtonDanceSin->setEnabled(false);
    ui->MarchButtonPro->setEnabled(true);
    ui->MgroupBoxPro->setVisible(false);
    m_Exam->StartDanceSin();
}

void MainWindow::on_MarchButtonPro_clicked()
{
    ui->MarchButtonPro->setEnabled(false);
    ui->MgroupBoxPro->setVisible(true);
    ui->MlabelPro->setText(m_Exam->GetCulPro());    
}

void MainWindow::StartCultSlot()
{
    m_Exam->StartCulPro();
    ui->MarchButtonDanceOrd->setEnabled(true);
    ui->MgroupBoxPro->setVisible(false);
    disconnect(ui->MButtonGrade,SIGNAL(clicked()),this,SLOT(StartCultSlot()));
    connect(ui->MButtonGrade,SIGNAL(clicked()),this,SLOT(StartDanceOrderSlot()));
}

void MainWindow::on_MarchButtonDanceOrd_clicked()
{
    ui->MarchButtonDanceOrd->setEnabled(false);
    ui->MgroupBoxPro->setVisible(true);
    ui->MlabelPro->setText(m_Exam->GetDancePro());    
}

void MainWindow::StartDanceOrderSlot()
{
    m_Exam->StartDanceOrder();
    ui->pushButtonControl->setEnabled(true);
    ui->MgroupBoxPro->setVisible(false);
    disconnect(ui->MButtonGrade,SIGNAL(clicked()),this,SLOT(StartDanceOrderSlot()));
    connect(ui->MButtonGrade,SIGNAL(clicked()),this,SLOT(StartCultSlot()));
}

void MainWindow::on_LookPeopleButtonGrade_clicked()
{
    CPeople * people;
    people = m_Exam->GetPeople(ui->LookPeoplecomboBox->currentText());

    vector<vector<double> > Grades = people->GetGrades();
    GradesDialog Dialog(Grades,this);
    Dialog.exec();
}

void MainWindow::on_LookPeoplecomboBox_currentTextChanged(const QString &arg1)
{
    CPeople *people = m_Exam->GetPeople(arg1);
    ui->LooKPeolplelabel->setText(people->GetName()+QString("\n\n")+QString::number(people->GetAge())
                                  +QString("\n\n")+people->GetSex()+QString("\n\n")+people->GetAddress());
}
