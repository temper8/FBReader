

#include "ZLBadaViewWidget.h"
#include "ZLbadaPaintContext.h"
#include "badaForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

result badaForm::OnDraw(void)
{
	AppLog("badaForm::OnDraw(void)");
	//shared_ptr<ZLView> myView = myHolder.view();

	ZLbadaPaintContext &context = (ZLbadaPaintContext&)myHolder.view()->context();
//	ZLbadaPaintContext &context = myView->context();
//	if (!myView->isNull())
//	{
		Control& control = *this;
		context.pCanvas = control.GetCanvasN();
		myHolder.view()->paint();
		context.pCanvas->Show();
//	}
	return E_SUCCESS;
}

void
badaForm::
OnTouchDoublePressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchDoublePressed");
}

void
badaForm::OnTouchFocusIn(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusIn");
}

void
badaForm::OnTouchFocusOut(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusOut");
}

void
badaForm::OnTouchLongPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchLongPressed");
	// Display the OptionMenu
	if (__pOptionMenu != null){
		__pOptionMenu->SetShowState(true);
		__pOptionMenu->Show();
	}
}

void
badaForm::OnTouchMoved(const Osp::Ui::Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchMoved");

}

void
badaForm::OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchPressed");

}

void badaForm::OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchReleased");
	//myHolder.view()->onStylusRelease(currentPosition.x, currentPosition.y);
	myHolder.view()->onFingerTap(currentPosition.x, currentPosition.y);
	OnDraw();
//	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
//	FormMgr* pFormMgr = static_cast<FormMgr *>(pFrame->GetControl("FormMgr"));
//	if (pFormMgr != null)
//		pFormMgr->SendUserEvent(FormMgr::REQUEST_DETECTFORM, null);
}

void badaForm::OnOrientationChanged( const Osp::Ui::Control&  source,  Osp::Ui::OrientationStatus  orientationStatus ){

	AppLog("OnOrientationChanged");
}

badaForm::badaForm(ZLbadaViewWidget &Holder): myHolder(Holder){

}

badaForm::~badaForm(void)
{
}

bool badaForm::Initialize()
{
	// Construct an XML form
	//Construct(L"IDF_B2FORM");
	//Construct(FORM_STYLE_NORMAL);
	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_INDICATOR|FORM_STYLE_OPTIONKEY);
	//SetName(L"IDF_FORM1");
	SetTitleText(L"FBReader Form");
	// Create an OptionKey
	//SetOptionkeyActionId(ID_OPTIONKEY);
	//AddOptionkeyActionListener(*this);

	// Create an OptionMenu
	__pOptionMenu = new OptionMenu();
	__pOptionMenu->Construct();
	__pOptionMenu->AddItem("Библиотека",ID_OPTIONMENU_ITEM1);
	__pOptionMenu->AddItem("Открыть",ID_OPTIONMENU_ITEM2);
	__pOptionMenu->AddItem("Поиск",ID_OPTIONMENU_ITEM3);
	__pOptionMenu->AddItem("Настройки",ID_OPTIONMENU_ITEM4);
	__pOptionMenu->AddItem("О программе",ID_OPTIONMENU_ITEM5);
	__pOptionMenu->AddItem("Содержание",ID_OPTIONMENU_ITEM6);
	__pOptionMenu->AddActionEventListener(*this);

	return true;
}

result badaForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here
	AddTouchEventListener(*this);
	AddOrientationEventListener(*this);
	// Get a button via resource ID
	/*__pButtonOk = static_cast<Button *>(GetControl(L"IDC_BUTTON_OK"));
	if (__pButtonOk != null)
	{
		__pButtonOk->SetActionId(ID_BUTTON_OK);
		__pButtonOk->AddActionEventListener(*this);


	}
*/
//	((GView*)myHolder.myApplication)->ReadImage();
	return r;
}

result badaForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void badaForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_BUTTON_OK:
		{
			AppLog("OK Button is clicked! \n");
			ZLbadaPaintContext &context = (ZLbadaPaintContext&)myHolder.view()->context();
			Control& control = *this;
			context.pCanvas = control.GetCanvasN();

			myHolder.view()->paint();
		}
		break;
	case ID_OPTIONKEY:
		{
			// Display the OptionMenu
			if (__pOptionMenu != null)
				__pOptionMenu->SetShowState(true);
			__pOptionMenu->Show();
		}
		break;
	default:
		break;
	}
}


