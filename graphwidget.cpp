#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>



GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-6000, -6000, 12000, 12000);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.4), qreal(0.4));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::shuffle()
{
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::addItem(QGraphicsItem *graphicsItem)
{
    scene()->addItem(graphicsItem);

}

void GraphWidget::removeItem(QGraphicsItem *graphicsItem){
    scene()->removeItem(graphicsItem);
}



void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    for (Node *node : std::as_const(nodes))
        node->calculateForces();

    bool itemsMoved = false;
    for (Node *node : std::as_const(nodes)) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., event->angleDelta().y() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QRectF sceneRect = this->sceneRect();
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::white);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

/**
 * @brief GraphWidget::createFromTable genere tous les noeuds et les liasons qu'il faut pour pouvoir avoir un graph qui correspond au données
 * @param data regroupe toutes les données qu'il nous faut pour pouvoir faire la cr&ation des noeuds
 */
void GraphWidget::createFromTable(QList<QMap<QString, int>> &datas){
    //pour chaque list on creer les noeuds et on les relie avec les ceux d'avant

    //création des noeuds

    int decallageDroite = -100;
    foreach (auto var, datas) {
        int decallageBas = -100;
        int nodeSize = 20; //valeur initial
        QList<Node*> precedentList;
        for(auto string:var.keys())
        {
            nodeSize = var.value(string);
            Node *node = new Node(this, nodeSize, string, QColor(Qt::blue),QColor(Qt::blue));
            addItem(node);
            precedentList.append(node);
            node->setPos(decallageDroite,decallageBas);
            decallageBas+=node->getNodeSize()*2;
        }
        save.append(precedentList);
        decallageDroite+=20;

        decallageDroite+=nodeSize*50*2;
    }


    //création des edges

    for (int i = 1; i < save.size(); ++i) {
        foreach (auto node, save[i]) { //noeud courant
            foreach (auto preNode, save[i-1]) { // noeud precedent
                if(node->names.contains(preNode->names)){
                    Edge *edge = new Edge(preNode, node, QColor(Qt::black), std::max(preNode->getNbIter(), node->getNbIter()));
                    addItem(edge);
                    saveEdge.append(edge);
                }
            }
        }
    }

}
