#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QBrush>
#include <QFrame>
#include <QPainter>
#include <QPen>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QShape : public QFrame {
    Q_OBJECT
    class QShapePrivate *d;
    friend class QShapePrivate;

    Q_PROPERTY(QPainter::RenderHints renderHints READ renderHints WRITE setRenderHints)
    Q_PROPERTY(QMargins margins READ margins WRITE setMargins)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
    Q_PROPERTY(QPen pen READ pen WRITE setPen)
    Q_PROPERTY(QShape::Shape shape READ shape WRITE setShape)
    Q_PROPERTY(QPoint radius READ radius WRITE setRadius)

    enum ShapeFlag {
        CircleFlag = 0x1,
        DiamondFlag = 0x2,
        RectangleFlag = 0x4,
        SquareFlag = 0x8,
        TriangleFlag = 0x10,
        //
        SquaredFlag = 0x100,
        RoundedFlag = 0x80,
    };

public:
    enum class Shape {
        Circle = QShape::CircleFlag,
        SquaredCircle = QShape::CircleFlag | QShape::SquaredFlag,
        Diamond = QShape::DiamondFlag,
        SquaredDiamond = QShape::DiamondFlag | QShape::SquaredFlag,
        Rectangle = QShape::RectangleFlag,
        RoundedRectangle = QShape::RectangleFlag | QShape::RoundedFlag,
        Square = QShape::SquaredFlag,
        RoundedSquare = QShape::SquaredFlag | QShape::RoundedFlag,
        Triangle = QShape::TriangleFlag,
        SquaredTriangle = QShape::TriangleFlag | QShape::SquaredFlag,
        User = 0x0
    };
    Q_ENUM(Shape)

    explicit QShape(QWidget *parent = nullptr);
    explicit QShape(QShape::Shape shape, QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    QPainter::RenderHints renderHints() const;
    void setRenderHints(QPainter::RenderHints renderHints);

    QMargins margins() const;
    void setMargins(const QMargins &margins);

    QBrush brush() const;
    void setBrush(const QBrush &brush);

    QPen pen() const;
    void setPen(const QPen &pen);

    QShape::Shape shape() const;
    void setShape(QShape::Shape shape);

    QPoint radius() const;
    void setRadius(const QPoint &radius);

    QPainterPath userPath() const;
    void setUserPath(const QPainterPath &userPath);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};
