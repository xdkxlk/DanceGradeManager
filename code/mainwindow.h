#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "CExam.h"
#include "CJudges.h"
#include "CPeople.h"
#include "CProblem.h"
#include "readdialog.h"
#include "gradesdialog.h"
#include "finishdialog.h"
using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void StartNewSlot();

    void StartAgainSlot();

    void TheNextPeopleSlot();

    void FinishSlot();

    void StartCultSlot();

    void StartDanceOrderSlot();

    void on_MarchButtonDanceSin_clicked();

    void on_MarchButtonPro_clicked();

    void on_LookPeopleButtonGrade_clicked();

    void on_MarchButtonDanceOrd_clicked();

    void on_LookPeoplecomboBox_currentTextChanged(const QString &arg1);

private:
    bool IsTheFirstRurnning;
    Ui::MainWindow *ui;
    CExam *m_Exam;
};

#endif // MAINWINDOW_H
