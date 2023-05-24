#include "QAbstractButtonLineEdit.h"
#include "QtWidgetsExtra/QEmbedableButton_p.h"

#include <QStyle>
#include <QHBoxLayout>

class QAbstractButtonLineEditPrivate : public QObject {
    Q_OBJECT

public:
    QAbstractButtonLineEditPrivate(QAbstractButtonLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , button(0) {
        Q_ASSERT(widget);

        const int frameMargin = widget->style()->pixelMetric(QStyle::PM_DefaultFrameWidth, 0, widget);
        const int height = widget->sizeHint().height() -(frameMargin *4);
        QMargins margins(widget->textMargins());

        button = widget->createButton();
        button->setCursor(Qt::ArrowCursor);
        button->setFixedSize(height, height);
        button->setIconSize(QSize(height, height));

        margins.setLeft(margins.left() +(frameMargin *2));

        QHBoxLayout* hl = new QHBoxLayout(widget);
        hl->setSpacing(0);
        hl->setContentsMargins(margins);
        hl->addWidget(button);
        hl->addStretch();

        margins.setLeft(margins.left() +height);
        widget->setTextMargins(margins);
    }

public:
    QAbstractButtonLineEdit *widget;
    QToolButton *button;
};

QAbstractButtonLineEdit::QAbstractButtonLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , d(new QAbstractButtonLineEditPrivate(this))
{
}

QAbstractButtonLineEdit::QAbstractButtonLineEdit(QAction *action, QWidget *parent)
    : QLineEdit(parent)
    , d(new QAbstractButtonLineEditPrivate(this))
{
    setDefaultAction(action);
}

QAbstractButtonLineEdit::QAbstractButtonLineEdit(QMenu *menu, QWidget *parent)
    : QLineEdit(parent)
    , d(new QAbstractButtonLineEditPrivate(this))
{
    setMenu(menu);
}

QAction *QAbstractButtonLineEdit::defaultAction() const
{
    return d->button->defaultAction();
}

void QAbstractButtonLineEdit::setDefaultAction(QAction *action)
{
    d->button->setDefaultAction(action);
}

QMenu *QAbstractButtonLineEdit::menu() const
{
    return d->button->menu();
}

void QAbstractButtonLineEdit::setMenu(QMenu *menu)
{
    d->button->setMenu(menu);
}

QToolButton *QAbstractButtonLineEdit::button() const
{
    return d->button;
}

QToolButton *QAbstractButtonLineEdit::createButton()
{
    QEmbedableButton *eb = new QEmbedableButton(this);
    eb->setEmbeded(true);
    return eb;
}

#include "QAbstractButtonLineEdit.moc"
