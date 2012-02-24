

#include "ZLBadaViewWidget.h"
#include "ZLbadaPaintContext.h"
#include "../dialogs/ZLbadaDialogManager.h"
#include "badaForm.h"
#include "OpenFileForm.h"
#include "../dialogs/DialogForm.h"
#include "badaForm.h"
#include <FSystem.h>
#include "../../../../../fbreader/src/fbreader/FBReader.h"
#include "../../../../../fbreader/src/fbreader/FBReaderActions.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::System;

result badaForm::OnDraw(void)
{
	AppLog("badaForm::OnDraw(void)");
	ZLbadaPaintContext &context = (ZLbadaPaintContext&)myHolder.view()->context();
	myCanvas->Clear();
	context.pCanvas = myCanvas;
	myHolder.view()->paint();
	if (showNewPage)
	{
		Osp::Graphics::Canvas* pCanvas = GetCanvasN();
		pCanvas->Copy(Point(0,0),*myCanvas,Rectangle(0,0,480,800));
		pCanvas->Show();
		delete pCanvas;
	}

}

//virtual bool onStylusPress(int x, int y);
//virtual bool onStylusRelease(int x, int y);
//virtual bool onStylusMove(int x, int y);
//virtual bool onStylusMovePressed(int x, int y);
//virtual bool onFingerTap(int x, int y);

void badaForm::OnTouchDoublePressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchDoublePressed");
}

void badaForm::OnTouchFocusIn(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusIn");
}

void badaForm::OnTouchFocusOut(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusOut");
}

void badaForm::OnTouchLongPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchLongPressed");

	// Display the OptionMenu
	if (__pOptionMenu != null){
		__pOptionMenu->SetShowState(true);
		__pOptionMenu->Show();
	}

}

void badaForm::OnTouchMoved(const Osp::Ui::Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchMoved");
	int x = currentPosition.x - startTouchPosition.x;
	int y = currentPosition.y - startTouchPosition.y;
	int r = 50;
	if (showNewPage)
	{
		capturedCanvas->Copy(Point(0,0),*myCanvas,Rectangle(0,0,480,800));
		showNewPage = false;
		if (x<0) FBReader::Instance().doAction(ActionCode::TAP_SCROLL_FORWARD);
		else FBReader::Instance().doAction(ActionCode::TAP_SCROLL_BACKWARD);
	}
	Canvas* pCanvas = GetCanvasN();
if (x<0){
	pCanvas->Copy(Point(0,0),*myCanvas,Rectangle(0,0,480,800));
	pCanvas->Copy(Point(x,0),*capturedCanvas,Rectangle(0,0,480,800));
}
else {
	pCanvas->Copy(Point(0,0),*capturedCanvas,Rectangle(0,0,480,800));
	pCanvas->Copy(Point(x-480,0),*myCanvas,Rectangle(0,0,480,800));
}
	pCanvas->Show();
	delete pCanvas;

//	myHolder.view()->onStylusMove(currentPosition.x, currentPosition.y);
}

void badaForm::OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchPressed");
  startTouchPosition = currentPosition;

 myHolder.view()->onStylusPress(currentPosition.x, currentPosition.y);
}

void badaForm::OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchReleased");
	if (!showNewPage) {
		Canvas* pCanvas = GetCanvasN();
		pCanvas->Copy(Point(0,0),*myCanvas,Rectangle(0,0,480,800));
		pCanvas->Show();
		delete pCanvas;
		showNewPage = true;
	}
	else
	{
		AppLog("currentPosition x=%d, y=%d",currentPosition.x, currentPosition.y);
			//myHolder.view()->onStylusRelease(currentPosition.x, currentPosition.y);
			if (Math::Abs(currentPosition.y-400)<100) {
					if (__pOptionMenu != null){
						__pOptionMenu->SetShowState(true);
						__pOptionMenu->Show();
					}
			}
			else
				{
				myHolder.view()->onFingerTap(currentPosition.x, currentPosition.y);
				//OnDraw();
				}

	}

}

void badaForm::OnOrientationChanged( const Osp::Ui::Control&  source,  Osp::Ui::OrientationStatus  orientationStatus ){

	AppLog("OnOrientationChanged");
}

badaForm::badaForm(ZLbadaViewWidget &Holder): myHolder(Holder), MenuItemCount(0), showNewPage(true){

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
	__pOptionMenu->AddActionEventListener(*this);

	myCanvas = new Canvas();
	myCanvas->Construct();
	capturedCanvas = new Canvas();
	capturedCanvas->Construct();

	return true;
}

