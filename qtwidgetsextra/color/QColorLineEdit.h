#ifndef QCOLORLINEEDIT_H
#define QCOLORLINEEDIT_H

#include <QLineEdit>

#include "QColorToolButton.h"

class QColorLineEdit : public QLineEdit
{
    Q_OBJECT
    class QColorLineEditPrivate* d;

    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption RESET resetCaption)
    Q_PROPERTY(QColorToolButton::ColorDialogOptions options READ options WRITE setOptions RESET resetOptions)

public:
    explicit QColorLineEdit(QWidget *parent = 0);
    explicit QColorLineEdit(const QColor &color, QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorToolButton::ColorDialogOptions options() const;
    void setOptions(QColorToolButton::ColorDialogOptions options);

private slots:
    void resetColor();
    void resetCaption();
    void resetOptions();

signals:
    void colorChanged(const QColor &color);
};

#endif // QCOLORLINEEDIT_H
