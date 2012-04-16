

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
	Osp::Graphics::Canvas* pCanvas = GetCanvasN();

//	pCanvas->Clear();
	//if (pCanvas == null) pCanvas = GetClientAreaCanvasN ();
  if (touchMove!=0){
	   pCanvas->Clear();
		if (touchMove == 1){
			pCanvas->Copy(Point(0,0),*myCanvas,formRect);
			AppLog("OnTouchMoved 1");
			//srcRect(-x,0,formRect.width+x,formRect.height);
			pCanvas->Copy(Point(0,0),*capturedCanvas,srcRect);
			AppLog("OnTouchMoved 2");
		}
		else {
			pCanvas->Copy(Point(0,0),*capturedCanvas,formRect);
			//Rectangle srcRect(formRect.width-currentPosition.x,0,currentPosition.x,formRect.height);
			pCanvas->Copy(Point(0,0),*myCanvas,srcRect);
		}
		AppLog("pCanvas->Show");
		pCanvas->Show();
   }
   else
   {
	   Rectangle newRect = GetBounds();
	   	if (newRect.width==formRect.width)
	   	{


	   			Osp::Graphics::Canvas* tmpCanvas = new Canvas;
	   			tmpCanvas->Construct();
	   			tmpCanvas->Clear();
		   		context.pCanvas = tmpCanvas;
		   		context.myHeight = formRect.height;
		   		context.myWidth = formRect.width;
		   		//context.restoreFont();
		   		myHolder.view()->paint();
		   		myCanvas->Copy(Point(0,0),*tmpCanvas,formRect);
		   		if (showNewPage)   		{
	   			AppLog("pCanvas->Copy");
	   				pCanvas->Copy(Point(0,0),*tmpCanvas,formRect);
	   				AppLog("pCanvas->Show");
	   				//tmpCanvas.Show();
	   				pCanvas->Show();
	   		}
		   	context.pCanvas = 0;
		   	//context.deleteMyFont();
		   	delete tmpCanvas;
	   	}
   }

 delete pCanvas;
//delete tmpCanvas;
}

//virtual bool onStylusPress(int x, int y);
//virtual bool onStylusRelease(int x, int y);
//virtual bool onStylusMove(int x, int y);
//virtual bool onStylusMovePressed(int x, int y);
//virtual bool onFingerTap(int x, int y);
void badaForm::OnKeyLongPressed (const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode){
	AppLog("OnKeyLongPressed");
}

void badaForm::OnKeyPressed (const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode){
	AppLog("OnKeyPressed");
}

void badaForm::OnKeyReleased (const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode){
	AppLog("OnKeyReleased");
	if (!FBReader::Instance().EnableTapScrollingByVolumeKeysOption.value()) return;

	switch (keyCode)
		{
	 	 case KEY_SIDE_UP :
	 	 	 	FBReader::Instance().doAction(ActionCode::TAP_SCROLL_FORWARD);
	 	 	// 	source.ConsumeInputEvent();
	 	 	 	break;

	 	 case KEY_SIDE_DOWN :
	 		    FBReader::Instance().doAction(ActionCode::TAP_SCROLL_BACKWARD);
	 	 	// 	source.ConsumeInputEvent();
	 	 	 	break;

	 	 }

}

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
/*	if (__pOptionMenu != null){
		__pOptionMenu->SetShowState(true);
		__pOptionMenu->Show();
	}
*/
}

