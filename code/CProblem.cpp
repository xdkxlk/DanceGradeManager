#include "CProblem.h"
#include <QFile>
#include <QTextStream>

CProblem::CProblem(QString FileCulturalPro, QString FileDancePro)
{
    QFile FileCur(FileCulturalPro);
    QFile FileDan(FileDancePro);
    if(FileCur.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&FileCur);
        QString line;
        while(1)
        {
            line=stream.readLine();
            if(line.isNull())
                break;
            m_CulturalPro.push_back(line);
        }
    }
    if(FileDan.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&FileDan);
        QString line;
        while(1)
        {
            line=stream.readLine();
            if(line.isNull())
                break;
            m_DancePro.push_back(line);
        }
    }
    FileCur.close();
    FileDan.close();
}

QString CProblem::GetCulturalPro()
{
    int num = qrand()%m_CulturalPro.size();
    return m_CulturalPro[num];
}

QString CProblem::GetDancePro()
{
    int num = qrand()%m_DancePro.size();
    return m_DancePro[num];
}
