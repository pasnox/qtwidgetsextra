#pragma once

#include <QtWidgetsExtra/Color/QColorAction.h>

#include <QPushButton>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QColorPushButton : public QPushButton {
    Q_OBJECT
    class QColorPushButtonPrivate *d;

    Q_PROPERTY(QColor color READ color WRITE setColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QColorAction::ColorDialogOptions options READ options WRITE setOptions)

public:
    explicit QColorPushButton(QWidget *parent = nullptr);
    explicit QColorPushButton(const QColor &color, QWidget *parent = nullptr);
    explicit QColorPushButton(const QString &colorName, QWidget *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorAction::ColorDialogOptions options() const;
    void setOptions(QColorAction::ColorDialogOptions options);

Q_SIGNALS:
    void colorChanged(const QColor &color);
};
