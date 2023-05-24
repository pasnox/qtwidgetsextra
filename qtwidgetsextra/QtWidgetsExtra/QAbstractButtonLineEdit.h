#ifndef QABSTRACTBUTTONLINEEDIT_H
#define QABSTRACTBUTTONLINEEDIT_H

#include <QLineEdit>

class QAbstractButtonLineEdit : public QLineEdit
{
    Q_OBJECT
    friend class QAbstractButtonLineEditPrivate;
    class QAbstractButtonLineEditPrivate* d;

public:
    explicit QAbstractButtonLineEdit(QWidget *parent = 0);
    explicit QAbstractButtonLineEdit(QAction *action, QWidget *parent = 0);
    explicit QAbstractButtonLineEdit(QMenu *menu, QWidget *parent = 0);

    QAction *defaultAction() const;
    void setDefaultAction(QAction *action);

    QMenu *menu() const;
    void setMenu(QMenu *menu);

protected:
    QToolButton *button() const;
    virtual QToolButton *createButton();
};

#endif // QABSTRACTBUTTONLINEEDIT_H
