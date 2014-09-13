#include "Generator.h"

QString Generator::Tab = QString(4, ' ');

// Entry

QString Generator::Entry::propertyName() const
{
    return Generator::nonTitleCased(n);
}

QString Generator::Entry::getterName() const
{
    return QString(
        "%1%2"
    )
        .arg(t == "bool" ? "is" : "")
        .arg(t == "bool" ? Generator::titleCased(propertyName()) : propertyName())
    ;
}

QString Generator::Entry::setterName() const
{
    return QString(
        "set%1"
    )
        .arg(Generator::titleCased(propertyName()))
    ;
}

QString Generator::Entry::signalName() const
{
    return propertyName()
        .append("Changed")
            ;
}

QString Generator::Entry::typeReturn() const
{
    switch (pt) {
        case Generator::Variable:
        case Generator::Reference:
            return t;
        case Generator::Pointer:
            return QString("%1 *").arg(t);
    }

    Q_ASSERT(0);
    return QString::null;
}

QString Generator::Entry::typeValue() const
{
    switch (pt) {
        case Generator::Variable:
            return QString("%1 %2").arg(t).arg(propertyName());
        case Generator::Reference:
            return QString("const %1 &%2").arg(t).arg(propertyName());
        case Generator::Pointer:
            return QString("%1 *%2").arg(t).arg(propertyName());
    }

    Q_ASSERT(0);
    return QString::null;
}

QString Generator::Entry::property() const
{
    return QString(
        "Q_PROPERTY(%1 %2 READ %3 WRITE %4%5)"
    )
        .arg(typeReturn())
        .arg(propertyName())
        .arg(getterName())
        .arg(setterName())
        .arg(s ? QString(" NOTIFY %1").arg(signalName()) : "")
    ;
}

QString Generator::Entry::signal() const
{
    return QString("void %1(%2);").arg(signalName()).arg(typeValue());
}

QString Generator::Entry::headerGetter() const
{
    return QString(
        "%1%2%3() const;"
    )
        .arg(typeReturn())
        .arg(pt == Generator::Pointer ? "" : " ")
        .arg(getterName())
    ;
}

QString Generator::Entry::headerSetter() const
{
    return QString(
        "void %1(%2%3);"
    )
        .arg(setterName())
        .arg(typeValue())
        .arg(dv.isEmpty() ? QString::null : QString(" = %1").arg(dv))
    ;
}

QStringList Generator::Entry::sourceGetter(const QString &className, const QString &tab) const
{
    return QString(
        "%1%2%3::%4() const\n"
        "{\n"
        "\treturn d->%5;\n"
        "}"
    )
        .arg(typeReturn())
        .arg(pt == Generator::Pointer ? "" : " ")
        .arg(className)
        .arg(getterName())
        .arg(propertyName())
        .replace("\t", tab)
        .split("\n")
    ;
}

QStringList Generator::Entry::sourceSetter(const QString &className, const QString &tab) const
{
    return QString(
        "void %1::%2(%3)\n"
        "{\n"
        "\tif (d->%4 == %4) {\n"
        "\t\treturn;\n"
        "\t}\n"
        "\n"
        "\td->%4 = %4;\n"
        "%5"
        "}"
    )
        .arg(className)
        .arg(setterName())
        .arg(typeValue())
        .arg(propertyName())
        .arg(s ? QString("\n\temit %1(%2);\n").arg(signalName()).arg(propertyName()) : QString::null)
        .replace("\t", tab)
        .split("\n")
    ;
}

// Generator

Generator::Generator()
{
}

Generator::Entry::List Generator::entries() const
{
    return m_entries;
}

void Generator::setEntries(const Generator::Entry::List &entries)
{
    m_entries = entries;
}

QString Generator::nameSpace() const
{
    return m_nameSpace;
}

void Generator::setNameSpace(const QString &nameSpace)
{
    m_nameSpace = nameSpace;
}

QString Generator::className() const
{
    return m_className;
}

void Generator::setClassName(const QString &className)
{
    m_className = className;
}

QString Generator::inheriting() const
{
    return m_inheriting;
}

void Generator::setInheriting(const QString &inheriting)
{
    m_inheriting = inheriting;
}

Generator::InheritingType Generator::inheritingType() const
{
    return m_inheritingType;
}

void Generator::setInheritingType(Generator::InheritingType inheritingType)
{
    m_inheritingType = inheritingType;
}

