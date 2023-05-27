#include "MainWindow.h"
#include "GeneratorDelegate.h"
#include "ui_MainWindow.h"

#include <QAbstractButton>
#include <QDebug>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui_MainWindow) {
    m_ui->setupUi(this);

    m_ui->cbInheritingType->addItem(QStringLiteral("Widget"), QVariant::fromValue(Generator::InheritingType::Widget));
    m_ui->cbInheritingType->addItem(QStringLiteral("Object"), QVariant::fromValue(Generator::InheritingType::Object));

    m_ui->twMembers->setColumnCount(6);

    const auto setHeaderText = [this](GeneratorDelegate::Column column, const QString &text) {
        m_ui->twMembers->headerItem()->setText(static_cast<int>(column), text);
    };
    const auto setHeaderSectionResizeMode = [this](GeneratorDelegate::Column column, QHeaderView::ResizeMode mode) {
        m_ui->twMembers->header()->setSectionResizeMode(static_cast<int>(column), mode);
    };

    setHeaderText(GeneratorDelegate::Column::Type, QStringLiteral("Type"));
    setHeaderText(GeneratorDelegate::Column::Name, QStringLiteral("Name"));
    setHeaderText(GeneratorDelegate::Column::ParameterType, QStringLiteral("ParameterType"));
    setHeaderText(GeneratorDelegate::Column::DefaultValue, QStringLiteral("DefaultValue"));
    setHeaderText(GeneratorDelegate::Column::Signal, QStringLiteral("Signal"));
    setHeaderText(GeneratorDelegate::Column::Property, QStringLiteral("Property"));

    setHeaderSectionResizeMode(GeneratorDelegate::Column::Type, QHeaderView::ResizeToContents);
    setHeaderSectionResizeMode(GeneratorDelegate::Column::Name, QHeaderView::Stretch);
    setHeaderSectionResizeMode(GeneratorDelegate::Column::ParameterType, QHeaderView::ResizeToContents);
    setHeaderSectionResizeMode(GeneratorDelegate::Column::DefaultValue, QHeaderView::ResizeToContents);
    setHeaderSectionResizeMode(GeneratorDelegate::Column::Signal, QHeaderView::ResizeToContents);
    setHeaderSectionResizeMode(GeneratorDelegate::Column::Property, QHeaderView::ResizeToContents);

    m_ui->twMembers->setItemDelegate(new GeneratorDelegate(this));
}

MainWindow::~MainWindow() = default;

void MainWindow::on_tbAdd_clicked() {
    static int i = 0;
    QTreeWidgetItem *item = new QTreeWidgetItem;
    const auto setItemText = [&](GeneratorDelegate::Column column, const QString &text) {
        item->setText(static_cast<int>(column), text);
    };
    const auto setItemCheckState = [&](GeneratorDelegate::Column column, Qt::CheckState state) {
        item->setCheckState(static_cast<int>(column), state);
    };

    setItemText(GeneratorDelegate::Column::Type, QStringLiteral("type%1").arg(i));
    setItemText(GeneratorDelegate::Column::Name, QStringLiteral("name%1").arg(i));
    setItemText(GeneratorDelegate::Column::ParameterType,
                QString::number(static_cast<int>(Generator::ParameterType::Reference)));
    setItemText(GeneratorDelegate::Column::DefaultValue, QString());
    setItemCheckState(GeneratorDelegate::Column::Signal, Qt::Unchecked);
    setItemCheckState(GeneratorDelegate::Column::Property, Qt::Unchecked);
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    m_ui->twMembers->addTopLevelItem(item);
    m_ui->twMembers->setCurrentItem(item);

    i++;
}

void MainWindow::on_tbRemove_clicked() {
    delete m_ui->twMembers->selectedItems().value(0);
}

void MainWindow::on_tbUp_clicked() {
    QTreeWidgetItem *item = m_ui->twMembers->selectedItems().value(0);
    int row = m_ui->twMembers->indexOfTopLevelItem(item);

    if (row > 0) {
        m_ui->twMembers->takeTopLevelItem(row);
        m_ui->twMembers->insertTopLevelItem(row - 1, item);
        m_ui->twMembers->setCurrentItem(item);
    }
}

void MainWindow::on_tbDown_clicked() {
    QTreeWidgetItem *item = m_ui->twMembers->selectedItems().value(0);
    int row = m_ui->twMembers->indexOfTopLevelItem(item);

    if (row < m_ui->twMembers->topLevelItemCount() - 1) {
        m_ui->twMembers->takeTopLevelItem(row);
        m_ui->twMembers->insertTopLevelItem(row + 1, item);
        m_ui->twMembers->setCurrentItem(item);
    }
}

void MainWindow::on_dbbButtons_clicked(QAbstractButton *button) {
    QDialogButtonBox::StandardButton sb = m_ui->dbbButtons->standardButton(button);

    switch (sb) {
    case QDialogButtonBox::Close:
        close();
        break;

    case QDialogButtonBox::Apply:
        apply();
        break;

    case QDialogButtonBox::Save:
        save();
        break;

    default:
        Q_ASSERT(0);
        break;
    }
}

