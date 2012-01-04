#include <ZLDialogManager.h>


#include "PageForm.h"
#include "ZLTreeNode.h"
#include "ZLTreeTitledNode.h"
#include <ZLTreeActionNode.h>
#include <ZLTreePageNode.h>
#include <FIo.h>
#include "../view/badaForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Content;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;

#define	ID_ACT_UPDATE	1600
#define ID_ACT_DELETE	1601
#define ID_ACT_CLOSE	1602

PageForm::PageForm() {
	// TODO Auto-generated constructor stub

}

PageForm::~PageForm() {
	// TODO Auto-generated destructor stub
}

bool PageForm::Initialize(const ZLTreePageNode& pageNode)
{
	AppLog("PageForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|
	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_0|FORM_STYLE_SOFTKEY_1);
	SetTitleText(String(pageNode.title().c_str()));

	AddSoftkeyActionListener(SOFTKEY_0, *this);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);

	return true;
}



result PageForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("PageForm::OnInitializing \n");
	SetSoftkeyText(SOFTKEY_0, L"Open");
	SetSoftkeyText(SOFTKEY_1, L"Back");
	// Creates close button

	    Button* pBtnClose = new Button();
	    pBtnClose->Construct(Rectangle(50, 50, 150, 050), L"Нажми");


	//	myModel->TestTest();


	if (pBtnClose == null)
	{
		AppLog("GetControl(IDC_BUTTON1) failed");
		return E_FAILURE;
	}else{
		pBtnClose->SetActionId(ID_ACT_UPDATE);
		pBtnClose->AddActionEventListener(*this);
		AddControl(*pBtnClose);
	}

    // Creates List
    List* pList = new List();
    __pLstSearchList = pList;
    pList->Construct(Rectangle(0, 200, 480, 500), LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 100, 0, 480, 0);
//pList->AddItemEventListener(*this);
    pList->AddItemEventListener(*this);

    // Creates a String
    String itemText1(L"Text1");
    String itemText2(L"Text2");
    String itemText3(L"Text4");
    String itemText4(L"Text5");
    // Adds an item to the List
    pList->AddItem(&itemText1, null, null, null, 500);
    pList->AddItem(&itemText2, null, null, null, 501);


    // Adds a List to the Form
    AddControl(*pList);


	return r;
}


result PageForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}

void PageForm::SetPreviousForm(Osp::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void PageForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_ACT_CLOSE:
		{
			AppLog("Close button is clicked! \n");
				Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
				pFrame->SetCurrentForm(*pPreviousForm);
				pPreviousForm->Draw();
				pPreviousForm->Show();
			    pPreviousForm->SendUserEvent(0, null);

		}
		break;
	case ID_ACT_UPDATE:
		{
			AppLog("UpdateContent");
		//	myModel->TestTest();

			break;
		}
	/*case ID_ACT_DELETE:
		{
			DeleteContent();
			break;
		}*/
	default:
		break;
	}
}


void PageForm::OnItemStateChanged (const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status)
{
//	String tmpContentPath;
//	ByteBuffer* bb;
	String strName;
	AppLog("index %d",index);
	/*
	ZLTreeNode* node = myModel->myCurrentNode->children().at(index);

	if (ZLTreeActionNode *actionNode = zlobject_cast<ZLTreeActionNode*>(node)) {
			AppLog("Node is ZLTreeActionNode %s ",actionNode->title().c_str());
			//bool result = actionNode->activate();
			//if (result == true) {
			//ZLApplication::Instance().refreshWindow();
			//return false;
		 }
	else
		if (ZLTreePageNode *pageNode = zlobject_cast<ZLTreePageNode*>(node)) {
			AppLog("Node is ZLTreePageNode %s ",pageNode->title().c_str());
            //  ZLQtPageDialog dialog(*pageNode,myTreeDialog);
            //  connect(myTreeDialog, SIGNAL(finished(int)), &dialog, SLOT(done(int)));
            //  dialog.run();
		}
	else {

		if (ZLTreeTitledNode *TitledNode = zlobject_cast<ZLTreeTitledNode*>(node)) {
			AppLog("Node is ZLTreeTitledNode %s ",TitledNode->title().c_str());
			strName = String(TitledNode->title().c_str());
			myModel->enter(node);
			//myModel->myCurrentNode = node;
			UpdateContent();
			}
		else
	    	{
			strName = "Node is not ZLTreeTitledNode ";
			}
	}
	*/

/*
	ContentSearchResult* pInfo = (ContentSearchResult*)__pLstContentInfo->GetAt(index);
	//TryCatch(pInfo != null, popStr = "Fail to convert to ContentSearchResult", "Fail to convert %i th node.", i);

	tmpContentPath = ((ContentInfo*)pInfo->GetContentInfo())->GetContentPath();
	bb = Osp::Base::Utility::StringUtil::StringToUtf8N(tmpContentPath);
	AppLog("tmpContentPath %s",(char*)bb->GetPointer());

	AppLog("Выбран файл! \n");
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	pFrame->SetCurrentForm(*pPreviousForm);
	pPreviousForm->Draw();
	pPreviousForm->Show();
	((badaForm*)pPreviousForm)->pSearchResultInfo=pInfo;
	pPreviousForm->SendUserEvent(0, null);
*/
    switch (itemId)
    {
        case 500:
            // Todo:
        	AppLog("500 \n");
            break;
        case 501:
            // Todo:
        	AppLog("501 \n");
            break;
        default:
            break;
    }
}






