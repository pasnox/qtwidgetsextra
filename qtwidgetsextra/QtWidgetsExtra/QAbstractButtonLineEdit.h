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
    explicit QAbstractButtonLineEdit(QAction *action, QLineEdit::ActionPosition position, QWidget *parent = 0);
    explicit QAbstractButtonLineEdit(QMenu *menu, QLineEdit::ActionPosition position, QWidget *parent = 0);

Q_SIGNALS:
    void returnPressed(const QString &text);
    void editingFinished(const QString &text);
};

#endif // QABSTRACTBUTTONLINEEDIT_H
