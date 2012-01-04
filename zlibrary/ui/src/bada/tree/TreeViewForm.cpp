
#include "TreeViewForm.h"
#include "PageForm.h"
#include "ZLTreeNode.h"
#include "ZLTreeTitledNode.h"
#include <ZLTreeActionNode.h>
#include <ZLTreePageNode.h>
#include <FIo.h>
#include "../view/badaForm.h"
#include "../image/ZLbadaImageManager.h"

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

TreeViewForm::TreeViewForm() {
	// TODO Auto-generated constructor stub

}

TreeViewForm::~TreeViewForm() {
	// TODO Auto-generated destructor stub
	AppLog("TreeViewForm::~TreeViewForm()");

	delete myModel;
	AppLog("delete myModel");

	//__pCustomList->RemoveAllItems();
	AppLog("__pCustomList->RemoveAllItems()");

  //  delete __pCustomList;
    AppLog("delete __pCustomList;");

//    delete __pCustomListItemFormat;
	AppLog("delete __pCustomListItemFormat;");
}

bool TreeViewForm::Initialize(const char *title)
{
	AppLog("TreeViewForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|
	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);
	SetTitleText(String(title));
	if (String(title).EndsWith("Content") ) {
		exitFlag = true;
		AppLog("exitFlag = true;");
	}
	else exitFlag= false;

//	AddSoftkeyActionListener(SOFTKEY_0, *this);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
//	SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);

	return true;
}



result TreeViewForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("TreeViewForm::OnInitializing \n");
	SetSoftkeyText(SOFTKEY_1, L"Back");

	AddOrientationEventListener(*this);

   // Creates CustomList
    __pCustomList = new CustomList();
	//__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_NORMAL);
	__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_MARK);

	__pCustomList->AddCustomItemEventListener(*this);

	// Creates an item format of the CustomList
	__pCustomListItemFormat = new CustomListItemFormat();
	__pCustomListItemFormat->Construct();

	__pCustomListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(90, 15, 300, 80), 30);
	__pCustomListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(90, 55, 300, 80), 20);
	__pCustomListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	__pCustomListItemFormat->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));
	//__pCustomListItemFormat->AddElement(ID_FORMAT_CUSTOM, Rectangle(320, 20, 80, 60));
	//__pCustomListItemFormat->SetElementEventEnabled(ID_LIST_TEXT, true);
	//__pCustomListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP, true);
	//__pCustomListItemFormat->SetElementEventEnabled(ID_FORMAT_CUSTOM, true);



    // Creates List
//    List* pList = new List();
//    __pLstSearchList = pList;
//	Osp::Graphics::Rectangle rect = GetBounds();
   // pList->Construct(Rectangle(0, 100, 480, 500), LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 100, 0, 480, 0);
//	pList->Construct(rect, LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 100, 0, rect.width, 0);
	//pList->Construct(rect, LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_IMAGE_TEXT_IMAGE, 100, 0, 240, 240);
//	pList->Construct(rect, LIST_STYLE_NORMAL, LIST_ITEM_DOUBLE_IMAGE_TEXT_TEXT, 50, 50, 100, 380);
    //pList->AddItemEventListener(*this);
  //  pList->AddTouchEventListener(*this);
    // Adds a List to the Form

    AddControl(*__pCustomList);
    UpdateContent();
	CreateContextMenuListStyle();


	return r;
}

result TreeViewForm::AddListItem(CustomList& customList, String title,String subTitle, Bitmap* pBitmapNormal)
{
    // Creates an item of the CustomList
    CustomListItem* pItem = new CustomListItem();

    pItem->Construct(100);
    pItem->SetItemFormat(*__pCustomListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE, title);
    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
//    pItem->SetCheckBox(ID_LIST_CHECKBOX);

    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));

    customList.AddItem(*pItem, ID_LIST_ITEM);

    return E_SUCCESS;
}


result TreeViewForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}

