/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <cctype>


#include <ZLStringUtil.h>
#include <ZLDialogManager.h>
//#include "../util/ZLQtKeyUtil.h"

#include "ZLbadaOptionView.h"
#include "ZLOptionEntry.h"
#include "ZLbadaDialogContent.h"
#include "DialogForm.h"

#include <FIo.h>

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Content;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;

void ZLbadaOptionView::_show() {
	AppLog("BooleanOptionView::_show()");
//	for (std::vector<QWidget*>::iterator it = myWidgets.begin(); it != myWidgets.end(); ++it) {
//		(*it)->show();
//	}
}

void ZLbadaOptionView::_hide() {
	AppLog("BooleanOptionView::_hide()");
//	for (std::vector<QWidget*>::iterator it = myWidgets.begin(); it != myWidgets.end(); ++it) {
//		(*it)->hide();
//	}
}

void BooleanOptionView::_createItem() {
	AppLog("BooleanOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());

	OptionListItem* pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pCustomListItemFormat1);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
	//    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
    pItem->SetCheckBox(ID_LIST_CHECKBOX);
  //  pItem->SetValue(50);
    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
	int groupIndex = myTab->form()->GroupCount-1;
	int itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	//myTab->form()->__pCustomList->GetLastCheckedItemIndex( groupIndex, itemIndex);
	checkState = ((ZLBooleanOptionEntry&)*myOption).initialState();
	myTab->form()->__pCustomList->SetItemChecked(groupIndex,itemIndex,checkState);
	AppLog("BooleanOptionView:: %d, %d",groupIndex,itemIndex );
	/*myCheckBox = new QCheckBox(::qtString(ZLOptionView::name()), myTab->widget());
	myCheckBox->setChecked(((ZLBooleanOptionEntry&)*myOption).initialState());
	myWidgets.push_back(myCheckBox);
	myTab->addItem(myCheckBox, myRow, myFromColumn, myToColumn);
	connect(myCheckBox, SIGNAL(toggled(bool)), this, SLOT(onStateChanged(bool)));*/
}


void BooleanOptionView::_setActive(bool active) {
	// myCheckButton->SetSelected(active);
}

void BooleanOptionView::_onAccept() const {
	AppLog("BooleanOptionView::_onAccept");
	((ZLBooleanOptionEntry&)*myOption).onAccept(checkState);
}

void BooleanOptionView::onStateChanged(bool state) {
	AppLog("BooleanOptionView::onStateChanged()");
	checkState = state;
	((ZLBooleanOptionEntry&)*myOption).onStateChanged(state);
}

void BooleanOptionView::OnActionPerformed(int actionId)
{
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("BooleanOptionView::ID_BUTTON_CHECKED");
	    	onStateChanged(!checkState);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("BooleanOptionView::ID_BUTTON_UNCHECKED");
	    	onStateChanged(false);
	        // Todo:
	        break;
    default:
        break;
    }
}


