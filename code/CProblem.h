#pragma once
#include <QString>
#include <vector>
#include <map>
#include "CPeople.h"
using namespace std;
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
class CProblem
{
public:
    //FileCulturalPro文化提问的文件路径，FileDancePro独舞的文件路径
    CProblem(QString FileCulturalPro, QString FileDancePro);
    //随机获得文化提问题目，并与当前选手people关联
    QString GetCulturalPro();
    //随机获得独舞题目，并与当前选手people关联
    QString GetDancePro();
    //清空每个问题所关联的人
   // void ClearPeo();

	~CProblem(void){ }
private:
    vector<QString> m_DancePro;
     vector<QString> m_CulturalPro;
};

