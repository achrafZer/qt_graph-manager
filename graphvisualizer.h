#ifndef GRAPHVISUALIZER_H
#define GRAPHVISUALIZER_H

#include "ui_graphvisualizer.h"
#include <QStandardItemModel>
#include <QDialog>

class GraphVisualizer : public QDialog, private Ui::GraphVisualizer
{
    Q_OBJECT
public:
    GraphVisualizer(QWidget *parent = nullptr);  
    ~GraphVisualizer();
    void read_file();
    void show_file();
    void write_file();
    void write_csv_file();
    void write_xlsx_file();
    void printOnUi();
    QStringList getDataFromUi();
    QMap<QString, int> getNode(QString &columns);
private slots:
    void on_pushButton_clicked();

private:
    QStringList data;

};
#endif // GRAPHVISUALIZER_H