void Boolean3OptionView::_createItem() {
	AppLog("Boolean3OptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());

	OptionListItem* pItem = new OptionListItem(this);
	    pItem->Construct(100);
	    pItem->SetItemFormat(*myTab->form()->__pCustomListItemFormat1);
	    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
		//    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
		//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
	    pItem->SetCheckBox(ID_LIST_CHECKBOX);
	    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
		myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
		AppLog("BooleanOptionView::_createItem() end");

 /*   myCheckButton = new CheckButton();
    myCheckButton->Construct(Rectangle(5, myTab->form()->YPos, myTab->form()->clientArea.width-10, 80),
	        CHECK_BUTTON_STYLE_MARK, BACKGROUND_STYLE_DEFAULT,
	        false, ZLOptionView::name().c_str());

	bool state = false;
	switch (((ZLBoolean3OptionEntry&)*myOption).initialState()) {
		case B3_FALSE:
			state = false;
			break;
		case B3_TRUE:
			state = true;
			break;
		case B3_UNDEFINED:
			state = false;
			break;
	}
    myCheckButton->SetSelected(state);
	myTab->form()->pScrollPanel->AddControl(*myCheckButton);
	myTab->form()->YPos+=120;
*/
	//myWidgets.push_back(myCheckBox);
	//myTab->addItem(myCheckBox, myRow, myFromColumn, myToColumn);
	//connect(myCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
}

void Boolean3OptionView::_setActive(bool active) {
	// myCheckButton->SetSelected(active);
}

void Boolean3OptionView::_onAccept() const {
	AppLog("Boolean3OptionView::_onAccept");
	/*
	ZLBoolean3 value = B3_UNDEFINED;
	switch (myCheckBox->checkState()) {
		case Qt::Checked:
			value = B3_TRUE;
			break;
		case Qt::Unchecked:
			value = B3_FALSE;
			break;
		case Qt::PartiallyChecked:
			value = B3_UNDEFINED;
			break;
	}
	((ZLBoolean3OptionEntry&)*myOption).onAccept(value);
	*/
}

void Boolean3OptionView::OnActionPerformed(int actionId)
{
    switch (actionId)
    {
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
    default:
        break;
    }
}
/*
void Boolean3OptionView::onStateChanged(int state) const {

	ZLBoolean3 value = B3_UNDEFINED;
	switch (state) {
		case Qt::Checked:
			value = B3_TRUE;
			break;
		case Qt::Unchecked:
			value = B3_FALSE;
			break;
		case Qt::PartiallyChecked:
			value = B3_UNDEFINED;
			break;
	}
	((ZLBoolean3OptionEntry&)*myOption).onStateChanged(value);

}*/

void ChoiceOptionView::_createItem() {
	AppLog(" ChoiceOptionView::_createItem()");

	myTab->form()->__pCustomList->AddGroup(String(ZLOptionView::name().c_str()), null);
	myTab->form()->GroupCount++;

	for (int i = 0; i < ((ZLChoiceOptionEntry&)*myOption).choiceNumber(); ++i) {
		AppLog(" i = %d",i);
		AppLog("choice title = %s",((ZLChoiceOptionEntry&)*myOption).text(i).c_str());
		OptionListItem* pItem = new OptionListItem(this);
	    pItem->Construct(100);
	    pItem->SetItemFormat(*myTab->form()->__pCustomListItemFormat1);
	    pItem->SetElement(ID_LIST_TEXT_TITLE,String(((ZLChoiceOptionEntry&)*myOption).text(i).c_str()));
		//    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
		//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
	    pItem->SetCheckBox(ID_LIST_CHECKBOX);
	    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
		myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);

	}
/*
	myGroupBox = new QGroupBox(::qtString(ZLOptionView::name()));
	myWidgets.push_back(myGroupBox);
	QVBoxLayout *layout = new QVBoxLayout(myGroupBox);
	myButtons = new QRadioButton*[((ZLChoiceOptionEntry&)*myOption).choiceNumber()];
	for (int i = 0; i < ((ZLChoiceOptionEntry&)*myOption).choiceNumber(); ++i) {
		myButtons[i] = new QRadioButton(myGroupBox);
		myButtons[i]->setText(::qtString(((ZLChoiceOptionEntry&)*myOption).text(i)));
		layout->addWidget(myButtons[i]);
	}
	myButtons[((ZLChoiceOptionEntry&)*myOption).initialCheckedIndex()]->setChecked(true);
	myTab->addItem(myGroupBox, myRow, myFromColumn, myToColumn);
	*/
}

void ChoiceOptionView::_setActive(bool active) {
//	myGroupBox->setEnabled(active);
}

void ChoiceOptionView::_onAccept() const {
/*	for (int i = 0; i < ((ZLChoiceOptionEntry&)*myOption).choiceNumber(); ++i) {
		if (myButtons[i]->isChecked()) {
			((ZLChoiceOptionEntry&)*myOption).onAccept(i);
			return;
		}
	}
*/
}

void ChoiceOptionView::OnActionPerformed(int actionId){
	AppLog("ChoiceOptionView::OnActionPerformed");
}

void ComboOptionView::_createItem() {
	AppLog("ComboOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());

	pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pCustomListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));

	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
 //   pItem->SetCheckBox(ID_LIST_CHECKBOX);
    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);


	/*
	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*myOption;
	QLabel *label = 0;
	const std::string &name = ZLOptionView::name();
	if (!name.empty()) {
		label = new QLabel(::qtString(name), myTab->widget());
	}
	myComboBox = new QComboBox(myTab->widget());
	myComboBox->setEditable(comboOption.isEditable());

	if (label != 0) {
		myWidgets.push_back(label);
	}
	myWidgets.push_back(myComboBox);

	connect(myComboBox, SIGNAL(activated(int)), this, SLOT(onValueSelected(int)));
	connect(myComboBox, SIGNAL(editTextChanged(const QString&)), this, SLOT(onValueEdited(const QString&)));

	if (label != 0) {
		int width = myToColumn - myFromColumn + 1;
		myTab->addItem(label, myRow, myFromColumn, myFromColumn + width / 2 - 1);
		myTab->addItem(myComboBox, myRow, myFromColumn + width / 2, myToColumn);
	} else {
		myTab->addItem(myComboBox, myRow, myFromColumn, myToColumn);
	}
*/
	reset();
}