bool MainWindow::saveFile(const QString &content, const QString &filePath) const {
    QDir dir;

    if (!dir.mkpath(QFileInfo(filePath).absolutePath())) {
        qWarning("%s: Can't create directory - %s", Q_FUNC_INFO, qPrintable(filePath));
        return false;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("%s: %s - %s", Q_FUNC_INFO, qPrintable(file.errorString()), qPrintable(filePath));
        return false;
    }

    if (file.write(content.toUtf8()) == -1) {
        qWarning("%s: %s - %s", Q_FUNC_INFO, qPrintable(file.errorString()), qPrintable(filePath));
        return false;
    }

    return true;
}

void MainWindow::apply() {
    Generator::Entry::List entries;

    for (int i = 0; i < m_ui->twMembers->topLevelItemCount(); i++) {
        const QTreeWidgetItem *item = m_ui->twMembers->topLevelItem(i);
        const auto itemText = [item](GeneratorDelegate::Column column) { return item->text(static_cast<int>(column)); };
        const auto itemCheckState = [item](GeneratorDelegate::Column column) {
            return item->checkState(static_cast<int>(column));
        };
        Generator::Entry entry;

        entry.n = itemText(GeneratorDelegate::Column::Name);
        entry.t = itemText(GeneratorDelegate::Column::Type);
        entry.pt = Generator::ParameterType(itemText(GeneratorDelegate::Column::ParameterType).toInt());
        entry.dv = itemText(GeneratorDelegate::Column::DefaultValue);
        entry.s = itemCheckState(GeneratorDelegate::Column::Signal) == Qt::Checked;
        entry.p = itemCheckState(GeneratorDelegate::Column::Property) == Qt::Checked;

        entries << entry;
    }

    m_generator.setEntries(entries);
    m_generator.setNameSpace(m_ui->leNameSpace->text());
    m_generator.setClassName(m_ui->leClassName->text());
    m_generator.setInheriting(m_ui->leInheriting->text());
    m_generator.setInheritingType(Generator::InheritingType(m_ui->cbInheritingType->currentData().toInt()));
    m_generator.setPluginGroup(m_ui->lePluginGroup->text());
    m_generator.setPluginIconFilePath(m_ui->lePluginIconFilePath->text());
    m_generator.setPluginToolTip(m_ui->lePluginToolTip->text());

    m_ui->pteHeader->setPlainText(m_generator.classHeader());
    m_ui->pteSource->setPlainText(m_generator.classSource());
    m_ui->ptePluginHeader->setPlainText(m_generator.pluginHeader());
    m_ui->ptePluginSource->setPlainText(m_generator.pluginSource());
    m_ui->pteProjectFile->setPlainText(m_generator.projectFileSource());
}

void MainWindow::save() {
    const QString projectSourceFilePath =
        QFileDialog::getExistingDirectory(this, tr("Please select project source folder"));

    if (projectSourceFilePath.isEmpty()) {
        return;
    }

    apply();

    const QString projectFile =
        QStringLiteral("%1/%2/%2.pri").arg(projectSourceFilePath).arg(m_generator.normalizedPluginGroup());

    saveFile(m_ui->pteHeader->toPlainText(),
             QStringLiteral("%1/%2/%3.h")
                 .arg(projectSourceFilePath)
                 .arg(m_generator.normalizedPluginGroup())
                 .arg(m_generator.className()));
    saveFile(m_ui->pteSource->toPlainText(),
             QStringLiteral("%1/%2/%3.cpp")
                 .arg(projectSourceFilePath)
                 .arg(m_generator.normalizedPluginGroup())
                 .arg(m_generator.className()));
    saveFile(m_ui->ptePluginHeader->toPlainText(),
             QStringLiteral("%1/%2/%3Plugin.h")
                 .arg(projectSourceFilePath)
                 .arg(m_generator.normalizedPluginGroup())
                 .arg(m_generator.className()));
    saveFile(m_ui->ptePluginSource->toPlainText(),
             QStringLiteral("%1/%2/%3Plugin.cpp")
                 .arg(projectSourceFilePath)
                 .arg(m_generator.normalizedPluginGroup())
                 .arg(m_generator.className()));

    if (!QFile::exists(projectFile)) {
        saveFile(m_ui->pteProjectFile->toPlainText(), projectFile);
    }

    const QStringList text = QStringList()
        << tr("Don't forget to:").prepend(QStringLiteral("<b>")).append(QStringLiteral("</b>"))
        << QStringLiteral("<ul>")
        << tr("Update the source project file to add the generated project include file if needed")
               .prepend(QStringLiteral("<li>"))
        << tr("Update the source project file HEADERS / SOURCES to add the new plugin").prepend(QStringLiteral("<li>"))
        << tr("Update the source class registering the plugins to add the new plugin").prepend(QStringLiteral("<li>"))
        << QStringLiteral("<ul>");

    QMessageBox::information(this, windowTitle(), text.join(QStringLiteral("\n")));
}
