#ifndef QCOLORACTION_H
#define QCOLORACTION_H

#include <QAction>
#include <QColorDialog>

// NOTE: This class duplicate QColorDialog::ColorDialogOptions because Qt forgot to make this enum a flag (Q_FLAGS)

class QColorAction : public QAction
{
    Q_OBJECT
    class QColorActionPrivate *d;

    Q_FLAGS(ColorDialogOptions)

public:
    enum ColorDialogOption {
        ShowAlphaChannel = QColorDialog::ShowAlphaChannel,
        NoButtons = QColorDialog::NoButtons,
        DontUseNativeDialog = QColorDialog::DontUseNativeDialog
    };
    Q_DECLARE_FLAGS(ColorDialogOptions, ColorDialogOption)

    explicit QColorAction(QObject *parent = 0);
    explicit QColorAction(const QColor &color, QObject *parent = 0);
    explicit QColorAction(const QString &colorName, QObject *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorAction::ColorDialogOptions options() const;
    void setOptions(QColorAction::ColorDialogOptions options);

    QIcon colorIcon(const QColor &color) const;
    QString colorName(const QColor &color) const;

signals:
    void colorChanged(const QColor &color);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QColorAction::ColorDialogOptions)

#endif // QCOLORACTION_H
