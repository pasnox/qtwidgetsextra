#pragma once

#include <QFrame>

class QIcon;

class QCollapsibleFrame : public QFrame {
  Q_OBJECT
  friend class QCollapsibleFramePrivate;
  class QCollapsibleFramePrivate *d;

  Q_PROPERTY(QWidget *title READ title WRITE setTitle NOTIFY titleChanged)
  Q_PROPERTY(QWidget *widget READ widget WRITE setWidget NOTIFY widgetChanged)

public:
  enum RestoreSizeBehavior { NoRestoreSizeBehavior, RestoreWindowSizeBehavior };

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
};
