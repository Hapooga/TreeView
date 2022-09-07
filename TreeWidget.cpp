#include "TreeWidget.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void TreeModel::FillNode(QTreeWidgetItem *node, QString& name, bool state, QString& message) const {

    node->setText(0, name);
    node->setDisabled(!state);
    node->setWhatsThis(0, message);

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void TreeModel::ParsLine(QString& line) {

    QStringList line_list = line.split(':');

    CreateTree(
                line_list[0].toInt(),
            line_list[1].toInt(),
            line_list[2],
            line_list[3].toInt(),
            line_list[4]
            );
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void TreeModel::CreateTree(int id, int parent_id, QString& name, bool state, QString& message){

    QTreeWidgetItem *new_node = nullptr;

    auto parent_it = nods.find(parent_id);

    if(nods.isEmpty() || parent_it  == nods.end()) {

        new_node = new QTreeWidgetItem(par);
        FillNode(new_node, name, state, message);
        par->addTopLevelItem(new_node);

    } else {

        new_node = new QTreeWidgetItem(parent_it.value());
        FillNode(new_node, name, state, message);
        parent_it.value()->addChild(new_node);

    }

    nods.insert(id, new_node);

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TreeModel::TreeModel(QObject* parent, QTreeWidget* parent_) : QObject(parent) {
    par = parent_;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void TreeModel::GetInput(QFile& file) {

    QString line;

    while (!file.atEnd()) {

        line = file.readLine();
        ParsLine(line);

    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TreeModel::~TreeModel() {

    qDebug() << "Deleted";
}

