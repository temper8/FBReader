/*
 * OpenFileForm.cpp
 *
 *  Created on: 15.11.2011
 *      Author: Alex
 */

#include "OpenFileForm.h"
#include <FIo.h>
#include "badaForm.h"

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

OpenFileForm::OpenFileForm() {
	// TODO Auto-generated constructor stub

}

OpenFileForm::~OpenFileForm() {
	// TODO Auto-generated destructor stub
}

bool OpenFileForm::Initialize()
{
	AppLog("OpenFileForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|
	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);
	SetTitleText(L"OpenFileForm");

//	AddSoftkeyActionListener(SOFTKEY_0, *this);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
//	SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);

	return true;
}



result OpenFileForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("OpenFileForm::OnInitializing \n");
	SetSoftkeyText(SOFTKEY_1, L"Back");
	// Creates close button

	    Button* pBtnClose = new Button();
	    pBtnClose->Construct(Rectangle(50, 50, 150, 150), L"Нажми");



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
    pList->AddItem(&itemText3, null, null, null, 502);
    pList->AddItem(&itemText4, null, null, null, 503);
    pList->AddItem(&itemText1, null, null, null, 500);
    pList->AddItem(&itemText2, null, null, null, 501);
    pList->AddItem(&itemText3, null, null, null, 502);
    pList->AddItem(&itemText4, null, null, null, 503);
    pList->AddItem(&itemText1, null, null, null, 500);
    pList->AddItem(&itemText2, null, null, null, 501);
    pList->AddItem(&itemText3, null, null, null, 502);
    pList->AddItem(&itemText4, null, null, null, 503);
    pList->AddItem(&itemText1, null, null, null, 500);
    pList->AddItem(&itemText2, null, null, null, 501);
    pList->AddItem(&itemText3, null, null, null, 502);
    pList->AddItem(&itemText4, null, null, null, 503);

    // Adds a List to the Form
    AddControl(*pList);



	return r;
}

void OpenFileForm::OnItemStateChanged (const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status)
{
	String tmpContentPath;
	ByteBuffer* bb;
	AppLog("index %d",index);
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


result OpenFileForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}

void OpenFileForm::SetPreviousForm(Osp::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void OpenFileForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
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
			((badaForm*)pPreviousForm)->pSearchResultInfo=null;
			pPreviousForm->SendUserEvent(0, null);


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

void OpenFileForm::UpdateContent(){
	//__pCommonPopup = new Popup;
	//__pCommonPopup->Initialize();
	//__pCommonPopup->SetMessage("Searching...");
	//__pCommonPopup->Show();

	String popStr;

	String sortColumn = null;
	String strQuery = L"";
	String strName = "";
	String tmpContentPath;
	String ch;
	String keyword = null;

	int totalPage = 0;
	int totalCount = 0;
	int nItemCount = 0;
	int nStartIndex = 0;
	int nIndex = 0;
	ByteBuffer* bb;
	ContentSearch contentSearch;

	result r = E_SUCCESS;

	_ClearContentInfoList();		// Clear content info list
	__pLstSearchList->RemoveAllItems();  // Clear ui list

	ch.Append("/");

	r = contentSearch.Construct(CONTENT_TYPE_ALL);
	TryCatch(E_SUCCESS == r, popStr = "Search fail - Construct fail.", "Construct() is failed by %s.", GetErrorMessage(r));

	strQuery = L"ContentFileName";
	strQuery.Append(L" LIKE '%.fb2'");
	//keyword = L" ";

		// convert special char
		//keyword.Replace(L"\\", L"\\\\");
		//keyword.Replace(L"_", L"\\_");
		//keyword.Replace(L"%", L"\\%");
		//keyword.Replace(L"'", L"\\'");

		//strQuery.Append(keyword);

		//strQuery.Append(L"'");
	bb = Osp::Base::Utility::StringUtil::StringToUtf8N(strQuery);
	AppLog("strQuery %s",(char*)bb->GetPointer());
	__pLstContentInfo = contentSearch.SearchN(1, 50, totalPage, totalCount, strQuery, sortColumn, SORT_ORDER_NONE);
	TryCatch(__pLstContentInfo != null, popStr = "Search failed.", "ContentSearch.SearchN() is failed by %s", GetErrorMessage(GetLastResult()));

	nItemCount = __pLstContentInfo->GetCount();
	if(nItemCount == 0){
		popStr = "No search result.";
		goto CATCH;
	}

	for( int i=0; i<nItemCount; i++ )
	{
		ContentSearchResult* pInfo = (ContentSearchResult*)__pLstContentInfo->GetAt(i);
		TryCatch(pInfo != null, popStr = "Fail to convert to ContentSearchResult", "Fail to convert %i th node.", i);

		tmpContentPath = ((ContentInfo*)pInfo->GetContentInfo())->GetContentPath();
		bb = Osp::Base::Utility::StringUtil::StringToUtf8N(tmpContentPath);
		AppLog("tmpContentPath %s",(char*)bb->GetPointer());
		while(nIndex != -1){
			tmpContentPath.IndexOf(ch, nStartIndex, nIndex);
			if(nIndex != -1) nStartIndex = nIndex+1;
		}
		tmpContentPath.SubString(nStartIndex, strName);
		nStartIndex = 0;
		nIndex = 0;

		r = __pLstSearchList->AddItem(&strName, null, null, null );
		TryCatch(E_SUCCESS == r, popStr = "Search fail - Construct fail." , "Construct() is failed by %s.", GetErrorMessage(r));
	}

	__pLstSearchList->Draw();
	__pLstSearchList->Show();

	//delete __pCommonPopup;

	return;

CATCH:

	//delete __pCommonPopup;
	//__pCommonPopup = new CommonPopup;
	//__pCommonPopup->Initialize();
	//__pCommonPopup->SetMessage(popStr);
	//__pCommonPopup->Show(2000);
	//delete __pCommonPopup;

	return;
}

void OpenFileForm::_ClearContentInfoList()
{
	if(__pLstContentInfo != null)
	{
		__pLstContentInfo->RemoveAll(true);
		delete __pLstContentInfo;
		__pLstContentInfo = null;
	}
}