result badaForm::OnInitializing(void)
{
	AppLog("badaForm::OnInitializing()");
	result r = E_SUCCESS;
//	RuntimeInfo::GetValue("ScreenHeight", ScreenHeight);
//	RuntimeInfo::GetValue("ScreenWidth", ScreenWidth);
//	AppLog("ScreenHeight=%d, ScreenWidth=%d",ScreenHeight, ScreenWidth);
	// TODO: Add your initialization code here
	AddTouchEventListener(*this);
	AddOrientationEventListener(*this);
//	((GView*)myHolder.myApplication)->ReadImage();
	return r;
}

result badaForm::OnTerminating(void)
{
	result r = E_SUCCESS;

    delete __pOptionMenu;

	return r;
}

void badaForm::AddMenuItem(const std::string &name, const  std::string &id){
	AppLog("badaForm::AddMenuItem %s,%s",name.c_str(),id.c_str());
	int count =__pOptionMenu->GetItemCount();
	AppLog("badaForm::AddMenuItem count=%d",count);
	AppLog("badaForm::AddMenuItem MenuItemCount=%d",MenuItemCount);

	if (count == 5) {
		__pOptionMenu->AddItem("more...",ID_OPTIONMENU_ITEM0 -1);
		ActionIdList[MenuItemCount] = id;
		__pOptionMenu->AddSubItem(5,name.c_str(),ID_OPTIONMENU_ITEM0 + MenuItemCount);
	}
	if (count < 5) {
		ActionIdList[MenuItemCount] = id;
		__pOptionMenu->AddItem(name.c_str(),ID_OPTIONMENU_ITEM0 + MenuItemCount);
	}
	if (count > 5) {
			ActionIdList[MenuItemCount] = id;
			__pOptionMenu->AddSubItem(5,name.c_str(),ID_OPTIONMENU_ITEM0 + MenuItemCount);
		}
	MenuItemCount++;
}

void badaForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
    int indx;
    AppLog("actionId %d",actionId);
    indx = actionId - ID_OPTIONMENU_ITEM0;//__pOptionMenu->GetItemIndexFromActionId(actionId);
    if (indx<0) return;
    AppLog("OPTIONMENU %d",indx);
    AppLog("FB Action %s",  ActionIdList[indx].c_str());

  	myHolder.doAction(ActionIdList[indx]);

}

DialogForm* badaForm::CreateDalogForm(void){
	result r = E_SUCCESS;
	//AppLog("CreateDalogForm %s",name);
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	DialogForm* pDialogForm = new DialogForm;
//	pDialogForm->Initialize();
	AppLog("pDialogForm->Initialize()");
	r = pFrame->AddControl(*pDialogForm);
	r = pFrame->SetCurrentForm(*pDialogForm);
	AppLog("r = pFrame->SetCurrentForm(*pDialogForm);");
	pDialogForm->SetPreviousForm(this);
//	r = pFrame->Draw();
//	AppLog("pFrame->Draw();");
//	r = pFrame->Show();
//	AppLog("pFrame->Show()");
	return pDialogForm;
}

void badaForm::goOpenFileForm()
{
	result r = E_SUCCESS;
	AppLog("go detail form");
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		OpenFileForm* pOpenFileForm = new OpenFileForm;
		//pOpenFileForm->SetPreviousForm(this);
		pOpenFileForm->SetPreviousForm(pFrame->GetCurrentForm());
		if(pOpenFileForm->Initialize()){
			r = pFrame->AddControl(*pOpenFileForm);
			if(IsFailed(r)){AppLog("Initialize() is failed by %s.", GetErrorMessage(r));return;}

			r = pFrame->SetCurrentForm(*pOpenFileForm);
			if(IsFailed(r)){
				AppLog("pFrame->SetCurrentForm() is failed by %s.", GetErrorMessage(r));
				return;
			}

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
			pOpenFileForm->StartSearch();
		}
}

void badaForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("badaForm::OnUserEventReceivedN");
	Form* prevForm = pFrame->GetCurrentForm();
	switch(requestId)
	{
	case 0:
		{
			AppLog("badaForm::OnUserEventReceivedN requestId = 0 ");
			pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			//myHolder.doAction(ActionIdList[2]);
			//DetailForm* pDetailForm = static_cast<DetailForm *>(pFrame->GetControl("DetailForm"));
			//badaForm* pbadaForm = (badaForm*)(pFrame->GetControl("badaForm"));
			if (prevForm != null)
			{
				AppLog("prevForm != null");
				pFrame->RemoveControl(*prevForm);
				AppLog("RemoveControl(*prevForm);");
				//ZLbadaDialogManager::deleteTreeDialog();
				AppLog("deleteTreeDialog");
			}

		}
		break;
	case 1:
		{
			AppLog("badaForm::а теперь Акшен открываем файл");
			pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			myHolder.doAction(ActionIdList[2]);
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



