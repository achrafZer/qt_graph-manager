#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;

/**
 * @brief Représente un nœud graphique dans un widget graphique et hérite de la classe QGraphicsItem de la bibliothèque graphique Qt.
 */
class Node : public QGraphicsItem
{
public:
    /**
     * @brief Constructeur qui crée un nouvel objet Node avec les informations fournies.
     * @param graphWidget un pointeur vers le widget graphique parent.
     * @param nodeSize la taille du nœud.
     * @param names le nom du nœud.
     * @param color1 la couleur principale du nœud.
     * @param color2 la couleur secondaire du nœud.
     */
    Node(GraphWidget *graphWidget, int nodeSize,QString names,QColor color1, QColor color2);

    /**
     * @brief Ajoute une arête à la liste d'arêtes du nœud.
     * @param edge l'arête à ajouter.
     */
    void addEdge(Edge *edge);

    /**
     * @brief edges
     * @return la liste d'arêtes associées au nœud.
     */
    QList<Edge *> edges() const;

    /**
     * @brief modifie la couleur du node
     * @param Une couleur valide
     */
    void setColor(QColor color);

    enum { Type = UserType + 1 };

    /**
     * @brief type
     * @return le type du nœud.
     */
    int type() const override { return Type; }

    /**
     * @brief Calcule les forces qui agissent sur le nœud.
     */
    void calculateForces();

    /**
     * @brief Avance la position du nœud selon les forces calculées.
     * @return
     */
    bool advancePosition();

    /**
     * @brief boundingRect
     * @return Retourne le rectangle englobant du nœud.
     */
    QRectF boundingRect() const override;

    /**
     * @brief shape
     * @return Retourne la forme du nœud.
     */
    QPainterPath shape() const override;

    /**
     * @brief Dessine le nœud
     * @param painter le peintre utilisé pour dessiner le nœud.
     * @param option les options de style pour dessiner le nœud.
     * @param widget le widget parent du nœud.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief getNodeSize
     * @return la taille du nœud.
     */
    int getNodeSize() const;

    /**
     * @brief Le nom du nœud.
     */
    QString  names;

    /**
     * @brief Savoir si le noeud est selectionné par l'utilisateur
     */
    bool isSelected;

    /**
     * @brief couleur que l'utilisateur à choisi
     */

    QColor colorUser;

    /**
     * @brief getNbIter
     * @return le nombre d'itération qu'il y a eu sur le noeud
     */

    int getNbIter();

    /**
     * @brief getnewPos
     * @return prochaine position du noeud
     */

    QPointF getnewPos();


protected:

    /**
     * @brief Est appelé lorsqu'il y a un changement dans l'objet Node.
     * @param change le type de changement.
     * @param value la valeur associée au changement.
     * @return
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    /**
     * @brief Est appelé lorsqu'un bouton de la souris est pressé sur le nœud.
     * @param event l'événement de souris.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief mouseReleaseEvent Est ppelée lorsqu'un bouton de la souris est relâché
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    /**
     * @brief List de tout les edges du noeud
     */
    QList<Edge *> edgeList;
    /**
     * @brief prochaine position du noeud
     */
    QPointF newPos;
    /**
     * @brief le graph dans lequel est le noeud
     */
    GraphWidget *graph;
    /**
     * @brief taille du noeud
     */
    int nodeSize;
    /**
     * @brief couleur du noeud
     */
    QColor colorUsed;
    /**
     * @brief nombre d'itération qu'il y a eu sur le noeud
     */
    int nbIter;

};

#endif // NODE_H
