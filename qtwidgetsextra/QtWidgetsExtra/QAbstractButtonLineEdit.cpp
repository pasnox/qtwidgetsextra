#include "QAbstractButtonLineEdit.h"

#include <QMenu>

class QAbstractButtonLineEditPrivate : public QObject {
    Q_OBJECT

public:
    explicit QAbstractButtonLineEditPrivate(QAbstractButtonLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP) {
        Q_ASSERT(widget);

        connect(widgetP, &QLineEdit::returnPressed, this,
                [widgetP]() { Q_EMIT widgetP->returnPressed(widgetP->text()); });
        connect(widgetP, &QLineEdit::editingFinished, this,
                [widgetP]() { Q_EMIT widgetP->editingFinished(widgetP->text()); });
    }

public:
    QAbstractButtonLineEdit *widget;
};

QAbstractButtonLineEdit::QAbstractButtonLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , d(new QAbstractButtonLineEditPrivate(this)) {
}

QAbstractButtonLineEdit::QAbstractButtonLineEdit(QAction *action, ActionPosition position, QWidget *parent)
    : QLineEdit(parent)
    , d(new QAbstractButtonLineEditPrivate(this)) {
    addAction(action, position);
}

QAbstractButtonLineEdit::QAbstractButtonLineEdit(QMenu *menu, ActionPosition position, QWidget *parent)
    : QLineEdit(parent)
    , d(new QAbstractButtonLineEditPrivate(this)) {
    addAction(menu->menuAction(), position);
}

#include "QAbstractButtonLineEdit.moc"
