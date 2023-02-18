#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDialog>
#include "ui_tabwidget.h"

/**
 * @brief La classe tabwidget est utilisé pour mettre en œuvre le stockage des données,
 * et les fonctions associées à ces données
 */
class TabWidget : public QWidget, private Ui::TabWidget
{

     Q_OBJECT
public:
    /**
     * @brief Le constructeur du tableaur
     * @param parent
     */
    TabWidget(QWidget *parent = nullptr);
    ~TabWidget();

    /**
     * @brief Effectue la lecture de differents types de fichiers
     * @return si oui ou non la lecture a pu etre faite
     */
    bool read_file();

    /**
     * @brief Affiche les données dans le tableur
     */
    void show_file();

    /**
     * @brief Permet de faire la sauvegarde de fichier
     */
    void write_file();

    /**
     * @brief write_csv_file
     * @param Root du fichier et son nom
     * @param row
     * @param col
     * @param minRand
     * @param maxRand
     */
    void write_csv_file(QString name, int row, int col, int minRand, int maxRand);

    /**
     * @brief write_xlsx_file
     * @param Root du fichier et son nom
     * @param row
     * @param col
     * @param minRand
     * @param maxRand
     */
    void write_xlsx_file(QString name, int row, int col, int minRand, int maxRand);

    void printOnUi();

    /**
     * @brief saveData
     */
    void saveData();

    /**
     * @brief Récupere les données qui sont dans le tableur
     * @return Une liste de string dans la quelle est stocké toute la ligne du graph
     */
    QStringList getDataFromUi();

    /**
     * @brief Pour une colonne donné, récupere la colone
     * @param La colonne que l'on veut récupérer
     * @return une map qui contient les futures noeuds et le nombre de fois qu'ils apparaissent dans la colonne
     */
    QMap<QString, int> getNode(QString &columns);

    /**
     * @brief getColonne
     * @return
     */
    QString getColonne();

    /**
     * @brief Enregistre le tableur pour les mettres dans le graphe
     */
    void registerData();

    /**
     * @brief Récupere les données qui sont dans datas
     * @return Les données
     */
    QStringList getData();
private:
    /**
     * @brief data est un QStringList qui sauvegarde les données. Il se compose d'un certain nombre de QStringList,
     * chaque QStringList stockant les données de chaque ligne
     */
    QStringList data;
};

#endif // TABWIDGET_H
