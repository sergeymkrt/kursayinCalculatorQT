//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#ifndef KURSAYINCALCULATOR_HISTORYITEM_H
#define KURSAYINCALCULATOR_HISTORYITEM_H


#include <QString>
#include <utility>

class HistoryItem {
public:
    HistoryItem(QString  expression, QString  result)
        : m_expression(std::move(expression)), m_result(std::move(result))
    {
    }

    [[nodiscard]] QString expression() const { return m_expression; }
    [[nodiscard]] QString result() const { return m_result; }

private:
    QString m_expression;
    QString m_result;
};


#endif //KURSAYINCALCULATOR_HISTORYITEM_H
