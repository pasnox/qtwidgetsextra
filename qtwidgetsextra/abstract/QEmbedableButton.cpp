#include "QEmbedableButton_p.h"

#include <QStylePainter>
#include <QStyleOptionToolButton>

QEmbedableButton::QEmbedableButton(QWidget *parent)
    : QToolButton(parent)
    , embeded(false)
{
}

bool QEmbedableButton::isEmbeded() const
{
    return embeded;
}

void QEmbedableButton::setEmbeded(bool embed)
{
    embeded = embed;
    update();
}

void QEmbedableButton::paintEvent(QPaintEvent *event)
{
    if (embeded) {
        QStylePainter p(this);
        QStyleOptionToolButton opt;
        initStyleOption(&opt);
        opt.state |= QStyle::State_AutoRaise;
        opt.state &= ~QStyle::State_Raised;
        opt.state &= ~QStyle::State_Sunken;
        //opt.state &= ~QStyle::State_On;
#if defined(Q_OS_MACX)
        opt.subControls &= ~QStyle::SC_ToolButton;
#endif
        p.drawComplexControl(QStyle::CC_ToolButton, opt);
    }
    else {
        QToolButton::paintEvent(event);
    }
}