void ComboOptionView::reset() {

	comboValue = ((ZLComboOptionEntry&)*myOption).initialValue();
	AppLog("ComboOptionView::reset initialValue = %s",comboValue.c_str());
	//const char *text = comboValue.c_str();
	//myEditField->SetText(String(text));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(comboValue.c_str()));
/*
	if (myComboBox == 0) {
		return;
	}

	const int count = myComboBox->count();
	for (int i = 0; i < count; ++i) {
		myComboBox->removeItem(0);
	}

	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*myOption;
	const std::vector<std::string> &values = comboOption.values();
	const std::string &initial = comboOption.initialValue();
	int selectedIndex = -1;
	int index = 0;
	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it, ++index) {
		myComboBox->insertItem(it - values.begin(), ::qtString(*it));
		if (*it == initial) {
			selectedIndex = index;
		}
	}
	if (selectedIndex >= 0) {
		myComboBox->setCurrentIndex(selectedIndex);
	}
	*/
}

void ComboOptionView::_setActive(bool active) {
//	myComboBox->setEnabled(active);
}

void ComboOptionView::_onAccept() const {
	AppLog("ComboOptionView::_onAccept %s",comboValue.c_str());
	((ZLComboOptionEntry&)*myOption).onAccept(comboValue.c_str());
}

void ComboOptionView::onValueSelected(int index) {
 	AppLog("ComboOptionView::onValueSelected %d", index);
	ZLComboOptionEntry &o = (ZLComboOptionEntry&)*myOption;
	if ((index >= 0) && (index < (int)o.values().size())) {
		o.onValueSelected(index);
	}
}

//void ComboOptionView::onValueEdited(const QString &value) {
//	ZLComboOptionEntry &o = (ZLComboOptionEntry&)*myOption;
//	if (o.useOnValueEdited()) {
//		o.onValueEdited((const char*)value.toUtf8());
//	}
//}

void ComboOptionView::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status){
	onValueSelected(index);
	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*this->option();
	const std::vector<std::string> &values = comboOption.values();
	comboValue = values[index];
	const char *text = (values[index].c_str());
//	myEditField->SetText(String(text));
	AppLog("pItem->SetElement(ID_LIST_TEXT_SUBTITLE %s", text);
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(text));
	AppLog("myTab->form()->SendUserEvent");
	myTab->form()->SendUserEvent(0, null);
}


//void ComboOptionView::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs){
	//DeleteComboOptionPopup();
//}

