#include "CExam.h"
#include <QString>
#include <QFileDialog>
#include <QTextStream>


CExam::CExam(QString PathName, int JudgeNum, QString CulturePro , QString DancePro)
{
    m_NowPeople=1;
    Read(PathName);
    m_Problem = new CProblem(CulturePro,DancePro);
    m_Judge = new CJudges(JudgeNum);
}

CPeople* CExam::StartAgain()
{
    m_NowPeople=1;
    this->ClearPeo();
    for(map<QString,CPeople*>::iterator index=m_Peoples.begin();index!=m_Peoples.end();index++)
    {
        index->second->ClearGrades();
    }
    return m_Peoples[m_Names[m_NowPeople-1]];
}

CPeople* CExam::StartNew(QString PathName, int JudgeNum, QString CulturePro , QString DancePro)
{
    m_NowPeople=1;
    for(map<QString,CPeople*>::iterator index = m_Peoples.begin();index!=m_Peoples.end();index++)
    {
        delete index->second;
    }
    m_Names.clear();
    m_Peoples.clear();;
    delete m_Problem;
    delete m_Judge;
    Read(PathName);
     m_Problem = new CProblem(CulturePro,DancePro);
     m_Judge = new CJudges(JudgeNum);
    return m_Peoples[m_Names[m_NowPeople-1]];
}

CPeople *CExam::GetNextPeople()
{
    m_NowPeople++;
    if(m_NowPeople>m_Peoples.size())
        return NULL;
    else
    {
        return m_Peoples[m_Names[m_NowPeople-1]];
    }
}

vector<QString> CExam::GetPeopleNames()
{
    return m_Names;
}

QString CExam::GetPeoSexPercent()
{
    int Man=0 , Woman=0;
    for(int i=0;i<m_Names.size();i++)
    {
        if(m_Peoples[m_Names[i]]->GetSex()==QString("\xE7\x94\xB7"))
            Man++;
        else
            Woman++;
    }

    QString Percent;
    if(Woman==0)
    {
        //全为男
        Percent = QString::fromUtf8("\xE5\x85\xA8\xE4\xB8\xBA\xE7\x94\xB7");
    }
    else if(Man==0)
    {
        //全为女
        Percent = QString::fromUtf8("\xE5\x85\xA8\xE4\xB8\xBA\xE5\xA5\xB3");
    }
    else
    {
        //男：女=
        Percent = QString::fromUtf8("\xE7\x94\xB7/\xE5\xA5\xB3=");
        Percent+=QString::number((Man*1.0)/Woman);
    }
    return Percent;
}

QString CExam::GetCulPro()
{
    QString Pro =  m_Problem->GetCulturalPro();
    map<QString,vector<CPeople*> >::iterator index=m_Cultural.begin();
    for(; index!=m_Cultural.end(); index++)
    {
        if(Pro == index->first)
            break;
    }
    if( index!=m_Cultural.end())
        index->second.push_back(m_Peoples[m_Names[m_NowPeople-1]]);
    else
    {
        vector<CPeople*> temp;
        temp.push_back(m_Peoples[m_Names[m_NowPeople-1]]);
        m_Cultural.insert(pair<QString,vector<CPeople*> >(Pro , temp));
    }
    return Pro;
}

QString CExam::GetDancePro()
{
    QString Pro = m_Problem->GetDancePro();
    map<QString,vector<CPeople*> >::iterator index=m_Dance.begin();
    for(; index!=m_Dance.end(); index++)
    {
        if(Pro == index->first)
            break;
    }
   if( index!=m_Dance.end())
       index->second.push_back(m_Peoples[m_Names[m_NowPeople-1]]);
   else
   {
       vector<CPeople*> temp;
       temp.push_back(m_Peoples[m_Names[m_NowPeople-1]]);
       m_Dance.insert(pair<QString,vector<CPeople*> >(Pro , temp));
   }
    return Pro;
}

map<QString,vector<double> > CExam::GetDanOrderAnalyse()
{
    map<QString,vector<double> > Resut;
    for(map<QString,vector<CPeople*> >::iterator index=m_Dance.begin();
        index!=m_Dance.end();index++)
    {
        double Min=0 , Max=0 ,Average=0;
        for(int i=0;i<index->second.size();i++)
        {
            if(i==0)
            {
                Min=index->second[i]->GetDanceOrdL();
                Max=index->second[i]->GetDanceOrdH();
                Average=index->second[i]->GetDanceOrdA();
            }
            else
            {
                if(Min>index->second[i]->GetDanceOrdL())
                    Min=index->second[i]->GetDanceOrdL();
                if(Max<index->second[i]->GetDanceOrdH())
                    Max=index->second[i]->GetDanceOrdH();
                Average+=index->second[i]->GetDanceOrdA();
            }
        }
        vector<double> Grades;
        Grades.push_back(Min);
        if(index->second.size() == 0)
            Grades.push_back(0);
        else
            Grades.push_back(Average/(index->second.size()));
        Grades.push_back(Max);
        Resut.insert(pair<QString,vector<double> >(index->first,Grades));
    }
    return Resut;
}

