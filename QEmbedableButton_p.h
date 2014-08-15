#ifndef QEMBEDABLEBUTTON_P_H
#define QEMBEDABLEBUTTON_P_H

#include <QToolButton>

class QEmbedableButton : public QToolButton
{
    Q_OBJECT

public:
    explicit QEmbedableButton(QWidget *parent = 0);

    bool isEmbeded() const;
    void setEmbeded(bool embed);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    bool embeded;
};

#endif // QEMBEDABLEBUTTON_P_H
