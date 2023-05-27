#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QToolButton>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QEmbedableButton : public QToolButton {
    Q_OBJECT

public:
    explicit QEmbedableButton(QWidget *parent = nullptr);

    bool isEmbeded() const;
    void setEmbeded(bool embed);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    bool embeded;
};
