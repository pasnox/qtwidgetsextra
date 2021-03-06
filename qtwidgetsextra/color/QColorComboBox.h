#ifndef QCOLORCOMBOBOX_H
#define QCOLORCOMBOBOX_H

#include <QComboBox>

#include "QColorListModel.h"

class QColorComboBox : public QComboBox
{
    Q_OBJECT
    class QColorComboBoxPrivate *d;

    Q_PROPERTY(QColorListModel::NameFormat nameFormat READ nameFormat WRITE setNameFormat)
    Q_PROPERTY(QStringList colorListNames READ colorListNames WRITE setColorListNames)
    Q_PROPERTY(QString currentColorName READ currentColorName WRITE setCurrentColorName USER true)

public:
    explicit QColorComboBox(QWidget *parent = 0);
    explicit QColorComboBox(const QStringList &colorListNames, QWidget *parent = 0);
    explicit QColorComboBox(const QList<QColor> &colorsList, QWidget *parent = 0);

    QColorListModel::NameFormat nameFormat() const;
    void setNameFormat(QColorListModel::NameFormat nameFormat);

    QStringList colorListNames() const;
    void setColorListNames(const QStringList &colorListNames);

    QList<QColor> colorsList() const;
    void setColorsList(const QList<QColor> &colorsList);

    QString currentColorName() const;
    QString currentTextColorName() const;

    QColor currentColor() const;
    QColor currentTextColor() const;

public slots:
    void setCurrentColorName(const QString &colorName);
    void setCurrentTextColorName(const QString &colorName);
    void setEditTextColorName(const QString &colorName);

    void setCurrentColor(const QColor &color);
    void setCurrentTextColor(const QColor &color);
    void setEditTextColor(const QColor &color);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:
    void activated(const QColor &color);
    void currentIndexChanged(const QColor &color);
    void currentTextChanged(const QColor &color);
    void editTextChanged(const QColor &color);
    void highlighted(const QColor &color);
};

#endif // QCOLORCOMBOBOX_H