void ComboOptionView::OnActionPerformed( int actionId)
{
	AppLog("ComboOptionView::OnActionPerformed %d",actionId);
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("ComboOptionView::ID_BUTTON_CHECKED");
	    	myTab->form()->ShowComboOptionPopup(this);
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

void ComboOptionView::OnActionPerformed(const Control& source, int actionId)
{
	AppLog("ComboOptionView::OnActionPerformed %d",actionId);
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("ComboOptionView::ID_BUTTON_CHECKED");
	    	myTab->form()->ShowComboOptionPopup(this);
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


ComboOptionPopup::ComboOptionPopup(void){}

ComboOptionPopup::~ComboOptionPopup(void){}

result ComboOptionPopup::Construct(const Osp::Ui::Controls::Form* pParentForm, ComboOptionView* parentComboOptionView) {
	result r = Popup::Construct(true, Dimension(465,750));
	if(IsFailed(r))
		return r;
	__parentComboOptionView = parentComboOptionView;

	SetTitleText(String(parentComboOptionView->title().c_str()));
	__pParentForm = const_cast<Form*>(pParentForm);

	if(__pParentForm == null)
		return E_FAILURE;

/*	Button* pCreateButton = new Button();
	pCreateButton->Construct(Rectangle(20, 550, 200, 70), L"Create");
	AddControl(*pCreateButton);
	pCreateButton->SetActionId(ID_BUTTON_CREATE);
	pCreateButton->AddActionEventListener(*this);
*/
	Button* pCancelButton = new Button();
	//pCancelButton->Construct(Rectangle(230, 550, 200, 70), L"Cancel");
	pCancelButton->Construct(Rectangle(125, 570, 200, 70), L"Cancel");
	AddControl(*pCancelButton);
	pCancelButton->SetActionId(ID_BUTTON_CANCEL);
	pCancelButton->AddActionEventListener(*this);


	__pComboList = new List();
	Osp::Graphics::Rectangle rect = GetBounds();
	__pComboList->Construct(Rectangle(20, 10, 480, 520), LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 90, 0, 400, 0);
		//pList->Construct(rect, LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 100, 0, rect.width, 0);
	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*__parentComboOptionView->option();
	const std::vector<std::string> &values = comboOption.values();
	const std::string &initial = comboOption.initialValue();
	int selectedIndex = -1;
	int index = 0;

	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it, ++index) {
		String itemText((*it).c_str());
		__pComboList->AddItem(&itemText, null, null, null );
		if (*it == initial) {
			selectedIndex = index;
		}
	}
	if (selectedIndex >= 0) {
		//myComboBox->setCurrentIndex(selectedIndex);
	}
	__pComboList->AddItemEventListener(*__parentComboOptionView);
    AddControl(*__pComboList);

	return E_SUCCESS;
}

void ComboOptionPopup::OnActionPerformed(const Control& source, int actionId)
{
	switch(actionId)
	{
		case ID_BUTTON_CREATE:
			//if(CreateCategory() == true)
			__pParentForm->SendUserEvent(0, null);
			break;
		case ID_BUTTON_CANCEL:
			__pParentForm->SendUserEvent(0, null);
			break;
		default:
			break;
	}
}





void SpinOptionView::_createItem() {
	AppLog("SpinOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());
	ZLSpinOptionEntry &entry = (ZLSpinOptionEntry&)*myOption;
	String str;
	str.Format(25, L"Value %d ",entry.initialValue());
	/*	myEditField = new EditField();
	myEditField->Construct(Rectangle(5, myTab->form()->YPos, myTab->form()->clientArea.width-10, 80),
			EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN,   true, 100, GROUP_STYLE_SINGLE );
	myEditField->SetGuideText("GuideText1");
	myEditField->SetKeypadEnabled(false);
	//myEditField->AddTouchEventListener(*this);
	//myEditField->AddActionEventListener(*this);
  //  const char *titleText = ZLOptionView::name().c_str();
	//mySpinBox->setValue(entry.initialValue());

	myEditField->SetTitleText(String(ZLOptionView::name().c_str()));

	myEditField->SetText(str);
	myTab->form()->pScrollPanel->AddControl(*myEditField);
	myTab->form()->YPos+=120;

	// Creates a Slider.
	pSlider = new Slider();
	pSlider->Construct(Rectangle(5, myTab->form()->YPos, myTab->form()->clientArea.width-10, 80),
						BACKGROUND_STYLE_DEFAULT, false, entry.minValue(), entry.maxValue());

    pSlider->SetValue(entry.initialValue());
	pSlider->AddAdjustmentEventListener(*this);

	    //Add a Slider to the Form.
	myTab->form()->pScrollPanel->AddControl(*pSlider);
	myTab->form()->YPos+=120;
*/
	pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pCustomListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, str);
	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
 //   pItem->SetCheckBox(ID_LIST_CHECKBOX);
    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);


	/*

	QLabel *label = new QLabel(::qtString(ZLOptionView::name()), myTab->widget());
	mySpinBox = new QSpinBox(myTab->widget());

	myWidgets.push_back(label);
	myWidgets.push_back(mySpinBox);

	mySpinBox->setMinimum(entry.minValue());
	mySpinBox->setMaximum(entry.maxValue());
	mySpinBox->setSingleStep(entry.step());
	mySpinBox->setValue(entry.initialValue());
	int width = myToColumn - myFromColumn + 1;
	myTab->addItem(label, myRow, myFromColumn, myFromColumn + width / 2 - 1);
	myTab->addItem(mySpinBox, myRow, myFromColumn + width / 2, myToColumn);
	*/
}

