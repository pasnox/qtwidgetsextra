#ifndef QCOLORCOMBOBOX_H
#define QCOLORCOMBOBOX_H

#include <QComboBox>

#include "QColorListModel.h"

class QColorComboBox : public QComboBox
{
    Q_OBJECT
    class QColorComboBoxPrivate *d;

    Q_PROPERTY(QColorListModel::NameFormat nameFormat READ nameFormat WRITE setNameFormat)
    // NOTE: Qt Designer has no editor for QList<QColor>
    //Q_PROPERTY(QList<QColor> colors READ colors WRITE setColors  USER true)
    Q_PROPERTY(QStringList colorNames READ colorNames WRITE setColorNames USER true)

public:
    explicit QColorComboBox(QWidget *parent = 0);
    explicit QColorComboBox(const QList<QColor> &colors, QWidget *parent = 0);

    QColorListModel::NameFormat nameFormat() const;
    void setNameFormat(QColorListModel::NameFormat nameFormat);

    QList<QColor> colors() const;
    void setColors(const QList<QColor> &colors);

    QStringList colorNames() const;
    void setColorNames(const QStringList &colorNames);

    QColor currentColor() const;

public slots:
    void setCurrentColor(const QColor &color);
    void setEditColor(const QColor &color);

signals:
    void activated(const QColor &color);
    void currentIndexChanged(const QColor &color);
    void currentColorChanged(const QColor &color);
    void editColorChanged(const QColor &color);
    void highlighted(const QColor &color);
};

#endif // QCOLORCOMBOBOX_H
