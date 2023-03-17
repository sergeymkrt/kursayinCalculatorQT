//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#include "../Headers/HistoryModel.h"

int HistoryModel::rowCount(const QModelIndex &parent = QModelIndex()) const {
    return m_historyList.count();
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_historyList.count())
            return {};

    const HistoryItem& historyItem = m_historyList.at(index.row());
    if (role == Qt::DisplayRole)
        return  historyItem.result();
    if(role == Qt::UserRole)
        return historyItem.expression();

    return {};
}

Qt::ItemFlags HistoryModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool HistoryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        HistoryItem& historyItem = m_historyList[index.row()];
        if (index.column() == 0)
            historyItem.expression() = value.toString();
        else if (index.column() == 1)
            historyItem.result() = value.toString();

        emit dataChanged(index, index, { role });
        return true;
    }
    return false;
}

void HistoryModel::addHistoryItem(const HistoryItem &item) {
    int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);
    m_historyList.append(item);
    endInsertRows();
}
