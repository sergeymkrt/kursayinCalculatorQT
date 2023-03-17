//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#include <iomanip>
#include "MainWindow.h"
#include "../../Core/Headers/Calculator.h"
#include "../../Core/Headers/HistoryDelegate.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QGridLayout;

    createHistoryList();
    createExpressionInput();
    createResultOutput();
    createCalculateButton();

    centralWidget->setLayout(layout);
}

void MainWindow::createHistoryList() {
    HistoryListView = new QListView;
    historyList = {};
    historyModel = new HistoryModel(historyList);
    HistoryListView->setModel(historyModel);
    HistoryListView->setItemDelegate(new HistoryDelegate(HistoryListView));

    layout->addWidget(HistoryListView, 0, 0, 1, 2);
}

void MainWindow::createExpressionInput() {
    ExpressionLabel = new QLabel("Expression: ");
    ExpressionInput = new QLineEdit;
    layout->addWidget(ExpressionLabel, 1, 0);
    layout->addWidget(ExpressionInput, 1, 1);

    connect(ExpressionInput, &QLineEdit::returnPressed, this, &MainWindow::calculateSum);
}

void MainWindow::createResultOutput() {
    ResultLabel = new QLabel("Result: ");
    ResultOutput = new QLineEdit;
    ResultOutput->setReadOnly(true);
    layout->addWidget(ResultLabel, 2, 0);
    layout->addWidget(ResultOutput, 2, 1);
}

void MainWindow::createCalculateButton() {
    CalculateButton = new QPushButton("Calculate");
    layout->addWidget(CalculateButton, 3, 0, 1, 2);
    connect(CalculateButton, &QPushButton::clicked, this, &MainWindow::calculateSum);
}

void MainWindow::calculateSum() {
    auto expression = ExpressionInput->text().toStdString();
    auto result = round(Calculator::evaluateExpression(&expression) * 100) / 100.0;
    auto resultString = QString::number(result, 'f', 2)
            .trimmed()
            .remove(QRegularExpression("0+$"))
            .remove(QRegularExpression("\\.$"));

    auto* model = dynamic_cast<HistoryModel *>(HistoryListView->model());
    model->addHistoryItem(HistoryItem(expression.c_str(), resultString));
    ResultOutput->setText(resultString);
    HistoryListView->scrollToBottom();
}