void SpinOptionView::_onAccept() const {
	AppLog("SpinOptionView::_onAccept()");
	//((ZLSpinOptionEntry&)*myOption).onAccept(mySpinBox->value());
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
	    //	myTab->form()->ShowComboOptionPopup(this);
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

void StringOptionView::_createItem() {
	AppLog("StringOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());
	//myTab->form();
/*	myEditField = new EditField();
	myEditField->Construct(Rectangle(5, myTab->form()->YPos, myTab->form()->clientArea.width-10, 80),
    EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN,
    true, 100, GROUP_STYLE_SINGLE );
	myEditField->SetGuideText("GuideText1");
  //  const char *titleText = ZLOptionView::name().c_str();
	myEditField->SetTitleText(String(ZLOptionView::name().c_str()));
	//myEditField->SetText("Просто Text1");
	myTab->form()->pScrollPanel->AddControl(*myEditField);

	myTab->form()->YPos+=120;
*/
	pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pCustomListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));

	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
 //   pItem->SetCheckBox(ID_LIST_CHECKBOX);
    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);




/*	myLineEdit = new QLineEdit(myTab->widget());
	myLineEdit->setEchoMode(myPasswordMode ? QLineEdit::Password : QLineEdit::Normal);
	myWidgets.push_back(myLineEdit);
	connect(myLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onValueEdited(const QString&)));
	if (!ZLOptionView::name().empty()) {
		QLabel *label = new QLabel(::qtString(ZLOptionView::name()), myTab->widget());
		myWidgets.push_back(label);
		int width = myToColumn - myFromColumn + 1;
		myTab->addItem(label, myRow, myFromColumn, myFromColumn + width / 2 - 1);
		myTab->addItem(myLineEdit, myRow, myFromColumn + width / 2, myToColumn);
	} else {
		myTab->addItem(myLineEdit, myRow, myFromColumn, myToColumn);
	}*/
	reset();
}

void StringOptionView::_setActive(bool active) {
//	myLineEdit->setReadOnly(!active);
}

void StringOptionView::_onAccept() const {
	AppLog("StringOptionView::_onAccept");
//	((ZLStringOptionEntry&)*myOption).onAccept((const char*)myLineEdit->text().toUtf8());
}

void StringOptionView::reset() {
	AppLog("StringOptionView::reset initialValue = %s",(((ZLStringOptionEntry&)*myOption).initialValue()).c_str());
	const char *text = (((ZLStringOptionEntry&)*myOption).initialValue()).c_str();
//	myEditField->SetText(String(text));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(text));
/*	if (myLineEdit == 0) {
		return;
	}
	myLineEdit->setText(::qtString(((ZLStringOptionEntry&)*myOption).initialValue()));
	myLineEdit->cursorForward(false, -myLineEdit->text().length());
*/}

