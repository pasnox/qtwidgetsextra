#pragma once

#include <QListView>
#include <QDir>

#include <QtWidgetsExtraLibExport.h>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QFileSystemListView : public QListView
{
    Q_OBJECT
    class QFileSystemListViewPrivate* d;
    Q_FLAGS(Sections)
    Q_ENUMS(SectionFlag)

    Q_PROPERTY(bool nameFilterDisables READ nameFilterDisables WRITE setNameFilterDisables)
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly)
    Q_PROPERTY(bool resolveSymlinks READ resolveSymlinks WRITE setResolveSymlinks)
    Q_PROPERTY(bool browsable READ browsable WRITE setBrowsable)
    Q_PROPERTY(QDir::Filters filters READ filters WRITE setFilters)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)
    Q_PROPERTY(QFileSystemListView::SectionFlag visibleSection READ visibleSection WRITE setVisibleSection)
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)

public:
    enum Column {
        NameColumn,
        SizeColumn,
        TypeColumn,
        LastModificationColumn
    };

    enum SectionFlag {
        AllSections = 0,
        NameSection = 0x1,
        SizeSection = 0x2,
        TypeSection = 0x4,
        LastModificationSection = 0x8
    };

    Q_DECLARE_FLAGS(Sections, SectionFlag)

    explicit QFileSystemListView(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;

    bool nameFilterDisables() const;
    void setNameFilterDisables(bool nameFilterDisables);

    bool readOnly() const;
    void setReadOnly(bool readOnly);

    bool resolveSymlinks() const;
    void setResolveSymlinks(bool resolveSymlinks);

    bool browsable() const;
    void setBrowsable(bool browsable);

    QDir::Filters filters() const;
    void setFilters(QDir::Filters filters);

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &nameFilters);

    QFileSystemListView::SectionFlag visibleSection() const;
    void setVisibleSection(QFileSystemListView::SectionFlag section);

    QString rootPath() const;
    void setRootPath(const QString &rootPath);

    QStringList selection() const;
    void setSelection(const QStringList &selection);
    void addSelection(QStringList &selection);
    void clearSelection();

Q_SIGNALS:
    void directoryLoaded(const QString &path);
    void fileRenamed(const QString &path, const QString &oldName, const QString &newName);
    void rootPathChanged(const QString &newPath);
};
