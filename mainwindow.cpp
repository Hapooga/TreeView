#include "mainwindow.h"
#include "ui_mainwindow.h"
\
#include <QString>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    box = new QMessageBox(this);
    tree_model = new TreeModel(this, ui->treeWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString file_name = QFileDialog::getOpenFileName(this, "Выбрать файл");
    QFile file(file_name);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){

        qDebug() << "File didn't open";

    } else {

        ui->treeWidget->clear();

        tree_model->GetInput(file);

        file.close();

    }

}


void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(!item->isDisabled()){

        box->setText(item->whatsThis(column));
        box->exec();

    }
}