void StringOptionView::OnActionPerformed( int actionId)
{
	AppLog("StringOptionView::OnActionPerformed %d",actionId);
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("ComboOptionView::ID_BUTTON_CHECKED");
	    	//myTab->form()->ShowComboOptionPopup(this);
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
//void StringOptionView::onValueEdited(const QString &value) {
//	ZLStringOptionEntry &o = (ZLStringOptionEntry&)*myOption;
//	if (o.useOnValueEdited()) {
//		o.onValueEdited((const char*)value.toUtf8());
//	}
//}
/*
class KeyLineEdit : public QLineEdit {

public:
	KeyLineEdit(KeyOptionView &keyView, QWidget *parent);

protected:
	void focusInEvent(QFocusEvent*);
	void focusOutEvent(QFocusEvent*);
	void keyPressEvent(QKeyEvent *keyEvent);

private:
	KeyOptionView &myKeyView;
};

KeyLineEdit::KeyLineEdit(KeyOptionView &keyView, QWidget *parent) : QLineEdit(parent), myKeyView(keyView) {
	focusOutEvent(0);
}

void KeyLineEdit::keyPressEvent(QKeyEvent *keyEvent) {
	std::string keyText = ZLQtKeyUtil::keyName(keyEvent);
	setText(keyText.c_str());
	if (!keyText.empty()) {
		myKeyView.myCurrentKey = keyText;
		myKeyView.myComboBox->setCurrentIndex(((ZLKeyOptionEntry&)*myKeyView.myOption).actionIndex(keyText));
		myKeyView.myComboBox->show();
	}
	((ZLKeyOptionEntry&)*myKeyView.myOption).onKeySelected(keyText);
}

void KeyLineEdit::focusInEvent(QFocusEvent*) {
	grabKeyboard();
}

void KeyLineEdit::focusOutEvent(QFocusEvent*) {
	releaseKeyboard();
}

void KeyOptionView::_createItem() {
	QWidget *widget = new QWidget(myTab->widget());
	QGridLayout *layout = new QGridLayout(widget);

	QLabel *label = new QLabel(widget);
	label->setText(::qtString(ZLResource::resource("keyOptionView")["actionFor"].value()));
	layout->addWidget(label, 0, 0);

	myKeyEditor = new KeyLineEdit(*this, widget);
	layout->addWidget(myKeyEditor, 0, 1);

	myWidgets.push_back(widget);
	myWidgets.push_back(label);
	myWidgets.push_back(myKeyEditor);

	myComboBox = new QComboBox(widget);
	const std::vector<std::string> &actions = ((ZLKeyOptionEntry&)*myOption).actionNames();
	for (std::vector<std::string>::const_iterator it = actions.begin(); it != actions.end(); ++it) {
		myComboBox->insertItem(it - actions.begin(), ::qtString(*it));
	}
	connect(myComboBox, SIGNAL(activated(int)), this, SLOT(onValueChanged(int)));
	layout->addWidget(myComboBox, 1, 0, 1, 2);
	myTab->addItem(widget, myRow, myFromColumn, myToColumn);
}

void KeyOptionView::reset() {
	if (myKeyEditor == 0) {
		return;
	}
	myCurrentKey.erase();
	myKeyEditor->setText("");
	((ZLKeyOptionEntry&)*myOption).onKeySelected(myCurrentKey);
	myComboBox->hide();
}

void KeyOptionView::_show() {
	ZLQtOptionView::_show();
	if (!myCurrentKey.empty()) {
		myComboBox->show();
	} else {
		myComboBox->hide();
	}
}

void KeyOptionView::_hide() {
	ZLQtOptionView::_hide();
	myComboBox->hide();
	myCurrentKey.erase();
	myKeyEditor->setText("");
	((ZLKeyOptionEntry&)*myOption).onKeySelected(myCurrentKey);
}

void KeyOptionView::_onAccept() const {
	((ZLKeyOptionEntry&)*myOption).onAccept();
}

void KeyOptionView::onValueChanged(int index) {
	if (!myCurrentKey.empty()) {
		((ZLKeyOptionEntry&)*myOption).onValueChanged(myCurrentKey, index);
	}
}

QSlider *ColorOptionView::createColorSlider(QGridLayout *layout, int index, const ZLResource &resource, int value) {
	layout->addWidget(new QLabel(::qtString(resource.value()), layout->parentWidget()), index, 0);
	QSlider *slider = new QSlider(Qt::Horizontal, layout->parentWidget());
	layout->addWidget(slider, index, 1);
	slider->setMinimum(0);
	slider->setMaximum(255);
	slider->setSingleStep(5);
	slider->setTracking(true);
	slider->setValue(value);
	connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(onSliderMove(int)));
	return slider;
}
*/

void ColorOptionView::addColor(const std::string &name, ZLColor color) {
//	ZLUnicodeUtil::Ucs2String txt;
//	::createNTWCHARString(txt, name);
	AppLog("ComboOptionView::addColor() name = %s",name.c_str());
	ourStrings.push_back(name);
	ourColors.push_back(color);
}
std::vector<std::string> ColorOptionView::ourStrings;
std::vector<ZLColor> ColorOptionView::ourColors;

void ColorOptionView::initVectors() {
	if (ourStrings.empty()) {
		const ZLResource &resource = ZLResource::resource(ZLDialogManager::COLOR_KEY);
		addColor(resource["black"].value(), ZLColor(0, 0, 0));
		addColor(resource["white"].value(), ZLColor(255, 255, 255));
		addColor(resource["maroon"].value(), ZLColor(128, 0, 0));
		addColor(resource["green"].value(), ZLColor(0, 128, 0));
		addColor(resource["olive"].value(), ZLColor(128, 128, 0));
		addColor(resource["navy"].value(), ZLColor(0, 0, 128));
		addColor(resource["purple"].value(), ZLColor(128, 0, 128));
		addColor(resource["teal"].value(), ZLColor(0, 128, 128));
		addColor(resource["silver"].value(), ZLColor(192, 192, 192));
		addColor(resource["gray"].value(), ZLColor(128, 128, 128));
		addColor(resource["red"].value(), ZLColor(255, 0, 0));
		addColor(resource["lime"].value(), ZLColor(0, 255, 0));
		addColor(resource["yellow"].value(), ZLColor(255, 255, 0));
		addColor(resource["blue"].value(), ZLColor(0, 0, 255));
		addColor(resource["magenta"].value(), ZLColor(255, 0, 255));
		addColor(resource["cyan"].value(), ZLColor(0, 255, 255));
	}
}

void ColorOptionView::_createItem() {
	AppLog("ComboOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());
	initVectors();
	pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pColorListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
    const ZLColor &color = ((ZLColorOptionEntry&)*myOption).color();
    Bitmap BitmapNormal;
    Osp::Graphics::Canvas canvas;
    canvas.Construct(Rectangle(0,0,10,10));
    canvas.FillRectangle(Color(color.Red,color.Green,color.Blue),Rectangle(0,0,10,10));
    BitmapNormal.Construct(canvas,Rectangle(0,0,10,10));
//	const char *text = (((ZLColorOptionEntry&)*myOption).initialValue()).c_str();
	//myEditField->SetText(String(text));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String("color"));

	pItem->SetElement(ID_LIST_BITMAP, BitmapNormal, &BitmapNormal);
  //  pItem->SetCheckBox(ID_LIST_CHECKBOX);
	pItem->SetElement(ID_LIST_CHECKBOX, BitmapNormal, &BitmapNormal);
    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);



	/*
	QWidget *widget = new QWidget(myTab->widget());
	myWidgets.push_back(widget);
	QGridLayout *layout = new QGridLayout(widget);
	const ZLColor &color = ((ZLColorOptionEntry&)*myOption).color();
	const ZLResource &resource = ZLResource::resource(ZLDialogManager::COLOR_KEY);
	myRSlider = createColorSlider(layout, 0, resource["red"], color.Red);
	myGSlider = createColorSlider(layout, 1, resource["green"], color.Green);
	myBSlider = createColorSlider(layout, 2, resource["blue"], color.Blue);

	myColorBar = new QLabel("                  ", widget);
	QPalette palette = myColorBar->palette();
	palette.setColor(myColorBar->backgroundRole(), QColor(color.Red, color.Green, color.Blue));
	myColorBar->setPalette(palette);
	myColorBar->setFrameStyle(QFrame::Panel | QFrame::Plain);
	layout->addWidget(myColorBar, 0, 2, 3, 1);
	myColorBar->setAutoFillBackground(true);

	myTab->addItem(widget, myRow, myFromColumn, myToColumn);
	*/
}

void ColorOptionView::reset() {
	/*
	if (myColorBar == 0) {
		return;
	}
	ZLColorOptionEntry &colorEntry = (ZLColorOptionEntry&)*myOption;
	colorEntry.onReset(ZLColor(myRSlider->value(), myGSlider->value(), myBSlider->value()));
	const ZLColor &color = colorEntry.color();
	myRSlider->setValue(color.Red);
	myGSlider->setValue(color.Green);
	myBSlider->setValue(color.Blue);
	QPalette palette = myColorBar->palette();
	palette.setColor(myColorBar->backgroundRole(), QColor(color.Red, color.Green, color.Blue));
	myColorBar->setPalette(palette);
	*/
}
/*
void ColorOptionView::onSliderMove(int) {
	QPalette palette = myColorBar->palette();
	palette.setColor(myColorBar->backgroundRole(), QColor(myRSlider->value(), myGSlider->value(), myBSlider->value()));
	myColorBar->setPalette(palette);
}
*/
void ColorOptionView::_onAccept() const {
	//((ZLColorOptionEntry&)*myOption).onAccept(ZLColor(myRSlider->value(), myGSlider->value(), myBSlider->value()));
}

void ColorOptionView::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status){
//	onValueSelected(index);
//	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*this->option();
//	const std::vector<std::string> &values = comboOption.values();
//	const char *text = (values[index].c_str());
//	myEditField->SetText(String(text));
//	AppLog("pItem->SetElement(ID_LIST_TEXT_SUBTITLE %s", text);
//	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(text));
	AppLog("myTab->form()->SendUserEvent");
	myTab->form()->SendUserEvent(0, null);
}

