#ifndef QCOLORPUSHBUTTON_H
#define QCOLORPUSHBUTTON_H

#include <QPushButton>
#include <QColorDialog>

// NOTE: This class duplicate QColorDialog::ColorDialogOptions because Qt forgot to make this enum a flag (Q_FLAGS)

class QColorPushButton : public QPushButton
{
    Q_OBJECT
    class QColorPushButtonPrivate* d;

    Q_FLAGS(ColorDialogOptions)

    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption RESET resetCaption)
    Q_PROPERTY(QColorPushButton::ColorDialogOptions options READ options WRITE setOptions RESET resetOptions)

public:
    enum ColorDialogOption {
        ShowAlphaChannel = QColorDialog::ShowAlphaChannel,
        NoButtons = QColorDialog::NoButtons,
        DontUseNativeDialog = QColorDialog::DontUseNativeDialog
    };
    Q_DECLARE_FLAGS(ColorDialogOptions, ColorDialogOption)

    explicit QColorPushButton(QWidget *parent = 0);
    explicit QColorPushButton(const QColor &color, QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorPushButton::ColorDialogOptions options() const;
    void setOptions(QColorPushButton::ColorDialogOptions options);

protected:
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void resetColor();
    void resetCaption();
    void resetOptions();

signals:
    void colorChanged(const QColor &color);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QColorPushButton::ColorDialogOptions)

#endif // QCOLORPUSHBUTTON_H
