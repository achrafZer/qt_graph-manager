#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;
class Edge;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:

    /**
     * @brief Constructeur de la classe GraphWidget
     *
     * @param parent Pointeur vers le widget parent
     */
    GraphWidget(QWidget *parent = nullptr);

    /**
     * @brief Méthode appelée lorsqu'un élément du graphe est déplacé
     * La méthode effectue un contrôle sur la variable timerId. Si timerId est nul,
     * cela signifie que le timer n'a pas été démarré et la méthode démarre un nouveau timer
     * en appelant la méthode startTimer avec un intervalle de temps de 1000 / 25 millisecondes.

     */
    void itemMoved();

    /**
     * @brief La liste qui contient l'ensemble des noeuds du graphe
     */
    QList<QList<Node*>> save;

    /**
     * @brief La liste que contient l'ensemble des edges du graphe
     */
    QList<Edge*> saveEdge;


public slots:

    /**
     * @brief Déplace les éléments de manière aléatoire
     */
    void shuffle();

    /**
     * @brief Zoome dans la vue
     */
    void zoomIn();

    /**
     * @brief Zoome hors de la vue
     */
    void zoomOut();

    /**
     * @brief Ajoute un élément graphique à la scène
     * @param graphicsItem Elément graphique à ajouter
     */
    void addItem(QGraphicsItem *graphicsItem);


    /**
     * @brief Supprime un élément graphique à la scène
     * @param graphicsItem
     */
    void removeItem(QGraphicsItem *graphicsItem);


    /**
     * @brief Creer le graphe depuis le tableur
     * @param Les données que l'on récupére du graphe
     */
    void createFromTable(QList<QMap<QString, int>> &datas);

protected:

    /**
    * @brief Gère les événements de la souris
    *
    * @param event Pointeur vers l'événement souris
    */
    void keyPressEvent(QKeyEvent *event) override;

    /**
    * @brief Gère les événements du timer
    *
    * @param event Pointeur vers l'événement timer
    */
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)

    /**
    * @brief Gère les événements de la roulette de la souris
    *
    * @param event Pointeur vers l'événement de la roulette de la souris
    */
    void wheelEvent(QWheelEvent *event) override;
#endif

    /**
     * @brief Dessine le fond de la scène
     *
     * @param painter Pointeur vers le peintre utilisé pour dessiner
     * @param rect Rectangle définissant la zone à dessiner
     */
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    /**
     * @brief Zoom sur la scène
     *
     * @param scale Facteur de zoom
     */
    void scaleView(qreal scaleFactor);

private:

    /**
     * @brief Identifiant du timer utilisé pour animer les déplacements
     */
    int timerId = 0;

    Node *centerNode;
};

#endif // GRAPHWIDGET_H