void TreeViewForm::SetPreviousForm(Osp::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void TreeViewForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	switch(actionId)
	{
	case ID_CONTEXT_ITEM:
		AppLog("ID_CONTEXT_ITEM0 is clicked! \n");

		//pFrame->SetCurrentForm(*pPreviousForm);
	//	pPreviousForm->Draw();
	//	pPreviousForm->Show();
	    pPreviousForm->SendUserEvent(0, null);

	case ID_CONTEXT_ITEM+1:
		AppLog("ID_CONTEXT_ITEM1 is clicked! \n");
	case ID_CONTEXT_ITEM+2:
		AppLog("ID_CONTEXT_ITEM2 is clicked! \n");
		if (selectedNode) {
			std::string actionText = selectedNode->actionText(selectedNode->actions()[actionId-ID_CONTEXT_ITEM]);
			AppLog("делаем  %s",actionText.c_str());
			//myHolder.doAction(ActionIdList[indx]);
			shared_ptr<ZLRunnableWithKey> _action = selectedNode->actions()[actionId-ID_CONTEXT_ITEM];
			if (!_action.isNull()) {
				AppLog("doAction %s",actionText.c_str());
				_action->run();
			   //pPreviousForm->SendUserEvent(0, null);
			}
		}
		break;
	case ID_ACT_CLOSE:
		{
			AppLog("Close button is clicked! \n");
			if (myModel->back()) {
				UpdateContent();
			}
			else	{
				//Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
				//pFrame->SetCurrentForm(*pPreviousForm);
				//pPreviousForm->Draw();
				//pPreviousForm->Show();
			    pPreviousForm->SendUserEvent(0, null);
			}
		}
		break;
	case ID_ACT_UPDATE:
		{
			AppLog("UpdateContent");
			UpdateContent();
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


void TreeViewForm::CreateContextMenuListStyle(void)
{
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
//	Bitmap* pNormalBitmap1 = pAppResource->GetBitmapN(L"call_type1.png");
//	Bitmap* pPressedBitmap1 = pAppResource->GetBitmapN(L"call_f_type1.png");


//	Bitmap* pNormalBitmap2 = pAppResource->GetBitmapN(L"message_type1.png");
//	Bitmap* pPressedBitmap2 = pAppResource->GetBitmapN(L"message_f_type1.png");

	__pContextMenuIconText = new ContextMenu();
	__pContextMenuIconText->Construct(Point(100, 240), CONTEXT_MENU_STYLE_LIST);
//	__pContextMenuIconText->AddItem(L"text1",ID_CONTEXT_ITEM1, *pNormalBitmap1, pPressedBitmap1);
//	__pContextMenuIconText->AddItem(L"text2",ID_CONTEXT_ITEM2, *pNormalBitmap2, pPressedBitmap2);
//	__pContextMenuIconText->AddItem(L"text1",ID_CONTEXT_ITEM0);
//	__pContextMenuIconText->AddItem(L"text2",ID_CONTEXT_ITEM1);
	__pContextMenuIconText->AddActionEventListener(*this);

	// Deallocate bitmaps
	//delete pNormalBitmap1;
	//delete pPressedBitmap1;
	//delete pNormalBitmap2;
	//delete pPressedBitmap2;

}


void TreeViewForm::OnItemStateChanged (const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	String strName;
	AppLog("index %d",index);
	ZLTreeNode* node = myModel->myCurrentNode->children().at(index);
    int actionsCount = node->actions().size();
	AppLog("node->actions().size %d", actionsCount);
	switch (actionsCount){
	case  0: if (ZLTreeTitledNode *TitledNode = zlobject_cast<ZLTreeTitledNode*>(node))
				{
			 	 AppLog("Node is ZLTreeTitledNode %s ",TitledNode->title().c_str());
			 	 strName = String(TitledNode->title().c_str());
			 	 SetTitleText(strName);
			 	 myModel->enter(node);
			 	 UpdateContent();
				};
			 break;
	case  1:
			// pFrame->SetCurrentForm(*pPreviousForm);
		//TODO испраивть на приличную проверку что действие в содежаннии
		if (exitFlag){
			AppLog("GetTitleText() == Book Content");
			//pFrame->SetCurrentForm(*pPreviousForm);
			pPreviousForm->SendUserEvent(0, null);
		}
		     node->actions()[0]->run();
		 break;
	default:
		Osp::Graphics::Rectangle r = source.GetBounds();
		AppLog("TouchPosition %d, %d",TouchPosition.x,TouchPosition.y);
		selectedNode = node;
		__pContextMenuIconText->RemoveAllItems();
		for (int i =0; i<actionsCount; i++){
			std::string actionText = node->actionText(node->actions()[i]);
			AppLog("actionText  %s",actionText.c_str());
			__pContextMenuIconText->AddItem(actionText.c_str(),ID_CONTEXT_ITEM+i);
		}
		__pContextMenuIconText->SetPosition(Point(TouchPosition.x,TouchPosition.y+r.y));
		__pContextMenuIconText->SetShowState(true);
		__pContextMenuIconText->Show();
	}
	/*
	if (actionsCount>0)
	{
		Osp::Graphics::Rectangle r = source.GetBounds();
		AppLog("TouchPosition %d, %d",TouchPosition.x,TouchPosition.y);
		selectedNode = node;
		__pContextMenuIconText->RemoveAllItems();
		for (int i =0; i<actionsCount; i++){
			std::string actionText = node->actionText(node->actions()[i]);
			AppLog("actionText  %s",actionText.c_str());
			__pContextMenuIconText->AddItem(actionText.c_str(),ID_CONTEXT_ITEM+i);
		}
		__pContextMenuIconText->SetPosition(Point(TouchPosition.x,TouchPosition.y+r.y));
		__pContextMenuIconText->SetShowState(true);
		__pContextMenuIconText->Show();
	}
	else
	{
		if (ZLTreeTitledNode *TitledNode = zlobject_cast<ZLTreeTitledNode*>(node)) {
					AppLog("Node is ZLTreeTitledNode %s ",TitledNode->title().c_str());
					strName = String(TitledNode->title().c_str());
					myModel->enter(node);
					//myModel->myCurrentNode = node;
					UpdateContent();
					}
	}

	/*
	if (ZLTreeActionNode *actionNode = zlobject_cast<ZLTreeActionNode*>(node)) {
			AppLog("Node is ZLTreeActionNode %s ",actionNode->title().c_str());
			bool result = actionNode->activate();
			//if (result == true) {
			//ZLApplication::Instance().refreshWindow();
			//return false;
		 }
	else
		if (ZLTreePageNode *pageNode = zlobject_cast<ZLTreePageNode*>(node)) {
			AppLog("Node is ZLTreePageNode %s ",pageNode->title().c_str());
			result r = E_SUCCESS;
			PageForm *pageForm = new PageForm;
			Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
			pageForm->Initialize(*pageNode);
			r = pFrame->AddControl(*pageForm);
			r = pFrame->SetCurrentForm(*pageForm);
			pageForm->SetPreviousForm(this);

			r = pFrame->Draw();
			AppLog("pFrame->Draw();");
			r = pFrame->Show();
			AppLog("pFrame->Show()");
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


void TreeViewForm::UpdateContent(){
	AppLog("TreeViewForm::UpdateContent()");

	String popStr;

	String strSub;
	String strName;


	result r = E_SUCCESS;
//	Osp::Media::Image *pImage = null;
//	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
//	Bitmap* pNormalBitmap1 = pAppResource->GetBitmapN(L"call_type1.png");
//	Bitmap* pPressedBitmap1 = pAppResource->GetBitmapN(L"call_f_type1.png");
//    Bitmap* pBitmapLeftIcon =  pAppResource->GetBitmapN(L"booktree-book.png");
//    Bitmap* pBitmapRightIcon = pAppResource->GetBitmapN(L"booktree-tag.png ");

 //  int width = pBitmapLeftIcon->GetWidth();
//   int height = pBitmapLeftIcon->GetHeight();
//   AppLog("width=%d height=%d",width, height);
//	String anycall_path("/Media/Images/anycall.jpg");
//	String samsung_path("/Media/Images/samsunglogo.jpg");
//	pImage = new Osp::Media::Image();
//	pBitmapLeftIcon = pImage->DecodeN(anycall_path, BITMAP_PIXEL_FORMAT_RGB565, LCD_WIDTH, LCD_HEIGHT);
//	pBitmapRightIcon = pImage->DecodeN(samsung_path, BITMAP_PIXEL_FORMAT_RGB565, LCD_WIDTH, LCD_HEIGHT);


//	__pLstSearchList->RemoveAllItems();  // Clear ui list
   __pCustomList->RemoveAllItems();  // Clear ui list
	AppLog("__pCustomList->RemoveAllItems()"
			"");
//	if (const ZLTreeTitledNode *TitledNode = zlobject_cast<const ZLTreeTitledNode*>(myModel->myCurrentNode)) {
//		AppLog("SetTitleText  %s",TitledNode->title().c_str());
//		SetTitleText(String(TitledNode->title().c_str()));
	//}

	AppLog("children().size() = %d ",myModel->myCurrentNode->children().size());


	ZLTreeNode::List::iterator it;
	for (int i =0; i<myModel->myCurrentNode->children().size(); i++) {
		ZLTreeNode* node = myModel->myCurrentNode->children().at(i);
		if (const ZLTreeTitledNode *TitledNode = zlobject_cast<const ZLTreeTitledNode*>(node)) {
				AppLog("ZLTreeTitledNode.titile %s",TitledNode->title().c_str());
				//AppLog("ZLTreeTitledNode.imageUrl =  %s",TitledNode->imageUrl().c_str());

				strName = String(TitledNode->title().c_str());
				strSub = String(TitledNode->subtitle().c_str());

				shared_ptr<ZLImage> cover =TitledNode->image();
				if (cover.isNull()) {	AppLog("cover.isNull()");}

				shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*cover);
				if (coverData.isNull()) {	AppLog("coverData.isNull()");}
				//pBitmapLeftIcon = 	((ZLbadaImageData&)coverData).pBitmap;
				Bitmap *pBmp;
				ZLImageData &image = *coverData;
				pBmp = 	((ZLbadaImageData&)image).pBitmap;
			    int imageWidth = pBmp->GetWidth();
			    int imageHeight = pBmp->GetHeight();
				AppLog("image w = %d, h = %d", imageWidth, imageHeight);

				AppLog("AddListItem");
				AddListItem(*__pCustomList, strName, strSub, pBmp);
				}
			else
			{
				strName = "Node is not ZLTreeTitledNode ";
			}

		//	r = __pLstSearchList->AddItem(&strName, null, null, null );

//		r = __pLstSearchList->AddItem(&strName,&strSub, pBitmapLeftIcon, null );


	}

//	delete pBitmapLeftIcon;
//	delete pBitmapRightIcon;



	__pCustomList->Draw();
	__pCustomList->Show();



	return;

}

void TreeViewForm::_ClearContentInfoList()
{
	if(__pLstContentInfo != null)
	{
		__pLstContentInfo->RemoveAll(true);
		delete __pLstContentInfo;
		__pLstContentInfo = null;
	}
}


void TreeViewForm::OnTouchDoublePressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchDoublePressed");
}

void TreeViewForm::OnTouchFocusIn(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusIn");
}

void TreeViewForm::OnTouchFocusOut(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusOut");
}

void TreeViewForm::OnTouchLongPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchLongPressed");

	// Display the OptionMenu

}

void TreeViewForm::OnTouchMoved(const Osp::Ui::Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchMoved");
//	myHolder.view()->onStylusMove(currentPosition.x, currentPosition.y);
}

void TreeViewForm::OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchPressed");
	TouchPosition = currentPosition;
//	myHolder.view()->onStylusPress(currentPosition.x, currentPosition.y);
}

void TreeViewForm::OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchReleased");

}


void TreeViewForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("TreeViewForm::OnUserEventReceivedN");
	Form* prevForm = pFrame->GetCurrentForm();
	switch(requestId)
	{
	case 0:
		{
			pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			if (prevForm != null)		{
				pFrame->RemoveControl(*prevForm);
				}

		}
		break;
	case 1:
		{
			AppLog("badaForm::а теперь Акшен открываем файл");
			pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			//myHolder.doAction(ActionIdList[2]);

		}
		break;
	default:
		break;
	}

}
void TreeViewForm::OnOrientationChanged( const Osp::Ui::Control&  source,  Osp::Ui::OrientationStatus  orientationStatus ){

	AppLog("OnOrientationChanged");
}

// Implements an ICustomItemEventListener
/*
void
TreeViewForm::OnItemStateChanged(const Control& source, int index, int itemId, ItemStatus status)
{
    switch (itemId)
    {
        case ID_LIST_ITEM:
            // Todo:
            break;
        default:
            break;
    }
}
*/
void
TreeViewForm::OnItemStateChanged(const Osp::Ui::Control& source, int index, int itemId, int elementId, Osp::Ui::ItemStatus status)
{
    switch (itemId)
    {
        case ID_LIST_ITEM:
            {
                switch (elementId)
                {
                    case ID_LIST_TEXT_TITLE:
                        // Todo:
                        break;

                    case ID_LIST_BITMAP:
                        // Todo:
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}