QString Generator::pluginGroup() const
{
    return m_pluginGroup;
}

QString Generator::normalizedPluginGroup() const
{
    return m_pluginGroup.toLower().simplified().replace(" ", "");
}

void Generator::setPluginGroup(const QString &pluginGroup)
{
    m_pluginGroup = pluginGroup;
}

QString Generator::pluginIconFilePath() const
{
    return m_pluginIconFilePath;
}

void Generator::setPluginIconFilePath(const QString &pluginIconFilePath)
{
    m_pluginIconFilePath = pluginIconFilePath;
}

QString Generator::pluginToolTip() const
{
    return m_pluginToolTip;
}

void Generator::setPluginToolTip(const QString &pluginToolTip)
{
    m_pluginToolTip = pluginToolTip;
}

QString Generator::classHeader() const
{
    QStringList output;
    bool hasProperties = false;
    bool hasSignals = false;
    bool hasReferencesOrPointers = false;

    output << QString("#ifndef %1_H").arg(m_className.toUpper());
    output << QString("#define %1_H").arg(m_className.toUpper());

    output << QString::null;

    if (!m_nameSpace.isEmpty()) {
        output << QString("namespace %1 {").arg(m_nameSpace);
        output << QString::null;
    }

    if (!m_inheriting.isEmpty()) {
        output << QString("#include <%1>").arg(m_inheriting);
        output << QString::null;
    }

    foreach (const Generator::Entry &entry, m_entries) {
        switch (entry.pt) {
            case Generator::Variable:
                break;
            case Generator::Reference:
            case Generator::Pointer:
                output << QString("class %1;").arg(entry.t);
                hasReferencesOrPointers = true;
                break;
        }
    }

    if (hasReferencesOrPointers) {
        output << QString::null;
    }

    output << QString("class %1%2").arg(m_className).arg(m_inheriting.isEmpty() ? QString::null : QString(" : public %1").arg(m_inheriting));
    output << QString("{");
    output << QString("Q_OBJECT").prepend(Generator::Tab);
    output << QString("class %1Private *d;").arg(m_className).prepend(Generator::Tab);

    output << QString::null;

    foreach (const Generator::Entry &entry, m_entries) {
        if (entry.p) {
            output << entry.property().prepend(Generator::Tab);
            hasProperties = true;
        }
    }

    if (hasProperties) {
        output << QString::null;
    }

    output << QString("public:");
    output << QString("explicit %1(%2 *parent = 0);").arg(m_className).arg(inheritingTypeClassName()).prepend(Generator::Tab);

    foreach (const Generator::Entry &entry, m_entries) {
        output << QString::null;
        output << entry.headerGetter().prepend(Generator::Tab);
        output << entry.headerSetter().prepend(Generator::Tab);

        if (entry.s) {
            hasSignals = true;
        }
    }

    if (hasSignals) {
        output << QString::null;

        output << QString("signals:");

        foreach (const Generator::Entry &entry, m_entries) {
            if (!entry.s) {
                continue;
            }

            output << entry.signal().prepend(Generator::Tab);
        }
    }

    output << QString("};");

    output << QString::null;

    if (!m_nameSpace.isEmpty()) {
        output << QString("} // %1").arg(m_nameSpace);
        output << QString::null;
    }

    output << QString("#endif // %1_H").arg(m_className.toUpper());

    output << QString::null;

    return output.join("\n");
}

