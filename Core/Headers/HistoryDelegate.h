//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#ifndef KURSAYINCALCULATOR_HISTORYDELEGATE_H
#define KURSAYINCALCULATOR_HISTORYDELEGATE_H


#include <QStyledItemDelegate>
#include <QPainter>

class HistoryDelegate : public QStyledItemDelegate{
public:
    explicit HistoryDelegate(QObject* parent = nullptr)
        : QStyledItemDelegate(parent)
    {
    }

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        // Get the data for the current item
        QString result = index.data(Qt::DisplayRole).toString();
        QString expression = index.data(Qt::UserRole).toString();

        painter->save();

        // Draw a rectangle around the cell
        painter->setPen(QPen(Qt::black, 1));

        QRect rect = option.rect;
        rect.setHeight(qMax(rect.height(), 40));

        painter->drawRect(rect);

         // Draw the title and URL onto the view
        painter->setFont(option.font);
        painter->setPen(option.palette.color(QPalette::WindowText));
        painter->drawText(rect.adjusted(2, 2, -2, -2), result);
        painter->setPen(QPen(Qt::gray));
        painter->drawText(rect.adjusted(2,2,-2,-2),expression, Qt::AlignBottom|Qt::AlignLeft);

        painter->restore();
    }

    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        // Get the font metrics for the current font
        QFontMetrics fontMetrics(option.font);

        // Calculate the required height of the cell
        int height = fontMetrics.height() * 2 + 16; // Add a small margin

        // Return the size hint as a QSize object
        return {option.rect.width(), height};
    }

};


#endif //KURSAYINCALCULATOR_HISTORYDELEGATE_H
