#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidgetItem>
#include <QString>
#include <QFile>
#include <QMap>
#include <QObject>


class TreeModel : public QObject {

    Q_OBJECT

    using ParentId = int;

    void FillNode(QTreeWidgetItem *node, QString& name, bool state, QString& message) const;

    void ParsLine(QString& line);

    void CreateTree(int id, int parent_id, QString& name, bool state, QString& message) ;

public:

    explicit TreeModel(QObject* parent = nullptr, QTreeWidget* parent_ = nullptr);

    void GetInput(QFile& file);

    ~TreeModel();

private:

    QTreeWidget *par;
    QMap<ParentId, QTreeWidgetItem*> nods;

};

#endif // TREEWIDGET_H
