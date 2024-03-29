#include "QUpDownButton.h"

#include <QAction>
#include <QBoxLayout>
#include <QToolButton>

class QUpDownButtonPrivate : public QObject {
    Q_OBJECT

public:
    explicit QUpDownButtonPrivate(QUpDownButton *widgetP, Qt::Orientation orientation)
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

        connect(upButton, &QAbstractButton::clicked, widget, &QUpDownButton::upClicked);
        connect(downButton, &QAbstractButton::clicked, widget, &QUpDownButton::downClicked);
        connect(upButton, &QAbstractButton::pressed, widget, &QUpDownButton::upPressed);
        connect(downButton, &QAbstractButton::pressed, widget, &QUpDownButton::downPressed);
        connect(upButton, &QAbstractButton::released, widget, &QUpDownButton::upReleased);
        connect(downButton, &QAbstractButton::released, widget, &QUpDownButton::downReleased);
        connect(upButton, &QAbstractButton::toggled, widget, &QUpDownButton::upToggled);
        connect(downButton, &QAbstractButton::toggled, widget, &QUpDownButton::downToggled);
        connect(upButton, &QToolButton::triggered, widget, &QUpDownButton::upTriggered);
        connect(downButton, &QToolButton::triggered, widget, &QUpDownButton::downTriggered);
    }

    Qt::Orientation directionToOrientation(QBoxLayout::Direction direction) const {
        switch (direction) {
        case QBoxLayout::LeftToRight:
        case QBoxLayout::RightToLeft:
            return Qt::Horizontal;
        case QBoxLayout::TopToBottom:
        case QBoxLayout::BottomToTop:
            return Qt::Vertical;
        }

        Q_UNREACHABLE();
    }

    QBoxLayout::Direction orientationToDirection(Qt::Orientation orientation) const {
        switch (orientation) {
        case Qt::Horizontal:
            return QBoxLayout::LeftToRight;
        case Qt::Vertical:
            return QBoxLayout::TopToBottom;
        }

        Q_UNREACHABLE();
    }

    void updateButtonArrows() {
        switch (directionToOrientation(layout->direction())) {
        case Qt::Horizontal:
            upButton->setArrowType(Qt::LeftArrow);
            downButton->setArrowType(Qt::RightArrow);
            break;
        case Qt::Vertical:
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
    , d(new QUpDownButtonPrivate(this, Qt::Vertical)) {
}

QUpDownButton::QUpDownButton(Qt::Orientation orientation, QWidget *parent)
    : QWidget(parent)
    , d(new QUpDownButtonPrivate(this, orientation)) {
}

Qt::Orientation QUpDownButton::orientation() const {
    return d->directionToOrientation(d->layout->direction());
}

void QUpDownButton::setOrientation(Qt::Orientation orientation) {
    d->layout->setDirection(d->orientationToDirection(orientation));
    d->updateButtonArrows();
}

int QUpDownButton::spacing() const {
    return d->layout->spacing();
}

void QUpDownButton::setSpacing(int spacing) {
    d->layout->setSpacing(spacing);
}

bool QUpDownButton::autoRaise() const {
    return d->upButton->autoRaise() && d->downButton->autoRaise();
}

void QUpDownButton::setAutoRaise(bool autoRaise) {
    d->upButton->setAutoRaise(autoRaise);
    d->downButton->setAutoRaise(autoRaise);
}

QToolButton::ToolButtonPopupMode QUpDownButton::popupMode() const {
    return d->upButton->popupMode();
}

void QUpDownButton::setPopupMode(QToolButton::ToolButtonPopupMode mode) {
    d->upButton->setPopupMode(mode);
    d->downButton->setPopupMode(mode);
}

QKeySequence QUpDownButton::upShortcut() const {
    return d->upButton->shortcut();
}

void QUpDownButton::setUpShortcut(const QKeySequence &key) {
    d->upButton->setShortcut(key);
}

QKeySequence QUpDownButton::downShortcut() const {
    return d->downButton->shortcut();
}

void QUpDownButton::setDownShortcut(const QKeySequence &key) {
    d->downButton->setShortcut(key);
}

QMenu *QUpDownButton::upMenu() const {
    return d->upButton->menu();
}

void QUpDownButton::setUpMenu(QMenu *menu) {
    d->upButton->setMenu(menu);
}

QMenu *QUpDownButton::downMenu() const {
    return d->downButton->menu();
}

void QUpDownButton::setDownMenu(QMenu *menu) {
    d->downButton->setMenu(menu);
}

void QUpDownButton::upAnimateClick() {
    d->upButton->animateClick();
}

void QUpDownButton::downAnimateClick() {
    d->downButton->animateClick();
}

void QUpDownButton::upClick() {
    d->upButton->click();
}

void QUpDownButton::downClick() {
    d->downButton->click();
}

void QUpDownButton::upToggle() {
    d->upButton->toggle();
}

void QUpDownButton::downToggle() {
    d->downButton->toggle();
}

void QUpDownButton::upShowMenu() {
    d->upButton->showMenu();
}

void QUpDownButton::downShowMenu() {
    d->downButton->showMenu();
}

#include "QUpDownButton.moc"
