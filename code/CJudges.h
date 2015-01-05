#pragma once
#include <QDialog>
#include <QDoubleSpinBox>
#include <vector>
using namespace std;
/*
 * 评委类
 * 拥有一个打分数的弹窗
 * 评委的打分是以次记的，进行一次打分获得最高最低平均分
 */
class CJudges : public QDialog
{
        Q_OBJECT
public:
    explicit CJudges(int NumOfJudges,QWidget *parent = 0);
    //开始一个新项目的评分
    void StartNew();
    //获得此次打分的最低分
	double GetGradeL()
	{ return m_GradeL;}
    //获得此次打分的平均分
	double GetGradeA()
	{ return m_GradeA;}
    //获得此次打分的最高分
	double GetGradeH()
	{ return m_GradeH;}

	~CJudges(void){ }

private slots:
    //确定按钮的槽，进行分数的统计
    void DoneClicked();

private:
    vector<QDoubleSpinBox*> JudgeSpinBox;
    QPushButton * Button;
    //评委人数
	int m_Num;

	double m_GradeL;
	double m_GradeA;
	double m_GradeH;
};

