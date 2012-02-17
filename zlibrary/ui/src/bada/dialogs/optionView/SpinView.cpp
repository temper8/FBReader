/*
 * SpinView.cpp
 *
 *  Created on: 14.02.2012
 *      Author: Alex
 */

#include <cctype>


#include <ZLStringUtil.h>
#include <ZLDialogManager.h>
//#include "../util/ZLQtKeyUtil.h"

#include "ZLbadaOptionView.h"
#include "ZLOptionEntry.h"
#include "../ZLbadaDialogContent.h"
#include "../DialogForm.h"
#include "../../image/ZLbadaImageManager.h"

#include <FIo.h>

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Content;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;

void SpinOptionView::_createItem() {
	AppLog("SpinOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());
	myValue = initialValue();
	String str;
	str.Format(25, L"%4d",myValue);
	CustomListItem* pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pSpinViewListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, str);
	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
 //   pItem->SetCheckBox(ID_LIST_CHECKBOX);
    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
	groupIndex = myTab->form()->GroupCount-1;
	itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	AppLog("groupIndex =%d itemIndex=%d",groupIndex,itemIndex);
}

void SpinOptionView::UpdateItem(){
	CustomListItem* pItem = new OptionListItem(this);
	String str;
	str.Format(25, L"%4d",myValue);
	pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pSpinViewListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, str);

	myTab->form()->__pCustomList->SetItemAt(groupIndex,itemIndex, *pItem, ID_LIST_ITEM);
}

void SpinOptionView::_onAccept() const {
	AppLog("SpinOptionView::_onAccept()");
	((ZLSpinOptionEntry&)*myOption).onAccept(myValue);
}

void SpinOptionView::OnAdjustmentValueChanged(const Osp::Ui::Control& source, int adjustment) {
//	AppLog("SpinOptionView::OnAdjustmentValueChanged() %d %d",pSlider->GetValue(), adjustment);
	String str;
//	str.Format(25, L"Value %d ",pSlider->GetValue());
//	myEditField->SetText(str);
//	myEditField->Draw();
//	myEditField->Show();
}


void SpinOptionView::OnActionPerformed( int actionId)
{
	AppLog("SpinOptionView::OnActionPerformed %d",actionId);
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("ComboOptionView::ID_BUTTON_CHECKED");
	    	myTab->form()->ShowSpinOptionPopup(this);

	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("ComboOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;
    default:
        break;
    }
}

SpinOptionPopup::SpinOptionPopup(void){}

SpinOptionPopup::~SpinOptionPopup(void){}

result SpinOptionPopup::Construct(const Osp::Ui::Controls::Form* pParentForm, SpinOptionView* parentSpinOptionView) {
	Osp::Graphics::Rectangle rect = pParentForm->GetBounds();
	AppLog("rect h = %d, w = %d", rect.height, rect.width);
	int height = 350;
	int width = rect.width-10;
	int buttonWidth = 200;
	result r = Popup::Construct(true, Dimension(width,height));
	if(IsFailed(r))
		return r;

	__parentSpinOptionView = parentSpinOptionView;

	SetTitleText(String(parentSpinOptionView->title().c_str()));
	__pParentForm = const_cast<Form*>(pParentForm);

	if(__pParentForm == null)
		return E_FAILURE;

	Button* pCreateButton = new Button();
	pCreateButton->Construct(Rectangle(20, height - 180, buttonWidth, 70), L"OK");
	AddControl(*pCreateButton);
	pCreateButton->SetActionId(ID_BUTTON_CREATE);
	pCreateButton->AddActionEventListener(*this);

	Button* pCancelButton = new Button();
	//pCancelButton->Construct(Rectangle(230, 550, 200, 70), L"Cancel");
	pCancelButton->Construct(Rectangle(width/2, height-180, buttonWidth, 70), L"Cancel");
	AddControl(*pCancelButton);
	pCancelButton->SetActionId(ID_BUTTON_CANCEL);
	pCancelButton->AddActionEventListener(*this);

    // Creates a Slider.
	Slider* pSlider = new Slider();
	AppLog("minValue = %d, maxValue = %d", parentSpinOptionView->minValue(), parentSpinOptionView->maxValue());
	int minValue = parentSpinOptionView->minValue();
	int maxValue = parentSpinOptionView->maxValue();
	if (maxValue>500) maxValue = 500;
   // pSlider->Construct(Rectangle(00, 0, width, 100), BACKGROUND_STYLE_DEFAULT, false, parentSpinOptionView->minValue(), parentSpinOptionView->maxValue());
    pSlider->Construct(Rectangle(0, 25, width, 100), BACKGROUND_STYLE_NONE, false, minValue, maxValue);
	pSlider->SetValue(__parentSpinOptionView->myValue);
    pSlider->AddAdjustmentEventListener(*this);

    //Add a Slider to the Form.
    AddControl(*pSlider);

	return E_SUCCESS;
}

void SpinOptionPopup::OnAdjustmentValueChanged(const Osp::Ui::Control& source, int adjustment){
	tmpValue = adjustment;
}

void SpinOptionPopup::OnActionPerformed(const Control& source, int actionId)
{
	switch(actionId)
	{
		case ID_BUTTON_CREATE:
			//if(CreateCategory() == true)
			__parentSpinOptionView->myValue = tmpValue;
			__parentSpinOptionView->UpdateItem();
			__pParentForm->SendUserEvent(0, null);
			break;
		case ID_BUTTON_CANCEL:
			__pParentForm->SendUserEvent(0, null);
			break;
		default:
			break;
	}
}

