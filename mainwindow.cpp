#include "mainwindow.h"
#include "edge.h"
#include "graphwidget.h"
#include "node.h"
#include "tabcreate.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QUndoStack>
#include <tabwidget.h>
#include <QDebug>
#include <QSvgGenerator>
#include <QLabel>
#include <QMessageBox>
#include <QColorDialog>
#include <QTimer>
#include <QDesktopServices>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), tab(new TabWidget()),gw(new GraphWidget())
{
    switcher = false;


    ui->setupUi(this);

    ui->Render_window->addWidget(tab);

/* Le temps est mise à jour et affichée toutes les secondes.
*/
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        QDateTime currentTime = QDateTime::currentDateTime();
        ui->label_time->setText(currentTime.toString("yyyy-MM-dd hh:mm:ss"));
    });
    timer->start(1000);

    connect(ui->actionOuvrir, &QAction::triggered, tab, &TabWidget::read_file);
    connect(ui->actionQuitter,&QAction::triggered, this, &QMainWindow::close);
    connect(ui->actionNouveau, &QAction::triggered, this,  &::MainWindow::write_file);

    connect(ui->actionEnregistrer, &QAction::triggered, tab, &TabWidget::saveData);
    connect(ui->actionExporter,&QAction::triggered, this, &MainWindow::export_img);
    connect(ui->actionAbout_us, &QAction::triggered, this, &MainWindow::show_about_us);
    connect (ui->realoadButton, SIGNAL(clicked()), this, SLOT(reload()));
    connect(ui->actionQuitter,&QAction::triggered,this,&QMainWindow::close);
    connect(ui->actionDocumentation, &QAction::triggered, this,[=](){
        QUrl url = QUrl::fromLocalFile("../projetIHM/html/index.html");
        QDesktopServices::openUrl(url);
    });


    switchMode(true);
}
MainWindow::~MainWindow()
{
}

void MainWindow::switchMode(bool isStartMode){
    if(isStartMode){
        tab->hide();
        ui->pushButton_switch->hide();
        ui->pushButton_Color->hide();
        ui->pushButton_Fusion->hide();
        ui->menubar->hide();
        ui->label_time->hide();
        ui->label_arrets->hide();
        ui->label_column->hide();
        ui->label_noeuds->hide();
        ui->label_ligne->hide();
        ui->dockWidget->hide();
        ui->dockWidget_2->hide();
    }
    else {
        tab->show();
        ui->pushButton_Start_Menue_Nouvea->hide();
        ui->pushButton_Start_Menue_ouvrir->hide();
        ui->pushButton_Start_Menue_quitter->hide();
        ui->menubar->show();
        ui->pushButton_switch->show();
        ui->pushButton_Color->show();
        ui->pushButton_Fusion->show();
        ui->Render_window->removeItem(ui->verticalSpacer_2);
        ui->pushButton_Color->hide();
        ui->pushButton_Fusion->hide();
        ui->label_time->show();
        ui->label_arrets->show();
        ui->label_column->show();
        ui->label_noeuds->show();
        ui->label_ligne->show();
        ui->dockWidget->show();
        ui->dockWidget_2->show();
    }
}

void MainWindow::on_pushButton_Start_Menue_Nouvea_clicked()
{
    write_file();
}

void MainWindow::on_pushButton_Start_Menue_quitter_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_Start_Menue_ouvrir_clicked()
{
    ui->Render_window->addWidget(tab);
    if(tab->read_file()){    //une fois que le fichier est ouvert on fait ce qu'il faut pour avoir tous les boutons de dispo
        switchMode(false);
        ui->label_ligne->setText("nbLignes: "+ QString::number(tab->getData().count()));
        ui->label_column->setText("nbColumn: "+ QString::number(tab->getData()[0].split(" ").size()));
        createGraph();
        ui->label_arrets->setText("nbArêtes: "+ QString::number(gw->saveEdge.size()));
        int nbNode = 0;
            foreach (auto var, gw->save) {
                nbNode += var.size();
            }
        ui->label_noeuds->setText("nbNoeuds: "+ QString::number(nbNode));
    }
}
void MainWindow::createGraph(){
    gw = new GraphWidget;
    QString colonnes = tab->getColonne();

    QList<QMap<QString, int>> allNodes = *new QList<QMap<QString, int>>();
    QString nodeName;

    int var = 0;
    //prend la premiere colonne puis ajoute les suivantes
    while(var < colonnes.split(" ").size()){

        if(var == 0)
            nodeName = colonnes.split(" ")[var];
        else
            nodeName.append(",").append(colonnes.split(" ")[var]);
        QMap nodes = tab->getNode(nodeName);

        allNodes.append(nodes);
        var+=1;

    }

    gw->createFromTable(allNodes);

}

void MainWindow::on_actionEnregistrer_triggered()
{
    tab->registerData();
}

