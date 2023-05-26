#include "Generator.h"

QString Generator::Tab = QString(4, QLatin1Char(' '));

// Entry

QString Generator::Entry::propertyName() const
{
    return Generator::nonTitleCased(n);
}

QString Generator::Entry::getterName() const
{
    return QStringLiteral(
        "%1%2"
    )
        .arg(t == QStringLiteral("bool") ? QStringLiteral("is") : QString())
        .arg(t == QStringLiteral("bool") ? Generator::titleCased(propertyName()) : propertyName())
    ;
}

QString Generator::Entry::setterName() const
{
    return QStringLiteral(
        "set%1"
    )
        .arg(Generator::titleCased(propertyName()))
    ;
}

QString Generator::Entry::signalName() const
{
    return propertyName()
        .append(QStringLiteral("Changed"))
    ;
}

QString Generator::Entry::typeReturn() const
{
    switch (pt) {
        case Generator::Variable:
        case Generator::Reference:
            return t;
        case Generator::Pointer:
            return QStringLiteral("%1 *").arg(t);
    }

    Q_ASSERT(false);
    return QString();
}

QString Generator::Entry::typeValue() const
{
    switch (pt) {
        case Generator::Variable:
            return QStringLiteral("%1 %2").arg(t).arg(propertyName());
        case Generator::Reference:
            return QStringLiteral("const %1 &%2").arg(t).arg(propertyName());
        case Generator::Pointer:
            return QStringLiteral("%1 *%2").arg(t).arg(propertyName());
    }

    Q_ASSERT(false);
    return QString();
}

QString Generator::Entry::property() const
{
    return QStringLiteral(
        "Q_PROPERTY(%1 %2 READ %3 WRITE %4%5)"
    )
        .arg(typeReturn())
        .arg(propertyName())
        .arg(getterName())
        .arg(setterName())
        .arg(s ? QStringLiteral(" NOTIFY %1").arg(signalName()) : QString())
    ;
}

QString Generator::Entry::signal() const
{
    return QStringLiteral("void %1(%2);").arg(signalName()).arg(typeValue());
}

QString Generator::Entry::headerGetter() const
{
    return QStringLiteral(
        "%1%2%3() const;"
    )
        .arg(typeReturn())
        .arg(pt == Generator::Pointer ? QString() : QStringLiteral(" "))
        .arg(getterName())
    ;
}

QString Generator::Entry::headerSetter() const
{
    return QStringLiteral(
        "void %1(%2%3);"
    )
        .arg(setterName())
        .arg(typeValue())
        .arg(dv.isEmpty() ? QString() : QStringLiteral(" = %1").arg(dv))
    ;
}

QStringList Generator::Entry::sourceGetter(const QString &className, const QString &tab) const
{
    return QStringLiteral(
        "%1%2%3::%4() const\n"
        "{\n"
        "\treturn d->%5;\n"
        "}"
    )
        .arg(typeReturn())
        .arg(pt == Generator::Pointer ? QString() : QStringLiteral(" "))
        .arg(className)
        .arg(getterName())
        .arg(propertyName())
        .replace(QStringLiteral("\t"), tab)
        .split(QStringLiteral("\n"))
    ;
}

