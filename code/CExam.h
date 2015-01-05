#pragma once
#include <vector>
#include <map>
#include <QString>
#include "CPeople.h"
#include "CProblem.h"
#include "CJudges.h"

/*
people�ļ����淽��
[People.csv]
[һ��һ�ˣ�һ��һ����Ϣ] m_Name  m_Age sex  address

problem�ļ����淽��
[File1 : �Ļ�����]
[CulturalPro.csv]
m_CulturalPro[һ��һ��һ��]
[File2�������赸]
[DancePro.csv]
m_DancePro[һ��һ��һ��]
*/

using namespace std;
class CExam
{
public:
    //PathName������Ա����Ϣ·����JudgeNum��ί������CulturePro�Ļ����ʵ��ļ�·����DancePro�����赸���ļ�·��
    CExam(QString PathName, int JudgeNum, QString CulturePro, QString DancePro);
    //PathName������Ա����Ϣ·����JudgeNum��ί������CulturePro�Ļ����ʵ��ļ�·����DancePro�����赸���ļ�·��
    //��ʼһ���µı��������ص�һ��������Ա
    CPeople *StartNew(QString PathName, int JudgeNum, QString CulturePro, QString DancePro);
    //���¿�ʼ��ֻ�����Ա�ɼ����������Ա��Ϣ������Ҫ���¶���
    CPeople *StartAgain();
    //��õ�һ��������ѡ��
    CPeople *GetFirstPeo()
    {
        return m_Peoples[m_Names[0]];
    }
    //��ʼ���������
    void StartDanceSin();
    //��ʼ�Ļ����ʵ�����
    void StartCulPro();
    //��ʼ�����赸������
    void StartDanceOrder();
    //�����һ������ѡ�֣���û����һ���˷���NULL
    CPeople *GetNextPeople();
    //���ĳ�����ֵ���Ա��Ϣ����û�з���NULL
    CPeople *GetPeople(QString name)
    {
        if(m_Peoples.find(name)!=m_Peoples.end())
        {
            return m_Peoples[name];
        }
        else
            return NULL;
    }
    //����Ļ����ʵ�����
    QString GetCulPro();
    //��ö������Ŀ
    QString GetDancePro();
    //�ж��Ƿ�Ϊ���һ��ѡ��
    bool IsTheLastPeople()
    {
        return m_NowPeople==m_Names.size();
    }
    //����������ָ��
    map<QString,vector<double> > GetDanOrderAnalyse();
    map<QString,vector<double> > GetCulAnalyse();

    //��ò�����Ա�������б�
    vector<QString> GetPeopleNames();
    //��ò�����Ա�Ա����
    QString GetPeoSexPercent();
    ~CExam(void);
private:
    //���ڵĲ�����Ա�����
    int m_NowPeople;
    CProblem *m_Problem;
    //ѡ�ֵ���������
    vector<QString> m_Names;
    //ѡ������������Ϣ�Ĺ���
    map<QString,CPeople*> m_Peoples;
    //��ί
    CJudges *m_Judge;
    map<QString,vector<CPeople*> > m_Dance;//������Ŀ�ͳ���ѡ�ֵĹ�������
    map<QString,vector<CPeople*> > m_Cultural;//�Ļ�������Ŀ�ͳ���ѡ�ֵĹ�������

    void Read(QString PathName);
    void ClearPeo();
};

