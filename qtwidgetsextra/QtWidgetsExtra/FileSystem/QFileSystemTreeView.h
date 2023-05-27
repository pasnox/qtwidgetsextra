#pragma once

#include <QTreeView>
#include <QDir>

#include <QtWidgetsExtraLibExport.h>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QFileSystemTreeView : public QTreeView
{
    Q_OBJECT
    class QFileSystemTreeViewPrivate* d;

    Q_PROPERTY(bool nameFilterDisables READ nameFilterDisables WRITE setNameFilterDisables)
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly)
    Q_PROPERTY(bool resolveSymlinks READ resolveSymlinks WRITE setResolveSymlinks)
    Q_PROPERTY(QDir::Filters filters READ filters WRITE setFilters)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)
    Q_PROPERTY(QFileSystemTreeView::Sections visibleSections READ visibleSections WRITE setVisibleSections)
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)

public:
    enum Column {
        NameColumn,
        SizeColumn,
        TypeColumn,
        LastModificationColumn
    };
    Q_ENUM(Column)

    enum SectionFlag {
        AllSections = 0,
        NameSection = 0x1,
        SizeSection = 0x2,
        TypeSection = 0x4,
        LastModificationSection = 0x8
    };
    Q_ENUM(SectionFlag)
    Q_DECLARE_FLAGS(Sections, SectionFlag)
    Q_FLAG(Sections)

    explicit QFileSystemTreeView(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model) override;

    bool nameFilterDisables() const;
    void setNameFilterDisables(bool nameFilterDisables);

    bool readOnly() const;
    void setReadOnly(bool readOnly);

    bool resolveSymlinks() const;
    void setResolveSymlinks(bool resolveSymlinks);

    QDir::Filters filters() const;
    void setFilters(QDir::Filters filters);

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &nameFilters);

    QFileSystemTreeView::Sections visibleSections() const;
    void setVisibleSections(QFileSystemTreeView::Sections sections);

    QString rootPath() const;
    void setRootPath(const QString &rootPath);

    using QTreeView::setSelection;

    QStringList selection() const;
    void setSelection(const QStringList &selection);
    void addSelection(QStringList &selection);
    void clearSelection();

Q_SIGNALS:
    void directoryLoaded(const QString &path);
    void fileRenamed(const QString &path, const QString &oldName, const QString &newName);
    void rootPathChanged(const QString &newPath);
};
