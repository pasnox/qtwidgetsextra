#ifndef QCOLORCOMBOBOXPLUGIN_H
#define QCOLORCOMBOBOXPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QColorComboBoxPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QColorComboBoxPlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool m_initialized;
};

#endif // QCOLORCOMBOBOXPLUGIN_H
