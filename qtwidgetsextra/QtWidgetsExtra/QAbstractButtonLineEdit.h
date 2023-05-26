#pragma once

#include <QLineEdit>

#include <QtWidgetsExtraLibExport.h>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QAbstractButtonLineEdit : public QLineEdit
{
    Q_OBJECT
    friend class QAbstractButtonLineEditPrivate;
    class QAbstractButtonLineEditPrivate* d;

public:
    explicit QAbstractButtonLineEdit(QWidget *parent = nullptr);
    explicit QAbstractButtonLineEdit(QAction *action, QLineEdit::ActionPosition position, QWidget *parent = nullptr);
    explicit QAbstractButtonLineEdit(QMenu *menu, QLineEdit::ActionPosition position, QWidget *parent = nullptr);

Q_SIGNALS:
    void returnPressed(const QString &text);
    void editingFinished(const QString &text);
};
