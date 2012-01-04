#include <ZLTreeTitledNode.h>
#include <ZLTreeActionNode.h>
#include <ZLTreePageNode.h>
#include <ZLApplication.h>
#include <ZLNetworkManager.h>

#include "ZLbadaTreeModel.h"
#include <FBase.h>

//#include "../image/ZLQtImageManager.h"
//#include "../dialogs/ZLQtPageDialog.h"
//#include "../menu/DrillDownMenu.h"
//#include "../network/ZLQtNetworkManager.h"

//#include "../dialogs/ZLQtUtil.h"

//#include <QtCore/QDebug>
//#include <QtCore/QUrl>
//#include <QtGui/QPainter>
//#include <QtGui/QDesktopWidget>
//#include <QtGui/QApplication>

//#include "../menu/DrillDownMenu.h"

ZLbadaTreeModel::ZLbadaTreeModel(ZLTreeListener::RootNode& rootNode, shared_ptr<ZLExecutionData::Listener> listener) :
myRootNode(rootNode), myListener(listener)
{

	AppLog("ZLbadaTreeModel::ZLbadaTreeModel");
    myCurrentNode = &myRootNode;

	AppLog("children().size() = %d ",myRootNode.children().size());
  //  myImageProvider = new ImageProvider(ImageProvider::THUMBNAIL, this);
//    connect(myImageProvider, SIGNAL(cacheUpdated()), this, SLOT(update()));
}

void ZLbadaTreeModel::TestTest(){
	AppLog("ZLbadaTreeModel::TestTest");
  //  myCurrentNode = &myRootNode;

	AppLog("myCurrentNode->children().size() = %d ",myCurrentNode->children().size());
}

bool ZLbadaTreeModel::back() {
	if (myCurrentNode == &myRootNode) {
		return false;
	}
	myCurrentNode = myCurrentNode->parent();
        //emit currentNodeChanged(myCurrentNode);
        //TODO fix problem:
        //when change description of catalog, it changes just in case when net libraries is opened again
        //emit layoutChanged();
	return true;
}

bool  ZLbadaTreeModel::enter(ZLTreeNode* node) {
	myCurrentNode = node;
	 myCurrentNode->requestChildren(myListener);
	/*
	ZLTreeNode* node = myCurrentNode->children().at(index.row());
	if (ZLTreeActionNode *actionNode = zlobject_cast<ZLTreeActionNode*>(node)) {
		bool result = actionNode->activate();
		if (result == true) {
			ZLApplication::Instance().refreshWindow();
			return false;
		}
        } else if (ZLTreePageNode *pageNode = zlobject_cast<ZLTreePageNode*>(node)) {
                ZLQtPageDialog dialog(*pageNode,myTreeDialog);
                connect(myTreeDialog, SIGNAL(finished(int)), &dialog, SLOT(done(int)));
                dialog.run();
	} else {
		myCurrentNode = node;
                //qDebug() << "\nrequesting children";
                myListener->showPercent(0,0); // indeterminant progress-bar
                //TODO implement each listener for each current node, because:
                //in case if one catalog item will requesting childrens,
                //then another item will requesting others,
                //progress bar will be hided if one will completed before other
                myCurrentNode->requestChildren(myListener);
                qDebug() << Q_FUNC_INFO << "emitting current node changed";
                emit currentNodeChanged(myCurrentNode);
	}
        emit layoutChanged();
        */
	return true;
}

void ZLbadaTreeModel::update() {
 //   emit layoutChanged();
}
 /*
int ZLbadaTreeModel::rowCount(const QModelIndex &parent) const {
        //qDebug() << "asking for rowCount... returning " << myCurrentNode->children().size();
	return myCurrentNode->children().size();
}

QVariant ZLbadaTreeModel::data(const QModelIndex &index, int role) const {

	if (!index.isValid() || index.row() >= myCurrentNode->children().size()) {
            //TODO may be remove second statement in 'if' above:
            //it is need in case if view don't take attention to rowCount
            //const ZLTreeNode* node = myCurrentNode->children().at(index.row());
            return QVariant();
        }

        const ZLTreeNode* node = myCurrentNode->children().at(index.row());
        switch (role) {
            case Qt::DisplayRole:
                    if (const ZLTreeTitledNode *titledNode = zlobject_cast<const ZLTreeTitledNode*>(node))
                            return QString::fromStdString(titledNode->title());
                    else
                            return QString("No title");
            case Qt::DecorationRole:
                //TODO check for asking decoration role only for items on screen
                if (const ZLTreeTitledNode *titledNode = zlobject_cast<const ZLTreeTitledNode*>(node)) {
                    return myImageProvider->getImageForNode(titledNode);
                }
                break;
            case SubTitleRole:
                    if (const ZLTreeTitledNode *titledNode = zlobject_cast<const ZLTreeTitledNode*>(node)) {
                            return QString::fromStdString(titledNode->subtitle());
                    }
            case Qt::SizeHintRole:
                    return MenuItemParameters::getItemSize();
            case Qt::FontRole:
                return MenuItemParameters::getFont();
//        case ActivatableRole:
//                return zlobject_cast<ZLTreeActionNode*>(node) != NULL;
//        case PageRole:
                  //TODO move code from this model to view, that will be work with roles
//                return zlobject_cast<ZLTreePageNode*>(node) != NULL;
        }
        return QVariant();


}
*/
/*
const ZLTreeNode* ZLbadaTreeModel::getTreeNode(const QModelIndex& index) const {
    //qDebug() << Q_FUNC_INFO << index;

    if (index.isValid()) {
        //TODO remove it:
        // it needs in case if view don't take attention to rowCount
        if (index.row() >= myCurrentNode->children().size()) {
            return 0;
        }
        const ZLTreeNode* node = myCurrentNode->children().at(index.row());
        //qDebug() << "returns node";
        return node;
    }

    return 0;
}
*/

void ZLbadaTreeModel::onNodeBeginInsert(ZLTreeNode *parent, size_t index) {
    //qDebug() << Q_FUNC_INFO << parent << index << parent->childIndex();
    //TODO there should be beginInsertRows instead of layoutChanged()
    //TODO remove it, emitting signal is needed to set actions for left soft-button
    //emit currentNodeChanged(myCurrentNode);
    //emit layoutChanged();
//    beginInsertRows(createIndex(parent), index, index);
}

void ZLbadaTreeModel::onNodeEndInsert() {
    //qDebug() << Q_FUNC_INFO;
    //TODO there should be endInsertRows instead of layoutChanged()
    //emit layoutChanged();
//    endInsertRows();
}

void ZLbadaTreeModel::onNodeBeginRemove(ZLTreeNode *parent, size_t index) {
    //qDebug() << Q_FUNC_INFO << parent << index;
    //TODO there should be beginRemoveRows instead of layoutChanged()
    //emit layoutChanged();
//    beginRemoveRows(createIndex(parent), index, index);
}

void ZLbadaTreeModel::onNodeEndRemove() {
    //qDebug() << Q_FUNC_INFO;
    //TODO there should be endRemoveRows instead of layoutChanged()
    //emit layoutChanged();
//    endRemoveRows();
}
void ZLbadaTreeModel::onNodeUpdated(ZLTreeNode *node) {
    //qDebug() << Q_FUNC_INFO << node;
    //TODO there should be dataChanged instead of layoutChanged()
    //emit layoutChanged();
//    QModelIndex index = createIndex(node);
//    emit dataChanged(index, index);
}


