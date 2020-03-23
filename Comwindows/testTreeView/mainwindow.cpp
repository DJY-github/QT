#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TreeView.h"
//#include <QModelIndexindex>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    m_pTreeModel = new TreeModel(this);
    ui->treeView->setModel(m_pTreeModel);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);//����treeview �ܹ�ʹ���Ҽ��˵�
    ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);//����treeview �ܹ�����ѡ
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex curItem=ui->treeView->indexAt(pos);  //��ȡ��ǰ������Ľڵ�
    bool isValid = curItem.isValid();
//    qDebug()<<"on_treeView_customContextMenuRequested";
    QModelIndex index=ui->treeView->currentIndex();
    CNodeBase *item = static_cast<CNodeBase*>(index.internalPointer());//�ڲ�����ָ��
    qDebug()<<"NodeType:"<<item->getNodeType();

    QString fileName=ui->treeView->model()->data(index).toString();
    QModelIndex parentIndex = ui->treeView->model()->parent(index);
    CNodeBase *parentItem = static_cast<CNodeBase*>(parentIndex.internalPointer());
    if(parentItem != NULL)
        qDebug()<<"parentNodeType:"<<parentItem->getNodeType();

    QMenu*menu=new QMenu;
    menu->addAction(QString(tr("%1-Export").arg(fileName)));

//    menu->addAction(QString(tr("%1-Import").arg(fileName)),this,SLOT(slotTest()));

//    menu->addAction(QString(tr("%1-Export").arg(fileName)),this,SLOT(slotTest()));

    menu->exec(QCursor::pos());

}

//��ȡ��ѡ�еĽڵ�
void MainWindow::on_pushButton_clicked()
{
    QModelIndexList	selectedList = ui->treeView->selectionModel()->selectedIndexes();
    foreach(QModelIndex modelIndex,selectedList)
    {
        CNodeBase *node = static_cast<CNodeBase*>(modelIndex.internalPointer());
        qDebug()<<node->getName();
    }

    QString resStr;
    m_pTreeModel->getCheckedItemData(resStr);
    QMessageBox::information(this, "just for test", resStr);
    qDebug()<<resStr;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    m_pTreeModel->updateModel(index);

//    CNodeBase *clickedItem = static_cast<CNodeBase*>(index.internalPointer());

//    ui->treeView->collapseAll();
    ui->treeView->collapse(index);
    ui->treeView->expand(index);
//    QModelIndex parentIndex = index.parent();
//    while(parentIndex.isValid())
//    {
//        ui->treeView->collapse(parentIndex);
//        ui->treeView->expand(parentIndex);
//        parentIndex = parentIndex.parent();
//    }
//    ui->treeView->collapse(index);
//    ui->treeView->expand(index);
//    ui->treeView->scrollTo(index);
}