map<QString,vector<double> > CExam::GetCulAnalyse()
{
    map<QString,vector<double> > Resut;
    for(map<QString,vector<CPeople*> >::iterator index=m_Cultural.begin();
        index!=m_Cultural.end();index++)
    {
        double Min=0 , Max=0 ,Average=0;
        for(int i=0;i<index->second.size();i++)
        {
            if(i==0)
            {
                Min=index->second[i]->GetAnswerL();
                Max=index->second[i]->GetAnswerH();
                Average=index->second[i]->GetAnswerA();
            }
            else
            {
                if(Min>index->second[i]->GetAnswerL())
                    Min=index->second[i]->GetAnswerL();
                if(Max<index->second[i]->GetAnswerH())
                    Max=index->second[i]->GetAnswerH();
                Average+=index->second[i]->GetAnswerA();
            }
        }
        vector<double> Grades;
        Grades.push_back(Min);
        if(index->second.size()==0)
            Grades.push_back(0);
        else
            Grades.push_back(Average/(index->second.size()));
        Grades.push_back(Max);
        Resut.insert(pair<QString,vector<double> >(index->first,Grades));
    }
    return Resut;
}

void CExam::StartDanceSin()
{
    m_Judge->StartNew();
    m_Judge->exec();
    m_Peoples[m_Names[m_NowPeople-1]]->SetGDanceSingleL(m_Judge->GetGradeL());
    m_Peoples[m_Names[m_NowPeople-1]]->SetGDanceSingleA(m_Judge->GetGradeA());
    m_Peoples[m_Names[m_NowPeople-1]]->SetGDanceSingleH(m_Judge->GetGradeH());
}

void CExam::StartCulPro()
{
    m_Judge->StartNew();
    m_Judge->exec();
    m_Peoples[m_Names[m_NowPeople-1]]->SetGAnswerL(m_Judge->GetGradeL());
    m_Peoples[m_Names[m_NowPeople-1]]->SetGAnswerA(m_Judge->GetGradeA());
    m_Peoples[m_Names[m_NowPeople-1]]->SetGAnswerH(m_Judge->GetGradeH());
}

void CExam::StartDanceOrder()
{
    m_Judge->StartNew();
    m_Judge->exec();
    m_Peoples[m_Names[m_NowPeople-1]]->SetGDanceOrderL(m_Judge->GetGradeL());
    m_Peoples[m_Names[m_NowPeople-1]]->SetGDanceOrderA(m_Judge->GetGradeA());
    m_Peoples[m_Names[m_NowPeople-1]]->SetGDanceOrderH(m_Judge->GetGradeH());
}

void CExam::ClearPeo()
{
    for(map<QString,vector<CPeople*> >::iterator index=m_Cultural.begin();
        index!=m_Cultural.end();index++)
    {
        index->second.clear();
    }
    for(map<QString,vector<CPeople*> >::iterator index=m_Dance.begin();
        index!=m_Dance.end();index++)
    {
        index->second.clear();
    }
}

void CExam::Read(QString PathName)
{
    /*
     * 选手文件
     * 姓名，年龄，性别，地址
     */
    QFile FileName(PathName);
    if(FileName.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&FileName);
        QString Line;
        while(1)
        {
            Line = stream.readLine();
            if(Line.isNull())
                break;
            QString name,age,sex,address;
            int index=0;
            for(index=0;index<Line.size();index++)
            {
                if(Line[index]==',')
                {
                    index++;
                    break;
                }
                name.push_back(Line[index]);
            }
            for(;index<Line.size();index++)
            {
                if(Line[index]==',')
                {
                    index++;
                    break;
                }
                age.push_back(Line[index]);
            }
            for(;index<Line.size();index++)
            {
                if(Line[index]==',')
                {
                    index++;
                    break;
                }
                sex.push_back(Line[index]);
            }
            for(;index<Line.size();index++)
            {
                address.push_back(Line[index]);
            }
            if(sex==QString::fromUtf8("\xE7\x94\xB7"))
            {
                CPeople *people = new CPeople(name,age.toInt(),SexMan,address);
                m_Names.push_back(name);
                m_Peoples.insert(pair<QString,CPeople*>(name,people));
            }
            else
            {
                CPeople * people = new CPeople(name,age.toInt(),SexWoman,address);
                m_Names.push_back(name);
                m_Peoples.insert(pair<QString,CPeople*>(name,people));
            }
        }
    }
    FileName.close();
}

CExam::~CExam()
{
    for(map<QString,CPeople*>::iterator index = m_Peoples.begin();index!=m_Peoples.end();index++)
    {
        delete index->second;
    }
    delete m_Problem;
    delete m_Judge;
}