void MainWindow::on_pushButton_switch_clicked()
{    
    switcher = !switcher;
    if(switcher)
    {
        ui->Render_window->addWidget(tab);
        ui->Render_window->removeWidget(gw);
        gw->hide();
        tab->show();
        ui->pushButton_Color->hide();
        ui->pushButton_Fusion->hide();
    }
    else
    {
        ui->Render_window->addWidget(gw);
        ui->Render_window->removeWidget(tab);
        tab->hide();
        gw->show();
        ui->pushButton_Color->show();
        ui->pushButton_Fusion->show();
    }

}

void MainWindow::export_img(){
    //centralWidget()->setLayout(ui->TEST);
    //setCentralWidget(centralWidget());
    QPixmap pixmap(centralWidget()->size());
    centralWidget()->render(&pixmap);
    QStringList filters;
    filters <<"PNG (*.png)"<<"BMP (*.bmp)"<<"SVG (*.svg)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"),"../projetIHM/exportImages",filters.join(";;"));
    if(!fileName.isEmpty()){
        if(fileName.endsWith(".png")){
            pixmap.save(fileName,"PNG");
        }else if(fileName.endsWith(".bmp")){
            pixmap.save(fileName,"BMP");
        }else if(fileName.endsWith(".svg")){
            QSvgGenerator generator;
            generator.setFileName(fileName);
            generator.setSize(pixmap.size());
            generator.setViewBox(QRect(QPoint(0,0),pixmap.size()));
            generator.setTitle("SVG Generator");
            generator.setDescription("Example");
            QPainter painter;
            painter.begin(&generator);
            painter.drawPixmap(0,0,pixmap);
            painter.end();
        }
    }
}

void MainWindow::show_about_us(){
    QMessageBox::information(this,tr("information"),tr("Ce logiciel est développé par le Groupe 4.\n"
                                                       "Par REMY, JINHUA, THEO, ETIENNE ET ACHRAF.\n"
                                                       "Contact: ILOVEIHM@etu.univ-amu.fr"));
}

void MainWindow::on_pushButton_Color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, ui->pushButton_Color);
    foreach (QList<Node*> var, gw->save) {
        foreach (Node* node, var) {
            if(node->isSelected){
                node->setColor(color);
                node->isSelected = false;
            }
        }
    }

    foreach (Edge *var, gw->saveEdge) {
        if(var->isSelected){
            var->setColor(color);
            var->isSelected = false;
        }
    }
}

void MainWindow::on_pushButton_Fusion_clicked()
{
    QString name = "";
    QList<Node*> selectedNodes;
    QList<Node*> linkedNodes;
    QList<Edge*> removedEdges;

    for (auto &nodeList : gw->save) {
        for (Node* node : nodeList) {
            if (node->isSelected) {
                selectedNodes.append(node);
                name.append(node->names).append("/");
            }
        }
    }

    if (selectedNodes.size() > 1) {
        int posX = 0;
        int posY = 0;
        int size = 0;

        for (Edge* edge : gw->saveEdge) {
            if (selectedNodes.contains(edge->destNode())) {
                linkedNodes.append(edge->sourceNode());
                removedEdges.append(edge);
            }
            else if (selectedNodes.contains(edge->sourceNode())) {
                linkedNodes.append(edge->destNode());
                removedEdges.append(edge);
            }
        }

        for (auto nodeList : gw->save) {
            for (int i = 0; i < nodeList.size(); i++) {
                Node* node = nodeList.at(i);
                if (selectedNodes.contains(node)) {
                    posX += node->getnewPos().x();
                    posY += node->getnewPos().y();
                    size += node->getNbIter();
                    gw->removeItem(node);
                    nodeList.remove(i--);
                }
            }
        }

        name.remove(name.length() - 1, 1);
        Node* newNode = new Node(gw, size, name, QColor(Qt::blue), QColor(Qt::blue));
        newNode->setPos(posX / selectedNodes.size(), posY / selectedNodes.size());
        gw->addItem(newNode);
        gw->save.last().append(newNode);

        for (Node* node : linkedNodes) {
            if (!selectedNodes.contains(node)) {
                Edge* edge = new Edge(newNode, node, QColor(Qt::black), std::max(newNode->getNbIter(), node->getNbIter()));
                gw->saveEdge.append(edge);
                gw->addItem(edge);
            }
        }

        for (Edge* edge : removedEdges) {
            gw->removeItem(edge);
            gw->saveEdge.removeOne(edge);
        }

        for (auto &nodeList : gw->save) {
            for (Node* node : nodeList) {
                node->isSelected = false;
            }
        }
    }
    else {
        QMessageBox::information(this, tr("Information"), tr("Vous n'avez sélectionné aucun ou un seul noeud pour la fusion."));
    }
}

TabCreate *tabcreate;
void MainWindow::write_file()
{
    tabcreate = new TabCreate;
    tabcreate->show();
}

void MainWindow::reload()
{

    tab->getDataFromUi();
    gw->deleteLater();
    createGraph();
    on_pushButton_switch_clicked();
    on_pushButton_switch_clicked();

}