void badaForm::OnTouchMoved(const Osp::Ui::Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchMoved");
	int x = currentPosition.x - startTouchPosition.x;
	int y = currentPosition.y - startTouchPosition.y;
	if (showNewPage) {
		capturedCanvas->Copy(Point(0,0),*myCanvas,formRect);
		showNewPage = false;
		if (x<0) FBReader::Instance().doAction(ActionCode::TAP_SCROLL_FORWARD);
		else FBReader::Instance().doAction(ActionCode::TAP_SCROLL_BACKWARD);
	}

 //  Canvas* pCanvas = source->GetCanvasN();
	if (x<0){
		touchMove = 1;
		//pCanvas->Copy(Point(0,0),*myCanvas,formRect);
		AppLog("OnTouchMoved 1");
		 srcRect = Rectangle(-x,0,formRect.width+x,formRect.height);
		//pCanvas->Copy(Point(0,0),*capturedCanvas,srcRect);
		AppLog("OnTouchMoved 2");
	}
	else {
		touchMove = 2;
		//pCanvas->Copy(Point(0,0),*capturedCanvas,formRect);
		 srcRect = Rectangle(formRect.width-currentPosition.x,0,currentPosition.x,formRect.height);
		//pCanvas->Copy(Point(0,0),*myCanvas,srcRect);
	}
	AppLog("pCanvas->Show");
//	pCanvas->Show();*/
//	delete pCanvas;
	Draw();
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
	touchMove = 0;
	AppLog("OnTouchReleased");
	if (!showNewPage) {
		Canvas* pCanvas = GetCanvasN();
		pCanvas->Copy(Point(0,0),*myCanvas,formRect);
		pCanvas->Show();
		delete pCanvas;
		showNewPage = true;
	}
	else
	{
		AppLog("currentPosition x=%d, y=%d",currentPosition.x, currentPosition.y);
			//myHolder.view()->onStylusRelease(currentPosition.x, currentPosition.y);
			if (Math::Abs(2*currentPosition.y-formRect.height)<200) {
				if (Math::Abs(2*currentPosition.x-formRect.width)<200){
					if (__pOptionMenu != null){
						__pOptionMenu->SetShowState(true);
						__pOptionMenu->Show();
					}
				}
				else
				{
				if (2*currentPosition.x>formRect.width) FBReader::Instance().doAction(ActionCode::TAP_SCROLL_FORWARD);
				else FBReader::Instance().doAction(ActionCode::TAP_SCROLL_BACKWARD);
				}
			}
			else
				{
				myHolder.view()->onFingerTap(currentPosition.x, currentPosition.y);
				//OnDraw();
				}

	}

}

void badaForm::setOrientation(int angle){

	Osp::Ui::Orientation badaAngle;

	switch (angle) {
		case ZLView::DEGREES0:
			badaAngle = ORIENTATION_PORTRAIT;
			break;
		case ZLView::DEGREES90:
			badaAngle = ORIENTATION_LANDSCAPE ;
			break;
		case ZLView::DEGREES180:
			badaAngle = ORIENTATION_PORTRAIT_REVERSE;
			break;
	    case ZLView::DEGREES270:
		    badaAngle = ORIENTATION_LANDSCAPE_REVERSE;
			break;
	    case -1:
	    	badaAngle = ORIENTATION_AUTOMATIC_FOUR_DIRECTION;
	    	break;
	}
	AppLog("badaAngle %d",badaAngle);
	SetOrientation(badaAngle);
}

void badaForm::OnOrientationChanged( const Osp::Ui::Control&  source,  Osp::Ui::OrientationStatus  orientationStatus ){

	AppLog("OnOrientationChanged");
	formRect = GetClientAreaBounds();

	if (myCanvas) delete myCanvas;

	myCanvas = new Canvas();
	myCanvas->Construct(formRect);

	if (capturedCanvas) delete capturedCanvas;

	capturedCanvas = new Canvas();
	capturedCanvas->Construct(formRect);

	OnDraw();
}

badaForm::badaForm(ZLbadaViewWidget &Holder): myHolder(Holder), MenuItemCount(0), showNewPage(true), touchMove(0){

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
	//SetTitleText(L"FBReader Form");
	// Create an OptionMenu
	__pOptionMenu = new OptionMenu();
	__pOptionMenu->Construct();
	__pOptionMenu->AddActionEventListener(*this);


	formRect = GetClientAreaBounds();

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
	AddKeyEventListener(*this);
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



