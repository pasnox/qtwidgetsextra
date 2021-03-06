#ifndef QCOLORPUSHBUTTON_H
#define QCOLORPUSHBUTTON_H

#include <QPushButton>

#include "QColorAction.h"

class QColorPushButton : public QPushButton
{
    Q_OBJECT
    class QColorPushButtonPrivate* d;

    Q_PROPERTY(QColor color READ color WRITE setColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QColorAction::ColorDialogOptions options READ options WRITE setOptions)

public:

    explicit QColorPushButton(QWidget *parent = 0);
    explicit QColorPushButton(const QColor &color, QWidget *parent = 0);
    explicit QColorPushButton(const QString &colorName, QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorAction::ColorDialogOptions options() const;
    void setOptions(QColorAction::ColorDialogOptions options);

signals:
    void colorChanged(const QColor &color);
};

#endif // QCOLORPUSHBUTTON_H
