#pragma once

#include <QList>
#include <QObject>
#include <QStringList>

class Generator {
    Q_GADGET

public:
    static QString Tab;

    enum class ParameterType {
        Variable,
        Reference,
        Pointer
    };
    Q_ENUM(ParameterType)

    enum class InheritingType {
        Widget,
        Object
    };
    Q_ENUM(InheritingType)

    struct Entry {
        typedef QList<Generator::Entry> List;

        QString t; // type
        QString n; // name
        Generator::ParameterType pt; // parameter type
        QString dv; // default value;
        bool s; // signal
        bool p; // property

        QString propertyName() const;
        QString getterName() const;
        QString setterName() const;
        QString signalName() const;
        QString typeReturn() const;
        QString typeValue() const;

        QString property() const;
        QString signal() const;
        QString headerGetter() const;
        QString headerSetter() const;
        QStringList sourceGetter(const QString &className, const QString &tab) const;
        QStringList sourceSetter(const QString &className, const QString &tab) const;
    };

public:
    Generator();

    Generator::Entry::List entries() const;
    void setEntries(const Generator::Entry::List &entries);

    QString nameSpace() const;
    void setNameSpace(const QString &nameSpace);

    QString className() const;
    void setClassName(const QString &className);

    QString inheriting() const;
    void setInheriting(const QString &inheriting);

    Generator::InheritingType inheritingType() const;
    void setInheritingType(Generator::InheritingType inheritingType);

    QString pluginGroup() const;
    QString normalizedPluginGroup() const;
    void setPluginGroup(const QString &pluginGroup);

    QString pluginIconFilePath() const;
    void setPluginIconFilePath(const QString &pluginIconFilePath);

    QString pluginToolTip() const;
    void setPluginToolTip(const QString &pluginToolTip);

    QString classHeader() const;
    QString classSource() const;
    QString pluginHeader() const;
    QString pluginSource() const;
    QString projectFileSource() const;

    static QString titleCased(const QString &string);
    static QString nonTitleCased(const QString &string);

private:
    Generator::Entry::List m_entries;
    QString m_nameSpace;
    QString m_className;
    QString m_inheriting;
    Generator::InheritingType m_inheritingType;
    QString m_pluginGroup;
    QString m_pluginIconFilePath;
    QString m_pluginToolTip;

    QString privateObjectName() const;
    QString inheritingTypeClassName() const;
};