/*

ZLQtPageDialog::ZLQtPageDialog(const ZLTreePageNode& pageNode, QWidget* parent) : QDialog(parent), myContent(pageNode.content()), myPageNode(pageNode) {

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(static_cast<ZLQtDialogContent&>(*myContent).widget());

    const std::string& back = ZLDialogManager::Instance().buttonName(ZLResourceKey("back"));
    QAction* action = new QAction(QString::fromStdString(back),this);
#ifdef __SYMBIAN__
    action->setSoftKeyRole( QAction::NegativeSoftKey );
#endif
    connect(action, SIGNAL(triggered()), this, SLOT(accept()));
    addAction( action );
#ifndef __SYMBIAN__
    QPushButton* backButton = new ButtonAction(action);
    layout->addWidget(backButton);
#endif

    QAction* pageMenuAction = new QAction(this);
#ifdef __SYMBIAN__
    pageMenuAction->setSoftKeyRole( QAction::PositiveSoftKey );
#endif
    myPageMenu = new TreeNodeActionsMenu(pageMenuAction, this);
    myPageMenu->setTreeNode(&pageNode);
    addAction(pageMenuAction);
    connect(pageMenuAction, SIGNAL(triggered()), myPageMenu, SLOT(activate()));
    connect(this,SIGNAL(finished(int)), myPageMenu, SLOT(onFinish(int)));
#ifndef __SYMBIAN__
        QPushButton* menuButton = new ButtonAction(pageMenuAction);
        layout->addWidget(menuButton);
#endif

    this->setLayout(layout);
}

ZLQtPageDialog::~ZLQtPageDialog() {
    //TODO reimplement the way to use inner widget in ZLQtDialogContent
    //(if not set parent to 0, it will crash, cause inner widget will be deleted)
    //static_cast<ZLQtDialogContent&>(*myContent).widget()->setParent(0);
}

bool ZLQtPageDialog::run() {
#ifdef __SYMBIAN__
    setWindowFlags(windowFlags() | Qt::WindowSoftkeysVisibleHint);
    setWindowState(Qt::WindowFullScreen);
#else
    setFixedSize(400, 600);
#endif
    NodePictureWidget* picture = new NodePictureWidget(myPageNode);
    ZLQtDialogContent* content = static_cast<ZLQtDialogContent*>(&*myContent);
    content->addItem(0, picture);
    content->close();
    return exec() == QDialog::Accepted;
}

NodePictureWidget::NodePictureWidget(const ZLTreePageNode& pageNode, QWidget* parent) : PictureWidget(QPixmap(), parent), myPageNode(pageNode) {
    //TODO implement a way for caching cover, if it has been loaded yet via network manager
    myImageProvider = new ImageProvider(ImageProvider::FULL, this);
    connect(myImageProvider, SIGNAL(cacheUpdated()), this, SLOT(refresh()));
    myPicture = myImageProvider->getImageForNode(&myPageNode);
}

void NodePictureWidget::refresh() {
    //qDebug() << Q_FUNC_INFO;
    if (ImageProvider::generateUrl(&myPageNode).scheme() == QLatin1String(ZLTreeTitledNode::LOCALFILE_SCHEME.c_str())) {
        return;
    }
    myPicture = myImageProvider->getImageForNode(&myPageNode);
    //qDebug() << Q_FUNC_INFO << myPicture.size();
    updateGeometry();
}
*/
