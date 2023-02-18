#include "edge.h"
#include "node.h"

#include <QPainter>
#include <QtMath>
#include <QGraphicsSceneMouseEvent>

Edge::Edge(Node *sourceNode, Node *destNode,QColor color,int edgeSize)
    : source(sourceNode), dest(destNode), color(color), edgeSize(edgeSize)
{
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
    this->isSelected = false;
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();
    int rayonSource = source->getNodeSize()/2;
    int rayonDest = dest->getNodeSize()/2;

    if (length > qreal(rayonSource  +rayonDest)) {
        QPointF edgeOffsetSource((line.dx() * rayonSource) / length , (line.dy() * rayonSource) / length);
        QPointF edgeOffsetDest((line.dx() * rayonDest) / length , (line.dy() * rayonDest) / length);
        sourcePoint = line.p1() + edgeOffsetSource;
        destPoint = line.p2() - edgeOffsetDest;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}


void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(event->button()==Qt::RightButton)
    {
        isSelected = !isSelected;
        if(isSelected)
            this->color = Qt::cyan;
        else
            this->color = this->colorUser;
    }

}


void Edge::setColor(QColor color){
    this->colorUser = color;
    update();
}


void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(color,edgeSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

}

