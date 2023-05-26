#pragma once

#include <QtWidgetsExtra/QAbstractButtonLineEdit.h>
#include <QtWidgetsExtra/Color/QColorAction.h>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QColorLineEdit : public QAbstractButtonLineEdit
{
    Q_OBJECT
    class QColorLineEditPrivate* d;

    Q_PROPERTY(QLineEdit::ActionPosition embededActionPosition READ embededActionPosition WRITE setEmbededActionPosition NOTIFY embededActionPositionChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QColorAction::ColorDialogOptions options READ options WRITE setOptions)

public:
    explicit QColorLineEdit(QWidget *parent = nullptr);
    explicit QColorLineEdit(const QColor &color, QWidget *parent = nullptr);
    explicit QColorLineEdit(const QString &colorName, QWidget *parent = nullptr);

    QLineEdit::ActionPosition embededActionPosition() const;
    void setEmbededActionPosition(QLineEdit::ActionPosition position);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorAction::ColorDialogOptions options() const;
    void setOptions(QColorAction::ColorDialogOptions options);

Q_SIGNALS:
    void embededActionPositionChanged(QLineEdit::ActionPosition position);
    void colorChanged(const QColor &color);
};
