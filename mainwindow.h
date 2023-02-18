#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <graphwidget.h>
#include <tabwidget.h>
class Node;
/**
 * @brief La fenetre principale
 */
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Le constructeur de MainWindow
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openTab();

private :
    /**
     * @brief L'ui pour l'affichage
     */
    Ui::MainWindow *ui;

    /**
     * @brief Le tableur
     */
    TabWidget* tab;

    /**
     * @brief Le graphe
     */
    GraphWidget* gw;

    /**
     * @brief Permet de passer de la vue graph à la vue tableur
     */
    bool switcher;

    /**
     * @brief passe de la vue de démarrage a la vue principal
     * @param isStartMode
     */
    void switchMode(bool isStartMode);

    /**
     * @brief Fait la création du graph
     */
    void createGraph();

private slots:
    //void on_pushButton_clicked();
    /**
    * @brief Pour exporter les graphes avec les informations au format SVG, BMP PNG.
    */
    void export_img();

    /**
     * @brief Afficher les infos de notre groupe.
    */
    void show_about_us();

    /**
     * @brief Lance l'action pour faire un nouveau document
     */
    void on_pushButton_Start_Menue_Nouvea_clicked();

    /**
     * @brief Lance l'action pour quitter l'application
     */
    void on_pushButton_Start_Menue_quitter_clicked();


    /**
     * @brief Lance l'action pour ouvrir un nouveau document
     */
    void on_pushButton_Start_Menue_ouvrir_clicked();


    void on_actionEnregistrer_triggered();

    /**
     * @brief Lance l'action pour changer de vue entre le graphe et le tableur
     */
    void on_pushButton_switch_clicked();

    /**
     * @brief Lance l'action pour faire la coloration des éléments selectionnés
     */
    void on_pushButton_Color_clicked();

    /**
     * @brief Lance l'action pour faire la fusion de noeud
     */
    void on_pushButton_Fusion_clicked();

    /**
     * @brief Enregistre le fichier
     */
    void write_file();

    /**
     * @brief Refait le graphe a partir du tableur
     */
    void reload();
};

#endif // MAINWINDOW_H
