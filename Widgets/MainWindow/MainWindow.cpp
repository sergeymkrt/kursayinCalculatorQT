//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#include <iomanip>
#include "MainWindow.h"
#include "../../Core/Calculator/Calculator.h"


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
    HistoryList = new QListView;
    layout->addWidget(HistoryList, 0, 0, 1, 2);
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
    auto result = Calculator::evaluateExpression(&expression);
    ResultOutput->setText(std::to_string(result).c_str());
}
