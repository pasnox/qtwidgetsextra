#pragma once

#include <QtWidgetsExtra/Color/QColorListModel.h>

#include <QComboBox>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QColorComboBox : public QComboBox {
    Q_OBJECT
    class QColorComboBoxPrivate *d;

    Q_PROPERTY(QColorListModel::NameFormat nameFormat READ nameFormat WRITE setNameFormat)
    Q_PROPERTY(QStringList colorNames READ colorNames WRITE setColorNames)
    Q_PROPERTY(QString currentColorName READ currentColorName WRITE setCurrentColorName USER true)

public:
    explicit QColorComboBox(QWidget *parent = nullptr);
    explicit QColorComboBox(const QStringList &colorNames, QWidget *parent = nullptr);
    explicit QColorComboBox(const QList<QColor> &colors, QWidget *parent = nullptr);

    QColorListModel::NameFormat nameFormat() const;
    void setNameFormat(QColorListModel::NameFormat nameFormat);

    QStringList colorNames() const;
    void setColorNames(const QStringList &colorNames);

    QList<QColor> colors() const;
    void setColors(const QList<QColor> &colors);

    QString currentColorName() const;
    QString currentTextColorName() const;

    QColor currentColor() const;
    QColor currentTextColor() const;

public Q_SLOTS:
    void setCurrentColorName(const QString &colorName);
    void setCurrentTextColorName(const QString &colorName);
    void setEditTextColorName(const QString &colorName);

    void setCurrentColor(const QColor &color);
    void setCurrentTextColor(const QColor &color);
    void setEditTextColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

Q_SIGNALS:
    void colorActivated(const QColor &color);
    void currentColorChanged(const QColor &color);
    void currentTextColorChanged(const QColor &color);
    void editTextColorChanged(const QColor &color);
    void colorHighlighted(const QColor &color);
};
