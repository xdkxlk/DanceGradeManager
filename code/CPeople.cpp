#include "CPeople.h"

vector<vector<double> > CPeople::GetGrades()
{
    vector<vector<double> > Grades;
    if(m_NumOfDone>=3)
    {
        vector<double> temp;
        for(int i=0;i<3;i++)
        {
            temp.push_back(m_GradeDanceSingle[i]);
        }
        Grades.push_back(temp);
        if(m_NumOfDone>=6)
        {
            vector<double> temp;
            for(int i=0;i<3;i++)
            {
                temp.push_back(m_GradeAnswer[i]);
            }
            Grades.push_back(temp);
            if(m_NumOfDone>=9)
            {
                vector<double> temp;
                for(int i=0;i<3;i++)
                {
                    temp.push_back(m_GradeDanceOrder[i]);
                }
                Grades.push_back(temp);
            }
        }
    }
    return Grades;
}
