#include "QShape.h"

#include <QPainterPath>

class QShapePrivate : public QObject {
    Q_OBJECT

public:
    explicit QShapePrivate(QShape *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , renderHints(QPainter::TextAntialiasing)
        , margins(QMargins(3, 3, 3, 3))
        , shape(QShape::Shape::Circle)
        , radius(QPoint(6, 6)) {
        Q_ASSERT(widget);
    }

    void updateShape() {
        const QRect contentsRect =
            widget->contentsRect().adjusted(margins.left(), margins.top(), -margins.right(), -margins.bottom());
        const int min = qMin(contentsRect.width(), contentsRect.height());
        QRect area = QRect(QPoint(), contentsRect.size());
        QPainterPath newPath;

        if (static_cast<int>(shape) & QShape::SquaredFlag) {
            area.setWidth(min);
            area.setHeight(min);
        }

        area.moveCenter(contentsRect.center());

        if (pen.style() != Qt::NoPen) {
            const int adjust = pen.isCosmetic() ? 1 : pen.width();
            area.adjust(0, 0, -adjust, -adjust);
        }

        switch (shape) {
        case QShape::Shape::Circle:
        case QShape::Shape::SquaredCircle: {
            newPath.addEllipse(area);
            break;
        }
        case QShape::Shape::Diamond:
        case QShape::Shape::SquaredDiamond: {
            const QPoint center = area.center();
            newPath.addPolygon(QPolygon(QVector<QPoint>()
                                        << QPoint(center.x(), area.top()) << QPoint(area.right(), center.y())
                                        << QPoint(center.x(), area.bottom()) << QPoint(area.left(), center.y())
                                        << QPoint(center.x(), area.top())));
            break;
        }
        case QShape::Shape::Rectangle: {
            newPath.addRect(area);
            break;
        }
        case QShape::Shape::RoundedRectangle: {
            newPath.addRoundedRect(area, radius.x(), radius.y());
            break;
        }
        case QShape::Shape::Square: {
            newPath.addRect(area);
            break;
        }
        case QShape::Shape::RoundedSquare: {
            newPath.addRoundedRect(area, radius.x(), radius.y());
            break;
        }
        case QShape::Shape::Triangle:
        case QShape::Shape::SquaredTriangle: {
            const QPoint center = area.center();
            newPath.addPolygon(QPolygon(QVector<QPoint>() << QPoint(center.x(), area.top()) << area.bottomRight()
                                                          << area.bottomLeft() << QPoint(center.x(), area.top())));
            break;
        }
        case QShape::Shape::User: {
            newPath = userPath;
            break;
        }
        }

        path = newPath;
        widget->update();
    }

public:
    QShape *widget;
    QPainter::RenderHints renderHints;
    QMargins margins;
    QBrush brush;
    QPen pen;
    QShape::Shape shape;
    QPoint radius;
    QPainterPath path;
    QPainterPath userPath;
};

QShape::QShape(QWidget *parent)
    : QFrame(parent)
    , d(new QShapePrivate(this)) {
}

QShape::QShape(QShape::Shape shape, QWidget *parent)
    : QFrame(parent)
    , d(new QShapePrivate(this)) {
    setShape(shape);
}

QSize QShape::minimumSizeHint() const {
    return d->shape == QShape::Shape::User ? d->userPath.boundingRect().size().toSize() : QSize(30, 30);
}

QSize QShape::sizeHint() const {
    return d->shape == QShape::Shape::User ? d->userPath.boundingRect().size().toSize() : QSize(50, 50);
}

QBrush QShape::brush() const {
    return d->brush;
}

QPainter::RenderHints QShape::renderHints() const {
    return d->renderHints;
}

void QShape::setRenderHints(QPainter::RenderHints renderHints) {
    if (d->renderHints == renderHints) {
        return;
    }

    d->renderHints = renderHints;
    d->updateShape();
}

QMargins QShape::margins() const {
    return d->margins;
}

void QShape::setMargins(const QMargins &margins) {
    if (d->margins == margins) {
        return;
    }

    d->margins = margins;
    d->updateShape();
}

void QShape::setBrush(const QBrush &brush) {
    if (d->brush == brush) {
        return;
    }

    d->brush = brush;
    d->updateShape();
}

QPen QShape::pen() const {
    return d->pen;
}

void QShape::setPen(const QPen &pen) {
    if (d->pen == pen) {
        return;
    }

    d->pen = pen;
    d->updateShape();
}

QShape::Shape QShape::shape() const {
    return d->shape;
}

void QShape::setShape(QShape::Shape shape) {
    if (d->shape == shape) {
        return;
    }

    d->shape = shape;
    d->updateShape();
}

QPoint QShape::radius() const {
    return d->radius;
}

void QShape::setRadius(const QPoint &radius) {
    if (d->radius == radius) {
        return;
    }

    d->radius = radius;
    d->updateShape();
}

QPainterPath QShape::userPath() const {
    return d->userPath;
}

void QShape::setUserPath(const QPainterPath &userPath) {
    if (d->userPath == userPath) {
        return;
    }

    d->userPath = userPath;
    d->updateShape();
}

void QShape::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(d->renderHints);
    painter.setBrush(d->brush);
    painter.setPen(d->pen);
    painter.drawPath(d->path);
}

void QShape::resizeEvent(QResizeEvent *event) {
    QFrame::resizeEvent(event);
    d->updateShape();
}

#include "QShape.moc"
