#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GeneratorDelegate.h"

#include <QHeaderView>
#include <QAbstractButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cbInheritingType->addItem("Widget", Generator::Widget);
    ui->cbInheritingType->addItem("Object", Generator::Object);
    ui->twMembers->setColumnCount(6);
    ui->twMembers->headerItem()->setText(GeneratorDelegate::ColumnType, QString("Type"));
    ui->twMembers->headerItem()->setText(GeneratorDelegate::ColumnName, QString("Name"));
    ui->twMembers->headerItem()->setText(GeneratorDelegate::ColumnParameterType, QString("ParameterType"));
    ui->twMembers->headerItem()->setText(GeneratorDelegate::ColumnDefaultValue, QString("DefaultValue"));
    ui->twMembers->headerItem()->setText(GeneratorDelegate::ColumnSignal, QString("Signal"));
    ui->twMembers->headerItem()->setText(GeneratorDelegate::ColumnProperty, QString("Property"));
    ui->twMembers->header()->setSectionResizeMode(GeneratorDelegate::ColumnType, QHeaderView::ResizeToContents);
    ui->twMembers->header()->setSectionResizeMode(GeneratorDelegate::ColumnName, QHeaderView::Stretch);
    ui->twMembers->header()->setSectionResizeMode(GeneratorDelegate::ColumnParameterType, QHeaderView::ResizeToContents);
    ui->twMembers->header()->setSectionResizeMode(GeneratorDelegate::ColumnDefaultValue, QHeaderView::ResizeToContents);
    ui->twMembers->header()->setSectionResizeMode(GeneratorDelegate::ColumnSignal, QHeaderView::ResizeToContents);
    ui->twMembers->header()->setSectionResizeMode(GeneratorDelegate::ColumnProperty, QHeaderView::ResizeToContents);
    ui->twMembers->setItemDelegate(new GeneratorDelegate(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tbAdd_clicked()
{
    static int i = 0;
    QTreeWidgetItem* item = new QTreeWidgetItem;

    item->setText(GeneratorDelegate::ColumnType, QString("type%1").arg(i));
    item->setText(GeneratorDelegate::ColumnName, QString("name%1").arg(i));
    item->setText(GeneratorDelegate::ColumnParameterType, QString::number(Generator::Reference));
    item->setText(GeneratorDelegate::ColumnDefaultValue, QString::null);
    item->setCheckState(GeneratorDelegate::ColumnSignal, Qt::Unchecked);
    item->setCheckState(GeneratorDelegate::ColumnProperty, Qt::Unchecked);
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    ui->twMembers->addTopLevelItem(item);
    ui->twMembers->setCurrentItem(item);

    i++;
}

void MainWindow::on_tbRemove_clicked()
{
    delete ui->twMembers->selectedItems().value(0);
}

void MainWindow::on_tbUp_clicked()
{
    QTreeWidgetItem* item = ui->twMembers->selectedItems().value(0);
    int row = ui->twMembers->indexOfTopLevelItem(item);

    if (row > 0) {
        ui->twMembers->takeTopLevelItem(row);
        ui->twMembers->insertTopLevelItem(row -1, item);
        ui->twMembers->setCurrentItem(item);
    }
}

void MainWindow::on_tbDown_clicked()
{
    QTreeWidgetItem* item = ui->twMembers->selectedItems().value(0);
    int row = ui->twMembers->indexOfTopLevelItem(item);

    if (row < ui->twMembers->topLevelItemCount() -1) {
        ui->twMembers->takeTopLevelItem(row);
        ui->twMembers->insertTopLevelItem(row +1, item);
        ui->twMembers->setCurrentItem(item);
    }
}

void MainWindow::on_dbbButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton sb = ui->dbbButtons->standardButton(button);

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

bool MainWindow::saveFile(const QString &content, const QString &filePath) const
{
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

void MainWindow::apply()
{
    Generator::Entry::List entries;

    for (int i = 0; i < ui->twMembers->topLevelItemCount(); i++) {
        const QTreeWidgetItem *item = ui->twMembers->topLevelItem(i);
        Generator::Entry entry;

        entry.t = item->text(GeneratorDelegate::ColumnType);
        entry.n = item->text(GeneratorDelegate::ColumnName);
        entry.pt = Generator::ParameterType(item->text(GeneratorDelegate::ColumnParameterType).toInt());
        entry.dv = item->text(GeneratorDelegate::ColumnDefaultValue);
        entry.s = item->checkState(GeneratorDelegate::ColumnSignal) == Qt::Checked;
        entry.p = item->checkState(GeneratorDelegate::ColumnProperty) == Qt::Checked;

        entries << entry;
    }

    m_generator.setEntries(entries);
    m_generator.setNameSpace(ui->leNameSpace->text());
    m_generator.setClassName(ui->leClassName->text());
    m_generator.setInheriting(ui->leInheriting->text());
    m_generator.setInheritingType(Generator::InheritingType(ui->cbInheritingType->currentData().toInt()));
    m_generator.setPluginGroup(ui->lePluginGroup->text());
    m_generator.setPluginIconFilePath(ui->lePluginIconFilePath->text());
    m_generator.setPluginToolTip(ui->lePluginToolTip->text());

    ui->pteHeader->setPlainText(m_generator.classHeader());
    ui->pteSource->setPlainText(m_generator.classSource());
    ui->ptePluginHeader->setPlainText(m_generator.pluginHeader());
    ui->ptePluginSource->setPlainText(m_generator.pluginSource());
    ui->pteProjectFile->setPlainText(m_generator.projectFileSource());
}

void MainWindow::save()
{
    const QString projectSourceFilePath = QFileDialog::getExistingDirectory(this, tr("Please select project source folder"));

    if (projectSourceFilePath.isEmpty()) {
        return;
    }

    apply();

    const QString projectFile = QString("%1/%2/%2.pri").arg(projectSourceFilePath).arg(m_generator.normalizedPluginGroup());

    saveFile(ui->pteHeader->toPlainText(), QString("%1/%2/%3.h").arg(projectSourceFilePath).arg(m_generator.normalizedPluginGroup()).arg(m_generator.className()));
    saveFile(ui->pteSource->toPlainText(), QString("%1/%2/%3.cpp").arg(projectSourceFilePath).arg(m_generator.normalizedPluginGroup()).arg(m_generator.className()));
    saveFile(ui->ptePluginHeader->toPlainText(), QString("%1/%2/%3Plugin.h").arg(projectSourceFilePath).arg(m_generator.normalizedPluginGroup()).arg(m_generator.className()));
    saveFile(ui->ptePluginSource->toPlainText(), QString("%1/%2/%3Plugin.cpp").arg(projectSourceFilePath).arg(m_generator.normalizedPluginGroup()).arg(m_generator.className()));

    if (!QFile::exists(projectFile)) {
        saveFile(ui->pteProjectFile->toPlainText(), projectFile);
    }

    const QStringList text = QStringList()
        << tr( "Don't forget to:" ).prepend(QString("<b>")).append(QString("</b>"))
        << QString("<ul>")
        << tr( "Update the source project file to add the generated project include file if needed" ).prepend(QString("<li>"))
        << tr( "Update the source project file HEADERS / SOURCES to add the new plugin" ).prepend(QString("<li>"))
        << tr( "Update the source class registering the plugins to add the new plugin" ).prepend(QString("<li>"))
        << QString("<ul>")
    ;

    QMessageBox::information(this, windowTitle(), text.join("\n"));
}
