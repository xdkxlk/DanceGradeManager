#include "CJudges.h"
#include <QPushButton>
#include <QLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <vector>
using namespace std;

CJudges::CJudges(int NumOfJudges, QWidget *parent) : QDialog(parent)
{
    setWindowFlags(windowFlags() &~Qt::WindowCloseButtonHint);//禁用关闭按钮
    //请评委打分
    setWindowTitle(QString::fromUtf8("\xE8\xAF\xB7\xE8\xAF\x84\xE5\xA7\x94\xE6\x89\x93\xE5\x88\x86"));

    m_Num = NumOfJudges;
    QVBoxLayout *VLayout = new QVBoxLayout(this);
    for(int i=0;i<NumOfJudges/3;i++)
    {
        QHBoxLayout *HLayout = new QHBoxLayout(this);
        for(int j=0;j<3;j++)
        {
            QDoubleSpinBox * Box = new QDoubleSpinBox(this);
            Box->setRange(0,100);
            HLayout->addWidget(Box);
            JudgeSpinBox.push_back(Box);
        }
        VLayout->addLayout(HLayout);
    }
    QHBoxLayout *HLayoutFina = new QHBoxLayout(this);
    for(int i=0;i<NumOfJudges%3;i++)
    {
        QDoubleSpinBox * Box = new QDoubleSpinBox(this);
        Box->setRange(0,100);
        HLayoutFina->addWidget(Box);
        JudgeSpinBox.push_back(Box);
    }
    HLayoutFina->addStretch();
    VLayout->addLayout(HLayoutFina);

    QHBoxLayout *ButtonLayout = new QHBoxLayout(this);
    Button = new QPushButton(QString::fromUtf8("\xE7\xA1\xAE\xE5\xAE\x9A"),this);  //确定
    ButtonLayout->addStretch();
    ButtonLayout->addWidget(Button);
    VLayout->addLayout(ButtonLayout);

    setLayout(VLayout);

    resize(sizeHint());

    connect(Button,SIGNAL(clicked()),this,SLOT(DoneClicked()));
    connect(Button,SIGNAL(clicked()),this,SLOT(accept()));
}

void CJudges::StartNew()
{
    for(int i=0;i<m_Num;i++)
    {
        JudgeSpinBox[i]->setValue(0);
    }
}

void CJudges::DoneClicked()
{
    vector<double> people(m_Num);
    int index=0;
    while(index<m_Num)
    {
        people[index++]=JudgeSpinBox[index]->value();
    }

    sort(people.begin(),people.end());

    m_GradeH = people[m_Num-1];
    m_GradeL = people[0];

    double sum=0;
    for(index=0;index<m_Num;index++)
    {
        sum+=people[index];
    }
    m_GradeA = sum/m_Num;
}
