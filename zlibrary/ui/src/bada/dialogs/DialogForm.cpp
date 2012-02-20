/*
 * DialogForm.cpp
 *
 *  Created on: 24.11.2011
 *      Author: Alex
 */

#include "DialogForm.h"
#include "optionView/ZLbadaOptionView.h"
#include <FIo.h>
#include "ZLbadaOptionsDialog.h"
//#include "badaForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Content;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;

bool DialogForm::Initialize(const char *title, bool showApplyButton)
{
	AppLog("DialogForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|

	if (showApplyButton) {
	//	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_0|FORM_STYLE_SOFTKEY_1);
		Construct(FORM_STYLE_NORMAL|FORM_STYLE_SOFTKEY_0|FORM_STYLE_SOFTKEY_1);
		AddSoftkeyActionListener(SOFTKEY_0, *this);
		SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
		SetSoftkeyText(SOFTKEY_0, L"Apply");
	}
	else
		Construct(FORM_STYLE_NORMAL|FORM_STYLE_SOFTKEY_1);
	SetTitleText(String(title));

	AddSoftkeyActionListener(SOFTKEY_1, *this);
	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);
	SetSoftkeyText(SOFTKEY_1, L"Back");

//	clientArea = GetClientAreaBounds();
  //  clientArea.x+= 10;
//    clientArea.y+= 00;
   // clientArea.width-= 20;
   // clientArea.height-= 20;
//    YPos=0;
	result r = E_SUCCESS;

//   pScrollPanel = new ScrollPanel();
//    pScrollPanel->Construct(Rectangle(0, 400, 480, 800));
 //   AddControl(*pScrollPanel);

	return true;
}

DialogForm::DialogForm() {
	// TODO Auto-generated constructor stub
	AppLog("DialogForm::DialogForm()");
}

DialogForm::~DialogForm() {
	// TODO Auto-generated destructor stub
	AppLog("delete __badaOptionsDialog;...");
	__badaOptionsDialog =0;
	AppLog("delete buttonBmp;...");
	delete buttonBmp;
	delete buttonBmp2;
	AppLog("delete __pCustomListItemFormat...");
	delete __pComboViewListItemFormat;
	delete __pSpinViewListItemFormat;
	delete __pStringViewListItemFormat;
	delete __pBooleanListItemFormat;
	delete __pCustomListItemFormat2;
	delete __pColorListItemFormat;
	delete __pImageViewListItemFormat;
	delete __pButtonViewListItemFormat;
	delete __pStaticTextListItemFormat;
	AppLog("DialogForm::~DialogForm()");
}

OptionListItem::OptionListItem(ZLbadaOptionView* badaOptionView) : CustomListItem(), mybadaOptionView(badaOptionView) {

	}

void OptionListItem::OnActionPerformed(int actionId){
	AppLog(" OptionListItem::OnActionPerformed");
	mybadaOptionView->OnActionPerformed(actionId);
	}



result DialogForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("DialogForm::OnInitializing");

	   // Creates CustomList

	Osp::Media::Image *pImage = new Osp::Media::Image();
    r = pImage->Construct();
	buttonBmp = pImage->DecodeN("/Res/icons/button-220x50.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	buttonBmp2 = pImage->DecodeN("/Res/icons/button-220x50s.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	arrowDownBmp = pImage->DecodeN("/Res/icons/arrow_down.png", BITMAP_PIXEL_FORMAT_ARGB8888);
	AppLog("pImage->DecodeN");


    __pCustomList = new GroupedList();
	GroupCount = 0;
	//__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_NORMAL);
	__pCustomList->Construct(Rectangle(0, 0, 480, 790), CUSTOM_LIST_STYLE_MARK);
//	__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_MARK_WITH_DIVIDER);
	//__pCustomList->AddCustomItemEventListener(*this);
	__pCustomList->AddGroupedItemEventListener(*this);
	  AddControl(*__pCustomList);

// ----------------   Creates an item format of the CustomList -------------------

//---------------------- __pSpinViewListItemFormat -------------------------------
	  __pSpinViewListItemFormat = new CustomListItemFormat();
	  __pSpinViewListItemFormat->Construct();

	  __pSpinViewListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(15, 25, 400, 80), 30, Color::COLOR_GREY, Color::COLOR_GREY);
	  __pSpinViewListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(420, 25, 400, 80), 30);
	  __pSpinViewListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	  __pSpinViewListItemFormat->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));

//---------------------- __pComboViewListItemFormat --------------------------------

	  __pComboViewListItemFormat = new CustomListItemFormat();
	  __pComboViewListItemFormat->Construct();

	  __pComboViewListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(10, 10, 400, 80), 25, Color::COLOR_GREY, Color::COLOR_GREY);
	  __pComboViewListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(10, 50, 400, 80), 28);
	  __pComboViewListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	  __pComboViewListItemFormat->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 40, 40));

