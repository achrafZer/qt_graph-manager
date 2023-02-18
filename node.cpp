#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QToolTip>

Node::Node(GraphWidget *graphWidget,int nodeSize,QString  names, QColor color1, QColor color2)
    : graph(graphWidget)
{
    this->colorUsed = color1;
    this->colorUser = color2;
    this->nbIter = nodeSize;
    this->nodeSize = nbIter*50;
    this->isSelected = false;
    this->names = names;
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setToolTip(names);
}
void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

void Node::setColor(QColor color){
    this->colorUser = color;
    this->colorUsed = colorUser;
    update();
}


void Node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }

    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        Node *node = qgraphicsitem_cast<Node *>(item);
        if (!node)
            continue;

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();

        double l = 2.0 * (dx * dx + dy * dy);
        double lnode = 2*(node->getNodeSize()/2+getNodeSize()/2)*(node->getNodeSize()/2+getNodeSize()/2)+2*(node->getNodeSize()/4+getNodeSize()/4)*(node->getNodeSize()/4+getNodeSize()/4);

        if (l > 0 && l< (lnode)) {
            xvel += (dx * 150.0) / l;
            yvel += (dy * 150.0) / l;
        }
    }

    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}

bool Node::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF Node::boundingRect() const
{
    //qreal adjust = 2;
    return QRectF(-nodeSize/2, -nodeSize/2, nodeSize, nodeSize);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-nodeSize/2, -nodeSize/2, nodeSize, nodeSize);
    return path;
}

QPointF Node::getnewPos(){
    return newPos;
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, colorUsed.lighter(120));
        gradient.setColorAt(0, colorUser.lighter(120));
    } else {
        gradient.setColorAt(0, colorUsed);
        gradient.setColorAt(1, colorUsed);
    }
    painter->setBrush(gradient);


    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-nodeSize/2, -nodeSize/2, nodeSize, nodeSize);

    painter->setPen(QPen(Qt::white, 0));
    QFont font = painter->font() ;
    double sub = 2+names.size()/2;
    font.setPointSize((nodeSize/sub));
    painter->setFont(font);
    painter->drawText(QRectF(-nodeSize/2,-nodeSize/2,nodeSize,nodeSize),Qt::AlignCenter,names);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        for (Edge *edge : std::as_const(edgeList))
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(event->button()==Qt::RightButton)
    {

        QPoint pos = QCursor::pos();
        QToolTip::showText(pos, names);
    }else QGraphicsItem::mousePressEvent(event);

}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(event->button()==Qt::RightButton)
    {
        isSelected = !isSelected;
        if(isSelected)
            this->colorUsed = Qt::cyan;
        else
            this->colorUsed = this->colorUser;

    }else QGraphicsItem::mouseReleaseEvent(event);
}

int Node::getNodeSize() const
{
    return nodeSize;
}

int Node::getNbIter(){
    return nbIter;
}

