#ifndef QBUTTONGROUPBOX_H
#define QBUTTONGROUPBOX_H

#include <QGroupBox>
#include <QVariant>

#include <QtWidgetsExtraLibExport.h>

class QAbstractButton;

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QButtonGroupBox : public QGroupBox
{
    Q_OBJECT
    friend class QButtonGroupBoxPrivate;
    class QButtonGroupBoxPrivate *d;

    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(QButtonGroupBox::Type type READ type WRITE setType)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(bool exclusive READ exclusive WRITE setExclusive)
    Q_PROPERTY(int checkedIndex READ checkedIndex)
    Q_PROPERTY(int checkedId READ checkedId)
    Q_PROPERTY(bool isEmpty READ isEmpty)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QStringList items READ items WRITE setItems)

public:
    enum Type {
        CheckBox,
        RadioBox
    };
    Q_ENUM(Type)

    using Button = QMap<int, QVariant>;
    using Buttons = QVector<Button>;

    explicit QButtonGroupBox(QWidget *parent = nullptr);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    QButtonGroupBox::Type type() const;
    void setType(QButtonGroupBox::Type type);

    QSize iconSize() const;
    void setIconSize(const QSize &iconSize);

    bool exclusive() const;
    void setExclusive(bool exclusive);

    void insertButton(int index, const Button &button);
    void addButton(const Button &button);
    void removeButton(int index);

    QVariant buttonData(int index, int role) const;
    void setButtonData(int index, int role, const QVariant &data);

    void clear();
    int count() const;
    bool isEmpty() const;

    int checkedIndex() const;
    int checkedId() const;

    QStringList items() const;
    void setItems(const QStringList &items);

    template <typename T>
    T buttonData(int index, int role) const {
        buttonData(index, role).value<T>();
    }

    template <typename T>
    void setButtonData(int index, int role, const T &data) {
        setButtonData(index, role, QVariant::fromValue(data));
    }

Q_SIGNALS:
    void buttonClicked(int index, int id);
    void buttonPressed(int index, int id);
    void buttonReleased(int index, int id);
    void buttonToggled(int index, int id, bool checked);

protected:
    virtual QAbstractButton *createButton() const;
};

#endif // QBUTTONGROUPBOX_H
