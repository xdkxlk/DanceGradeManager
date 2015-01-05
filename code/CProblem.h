#pragma once
#include <QString>
#include <vector>
#include <map>
#include "CPeople.h"
using namespace std;
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
class CProblem
{
public:
    //FileCulturalPro�Ļ����ʵ��ļ�·����FileDancePro������ļ�·��
    CProblem(QString FileCulturalPro, QString FileDancePro);
    //�������Ļ�������Ŀ�����뵱ǰѡ��people����
    QString GetCulturalPro();
    //�����ö�����Ŀ�����뵱ǰѡ��people����
    QString GetDancePro();
    //���ÿ����������������
   // void ClearPeo();

	~CProblem(void){ }
private:
    vector<QString> m_DancePro;
     vector<QString> m_CulturalPro;
};

