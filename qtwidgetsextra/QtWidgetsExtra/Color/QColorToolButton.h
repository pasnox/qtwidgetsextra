#pragma once

#include <QtWidgetsExtra/QEmbedableButton_p.h>
#include <QtWidgetsExtra/Color/QColorAction.h>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QColorToolButton : public QEmbedableButton
{
    Q_OBJECT
    class QColorToolButtonPrivate *d;

    Q_PROPERTY(QColor color READ color WRITE setColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QColorAction::ColorDialogOptions options READ options WRITE setOptions)

public:
    explicit QColorToolButton(QWidget *parent = 0);
    explicit QColorToolButton(const QColor &color, QWidget *parent = 0);
    explicit QColorToolButton(const QString &colorName, QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorAction::ColorDialogOptions options() const;
    void setOptions(QColorAction::ColorDialogOptions options);

Q_SIGNALS:
    void colorChanged(const QColor &color);
};
