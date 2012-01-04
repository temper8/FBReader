/*
 * DialogForm.cpp
 *
 *  Created on: 24.11.2011
 *      Author: Alex
 */

#include "DialogForm.h"
#include "ZLbadaOptionView.h"
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

bool DialogForm::Initialize(const char *title)
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
		Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);
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
}

DialogForm::~DialogForm() {
	// TODO Auto-generated destructor stub
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
	AppLog("DialogForm::OnInitializing \n");

	   // Creates CustomList


  //  __pCustomList = new CustomList();
	  __pCustomList = new GroupedList();
	  GroupCount = 0;
		//__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_NORMAL);
	__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_MARK);
//	__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_MARK_WITH_DIVIDER);
	//__pCustomList->AddCustomItemEventListener(*this);
	__pCustomList->AddGroupedItemEventListener(*this);
	  AddControl(*__pCustomList);

	// Creates an item format of the CustomList
	__pCustomListItemFormat = new CustomListItemFormat();
	__pCustomListItemFormat->Construct();

	__pCustomListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(15, 5, 400, 80), 25, Color::COLOR_BLUE, Color::COLOR_BLUE);
	__pCustomListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(30, 45, 400, 80), 30);
	__pCustomListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	__pCustomListItemFormat->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));
	  AddControl(*__pCustomList);

		// Creates an item format of the CustomList
	__pCustomListItemFormat1 = new CustomListItemFormat();
	__pCustomListItemFormat1->Construct();

	__pCustomListItemFormat1->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(20, 20, 400, 80), 30);
	__pCustomListItemFormat1->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(20, 55, 400, 80), 20);
	__pCustomListItemFormat1->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	__pCustomListItemFormat1->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));
	__pCustomListItemFormat1->SetElementEventEnabled(ID_LIST_CHECKBOX, true);

	__pCustomListItemFormat2 = new CustomListItemFormat();
	__pCustomListItemFormat2->Construct();

	__pCustomListItemFormat2->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(90, 15, 300, 80), 30, Color::COLOR_RED, Color::COLOR_RED);
	__pCustomListItemFormat2->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(90, 55, 300, 80), 20);
	__pCustomListItemFormat2->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(10, 5, 70, 90));
	__pCustomListItemFormat2->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 15, 50, 50));
//	__pCustomListItemFormat2->SetElementEventEnabled(ID_LIST_CHECKBOX, true);


	__pColorListItemFormat = new CustomListItemFormat();
	__pColorListItemFormat->Construct();

	__pColorListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Osp::Graphics::Rectangle(15, 10, 300, 80), 30, Color::COLOR_RED, Color::COLOR_RED);
	__pColorListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Osp::Graphics::Rectangle(105, 55, 300, 80), 30);
	__pColorListItemFormat->AddElement(ID_LIST_BITMAP, Osp::Graphics::Rectangle(15, 45, 80, 40));
	__pColorListItemFormat->AddElement(ID_LIST_CHECKBOX, Osp::Graphics::Rectangle(420, 10, 90, 90));
//	__pColorListItemFormat->SetElementEventEnabled(ID_LIST_TEXT_TITLE, true);
//	__pColorListItemFormat->SetElementEventEnabled(ID_LIST_TEXT_SUBTITLE, true);
	__pColorListItemFormat->SetElementEventEnabled(ID_LIST_CHECKBOX, true);



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
	CustomListItem* pItem = new CustomListItem();
    pItem->Construct(100);
    pItem->SetItemFormat(*__pCustomListItemFormat2);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String(title));
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
			__badaOptionsDialog->apply();
			pPreviousForm->SendUserEvent(0, null);
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
			DeleteComboOptionPopup();
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

void DialogForm::DeleteComboOptionPopup(){
	//DeleteCreateCategoryPopup();
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
	pItem->OnActionPerformed(ID_BUTTON_CHECKED);

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