QString Generator::classSource() const
{
    QStringList output;
    bool hasReferencesOrPointers = false;
    bool hasDefaultValues = false;

    output << QString("#include \"%1.h\"").arg(m_className);

    output << QString::null;

    if (!m_nameSpace.isEmpty()) {
        output << QString("namespace %1 {").arg(m_nameSpace);
        output << QString::null;
    }

    foreach (const Generator::Entry &entry, m_entries) {
        switch (entry.pt) {
            case Generator::Variable:
                break;
            case Generator::Reference:
            case Generator::Pointer:
                output << QString("#include <%1>").arg(entry.t);
                hasReferencesOrPointers = true;
                break;
        }

        if (!entry.dv.isEmpty()) {
            hasDefaultValues = true;
        }
    }

    if (hasReferencesOrPointers) {
        output << QString::null;
    }

    output << QString("class %1Private : public QObject").arg(m_className);
    output << QString("{");
    output << QString("Q_OBJECT").prepend(Generator::Tab);

    output << QString::null;

    output << QString("public:");
    output << QString("%1Private(%1 *%2P)").arg(m_className).arg(privateObjectName()).prepend(Generator::Tab);
    output << QString(": QObject(%1P)").arg(privateObjectName()).prepend(Generator::Tab).prepend(Generator::Tab);
    output << QString(", %1(%1P)%2").arg(privateObjectName()).arg(hasDefaultValues ? QString::null : QString(" {")).prepend(Generator::Tab).prepend(Generator::Tab);

    if (hasDefaultValues) {
        foreach (const Generator::Entry &entry, m_entries) {
            if (!entry.dv.isEmpty()) {
                output << QString(", %1(%2)").arg(entry.propertyName()).arg(entry.dv).prepend(Generator::Tab).prepend(Generator::Tab);
            }
        }

        output.last().append(QString(" {"));
    }

    output << QString("Q_ASSERT(%1);").arg(privateObjectName()).prepend(Generator::Tab).prepend(Generator::Tab);
    output << QString("}").prepend(Generator::Tab);

    output << QString::null;

    output << QString("public:");
    output << QString("%1 *%2;").arg(m_className).arg(privateObjectName()).prepend(Generator::Tab);

    foreach (const Generator::Entry &entry, m_entries) {
        output << QString("%1%2%3;").arg(entry.typeReturn()).arg(entry.pt == Generator::Pointer ? "" : " ").arg(entry.propertyName()).prepend(Generator::Tab);
    }

    output << QString("};");

    output << QString::null;

    output << QString("%1::%1(%2 *parent)").arg(m_className).arg(inheritingTypeClassName());
    output << QString(": %1(parent)").arg(m_inheriting).prepend(Generator::Tab);
    output << QString(", d(new %1Private(this))").arg(m_className).prepend(Generator::Tab);
    output << QString("{");
    output << QString("}");

    foreach (const Generator::Entry &entry, m_entries) {
        output << QString::null;
        output << entry.sourceGetter(m_className, Generator::Tab);
        output << QString::null;
        output << entry.sourceSetter(m_className, Generator::Tab);
    }

    output << QString::null;

    output << QString("#include \"%1.moc\"").arg(m_className);

    output << QString::null;

    if (!m_nameSpace.isEmpty()) {
        output << QString("} // %1").arg(m_nameSpace);
        output << QString::null;
    }

    return output.join("\n");
}

QString Generator::pluginHeader() const
{
    QStringList output;

    output << QString("#ifndef %1PLUGIN_H").arg(m_className.toUpper());
    output << QString("#define %1PLUGIN_H").arg(m_className.toUpper());

    output << QString::null;

    output << QString("#include <QDesignerCustomWidgetInterface>");

    output << QString::null;

    output << QString("class %1Plugin : public QObject, public QDesignerCustomWidgetInterface").arg(m_className);
    output << QString("{");
    output << QString("Q_OBJECT").prepend(Generator::Tab);
    output << QString("Q_INTERFACES(QDesignerCustomWidgetInterface)").prepend(Generator::Tab);

    output << QString::null;

    output << QString("public:");
    output << QString("%1Plugin(QObject *parent = 0);").arg(m_className).prepend(Generator::Tab);

    output << QString::null;

    output << QString("bool isContainer() const;").prepend(Generator::Tab);
    output << QString("bool isInitialized() const;").prepend(Generator::Tab);
    output << QString("QIcon icon() const;").prepend(Generator::Tab);
    output << QString("QString domXml() const;").prepend(Generator::Tab);
    output << QString("QString group() const;").prepend(Generator::Tab);
    output << QString("QString includeFile() const;").prepend(Generator::Tab);
    output << QString("QString name() const;").prepend(Generator::Tab);
    output << QString("QString toolTip() const;").prepend(Generator::Tab);
    output << QString("QString whatsThis() const;").prepend(Generator::Tab);
    output << QString("QWidget *createWidget(QWidget *parent);").prepend(Generator::Tab);
    output << QString("void initialize(QDesignerFormEditorInterface *core);").prepend(Generator::Tab);

    output << QString::null;

    output << QString("private:");
    output << QString("bool m_initialized;").prepend(Generator::Tab);
    output << QString("};");

    output << QString::null;

    output << QString("#endif // %1PLUGIN_H").arg(m_className.toUpper());

    output << QString::null;

    return output.join("\n");
}

