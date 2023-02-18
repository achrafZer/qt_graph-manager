#ifndef TABCREATE_H
#define TABCREATE_H

#include <tabwidget.h>
#include <QWidget>

namespace Ui {
class TabCreate;
}

class TabCreate : public QWidget
{
    Q_OBJECT

public:
    explicit TabCreate(QWidget *parent = nullptr,TabWidget *tabWidget = nullptr);
    ~TabCreate();

private:
    /**
     * @brief ui
     */
    Ui::TabCreate *ui;
    /**
     * @brief m_tabWidget
     */
    TabWidget *m_tabWidget;
    /**
     * @brief nombre de ligne choisi par l'utilisateur
     */
    int m_rows = 0;
    /**
     * @brief nombre de colonne choisi par l'utilisateur
     */
    int m_columns = 0;
    /**
     * @brief vrai si l'utilisateur veut des valeurs aléatoire, faux sinon
     */
    bool m_is_random = false;
    /**
     * @brief valeur minimale de la génération aléatoire
     */
    int m_min_rand = 0;
    /**
     * @brief valeur maximale de la génération aléatoire
     */
    int m_max_rand = 0;
    /**
     * @brief vrai si l'utilisateur veut créer un fichier csv, faux sinon
     */
    bool m_is_csv = false;
    /**
     * @brief vrai si l'utilisateur veut créer un fichier xlsx, faux sinon
     */
    bool m_is_xlsx = false;

protected slots:
    /**
     * @brief méthode appelé quand l'utilisateur change le nombre de ligne et qui set m_rows
     * @param rows
     */
    void onSpinRows(int rows);
    /**
     * @brief méthode appelé quand l'utilisateur change le nombre de colonne et qui set m_columns
     * @param columns
     */
    void onSpinColumns(int columns);
    /**
     * @brief méthode appelé quand l'utilisateur choisi la génération aléatoire et qui set m_is_random à vrai
     */
    void onRandomButton();
    /**
     * @brief méthode appelé quand l'utilisateur ne veut pas de génération aléatoire et qui set m_is_random à faux
     */
    void onNoButton();
    /**
     * @brief méthode appelé quand l'utilisateur change le minimum aléatoire et qui set m_min_rand
     * @param random min
     */
    void onMinRandomSpin(int min);
    /**
     * @brief méthode appelé quand l'utilisateur change le maximum aléatoire et qui set m_max_rand
     * @param random max
     */
    void onMaxRandomSpin(int max);
    /**
     * @brief méthode appelé quand l'utilisateur choisi de créer un fichier csv et qui set m_is_csv à vrai ou à faux s'il n'en veut plus
     */
    void onCsvButton();

    /**
     * @brief méthode appelé quand l'utilisateur choisi de créer un fichier xlsx et qui set m_is_xlsx à vrai ou à faux s'il n'en veut plus
     */
    void onXlsxButton();
    /**
     * @brief méthode appelé quand l'utilisateur appui sur ok et créer donc le ou les fichiers en fonction de tout les paramètres
     */
    void onOkButton();
};

#endif // TABCREATE_H