//---------------------- __pComboViewListItemFormat --------------------------------

	  __pStringViewListItemFormat = new CustomListItemFormat();
	  __pStringViewListItemFormat->Construct();

	  __pStringViewListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(15, 10, 400, 80), 25, Color::COLOR_GREY, Color::COLOR_GREY);
	  __pStringViewListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(30, 50, 400, 80), 30);
	  __pStringViewListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	  __pStringViewListItemFormat->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));

//---------------------- __pBooleanListItemFormat --------------------------------

		// Creates an item format of the CustomList
	__pBooleanListItemFormat = new CustomListItemFormat();
	__pBooleanListItemFormat->Construct();

	__pBooleanListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(20, 10, 400, 80), 28, Color::COLOR_GREY, Color::COLOR_GREY);
	__pBooleanListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(20, 55, 400, 80), 20);
	__pBooleanListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	__pBooleanListItemFormat->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));
	__pBooleanListItemFormat->SetElementEventEnabled(ID_LIST_CHECKBOX, true);


//---------------------- __pCustomListItemFormat2 --------------------------------

	__pCustomListItemFormat2 = new CustomListItemFormat();
	__pCustomListItemFormat2->Construct();

	__pCustomListItemFormat2->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(90, 10, 300, 80), 25, Color::COLOR_GREY, Color::COLOR_GREY);
	__pCustomListItemFormat2->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(90, 55, 300, 80), 20);
	__pCustomListItemFormat2->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	__pCustomListItemFormat2->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));
//	__pCustomListItemFormat2->SetElementEventEnabled(ID_LIST_CHECKBOX, true);


//---------------------- __pColorListItemFormat --------------------------------

	__pColorListItemFormat = new CustomListItemFormat();
	__pColorListItemFormat->Construct();

	__pColorListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(15, 25, 300, 80), 30, Color::COLOR_GREY, Color::COLOR_GREY);
	__pColorListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(105, 55, 300, 80), 30);
	__pColorListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(15, 45, 80, 40));
	__pColorListItemFormat->AddElement(ID_LIST_COLOR, Osp::Graphics::Rectangle(370, 20, 100, 45));
//	__pColorListItemFormat->SetElementEventEnabled(ID_LIST_TEXT_TITLE, true);
//	__pColorListItemFormat->SetElementEventEnabled(ID_LIST_TEXT_SUBTITLE, true);
	//__pColorListItemFormat->SetElementEventEnabled(ID_LIST_CHECKBOX, true);


//---------------------- __pImageViewListItemFormat --------------------------------

	__pImageViewListItemFormat = new CustomListItemFormat();
	__pImageViewListItemFormat->Construct();

	__pImageViewListItemFormat->AddElement(ID_LIST_BACKGROUND, Osp::Graphics::Rectangle(0, 0, 480, 300));
	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 15, 200, 300));
	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP1, Osp::Graphics::Rectangle(240, 25, 220, 52));
	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP2, Osp::Graphics::Rectangle(240, 100, 220, 52));
	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP3, Osp::Graphics::Rectangle(240, 175, 220, 52));
	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP4, Osp::Graphics::Rectangle(240, 250, 220, 52));

	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BACKGROUND, false);
	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP, true);
	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP1, true);
	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP2, true);
	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP3, true);
	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP4, true);


//---------------------- __pButtonViewListItemFormat --------------------------------

	  __pButtonViewListItemFormat = new CustomListItemFormat();
	  __pButtonViewListItemFormat->Construct();

	//  __pButtonViewListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(90, 5, 300, 52));
	  __pButtonViewListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(290, 5, 150, 52));
	  __pButtonViewListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(10, 12, 250, 80), 30, Color::COLOR_WHITE, Color::COLOR_BLUE);
	  __pButtonViewListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(300, 12, 180, 50), 30, Color::COLOR_BLACK, Color::COLOR_BLUE);
	  __pButtonViewListItemFormat->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));


//---------------------- __pStaticTextListItemFormat --------------------------------

	  __pStaticTextListItemFormat = new CustomListItemFormat();
	  __pStaticTextListItemFormat->Construct();

	  __pStaticTextListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(90, 25, 300, 52));
	  __pStaticTextListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(90, 15, 400, 80), 55, Color::COLOR_BLUE, Color::COLOR_BLUE);
	  __pStaticTextListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(90, 30, 400, 80), 30, Color::COLOR_BLACK, Color::COLOR_BLUE);
	  __pStaticTextListItemFormat->AddElement(ID_LIST_CUSTOM, Osp::Graphics::Rectangle(0, 0, 480, 1300));

	return r;
}


