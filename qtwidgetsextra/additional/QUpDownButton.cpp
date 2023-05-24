#include "QUpDownButton.h"

#include <QToolButton>
#include <QBoxLayout>

class QUpDownButtonPrivate : public QObject {
    Q_OBJECT

public:
    QUpDownButtonPrivate(QUpDownButton *widgetP, Qt::Orientation orientation)
        : QObject(widgetP)
        , widget(widgetP)
        , layout(new QBoxLayout(orientationToDirection(orientation), widget))
        , upButton(new QToolButton(widget))
        , downButton(new QToolButton(widget))
        , autoRaise(false) {
        Q_ASSERT(widget);

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(1);
        layout->addWidget(upButton);
        layout->addWidget(downButton);

        upButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        downButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        updateButtonArrows();

        connect(upButton, SIGNAL(clicked(bool)), widget, SIGNAL(upClicked(bool)));
        connect(downButton, SIGNAL(clicked(bool)), widget, SIGNAL(downClicked(bool)));
        connect(upButton, SIGNAL(pressed()), widget, SIGNAL(upPressed()));
        connect(downButton, SIGNAL(pressed()), widget, SIGNAL(downPressed()));
        connect(upButton, SIGNAL(released()), widget, SIGNAL(upReleased()));
        connect(downButton, SIGNAL(released()), widget, SIGNAL(downReleased()));
        connect(upButton, SIGNAL(toggled(bool)), widget, SIGNAL(upToggled(bool)));
        connect(downButton, SIGNAL(toggled(bool)), widget, SIGNAL(downToggled(bool)));
        connect(upButton, SIGNAL(triggered(QAction*)), widget, SIGNAL(upTriggered(QAction*)));
        connect(downButton, SIGNAL(triggered(QAction*)), widget, SIGNAL(downTriggered(QAction*)));
    }

    Qt::Orientation directionToOrientation(QBoxLayout::Direction direction) const {
        switch (direction) {
            case QBoxLayout::LeftToRight:
            case QBoxLayout::RightToLeft:
                return Qt::Horizontal;
            case QBoxLayout::TopToBottom:
            case QBoxLayout::BottomToTop:
            default:
                return Qt::Vertical;
        }
    }

    QBoxLayout::Direction orientationToDirection(Qt::Orientation orientation) const {
        switch (orientation) {
            case Qt::Horizontal:
                return QBoxLayout::LeftToRight;
            case Qt::Vertical:
            default:
                return QBoxLayout::TopToBottom;
        }
    }

    void updateButtonArrows() {
        switch (directionToOrientation(layout->direction())) {
            case Qt::Horizontal:
                upButton->setArrowType(Qt::LeftArrow);
                downButton->setArrowType(Qt::RightArrow);
                break;
            case Qt::Vertical:
            default:
                upButton->setArrowType(Qt::UpArrow);
                downButton->setArrowType(Qt::DownArrow);
                break;
        }
    }

public:
    QUpDownButton *widget;
    QBoxLayout *layout;
    QToolButton *upButton;
    QToolButton *downButton;
    bool autoRaise;
};

QUpDownButton::QUpDownButton(QWidget *parent)
    : QWidget(parent)
    , d(new QUpDownButtonPrivate(this, Qt::Vertical))
{
}

QUpDownButton::QUpDownButton(Qt::Orientation orientation, QWidget *parent)
    : QWidget(parent)
    , d(new QUpDownButtonPrivate(this, orientation))
{
}

Qt::Orientation QUpDownButton::orientation() const
{
    return d->directionToOrientation(d->layout->direction());
}

void QUpDownButton::setOrientation(Qt::Orientation orientation)
{
    d->layout->setDirection(d->orientationToDirection(orientation));
    d->updateButtonArrows();
}

int QUpDownButton::spacing() const
{
    return d->layout->spacing();
}

void QUpDownButton::setSpacing(int spacing)
{
    d->layout->setSpacing(spacing);
}

bool QUpDownButton::autoRaise() const
{
    return d->upButton->autoRaise() && d->downButton->autoRaise();
}

void QUpDownButton::setAutoRaise(bool autoRaise)
{
    d->upButton->setAutoRaise(autoRaise);
    d->downButton->setAutoRaise(autoRaise);
}

QToolButton::ToolButtonPopupMode QUpDownButton::popupMode() const
{
    return d->upButton->popupMode();
}

void QUpDownButton::setPopupMode(QToolButton::ToolButtonPopupMode mode)
{
    d->upButton->setPopupMode(mode);
    d->downButton->setPopupMode(mode);
}

QKeySequence QUpDownButton::upShortcut() const
{
    return d->upButton->shortcut();
}

void QUpDownButton::setUpShortcut(const QKeySequence &key)
{
    d->upButton->setShortcut(key);
}

QKeySequence QUpDownButton::downShortcut() const
{
    return d->downButton->shortcut();
}

void QUpDownButton::setDownShortcut(const QKeySequence &key)
{
    d->downButton->setShortcut(key);
}

QMenu *QUpDownButton::upMenu() const
{
    return d->upButton->menu();
}

void QUpDownButton::setUpMenu(QMenu *menu)
{
    d->upButton->setMenu(menu);
}

QMenu *QUpDownButton::downMenu() const
{
    return d->downButton->menu();
}

void QUpDownButton::setDownMenu(QMenu *menu)
{
    d->downButton->setMenu(menu);
}

void QUpDownButton::upAnimateClick()
{
    d->upButton->animateClick();
}

void QUpDownButton::downAnimateClick()
{
    d->downButton->animateClick();
}

void QUpDownButton::upClick()
{
    d->upButton->click();
}

void QUpDownButton::downClick()
{
    d->downButton->click();
}

void QUpDownButton::upToggle()
{
    d->upButton->toggle();
}

void QUpDownButton::downToggle()
{
    d->downButton->toggle();
}

void QUpDownButton::upShowMenu()
{
    d->upButton->showMenu();
}

void QUpDownButton::downShowMenu()
{
    d->downButton->showMenu();
}

#include "QUpDownButton.moc"
