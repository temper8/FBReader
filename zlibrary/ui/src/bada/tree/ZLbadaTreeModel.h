#ifndef __ZLBADATREEMODEL_H__
#define __ZLBADATREEMODEL_H__

//#include <QtCore/QMap>

//#include <QtCore/QAbstractListModel>
//#include <QtNetwork/QNetworkAccessManager>
//#include <QtGui/QDialog>

#include <ZLTreeListener.h>

//#include "../view/ImageUtils.h"
//#include "../view/ImageProvider.h"

class ZLbadaTreeModel  {


public:
        enum TreeRoles {
                SubTitleRole,// = Qt::UserRole,
                ActivatableRole,
                PageRole
        };

public:
       ZLbadaTreeModel(ZLTreeListener::RootNode& rootNode, shared_ptr<ZLExecutionData::Listener> listener);

public:
	//int rowCount(const QModelIndex &parent = QModelIndex()) const;
	//QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
     //   const ZLTreeNode* getTreeNode(const QModelIndex& index) const;
    void TestTest();

public:
	void onNodeBeginInsert(ZLTreeNode *parent, size_t index);
	void onNodeEndInsert();
	void onNodeBeginRemove(ZLTreeNode *parent, size_t index);
	void onNodeEndRemove();
	void onNodeUpdated(ZLTreeNode *node);

//signals:
        void currentNodeChanged(const ZLTreeNode* node);

public ://slots:
	bool back();
	bool enter(ZLTreeNode* node);
    void update();
	ZLTreeNode* myCurrentNode;
	ZLTreeListener::RootNode& myRootNode;
private:

        //FIXME remove mutable
    //    mutable ImageProvider* myImageProvider;

        //TODO remove two-sided pointing (model should not know about ui element)
    //    QDialog* myTreeDialog;

    shared_ptr<ZLExecutionData::Listener> myListener;
};

#endif /* __ZLBADATREEMODEL_H__ */
