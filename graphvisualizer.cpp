#include "graphvisualizer.h"
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
#include "xlsxdocument.h"
#include "graphvisualizer.h"
GraphVisualizer::GraphVisualizer(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

}

GraphVisualizer::~GraphVisualizer()
{
}
void GraphVisualizer::read_file(){
    QMessageBox qMessageBox;
    qMessageBox.setText("Si votre système d'exploitation est linux les fichiers .xlsx ne seront pas utilisables ni lisibles!");
    qMessageBox.exec();
    show();
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"../projetIHM/testData",tr("Excel(*.csv *.xlsx *.txt)"));
    QFileInfo fileInfo(fileName);
    QString fileSuffix = fileInfo.suffix();
    QFile file(fileName);
    QTextStream in(&file);
    data.clear();

    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"OPEN FILE FAILED!";
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

    }else{
        qDebug()<<"other types";
    }
    file.close();
}
void GraphVisualizer::show_file(){
    QTableView *tableView = new QTableView;
    //tableView->setModel(this->data);
    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tableView);
    window->setLayout(layout);

    window->show();
}
void GraphVisualizer::write_file(){

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
void GraphVisualizer::write_xlsx_file(){
    QXlsx::Document xlsx_randomGenerate;
    int row = QInputDialog::getInt(this, "Input Rows", "Enter number of rows:");
    int col = QInputDialog::getInt(this, "Input Cols(1-26)", "Enter number of cols:");
    //on considère de A-Z
    while(col>26){
        col = QInputDialog::getInt(this, "Input Cols(1-26)", "Index Range Error! Enter number of cols:");
    }
    for(int i = 1;i<=col;i++){
        xlsx_randomGenerate.write(1, i, QString(QChar('A' + i - 1)));
    }
    for (int i = 2; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            int value = QRandomGenerator::global()->bounded(row+1);//random number pas encore determiné.
            xlsx_randomGenerate.write(i, j, QString(QChar(j + 'a' - 1)) + QString::number(value));
        }
    }
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "../projetIHM/testData", "Excel Files (*.xlsx)");

    if (!fileName.isEmpty()) {
        xlsx_randomGenerate.saveAs(fileName);
    }
    read_file();
    printOnUi();
}
void GraphVisualizer::write_csv_file(){
    int row = QInputDialog::getInt(this, "Input Rows", "Enter number of rows:");
    int col = QInputDialog::getInt(this, "Input Cols", "Enter number of cols:");
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "../projetIHM/testData", "CSV Files (*.csv)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
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
                    int value = QRandomGenerator::global()->bounded(row);
                    stream << QString(QChar('a' + j - 1))+QString::number(value);
                    if (j < col) {
                        stream << ",";
                    }
                }
                stream << "\n";
            }
        }
    }
    read_file();
    printOnUi();
}

void GraphVisualizer::printOnUi()
{
    //GENERATE TAB A CHANGER PLUS TARD
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

QStringList GraphVisualizer::getDataFromUi()
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

void GraphVisualizer::on_pushButton_clicked()
{
    getDataFromUi();
    write_file();
}

QMap<QString, int> GraphVisualizer::getNode(QString &columns)
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


