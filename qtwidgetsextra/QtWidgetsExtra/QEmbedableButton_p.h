#pragma once

#include <QToolButton>

#include <QtWidgetsExtraLibExport.h>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QEmbedableButton : public QToolButton
{
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
