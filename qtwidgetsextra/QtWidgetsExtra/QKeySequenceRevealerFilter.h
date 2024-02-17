#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QObject>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QKeySequenceRevealerFilter : public QObject {
    Q_OBJECT

public:
    using QObject::QObject;

protected:
    bool eventFilter(QObject *object, QEvent *event) override;
};
