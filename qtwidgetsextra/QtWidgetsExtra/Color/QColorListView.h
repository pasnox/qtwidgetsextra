#pragma once

#include <QListView>

#include <QtWidgetsExtra/Color/QColorListModel.h>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QColorListView : public QListView
{
    Q_OBJECT
    class QColorListViewPrivate *d;

    Q_PROPERTY(QColorListModel::NameFormat nameFormat READ nameFormat WRITE setNameFormat)
    Q_PROPERTY(QStringList colorListNames READ colorListNames WRITE setColorListNames)

public:
    explicit QColorListView(QWidget *parent = nullptr);
    explicit QColorListView(const QStringList &colorListNames, QWidget *parent = nullptr);
    explicit QColorListView(const QList<QColor> &colorsList, QWidget *parent = nullptr);

    QColorListModel::NameFormat nameFormat() const;
    void setNameFormat(QColorListModel::NameFormat nameFormat);

    QStringList colorListNames() const;
    void setColorListNames(const QStringList &colorListNames);

    QList<QColor> colorsList() const;
    void setColorsList(const QList<QColor> &colorsList);

    QStringList selectedColorListNames() const;
    void setSelectedColorListNames(const QStringList &colorListNames);

    QList<QColor> selectedColorsList() const;
    void setSelectedColorsList(const QList<QColor> &colorsList);
};
