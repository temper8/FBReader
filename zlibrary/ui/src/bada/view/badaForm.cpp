

#include "ZLBadaViewWidget.h"
#include "ZLbadaPaintContext.h"
#include "badaForm.h"
#include "OpenFileForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Collection;

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
	// Display the OptionMenu
	if (__pOptionMenu != null){
		__pOptionMenu->SetShowState(true);
		__pOptionMenu->Show();
	}
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
	AppLog("badaForm::Initialize()");
	// Construct an XML form
	//Construct(L"IDF_B2FORM");
	//Construct(FORM_STYLE_NORMAL);FORM_STYLE_TITLE||FORM_STYLE_INDICATOR
	Construct(FORM_STYLE_NORMAL);
	//SetName(L"IDF_FORM1");
	SetTitleText(L"FBReader Form");
	// Create an OptionKey
	//SetOptionkeyActionId(ID_OPTIONKEY);
	//AddOptionkeyActionListener(*this);

	// Create an OptionMenu
	__pOptionMenu = new OptionMenu();
	__pOptionMenu->Construct();
	//__pOptionMenu->AddItem("Библиотека",ID_OPTIONMENU_ITEM1);
	//__pOptionMenu->AddItem("Открыть",ID_OPTIONMENU_ITEM2);
	//__pOptionMenu->AddItem("Поиск",ID_OPTIONMENU_ITEM3);
	//__pOptionMenu->AddItem("Настройки",ID_OPTIONMENU_ITEM4);
	//__pOptionMenu->AddItem("О программе",ID_OPTIONMENU_ITEM5);
	//__pOptionMenu->AddItem("Содержание",ID_OPTIONMENU_ITEM6);
	__pOptionMenu->AddActionEventListener(*this);

	return true;
}

result badaForm::OnInitializing(void)
{
	AppLog("badaForm::OnInitializing()");
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

    delete __pOptionMenu;

	return r;
}

void badaForm::AddMenuItem(const std::string &name,const  std::string &id){
	AppLog("badaForm::AddMenuItem %s,%s",name.c_str(),id.c_str());
	int count =__pOptionMenu->GetItemCount();
	AppLog("badaForm::AddMenuItem count=%d,%s",count);
	ActionIdList[count] = id;
	__pOptionMenu->AddItem(name.c_str(),ID_OPTIONMENU_ITEM0 + count);


}
void badaForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
    int indx;
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


	case ID_OPTIONMENU_ITEM0:
	case ID_OPTIONMENU_ITEM1:
	case ID_OPTIONMENU_ITEM2:
	case ID_OPTIONMENU_ITEM3:
	case ID_OPTIONMENU_ITEM4:
	case ID_OPTIONMENU_ITEM5:
		indx = __pOptionMenu->GetItemIndexFromActionId(actionId);
    	AppLog("OPTIONMENU %d",indx);
        if (indx==2) {

        	AppLog("go open file");
     		goOpenFileForm();
    	  }
        else {
        	AppLog("делаем что-то другое");
        	myHolder.doAction(ActionIdList[indx]);
        };

		break;

	default:
		break;
	}
}

void badaForm::goOpenFileForm()
{
	result r = E_SUCCESS;
	AppLog("go detail form");
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		OpenFileForm* pOpenFileForm = new OpenFileForm;

		if(pOpenFileForm->Initialize()){
			r = pFrame->AddControl(*pOpenFileForm);
			if(IsFailed(r)){
				AppLog("pOpenFileForm->Initialize() is failed by %s.", GetErrorMessage(r));
				return;
			}

			r = pFrame->SetCurrentForm(*pOpenFileForm);
			if(IsFailed(r)){
				AppLog("pFrame->SetCurrentForm() is failed by %s.", GetErrorMessage(r));
				return;
			}
			//pOpenFileForm->
			pOpenFileForm->SetPreviousForm(this);
			AppLog("LoadContentInfo");
			//_detailForm->LoadContentInfo((ContentSearchResult*)__pLstContentInfo->GetAt(index));

			r = pFrame->Draw();
			if(IsFailed(r)){
				AppLog("pFrame->Draw() is failed by %s.", GetErrorMessage(r));
				return;
			}
			r = pFrame->Show();
			if(IsFailed(r)){
				AppLog("pFrame->Show() is failed by %s.", GetErrorMessage(r));
				return;
			}
		}
}

void badaForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("badaForm::OnUserEventReceivedN");

	switch(requestId)
	{
	case 0:
		{
			AppLog("badaForm::а теперь Акшен открываем файл");
			pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			myHolder.doAction(ActionIdList[2]);
			//DetailForm* pDetailForm = static_cast<DetailForm *>(pFrame->GetControl("DetailForm"));
			//badaForm* pbadaForm = (badaForm*)(pFrame->GetControl("badaForm"));
			//if (pDetailForm != null)
			//	pFrame->RemoveControl(*pDetailForm);
		}
		break;
	case 1:
		{
		/*	pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			DetailForm* pDetailForm = static_cast<DetailForm *>(pFrame->GetControl("DetailForm"));
			if (pDetailForm != null)
				pFrame->RemoveControl(*pDetailForm);

			SearchContent();
			*/
		}
		break;
	default:
		break;
	}

}



