#pragma once

#include <QtWidgetsExtra/Color/QColorListModel.h>

#include <QListView>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QColorListView : public QListView {
    Q_OBJECT
    class QColorListViewPrivate *d;

    Q_PROPERTY(QColorListModel::NameFormat nameFormat READ nameFormat WRITE setNameFormat)
    Q_PROPERTY(QStringList colorNames READ colorNames WRITE setColorNames)

public:
    explicit QColorListView(QWidget *parent = nullptr);
    explicit QColorListView(const QStringList &colorListNames, QWidget *parent = nullptr);
    explicit QColorListView(const QList<QColor> &colorsList, QWidget *parent = nullptr);

    QColorListModel::NameFormat nameFormat() const;
    void setNameFormat(QColorListModel::NameFormat nameFormat);

    QStringList colorNames() const;
    void setColorNames(const QStringList &colorListNames);

    QList<QColor> colors() const;
    void setColors(const QList<QColor> &colorsList);

    QStringList selectedColorNames() const;
    void setSelectedColorNames(const QStringList &colorListNames);

    QList<QColor> selectedColors() const;
    void setSelectedColors(const QList<QColor> &colorsList);
};
