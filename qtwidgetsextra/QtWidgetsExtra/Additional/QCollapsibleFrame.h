#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QFrame>
#include <QIcon>

class QIcon;

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QCollapsibleFrame : public QFrame {
    Q_OBJECT
    friend class QCollapsibleFramePrivate;
    class QCollapsibleFramePrivate *d;

    Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded NOTIFY expanded)
    Q_PROPERTY(QIcon collapsedIcon READ collapsedIcon WRITE setCollapsedIcon NOTIFY collapsedIconChanged)
    Q_PROPERTY(QIcon expandedIcon READ expandedIcon WRITE setExpandedIcon NOTIFY expandedIconChanged)
    Q_PROPERTY(int indentation READ indentation WRITE setIndentation NOTIFY indentationChanged)
    Q_PROPERTY(QWidget *title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QWidget *widget READ widget WRITE setWidget NOTIFY widgetChanged)

    // Qt Designer does not support pointer based properties, so we work around this by adding those extra properties.
    // Those will lookup objects by name in the collapsible frame and set the native property in the next event loop.
    Q_PROPERTY(QString titleObjectName READ titleObjectName WRITE setTitleObjectName NOTIFY titleChanged)
    Q_PROPERTY(QString widgetObjectName READ widgetObjectName WRITE setWidgetObjectName NOTIFY widgetChanged)

public:
    enum RestoreSizeBehavior {
        NoRestoreSizeBehavior,
        RestoreWindowSizeBehavior
    };
    Q_ENUM(RestoreSizeBehavior)

    explicit QCollapsibleFrame(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;

    QCollapsibleFrame::RestoreSizeBehavior restoreSizeBehavior() const;
    void setRestoreSizeBehavior(QCollapsibleFrame::RestoreSizeBehavior behavior);

    QWidget *title() const;
    QWidget *takeTitle();
    void setTitle(QWidget *title);

    QWidget *widget() const;
    QWidget *takeWidget();
    void setWidget(QWidget *widget);

    QString titleObjectName() const;
    void setTitleObjectName(const QString &name);

    QString widgetObjectName() const;
    void setWidgetObjectName(const QString &name);

    QString collapseToolTip() const;
    QIcon collapsedIcon() const;
    QIcon expandedIcon() const;

    bool isCollapsed() const;
    bool isExpanded() const;
    int indentation() const;

public Q_SLOTS:
    void setCollapseToolTip(const QString &toolTip);
    void setCollapsedIcon(const QIcon &icon);
    void setExpandedIcon(const QIcon &icon);
    void setIcon(const QIcon &icon);
    void setCollapsed(bool collapsed);
    void setExpanded(bool expanded);
    void setIndentation(int indentation);

Q_SIGNALS:
    void titleChanged();
    void widgetChanged();
    void aboutToCollapse();
    void collapsed();
    void aboutToExpand();
    void expanded();
    void collapsedIconChanged();
    void expandedIconChanged();
    void indentationChanged();
};
