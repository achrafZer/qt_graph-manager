#include "tabwidget.h"
#include "qpainter.h"
#include "ui_tabwidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTableView>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <qimagewriter.h>
#include "xlsxdocument.h"
#include <tabcreate.h>



TabWidget::TabWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

TabWidget::~TabWidget()
{
}

bool TabWidget::read_file(){

    QMessageBox qMessageBox;
    qMessageBox.setText("Si votre système d'exploitation est linux les fichiers .xlsx ne seront pas utilisables ni lisibles!");
    qMessageBox.exec();
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"../projetIHM/testData",tr("Excel(*.csv *.xlsx *.txt)"));
    QFileInfo fileInfo(fileName);
    QString fileSuffix = fileInfo.suffix();
    QFile file(fileName);
    QTextStream in(&file);
    data.clear();

    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"OPEN FILE FAILED!";
        return false;
    }
    if(fileSuffix == "xlsx"){
        qDebug()<<"xlsx";
        QXlsx::Document xlsx(fileName);
        int nbRow = xlsx.dimension().lastRow();
        int nbCol = xlsx.dimension().lastColumn();

        for(int row = 1;row<=nbRow;++row){
            QStringList rowData;
            for(int col = 1; col<=nbCol;++col){
                QXlsx::Cell *cell=xlsx.cellAt(row,col);
                rowData<<cell->value().toString();
            }
            this->data.append(rowData.join(" "));
        }
        qDebug()<<this->data;


        printOnUi();
        getDataFromUi();

        return true;

    }else if(fileSuffix == "csv"){
        qDebug()<<"csv";
        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList fields = line.split(",");
            this->data.append(fields.join(" "));
        }

        qDebug()<<this->data;

        printOnUi();
        getDataFromUi();
        return true;

    }else{
        qDebug()<<"other types";
        return false;
    }

    file.close();
}



void TabWidget::show_file(){
    QTableView *tableView = new QTableView;
    //tableView->setModel(this->data);
    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tableView);
    window->setLayout(layout);

    window->show();
}

void TabWidget::write_file(){

    QFile file("../projetIHM/csv_fileTest.csv");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream stream(&file);

        for (int i = 0; i < data.size(); i++) {
            QStringList tmp = data[i].split(" ");
            for(int j = 0; j < tmp.size();j ++)
            {
                stream << tmp[j] << '\t';
            }
            stream << '\n';
        }
        file.close();
        qDebug() << "register";
    }
}

void TabWidget::write_xlsx_file(QString name, int row, int col, int minRand, int maxRand){

    QXlsx::Document xlsx_randomGenerate;
    for(int i = 1;i<=col;i++){
        xlsx_randomGenerate.write(1, i, QString(QChar('A' + i - 1)));
    }
    for (int i = 2; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            int value = QRandomGenerator::global()->bounded(minRand,maxRand);//random number pas encore determiné.
            xlsx_randomGenerate.write(i, j, QString(QChar(j + 'a' - 1)) + QString::number(value));
        }
    }
    qDebug()<<name;
    if (!name.isEmpty()) {
        xlsx_randomGenerate.saveAs(name);
    }
}

void TabWidget::write_csv_file(QString name, int row, int col, int minRand, int maxRand){
    if (!name.isEmpty()) {
        QFile file(name);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            for(int i = 1;i<=col;i++){
               stream<<QString(QChar('A' + i - 1));
               if(i<col){
                   stream<<",";
               }
            }
            stream <<"\n";
            for (int i = 2; i <= row; i++) {
                for (int j = 1; j <= col; j++) {
                    int value = QRandomGenerator::global()->bounded(minRand,maxRand);
                    stream << QString(QChar('a' + j - 1))+QString::number(value);
                    if (j < col) {
                        stream << ",";
                    }
                }
                stream << "\n";
            }
        }
    }
}

void TabWidget::printOnUi()
{
    //GENERATE TAB
    int maxRow = data.size()-1;
    int maxCol = data[0].split(" ").size();

    QStandardItemModel *model = new QStandardItemModel(maxRow, maxCol,this);
    tableView->setModel(model);

    model->setHorizontalHeaderLabels(data[0].split(" "));

    // Generate data
    for(int row = 0; row < maxRow; row++)
    {
        QStringList tmp = data[row+1].split(" ");
        for(int col = 0; col < maxCol; col++)
        {
            QModelIndex index = model->index(row,col,QModelIndex());
            model->setData(index, tmp[col]);
        }
    }
}

QStringList TabWidget::getDataFromUi()
{
    qDebug() << "before : " << data;
    int nbCol = data[0].split(" ").size();
    for(int i = 1; i < data.size(); i++)
    {
        QString tmp = "";
        bool first = true;
        for(int j = 0; j < nbCol; j++)
        {
            if(first)
            {
                first = false;
                tmp = tmp + tableView->model()->data(tableView->model()->index(i-1,j)).toString();
            }
            else
            {
                tmp =  tmp + " " + tableView->model()->data(tableView->model()->index(i-1,j)).toString();
            }
        }
        data[i] = tmp;

    }
    qDebug() << "after : " << data;
    return data;
}

void TabWidget::registerData(){
    getDataFromUi();
    saveData();
}

QString TabWidget::getColonne(){
    return data.first();
}
/**
 * @brief TabWidget::getNode prendre une liste de colonnes et retourne la liste des lignes en comptant les redondances
 * @param columns une liste de colonnes en String et qui sont séparé par des virgules
 * @return une QMap qui regroupe le nom du noeud et le le nombre d'occurence de ce noeud
 */
QMap<QString, int> TabWidget::getNode(QString &columns)
{
    QStringList columnNames = columns.split(",");
    QMap<QString, int> countMap;
    QStringList firstLine = data.first().split(" ");
    QList<int> columnIndices;
    for (int i = 0; i < firstLine.count(); ++i) {
        if (columnNames.contains(firstLine[i])) {
            columnIndices << i;
        }
    }
    for (int j = 1; j < data.count(); ++j) {
        QStringList values = data[j].split(" ");
        QString key;
        for (int i = 0; i < columnIndices.count(); ++i) {

            key += values[columnIndices[i]];
            if (i < columnIndices.count() - 1) {
                key += " ";
            }
        }
        ++countMap[key];
    }
    return countMap;
}

void TabWidget::saveData()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save File", "../projetIHM/testData","Excel Files (*.xlsx);;CSV Files (*.csv)");
    if(fileName.isEmpty())
       return;
    QFile file(fileName);
    QFileInfo fileInfo(fileName);
    QString fileSuffix = fileInfo.suffix();

    if(fileSuffix == "xlsx"){
        QXlsx::Document xlsx;
        int row = 1;
        foreach(QString string, data){
            QStringList elements = string.split(" ");
            int col = 1;
            foreach(QString element, elements){
                xlsx.write(row,col,element);
                col++;
            }
            row++;
        }
       xlsx.saveAs(fileName);
    }

    else if(fileSuffix == "csv"){
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            foreach(QString string, data){
                QStringList elements = string.split(" ");
                stream<<elements.join(",")<<Qt::endl;
            }
        }
    }
    file.close();
}

QStringList TabWidget::getData(){
    return this->data;
}

