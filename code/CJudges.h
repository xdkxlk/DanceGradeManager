#pragma once
#include <QDialog>
#include <QDoubleSpinBox>
#include <vector>
using namespace std;
/*
 * ��ί��
 * ӵ��һ��������ĵ���
 * ��ί�Ĵ�����Դμǵģ�����һ�δ�ֻ��������ƽ����
 */
class CJudges : public QDialog
{
        Q_OBJECT
public:
    explicit CJudges(int NumOfJudges,QWidget *parent = 0);
    //��ʼһ������Ŀ������
    void StartNew();
    //��ô˴δ�ֵ���ͷ�
	double GetGradeL()
	{ return m_GradeL;}
    //��ô˴δ�ֵ�ƽ����
	double GetGradeA()
	{ return m_GradeA;}
    //��ô˴δ�ֵ���߷�
	double GetGradeH()
	{ return m_GradeH;}

	~CJudges(void){ }

private slots:
    //ȷ����ť�Ĳۣ����з�����ͳ��
    void DoneClicked();

private:
    vector<QDoubleSpinBox*> JudgeSpinBox;
    QPushButton * Button;
    //��ί����
	int m_Num;

	double m_GradeL;
	double m_GradeA;
	double m_GradeH;
};

