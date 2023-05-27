#include "QCollapsibleFrame.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QPainter>
#include <QPointer>
#include <QStyle>
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>

class QCollapsibleToolButton : public QToolButton {
public:
    using QToolButton::QToolButton;

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        if (!icon().isNull()) {
            const QIcon::Mode mode = isEnabled() ? QIcon::Normal : QIcon::Disabled;
            const QIcon::State state = QIcon::Off;
            QPainter painter(this);
            QRect r(QPoint(), iconSize());
            r.moveCenter(contentsRect().center());
            icon().paint(&painter, r, Qt::AlignCenter, mode, state);
        }
    }
};

class QCollapsibleFramePrivate : public QObject {
    Q_OBJECT

public:
    QCollapsibleFrame *editor;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QToolButton *button;
    QPointer<QWidget> title;
    QPointer<QWidget> widget;
    QIcon collapsedIcon;
    QIcon expandedIcon;
    bool collapsed;
    //
    QCollapsibleFrame::RestoreSizeBehavior resizeBehavior = QCollapsibleFrame::RestoreSizeBehavior::Window;
    QSize oldCollapsedSize;
    QSize oldExpandedSize;

public:
    explicit QCollapsibleFramePrivate(QCollapsibleFrame *_editor)
        : QObject(_editor)
        , editor(_editor)
        , horizontalLayout(new QHBoxLayout)
        , verticalLayout(new QVBoxLayout(editor))
        , button(new QCollapsibleToolButton(editor))
        , collapsed(false) {
        button->setToolButtonStyle(Qt::ToolButtonIconOnly);
        button->setCheckable(true);

        horizontalLayout->addWidget(button, 0, Qt::AlignLeft);

        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->addLayout(horizontalLayout);
        verticalLayout->setAlignment(horizontalLayout, Qt::AlignTop);

        connect(button, &QAbstractButton::toggled, this, &QCollapsibleFramePrivate::button_toggled);
    }

    void button_toggled(bool toggled) {
        switch (resizeBehavior) {
        case QCollapsibleFrame::RestoreSizeBehavior::Window:
            storeSizes(editor->window());
            break;
        case QCollapsibleFrame::RestoreSizeBehavior::None:
            break;
        }

        collapsed = !toggled;

        if (collapsed) {
            Q_EMIT editor->aboutToCollapse();
        } else {
            Q_EMIT editor->aboutToExpand();
        }

        button->setIcon(collapsed ? editor->collapsedIcon() : editor->expandedIcon());
        button->setChecked(toggled);

        if (widget) {
            widget->setVisible(toggled);
        }

        switch (resizeBehavior) {
        case QCollapsibleFrame::RestoreSizeBehavior::Window:
            QMetaObject::invokeMethod(
                this, [this]() { restoreSize(editor->window()); }, Qt::QueuedConnection);
            break;
        case QCollapsibleFrame::RestoreSizeBehavior::None:
            break;
        }
    }

    void storeSizes(QWidget *widget) {
        if (widget->isHidden() || !widget->size().isValid()) {
            return;
        }

        oldCollapsedSize = collapsed ? widget->size() : oldCollapsedSize;
        oldExpandedSize = collapsed ? oldExpandedSize : widget->size();
    }

    void restoreSize(QWidget *widget) {
        if (widget->isHidden()) {
            return;
        }

        if (collapsed) {
            if (oldCollapsedSize.isValid()) {
                const auto layouts = widget->findChildren<QLayout *>();
                for (QLayout *layout : layouts) {
                    layout->invalidate();
                    layout->activate();
                }

                widget->resize(oldCollapsedSize);
            }
            Q_EMIT editor->collapsed();
        } else {
            if (oldExpandedSize.isValid()) {
                const auto layouts = widget->findChildren<QLayout *>();
                for (QLayout *layout : layouts) {
                    layout->invalidate();
                    layout->activate();
                }

                widget->resize(oldExpandedSize);
            }
            Q_EMIT editor->expanded();
        }
    }
};

QCollapsibleFrame::QCollapsibleFrame(QWidget *parent)
    : QFrame(parent)
    , d(new QCollapsibleFramePrivate(this)) {
    d->button_toggled(d->button->isChecked());
}

QSize QCollapsibleFrame::minimumSizeHint() const {
    const QMargins margins = d->verticalLayout->contentsMargins();
    QSize sh(d->button->minimumSizeHint());

    sh.rwidth() += margins.left() + margins.right();
    sh.rheight() += margins.top() + margins.bottom();

    if (d->collapsed) {
    } else if (d->widget) {
        int spacing = d->verticalLayout->spacing();

        if (spacing == -1) {
            spacing = style()->pixelMetric(QStyle::PM_LayoutVerticalSpacing);
        }

        if (spacing == -1) {
            spacing = style()->layoutSpacing(d->button->sizePolicy().controlType(),
                                             d->widget->sizePolicy().controlType(), Qt::Vertical, 0, this);
        }

        sh.rwidth() = qMax(sh.width(), d->widget->minimumSizeHint().width());
        sh.rheight() += d->widget->minimumSizeHint().height();
        sh.rheight() += spacing;
    }

    return sh;
}

