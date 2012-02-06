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

