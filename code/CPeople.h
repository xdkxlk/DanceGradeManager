#pragma once
#include <QString>
#include <vector>
#include "SexEnum.h"
using namespace std;
class CPeople
{
public:
    CPeople(QString name, int age, SexModel sex, QString address) :
        m_Name(name), m_Age(age), m_Sex(sex), m_Address(address) ,m_NumOfDone(0) { }

    vector<vector<double> > GetGrades();

    void ClearGrades()
    {
        m_NumOfDone=0;
    }

    QString GetName()
    {
        return m_Name;
    }
    QString GetSex()
    {
        switch(m_Sex)
        {
        case SexMan:
            return QString::fromUtf8("\xE7\x94\xB7");//男
            break;
        default:
            return QString::fromUtf8("\xE5\xA5\xB3");//女
            break;
        }
    }
    int GetAge()
    {
        return m_Age;
    }
    QString GetAddress()
    {
        return m_Address;
    }

    double GetDanceSingleA()
    {
        return m_GradeDanceSingle[1];
    }
    double GetAnswerA()
    {
        return m_GradeAnswer[1];
    }
    double GetDanceOrdA()
    {
        return m_GradeDanceOrder[1];
    }

    double GetDanceSingleL()
    {
        return m_GradeDanceSingle[0];
    }
    double GetAnswerL()
    {
        return m_GradeAnswer[0];
    }
    double GetDanceOrdL()
    {
        return m_GradeDanceOrder[0];
    }

    double GetDanceSingleH()
    {
        return m_GradeDanceSingle[2];
    }
    double GetAnswerH()
    {
        return m_GradeAnswer[2];
    }
    double GetDanceOrdH()
    {
        return m_GradeDanceOrder[2];
    }

    void SetGDanceSingleL(double grade)
    {
        m_GradeDanceSingle[0] =  grade;
        m_NumOfDone++;
    }
    void SetGAnswerL(double grade)
    {
        m_GradeAnswer[0] = grade;
        m_NumOfDone++;
    }
    void SetGDanceOrderL(double grade)
    {
        m_GradeDanceOrder[0] = grade;
        m_NumOfDone++;
    }

    void SetGDanceSingleA(double grade)
    {
        m_GradeDanceSingle[1] =  grade;
        m_NumOfDone++;
    }
    void SetGAnswerA(double grade)
    {
        m_GradeAnswer[1] = grade;
        m_NumOfDone++;
    }
    void SetGDanceOrderA(double grade)
    {
        m_GradeDanceOrder[1] = grade;
        m_NumOfDone++;
    }

    void SetGDanceSingleH(double grade)
    {
        m_GradeDanceSingle[2] =  grade;
        m_NumOfDone++;
    }
    void SetGAnswerH(double grade)
    {
        m_GradeAnswer[2] = grade;
        m_NumOfDone++;
    }
    void SetGDanceOrderH(double grade)
    {
        m_GradeDanceOrder[2] = grade;
        m_NumOfDone++;
    }

    ~CPeople(void){ }
private:
    QString m_Name;
	SexModel m_Sex;
	int m_Age;
    QString m_Address;
    int m_NumOfDone; //对已经完成了的项目进行计数，一个环节有最高，最低，平均三个环节

    //0,1,2分别为 最低分 平均分 最高分
    double m_GradeDanceSingle[3];//独舞成绩
    double m_GradeAnswer[3];//文化提问成绩
    double m_GradeDanceOrder[3];//命题舞蹈成绩
};