QCollapsibleFrame::RestoreSizeBehavior QCollapsibleFrame::restoreSizeBehavior() const {
    return d->resizeBehavior;
}

void QCollapsibleFrame::setRestoreSizeBehavior(QCollapsibleFrame::RestoreSizeBehavior behavior) {
    if (d->resizeBehavior != behavior) {
        d->resizeBehavior = behavior;
        d->button_toggled(d->button->isChecked());
    }
}

QWidget *QCollapsibleFrame::title() const {
    return d->title;
}

QWidget *QCollapsibleFrame::takeTitle() {
    if (!d->title) {
        return nullptr;
    }

    QWidget *title = d->title;
    d->title = nullptr;
    d->horizontalLayout->removeWidget(title);
    title->setParent(nullptr);

    d->button_toggled(d->button->isChecked());

    Q_EMIT titleChanged();

    return title;
}

void QCollapsibleFrame::setTitle(QWidget *title) {
    if (d->title != title) {
        /*delete*/ takeTitle();

        if (title) {
            d->title = title;
            d->horizontalLayout->addWidget(title, 1);
            d->button_toggled(d->button->isChecked());
        }

        Q_EMIT titleChanged();
    }
}

QWidget *QCollapsibleFrame::widget() const {
    return d->widget;
}

QWidget *QCollapsibleFrame::takeWidget() {
    if (!d->widget) {
        return 0;
    }

    QWidget *widget = d->widget;
    d->widget = 0;
    d->verticalLayout->removeWidget(widget);
    widget->setParent(0);

    d->button_toggled(d->button->isChecked());

    Q_EMIT widgetChanged();

    return widget;
}

void QCollapsibleFrame::setWidget(QWidget *widget) {
    if (d->widget != widget) {
        /*delete*/ takeWidget();

        if (widget) {
            d->widget = widget;
            d->verticalLayout->addWidget(widget);
            d->button_toggled(d->button->isChecked());
        }

        Q_EMIT widgetChanged();
    }
}

QString QCollapsibleFrame::titleObjectName() const {
    if (auto w = title()) {
        return w->objectName();
    }

    return {};
}

void QCollapsibleFrame::setTitleObjectName(const QString &name) {
    QMetaObject::invokeMethod(
        this,
        [this, name]() {
            if (titleObjectName() != name) {
                setTitle(findChild<QWidget *>(name));
            }
        },
        Qt::QueuedConnection);
}

QString QCollapsibleFrame::widgetObjectName() const {
    if (auto w = widget()) {
        return w->objectName();
    }

    return {};
}

void QCollapsibleFrame::setWidgetObjectName(const QString &name) {
    QMetaObject::invokeMethod(
        this,
        [this, name]() {
            if (widgetObjectName() != name) {
                setWidget(findChild<QWidget *>(name));
            }
        },
        Qt::QueuedConnection);
}

QString QCollapsibleFrame::collapseToolTip() const {
    return d->button->toolTip();
}

QIcon QCollapsibleFrame::collapsedIcon() const {
    return d->collapsedIcon.isNull() ? style()->standardIcon(QStyle::SP_ArrowRight) : d->collapsedIcon;
}

QIcon QCollapsibleFrame::expandedIcon() const {
    return d->expandedIcon.isNull() ? style()->standardIcon(QStyle::SP_ArrowDown) : d->expandedIcon;
}

bool QCollapsibleFrame::isCollapsed() const {
    return d->collapsed;
}

bool QCollapsibleFrame::isExpanded() const {
    return !isCollapsed();
}

int QCollapsibleFrame::indentation() const {
    return d->verticalLayout->contentsMargins().left();
}

void QCollapsibleFrame::setCollapseToolTip(const QString &toolTip) {
    d->button->setToolTip(toolTip);
}

void QCollapsibleFrame::setCollapsedIcon(const QIcon &icon) {
    d->collapsedIcon = icon;
    Q_EMIT collapsedIconChanged();

    if (d->collapsed) {
        d->button->setIcon(collapsedIcon());
    }
}

void QCollapsibleFrame::setExpandedIcon(const QIcon &icon) {
    d->expandedIcon = icon;
    Q_EMIT expandedIconChanged();

    if (!d->collapsed) {
        d->button->setIcon(expandedIcon());
    }
}

void QCollapsibleFrame::setIcon(const QIcon &icon) {
    setCollapsedIcon(icon);
    setExpandedIcon(icon);
}

void QCollapsibleFrame::setCollapsed(bool collapsed) {
    if (d->collapsed != collapsed) {
        d->button->setChecked(!collapsed);
    }
}

void QCollapsibleFrame::setExpanded(bool expanded) {
    setCollapsed(!expanded);
}

void QCollapsibleFrame::setIndentation(int indentation) {
    if (QCollapsibleFrame::indentation() != indentation) {
        QMargins margins = d->verticalLayout->contentsMargins();
        margins.setLeft(indentation);
        d->verticalLayout->setContentsMargins(margins);
        Q_EMIT indentationChanged();
    }
}

#include "QCollapsibleFrame.moc"
