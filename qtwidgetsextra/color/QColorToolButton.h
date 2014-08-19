#ifndef QCOLORTOOLBUTTON_H
#define QCOLORTOOLBUTTON_H

#include <QToolButton>
#include <QColorDialog>

class QColorToolButton : public QToolButton
{
    Q_OBJECT
    class QColorToolButtonPrivate* d;

    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor USER true NOTIFY colorChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption RESET resetCaption)
    Q_PROPERTY(QColorDialog::ColorDialogOptions options READ options WRITE setOptions RESET resetOptions)

public:
    explicit QColorToolButton(QWidget *parent = 0);
    explicit QColorToolButton(const QColor &color, QWidget *parent = 0);

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

#endif // QCOLORTOOLBUTTON_H
