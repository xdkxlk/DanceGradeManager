#pragma once
#include <vector>
#include <map>
#include <QString>
#include "CPeople.h"
#include "CProblem.h"
#include "CJudges.h"

/*
people文件保存方法
[People.csv]
[一行一人，一空一种信息] m_Name  m_Age sex  address

problem文件保存方法
[File1 : 文化提问]
[CulturalPro.csv]
m_CulturalPro[一空一行一题]
[File2：命题舞蹈]
[DancePro.csv]
m_DancePro[一空一行一题]
*/

using namespace std;
class CExam
{
public:
    //PathName参赛人员的信息路径，JudgeNum评委人数，CulturePro文化提问的文件路径，DancePro命题舞蹈的文件路径
    CExam(QString PathName, int JudgeNum, QString CulturePro, QString DancePro);
    //PathName参赛人员的信息路径，JudgeNum评委人数，CulturePro文化提问的文件路径，DancePro命题舞蹈的文件路径
    //开始一个新的比赛，返回第一个参赛人员
    CPeople *StartNew(QString PathName, int JudgeNum, QString CulturePro, QString DancePro);
    //重新开始，只清空人员成绩，不清空人员信息，不需要重新读入
    CPeople *StartAgain();
    //获得第一个比赛的选手
    CPeople *GetFirstPeo()
    {
        return m_Peoples[m_Names[0]];
    }
    //开始独舞的评分
    void StartDanceSin();
    //开始文化提问的评分
    void StartCulPro();
    //开始命题舞蹈的评分
    void StartDanceOrder();
    //获得下一个参赛选手，若没有下一个了返回NULL
    CPeople *GetNextPeople();
    //获得某个名字的人员信息，若没有返回NULL
    CPeople *GetPeople(QString name)
    {
        if(m_Peoples.find(name)!=m_Peoples.end())
        {
            return m_Peoples[name];
        }
        else
            return NULL;
    }
    //获得文化提问的问题
    QString GetCulPro();
    //获得独舞的题目
    QString GetDancePro();
    //判断是否为最后一名选手
    bool IsTheLastPeople()
    {
        return m_NowPeople==m_Names.size();
    }
    //获得问题类的指针
    map<QString,vector<double> > GetDanOrderAnalyse();
    map<QString,vector<double> > GetCulAnalyse();

    //获得参赛人员的名字列表
    vector<QString> GetPeopleNames();
    //获得参赛人员性别比例
    QString GetPeoSexPercent();
    ~CExam(void);
private:
    //现在的参赛人员的序号
    int m_NowPeople;
    CProblem *m_Problem;
    //选手的姓名索引
    vector<QString> m_Names;
    //选手姓名和其信息的关联
    map<QString,CPeople*> m_Peoples;
    //评委
    CJudges *m_Judge;
    map<QString,vector<CPeople*> > m_Dance;//独舞题目和抽中选手的关联容器
    map<QString,vector<CPeople*> > m_Cultural;//文化提问题目和抽中选手的关联容器

    void Read(QString PathName);
    void ClearPeo();
};

