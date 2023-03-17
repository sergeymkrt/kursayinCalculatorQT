//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#ifndef KURSAYINCALCULATOR_MAINWINDOW_H
#define KURSAYINCALCULATOR_MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QListView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "../../Core/Headers/HistoryModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void calculateSum();

private:
    void createHistoryList();
    void createExpressionInput();
    void createResultOutput();
    void createCalculateButton();

    QList<HistoryItem> historyList;
    HistoryModel *historyModel;
    QGridLayout *layout;
    QLabel *ExpressionLabel{};
    QLabel *ResultLabel{};
    QLineEdit *ExpressionInput{};
    QLineEdit *ResultOutput{};
    QListView *HistoryListView{};
    QPushButton *CalculateButton{};
};


#endif //KURSAYINCALCULATOR_MAINWINDOW_H
