#pragma once

#include <QtDesigner>
#include <QtPlugin>

class QtWidgetsExtra : public QObject, public QDesignerCustomWidgetCollectionInterface {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
#endif // QT_VERSION >= 0x050000

public:
    explicit QtWidgetsExtra(QObject *parent = nullptr);

    QList<QDesignerCustomWidgetInterface *> customWidgets() const override;

private:
    QList<QDesignerCustomWidgetInterface *> m_widgets;
};