void ColorOptionView::OnActionPerformed(int actionId)
{
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("BooleanOptionView::ID_BUTTON_CHECKED");
	    	myTab->form()->ShowColorComboOptionPopup(this);
	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("BooleanOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;
    default:
        break;
    }
}


ColorComboOptionPopup::ColorComboOptionPopup(void){}

ColorComboOptionPopup::~ColorComboOptionPopup(void){}

result ColorComboOptionPopup::Construct(const Osp::Ui::Controls::Form* pParentForm,  ColorOptionView* parentColorOptionView) {
	result r = Popup::Construct(true, Dimension(465,750));
	if(IsFailed(r))
		return r;
	__parentColorOptionView = parentColorOptionView;

	//SetTitleText(String(parentColorOptionView->title().c_str()));
	SetTitleText(String("Select color"));
	__pParentForm = const_cast<Form*>(pParentForm);

	if(__pParentForm == null)
		return E_FAILURE;

	Button* pCreateButton = new Button();
	pCreateButton->Construct(Rectangle(20, 580, 200, 70), L"Select");
	AddControl(*pCreateButton);
	pCreateButton->SetActionId(ID_BUTTON_CREATE);
	pCreateButton->AddActionEventListener(*this);


	Button* pCancelButton = new Button();
	pCancelButton->Construct(Rectangle(230, 580, 200, 70), L"Cancel");
	AddControl(*pCancelButton);
	pCancelButton->SetActionId(ID_BUTTON_CANCEL);
	pCancelButton->AddActionEventListener(*this);

	   // Creates a ColorPicker.
	ColorPicker* pColorPicker = new ColorPicker();
	pColorPicker->Construct(Point(0,0));

	// Adds a ColorChangeEvent listener.
	// pColorPicker->AddColorChangeEventListener(*this);

	 // Adds a ColorPicker to the Form.
	 AddControl(*pColorPicker);


	__pComboList = new List();
	Osp::Graphics::Rectangle rect = GetBounds();
	__pComboList->Construct(Rectangle(20, 310, 480, 250), LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_IMAGE_TEXT, 45, 0, 100, 300);
		//pList->Construct(rect, LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 100, 0, rect.width, 0);
	//const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*__parentColorOptionView->option();
//	const std::vector<std::string> &values = comboOption.values();
//	const std::string &initial = comboOption.initialValue();
	int selectedIndex = -1;
	int index = 0;
	String itemText("text");

	for (int i = 0; i<__parentColorOptionView->ourStrings.size(); i++)
	{
	    const ZLColor &color = __parentColorOptionView->ourColors[i];
	    Bitmap BitmapNormal;
	    Osp::Graphics::Canvas canvas;
	    canvas.Construct(Rectangle(0,0,10,10));
	    canvas.FillRectangle(Color(color.Red,color.Green,color.Blue),Rectangle(0,0,10,10));
	    BitmapNormal.Construct(canvas,Rectangle(0,0,10,10));
		itemText = String(__parentColorOptionView->ourStrings[i].c_str());
		__pComboList->AddItem(&itemText, null, &BitmapNormal, null );
	}



	/*for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it, ++index) {
		String itemText((*it).c_str());
		__pComboList->AddItem(&itemText, null, null, null );
		if (*it == initial) {
			selectedIndex = index;
		}
	}*/

	if (selectedIndex >= 0) {
		//myComboBox->setCurrentIndex(selectedIndex);
	}
	__pComboList->AddItemEventListener(*__parentColorOptionView);
    AddControl(*__pComboList);

	return E_SUCCESS;
}

void ColorComboOptionPopup::OnActionPerformed(const Control& source, int actionId)
{
	switch(actionId)
	{
		case ID_BUTTON_CREATE:
			//if(CreateCategory() == true)
			__pParentForm->SendUserEvent(0, null);
			break;
		case ID_BUTTON_CANCEL:
			__pParentForm->SendUserEvent(0, null);
			break;
		default:
			break;
	}
}



/*
void StaticTextOptionView::_createItem() {
	const std::string &text = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
	QLabel *label = new QLabel(::qtString(text), myTab->widget());
	myWidgets.push_back(label);
	myTab->addItem(label, myRow, myFromColumn, myToColumn);
}

void StaticTextOptionView::_onAccept() const {
}

*/
