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
    pItem->SetItemFormat(*myTab->form()->__pStringViewListItemFormat);
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
