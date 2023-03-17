//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#ifndef KURSAYINCALCULATOR_HISTORYMODEL_H
#define KURSAYINCALCULATOR_HISTORYMODEL_H

#include <string>
#include <QAbstractListModel>
#include "HistoryItem.h"

class HistoryModel : public QAbstractListModel {
public:
    explicit HistoryModel(const QList<HistoryItem>& historyList)
        : QAbstractListModel(), m_historyList(historyList)
    {
    }

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    void addHistoryItem(const HistoryItem& item);


private:
    QList<HistoryItem> m_historyList;
};


#endif //KURSAYINCALCULATOR_HISTORYMODEL_H