QString Generator::pluginSource() const
{
    QStringList output;

    output << QString("#include \"%1Plugin.h\"").arg(m_className);
    output << QString("#include \"%1.h\"").arg(m_className);

    output << QString::null;

    output << QString("#include <QtPlugin>");

    output << QString::null;

    output << QString("%1Plugin::%1Plugin(QObject *parent)").arg(m_className);
    output << QString(": QObject(parent)").prepend(Generator::Tab);
    output << QString("{");
    output << QString("m_initialized = false;").prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("void %1Plugin::initialize(QDesignerFormEditorInterface * /* core */)").arg(m_className);
    output << QString("{");
    output << QString("if (m_initialized) {").prepend(Generator::Tab);
    output << QString("return;").prepend(Generator::Tab).prepend(Generator::Tab);
    output << QString("}").prepend(Generator::Tab);

    output << QString::null;

    output << QString("// Add extension registrations, etc. here").prepend(Generator::Tab);

    output << QString::null;

    output << QString("m_initialized = true;").prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("bool %1Plugin::isInitialized() const").arg(m_className);
    output << QString("{");
    output << QString("return m_initialized;").prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("QWidget *%1Plugin::createWidget(QWidget *parent)").arg(m_className);
    output << QString("{");
    output << QString("return new %1%2(parent);").arg(m_nameSpace.isEmpty() ? QString::null : QString("%1::").arg(m_nameSpace)).arg(m_className).prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("QString %1Plugin::name() const").arg(m_className);
    output << QString("{");
    output << QString("return QLatin1String(\"%1\");").arg(m_className).prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("QString %1Plugin::group() const").arg(m_className);
    output << QString("{");
    output << QString("return QLatin1String(\"Qt Widgets Extra / %1\");").arg(m_pluginGroup).prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("QIcon %1Plugin::icon() const").arg(m_className);
    output << QString("{");
    output << QString("return QIcon(QLatin1String(\"%1\"));").arg(m_pluginIconFilePath).prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("QString %1Plugin::toolTip() const").arg(m_className);
    output << QString("{");
    output << QString("return QLatin1String(\"%1\");").arg(m_pluginToolTip).prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("QString %1Plugin::whatsThis() const").arg(m_className);
    output << QString("{");
    output << QString("return toolTip();").prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("bool %1Plugin::isContainer() const").arg(m_className);
    output << QString("{");
    output << QString("return false;").prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("QString %1Plugin::domXml() const").arg(m_className);
    output << QString("{");
    output << QString("return QLatin1String(\"<widget class=\\\"%1\\\" name=\\\"%2\\\">\\n</widget>\\n\");").arg(m_className).arg(Generator::nonTitleCased(m_className.mid(1))).prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    output << QString("QString %1Plugin::includeFile() const").arg(m_className);
    output << QString("{");
    output << QString("return QLatin1String(\"%1.h\");").arg(m_className).prepend(Generator::Tab);
    output << QString("}");

    output << QString::null;

    return output.join("\n");
}

QString Generator::projectFileSource() const
{
    const QString normalizedGroup = normalizedPluginGroup();
    QStringList output;

    output << QString("DEPENDPATH *= %1").arg(normalizedGroup);
    output << QString("INCLUDEPATH *= %1").arg(normalizedGroup);

    output << QString::null;

    output << QString("HEADERS *= \\");
    output << QString("%1/%2.h").arg(normalizedGroup).arg(m_className).prepend(Generator::Tab);

    output << QString::null;

    output << QString("SOURCES *= \\");
    output << QString("%1/%2.cpp").arg(normalizedGroup).arg(m_className).prepend(Generator::Tab);

    output << QString::null;

    return output.join("\n");
}

QString Generator::titleCased(const QString &string)
{
    QString s = string;

    if (!s.isEmpty()) {
        s[0] = s[0].toTitleCase();
    }

    return s;
}

QString Generator::nonTitleCased(const QString &string)
{
    QString s = string;

    if (!s.isEmpty()) {
        s[0] = s[0].toLower();
    }

    return s;
}

QString Generator::privateObjectName() const
{
    switch (m_inheritingType) {
        case Generator::Widget:
            return QString("widget");
        case Generator::Object:
            return QString("object");
    }

    Q_ASSERT(0);
    return QString::null;
}

QString Generator::inheritingTypeClassName() const
{
    return m_inheritingType == Generator::Widget ? QString("QWidget") : QString("QObject");
}
