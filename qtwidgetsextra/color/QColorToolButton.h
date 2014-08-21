#ifndef QCOLORTOOLBUTTON_H
#define QCOLORTOOLBUTTON_H

#include "QEmbedableButton_p.h"

#include <QColorDialog>

// NOTE: This class duplicate QColorDialog::ColorDialogOptions because Qt forgot to make this enum a flag (Q_FLAGS)

class QColorToolButton : public QEmbedableButton
{
    Q_OBJECT
    class QColorToolButtonPrivate* d;

    Q_FLAGS(ColorDialogOptions)

    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption RESET resetCaption)
    Q_PROPERTY(QColorToolButton::ColorDialogOptions options READ options WRITE setOptions RESET resetOptions)

public:
    enum ColorDialogOption {
        ShowAlphaChannel = QColorDialog::ShowAlphaChannel,
        NoButtons = QColorDialog::NoButtons,
        DontUseNativeDialog = QColorDialog::DontUseNativeDialog
    };
    Q_DECLARE_FLAGS(ColorDialogOptions, ColorDialogOption)

    explicit QColorToolButton(QWidget *parent = 0);
    explicit QColorToolButton(const QColor &color, QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorToolButton::ColorDialogOptions options() const;
    void setOptions(QColorToolButton::ColorDialogOptions options);

    QIcon colorIcon(const QColor &color) const;

protected:
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void resetColor();
    void resetCaption();
    void resetOptions();

signals:
    void colorChanged(const QColor &color);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QColorToolButton::ColorDialogOptions)

#endif // QCOLORTOOLBUTTON_H
