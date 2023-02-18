#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

/**
 * @brief La classe Edge représente une arête dans un graphe.
 *
 * Elle est dérivée de QGraphicsItem et est responsable de dessiner une arête entre deux nœuds dans un graphe.
 * Elle stocke les informations sur les nœuds source et destination, la couleur et la taille de l'arête.

 */
class Edge : public QGraphicsItem
{
public:

    /**
     * @brief Constructeur pour la classe Edge.
     * @param sourceNode Le nœud source pour l'arête.
     * @param destNode Le nœud de destination pour l'arête.
     * @param color La couleur de l'arête.
     * @param edgeSize La taille de l'arête.
     */
    Edge(Node *sourceNode, Node *destNode,QColor color,int edgeSize);

    /**
     * @brief Renvoie le nœud source de l'arête.
     * @return Le nœud source.
     */
    Node *sourceNode() const;

    /**
     * @brief Renvoie le nœud de destination de l'arête.
     * @return Le nœud de destination.
     */
    Node *destNode() const;

    /**
     * @brief Ajuste la position des nœuds source et destination sur l'arête.
     * Cette méthode calcule la position des nœuds source et destination sur l'arête en fonction de la position de chaque nœud sur le graphe.
     */
    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    /**
     * @brief Vérifie si le noeud est séléctionné
     */
    bool isSelected;

    /**
     * @brief Simple setter qui modifie la couleur du noeud
     * @param La nouvelle couleur du noeud
     */
    void setColor(QColor color);
protected:

    /**
     * @brief Renvoie la zone englobante pour l'arête.
     * @return La zone qui englobe l'arrête.
     */
    QRectF boundingRect() const override;

    /**
     * @brief  Dessine l'arête.
     *
     * @param painter Le peintre utilisé pour dessiner l'arête.
     * @param option Les options de style pour dessiner l'arête.
     * @param widget Le widget parent pour dessiner l'arête.
     *
     * Cette méthode utilise les informations stockées
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief Est déclenchée quand on clique dessus et applique soit le mouvement si clique gauche soit la sélection si clique droit
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    Node *source, *dest;
    QColor color;
    QColor colorUser;
    int edgeSize;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;


};

#endif // EDGE_H
