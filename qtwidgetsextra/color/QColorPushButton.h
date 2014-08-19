#ifndef QCOLORPUSHBUTTON_H
#define QCOLORPUSHBUTTON_H

#include <QPushButton>
#include <QColorDialog>

class QColorPushButton : public QPushButton
{
    Q_OBJECT
    class QColorPushButtonPrivate* d;

    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption RESET resetCaption)
    Q_PROPERTY(QColorDialog::ColorDialogOptions options READ options WRITE setOptions RESET resetOptions)

public:
    explicit QColorPushButton(QWidget *parent = 0);
    explicit QColorPushButton(const QColor &color, QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorDialog::ColorDialogOptions options() const;
    void setOptions(QColorDialog::ColorDialogOptions options);

protected:
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void resetColor();
    void resetCaption();
    void resetOptions();

signals:
    void colorChanged(const QColor &color);
};

Q_DECLARE_METATYPE(QColorDialog::ColorDialogOptions)

#endif // QCOLORPUSHBUTTON_H
