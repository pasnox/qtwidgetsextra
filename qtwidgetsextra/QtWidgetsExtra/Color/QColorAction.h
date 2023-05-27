#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QAction>
#include <QColorDialog>

// NOTE: This class duplicate QColorDialog::ColorDialogOptions because Qt forgot to make this enum a flag (Q_FLAG)

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QColorAction : public QAction {
    Q_OBJECT
    class QColorActionPrivate *d;

public:
    enum class ColorDialogOption {
        ShowAlphaChannel = QColorDialog::ShowAlphaChannel,
        NoButtons = QColorDialog::NoButtons,
        DontUseNativeDialog = QColorDialog::DontUseNativeDialog
    };
    Q_ENUM(ColorDialogOption)
    Q_DECLARE_FLAGS(ColorDialogOptions, ColorDialogOption)
    Q_FLAG(ColorDialogOptions)

    explicit QColorAction(QObject *parent = nullptr);
    explicit QColorAction(const QColor &color, QObject *parent = nullptr);
    explicit QColorAction(const QString &colorName, QObject *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    QString caption() const;
    void setCaption(const QString &caption);

    QColorAction::ColorDialogOptions options() const;
    void setOptions(QColorAction::ColorDialogOptions options);

    QIcon colorIcon(const QColor &color) const;
    QString colorName(const QColor &color) const;

Q_SIGNALS:
    void colorChanged(const QColor &color);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QColorAction::ColorDialogOptions)