result  DialogForm::AddTab(const char *title){
	AppLog("DialogForm::AddTab %s", title);
	result r = E_SUCCESS;
/*	Label* pTempLabel = new Label;
	pTempLabel->Construct(Rectangle(00,YPos,clientArea.width,100), String(title));
	pTempLabel->SetTextColor(Color::COLOR_RED);
	pTempLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(*pTempLabel);
	YPos+=100;
*/
    __pCustomList->AddGroup(String(title), null);
    GroupCount++;
//	CustomListItem* pItem = new CustomListItem();
  //  pItem->Construct(100);
//    pItem->SetItemFormat(*__pCustomListItemFormat2);
  //  pItem->SetElement(ID_LIST_TEXT_TITLE,String(title));
	//    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
	//    pItem->SetCheckBox(ID_LIST_CHECKBOX);

	    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));

 //  __pCustomList->AddItem(GroupCount-1, *pItem, ID_LIST_ITEM);
}

result DialogForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}



void DialogForm::SetPreviousForm(Osp::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void DialogForm::OnActionPerformed(const Osp::Ui::Control & source, int actionId)
{
	AppLog("DialogForm::OnActionPerformed");
	switch(actionId)
	{
	case ID_ACT_CLOSE:
		{
			AppLog("Close button is clicked! \n");
			Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
			//pFrame->SetCurrentForm(*pPreviousForm);
			//pPreviousForm->Draw();
			//pPreviousForm->Show();
			//((badaForm*)pPreviousForm)->pSearchResultInfo=null;
			pPreviousForm->SendUserEvent(0, null);
		}
		break;
	case ID_ACT_UPDATE:
		{
			AppLog("UpdateContent");
			//((shared_ptr<ZLbadaOptionsDialog>)__badaOptionsDialog)->apply();
			__badaOptionsDialog->accept();
			pPreviousForm->SendUserEvent(2, null);
		//	UpdateContent();

		}
		break;
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("BooleanOptionView::ID_BUTTON_CHECKED");
	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("BooleanOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;

	/*case ID_ACT_DELETE:
		{
			DeleteContent();
			break;
		}*/
	default:
		break;
	}
}


void DialogForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("DialogForm::OnUserEventReceivedN");
	//Form* prevForm = pFrame->GetCurrentForm();
	switch(requestId)
	{
	case 0:
		{

			pFrame->SetCurrentForm(*this);
			DeleteOptionPopup();
			//pFrame->RequestRedraw();
			Draw();
			Show();
		//	if (prevForm != null)		{
		//		pFrame->RemoveControl(*prevForm);
		//		}

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

void DialogForm::DeleteOptionPopup(){
	//DeleteCreateCategoryPopup();
	if(__pSpinOptionPopup)
	{
		delete __pSpinOptionPopup;
		__pSpinOptionPopup = null;
	}

	if(__pComboOptionPopup)
	{
		delete __pComboOptionPopup;
		__pComboOptionPopup = null;
	}

	if(__pColorComboOptionPopup)
	{
		delete __pColorComboOptionPopup;
		__pColorComboOptionPopup = null;
	}
}

void DialogForm::ShowColorComboOptionPopup(ColorOptionView* pColorOptionView){
	//DeleteCreateCategoryPopup();

	__pColorComboOptionPopup = new ColorComboOptionPopup();
	//AddControl(*__pComboOptionPopup);
	__pColorComboOptionPopup->Construct(this, pColorOptionView);
	__pColorComboOptionPopup->Show();
}

void DialogForm::ShowSpinOptionPopup(SpinOptionView* pSpinOptionView){
	//DeleteCreateCategoryPopup();

	__pSpinOptionPopup = new SpinOptionPopup();
	//AddControl(*__pComboOptionPopup);
	__pSpinOptionPopup->Construct(this, pSpinOptionView);
	__pSpinOptionPopup->Show();
}


void DialogForm::ShowComboOptionPopup(ComboOptionView* pComboOptionView){
	//DeleteCreateCategoryPopup();

	__pComboOptionPopup = new ComboOptionPopup();
	//AddControl(*__pComboOptionPopup);
	__pComboOptionPopup->Construct(this, pComboOptionView);
	__pComboOptionPopup->Show();
}

//void DialogForm::OnItemStateChanged (const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status)
void  DialogForm::OnItemStateChanged (const Osp::Ui::Control &source, int groupIndex, int itemIndex, int itemId, Osp::Ui::ItemStatus status)
{
	AppLog("DialogForm::OnItemStateChanged 1");
	//OptionListItem* pItem = (OptionListItem*)__pCustomList->GetItemAt(index);
	OptionListItem* pItem = (OptionListItem*)__pCustomList->GetItemAt(groupIndex, itemIndex);
	pItem->OnActionPerformed(ID_BUTTON_CHECKED);
}

//void DialogForm::OnItemStateChanged(const Osp::Ui::Control& source, int index, int itemId, int elementId, Osp::Ui::ItemStatus status)
void  DialogForm::OnItemStateChanged (const Osp::Ui::Control &source, int groupIndex, int itemIndex, int itemId, int elementId, Osp::Ui::ItemStatus status)
{
	AppLog("DialogForm::OnItemStateChanged 2");
	OptionListItem* pItem = (OptionListItem*)__pCustomList->GetItemAt(groupIndex, itemIndex);
	pItem->OnActionPerformed(elementId);

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

