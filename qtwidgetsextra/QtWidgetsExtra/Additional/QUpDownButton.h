#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QToolButton>
#include <QWidget>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QUpDownButton : public QWidget {
    Q_OBJECT
    class QUpDownButtonPrivate *d;

    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(bool autoRaise READ autoRaise WRITE setAutoRaise)
    Q_PROPERTY(QToolButton::ToolButtonPopupMode popupMode READ popupMode WRITE setPopupMode)
    Q_PROPERTY(QKeySequence upShortcut READ upShortcut WRITE setUpShortcut)
    Q_PROPERTY(QKeySequence downShortcut READ downShortcut WRITE setDownShortcut)

public:
    explicit QUpDownButton(QWidget *parent = nullptr);
    explicit QUpDownButton(Qt::Orientation orientation, QWidget *parent = nullptr);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    int spacing() const;
    void setSpacing(int spacing);

    bool autoRaise() const;
    void setAutoRaise(bool autoRaise);

    QToolButton::ToolButtonPopupMode popupMode() const;
    void setPopupMode(QToolButton::ToolButtonPopupMode mode);

    QKeySequence upShortcut() const;
    void setUpShortcut(const QKeySequence &key);

    QKeySequence downShortcut() const;
    void setDownShortcut(const QKeySequence &key);

    QMenu *upMenu() const;
    void setUpMenu(QMenu *menu);

    QMenu *downMenu() const;
    void setDownMenu(QMenu *menu);

public Q_SLOTS:
    void upAnimateClick();
    void downAnimateClick();
    void upClick();
    void downClick();
    void upToggle();
    void downToggle();
    void upShowMenu();
    void downShowMenu();

Q_SIGNALS:
    void upClicked(bool checked = false);
    void downClicked(bool checked = false);
    void upPressed();
    void downPressed();
    void upReleased();
    void downReleased();
    void upToggled(bool checked);
    void downToggled(bool checked);
    void upTriggered(QAction *action);
    void downTriggered(QAction *action);
};