QStringList Generator::Entry::sourceSetter(const QString &className, const QString &tab) const
{
    return QStringLiteral(
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
        .arg(s ? QStringLiteral("\n\temit %1(%2);\n").arg(signalName()).arg(propertyName()) : QString())
        .replace(QStringLiteral("\t"), tab)
        .split(QStringLiteral("\n"))
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
    return m_pluginGroup.toLower().simplified().replace(QStringLiteral(" "), QString());
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

    output << QStringLiteral("#ifndef %1_H").arg(m_className.toUpper());
    output << QStringLiteral("#define %1_H").arg(m_className.toUpper());

    output << QString();

    if (!m_nameSpace.isEmpty()) {
        output << QStringLiteral("namespace %1 {").arg(m_nameSpace);
        output << QString();
    }

    if (!m_inheriting.isEmpty()) {
        output << QStringLiteral("#include <%1>").arg(m_inheriting);
        output << QString();
    }

    foreach (const Generator::Entry &entry, m_entries) {
        switch (entry.pt) {
            case Generator::Variable:
                break;
            case Generator::Reference:
            case Generator::Pointer:
                output << QStringLiteral("class %1;").arg(entry.t);
                hasReferencesOrPointers = true;
                break;
        }
    }

    if (hasReferencesOrPointers) {
        output << QString();
    }

    output << QStringLiteral("class %1%2").arg(m_className).arg(m_inheriting.isEmpty() ? QString() : QStringLiteral(" : public %1").arg(m_inheriting));
    output << QStringLiteral("{");
    output << QStringLiteral("Q_OBJECT").prepend(Generator::Tab);
    output << QStringLiteral("class %1Private *d;").arg(m_className).prepend(Generator::Tab);

    output << QString();

    foreach (const Generator::Entry &entry, m_entries) {
        if (entry.p) {
            output << entry.property().prepend(Generator::Tab);
            hasProperties = true;
        }
    }

    if (hasProperties) {
        output << QString();
    }

    output << QStringLiteral("public:");
    output << QStringLiteral("explicit %1(%2 *parent = 0);").arg(m_className).arg(inheritingTypeClassName()).prepend(Generator::Tab);

    foreach (const Generator::Entry &entry, m_entries) {
        output << QString();
        output << entry.headerGetter().prepend(Generator::Tab);
        output << entry.headerSetter().prepend(Generator::Tab);

        if (entry.s) {
            hasSignals = true;
        }
    }

    if (hasSignals) {
        output << QString();

        output << QStringLiteral("Q_SIGNALS:");

        foreach (const Generator::Entry &entry, m_entries) {
            if (!entry.s) {
                continue;
            }

            output << entry.signal().prepend(Generator::Tab);
        }
    }

    output << QStringLiteral("};");

    output << QString();

    if (!m_nameSpace.isEmpty()) {
        output << QStringLiteral("} // %1").arg(m_nameSpace);
        output << QString();
    }

    output << QStringLiteral("#endif // %1_H").arg(m_className.toUpper());

    output << QString();

    return output.join(QStringLiteral("\n"));
}

QString Generator::classSource() const
{
    QStringList output;
    bool hasReferencesOrPointers = false;
    bool hasDefaultValues = false;

    output << QStringLiteral("#include \"%1.h\"").arg(m_className);

    output << QString();

    if (!m_nameSpace.isEmpty()) {
        output << QStringLiteral("namespace %1 {").arg(m_nameSpace);
        output << QString();
    }

    foreach (const Generator::Entry &entry, m_entries) {
        switch (entry.pt) {
            case Generator::Variable:
                break;
            case Generator::Reference:
            case Generator::Pointer:
                output << QStringLiteral("#include <%1>").arg(entry.t);
                hasReferencesOrPointers = true;
                break;
        }

        if (!entry.dv.isEmpty()) {
            hasDefaultValues = true;
        }
    }

    if (hasReferencesOrPointers) {
        output << QString();
    }

    output << QStringLiteral("class %1Private : public QObject").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("Q_OBJECT").prepend(Generator::Tab);

    output << QString();

    output << QStringLiteral("public:");
    output << QStringLiteral("%1Private(%1 *%2P)").arg(m_className).arg(privateObjectName()).prepend(Generator::Tab);
    output << QStringLiteral(": QObject(%1P)").arg(privateObjectName()).prepend(Generator::Tab).prepend(Generator::Tab);
    output << QStringLiteral(", %1(%1P)%2").arg(privateObjectName()).arg(hasDefaultValues ? QString() : QStringLiteral(" {")).prepend(Generator::Tab).prepend(Generator::Tab);

    if (hasDefaultValues) {
        foreach (const Generator::Entry &entry, m_entries) {
            if (!entry.dv.isEmpty()) {
                output << QStringLiteral(", %1(%2)").arg(entry.propertyName()).arg(entry.dv).prepend(Generator::Tab).prepend(Generator::Tab);
            }
        }

        output.last().append(QStringLiteral(" {"));
    }

    output << QStringLiteral("Q_ASSERT(%1);").arg(privateObjectName()).prepend(Generator::Tab).prepend(Generator::Tab);
    output << QStringLiteral("}").prepend(Generator::Tab);

    output << QString();

    output << QStringLiteral("public:");
    output << QStringLiteral("%1 *%2;").arg(m_className).arg(privateObjectName()).prepend(Generator::Tab);

    foreach (const Generator::Entry &entry, m_entries) {
        output << QStringLiteral("%1%2%3;").arg(entry.typeReturn()).arg(entry.pt == Generator::Pointer ? QString() : QStringLiteral(" ")).arg(entry.propertyName()).prepend(Generator::Tab);
    }

    output << QStringLiteral("};");

    output << QString();

    output << QStringLiteral("%1::%1(%2 *parent)").arg(m_className).arg(inheritingTypeClassName());
    output << QStringLiteral(": %1(parent)").arg(m_inheriting).prepend(Generator::Tab);
    output << QStringLiteral(", d(new %1Private(this))").arg(m_className).prepend(Generator::Tab);
    output << QStringLiteral("{");
    output << QStringLiteral("}");

    foreach (const Generator::Entry &entry, m_entries) {
        output << QString();
        output << entry.sourceGetter(m_className, Generator::Tab);
        output << QString();
        output << entry.sourceSetter(m_className, Generator::Tab);
    }

    output << QString();

    output << QStringLiteral("#include \"%1.moc\"").arg(m_className);

    output << QString();

    if (!m_nameSpace.isEmpty()) {
        output << QStringLiteral("} // %1").arg(m_nameSpace);
        output << QString();
    }

    return output.join(QStringLiteral("\n"));
}

QString Generator::pluginHeader() const
{
    QStringList output;

    output << QStringLiteral("#ifndef %1PLUGIN_H").arg(m_className.toUpper());
    output << QStringLiteral("#define %1PLUGIN_H").arg(m_className.toUpper());

    output << QString();

    output << QStringLiteral("#include <QDesignerCustomWidgetInterface>");

    output << QString();

    output << QStringLiteral("class %1Plugin : public QObject, public QDesignerCustomWidgetInterface").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("Q_OBJECT").prepend(Generator::Tab);
    output << QStringLiteral("Q_INTERFACES(QDesignerCustomWidgetInterface)").prepend(Generator::Tab);

    output << QString();

    output << QStringLiteral("public:");
    output << QStringLiteral("%1Plugin(QObject *parent = 0);").arg(m_className).prepend(Generator::Tab);

    output << QString();

    output << QStringLiteral("bool isContainer() const;").prepend(Generator::Tab);
    output << QStringLiteral("bool isInitialized() const;").prepend(Generator::Tab);
    output << QStringLiteral("QIcon icon() const;").prepend(Generator::Tab);
    output << QStringLiteral("QString domXml() const;").prepend(Generator::Tab);
    output << QStringLiteral("QString group() const;").prepend(Generator::Tab);
    output << QStringLiteral("QString includeFile() const;").prepend(Generator::Tab);
    output << QStringLiteral("QString name() const;").prepend(Generator::Tab);
    output << QStringLiteral("QString toolTip() const;").prepend(Generator::Tab);
    output << QStringLiteral("QString whatsThis() const;").prepend(Generator::Tab);
    output << QStringLiteral("QWidget *createWidget(QWidget *parent);").prepend(Generator::Tab);
    output << QStringLiteral("void initialize(QDesignerFormEditorInterface *core);").prepend(Generator::Tab);

    output << QString();

    output << QStringLiteral("private:");
    output << QStringLiteral("bool m_initialized;").prepend(Generator::Tab);
    output << QStringLiteral("};");

    output << QString();

    output << QStringLiteral("#endif // %1PLUGIN_H").arg(m_className.toUpper());

    output << QString();

    return output.join(QStringLiteral("\n"));
}

QString Generator::pluginSource() const
{
    QStringList output;

    output << QStringLiteral("#include \"%1Plugin.h\"").arg(m_className);
    output << QStringLiteral("#include \"%1.h\"").arg(m_className);

    output << QString();

    output << QStringLiteral("#include <QtPlugin>");

    output << QString();

    output << QStringLiteral("%1Plugin::%1Plugin(QObject *parent)").arg(m_className);
    output << QStringLiteral(": QObject(parent)").prepend(Generator::Tab);
    output << QStringLiteral("{");
    output << QStringLiteral("m_initialized = false;").prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("void %1Plugin::initialize(QDesignerFormEditorInterface * /* core */)").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("if (m_initialized) {").prepend(Generator::Tab);
    output << QStringLiteral("return;").prepend(Generator::Tab).prepend(Generator::Tab);
    output << QStringLiteral("}").prepend(Generator::Tab);

    output << QString();

    output << QStringLiteral("// Add extension registrations, etc. here").prepend(Generator::Tab);

    output << QString();

    output << QStringLiteral("m_initialized = true;").prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("bool %1Plugin::isInitialized() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return m_initialized;").prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("QWidget *%1Plugin::createWidget(QWidget *parent)").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return new %1%2(parent);").arg(m_nameSpace.isEmpty() ? QString() : QStringLiteral("%1::").arg(m_nameSpace)).arg(m_className).prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("QString %1Plugin::name() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return QStringLiteral(\"%1\");").arg(m_className).prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("QString %1Plugin::group() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return QStringLiteral(\"Qt Widgets Extra / %1\");").arg(m_pluginGroup).prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("QIcon %1Plugin::icon() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return QIcon(QStringLiteral(\"%1\"));").arg(m_pluginIconFilePath).prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("QString %1Plugin::toolTip() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return QStringLiteral(\"%1\");").arg(m_pluginToolTip).prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("QString %1Plugin::whatsThis() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return toolTip();").prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("bool %1Plugin::isContainer() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return false;").prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("QString %1Plugin::domXml() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return QStringLiteral(\"<widget class=\\\"%1\\\" name=\\\"%2\\\">\\n</widget>\\n\");").arg(m_className).arg(Generator::nonTitleCased(m_className.mid(1))).prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    output << QStringLiteral("QString %1Plugin::includeFile() const").arg(m_className);
    output << QStringLiteral("{");
    output << QStringLiteral("return QStringLiteral(\"%1.h\");").arg(m_className).prepend(Generator::Tab);
    output << QStringLiteral("}");

    output << QString();

    return output.join(QStringLiteral("\n"));
}

QString Generator::projectFileSource() const
{
    const QString normalizedGroup = normalizedPluginGroup();
    QStringList output;

    output << QStringLiteral("DEPENDPATH *= %1").arg(normalizedGroup);
    output << QStringLiteral("INCLUDEPATH *= %1").arg(normalizedGroup);

    output << QString();

    output << QStringLiteral("HEADERS *= \\");
    output << QStringLiteral("%1/%2.h").arg(normalizedGroup).arg(m_className).prepend(Generator::Tab);

    output << QString();

    output << QStringLiteral("SOURCES *= \\");
    output << QStringLiteral("%1/%2.cpp").arg(normalizedGroup).arg(m_className).prepend(Generator::Tab);

    output << QString();

    return output.join(QStringLiteral("\n"));
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
            return QStringLiteral("widget");
        case Generator::Object:
            return QStringLiteral("object");
    }

    Q_ASSERT(false);
    return QString();
}

QString Generator::inheritingTypeClassName() const
{
    return m_inheritingType == Generator::Widget ? QStringLiteral("QWidget") : QStringLiteral("QObject");
}
