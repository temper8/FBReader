/*
 * DialogForm.cpp
 *
 *  Created on: 24.11.2011
 *      Author: Alex
 */

#include "DialogForm.h"

#include <FIo.h>
//#include "badaForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Content;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;

#define	ID_ACT_UPDATE	1700
#define ID_ACT_DELETE	1701
#define ID_ACT_CLOSE	1702

bool DialogForm::Initialize(const char *title)
{
	AppLog("DialogForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|
	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);
	SetTitleText(String(title));

//	AddSoftkeyActionListener(SOFTKEY_0, *this);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
//	SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);
	AppLog("DialogForm::AddControls");
	SetSoftkeyText(SOFTKEY_1, L"Back");

	clientArea = GetClientAreaBounds();
    clientArea.x+= 10;
    clientArea.y+= 00;
    clientArea.width-= 20;
    clientArea.height-= 20;
    YPos=0;
	AddControls();
	return true;
}



DialogForm::DialogForm() {
	// TODO Auto-generated constructor stub

}

DialogForm::~DialogForm() {
	// TODO Auto-generated destructor stub
}

result  DialogForm::AddTab(const char *title){
	result r = E_SUCCESS;
	AppLog("DialogForm::AddTab YPos=%d",YPos);

	Label* pTempLabel = new Label;
	pTempLabel->Construct(Rectangle(00,YPos,clientArea.width,100), String(title));
	pTempLabel->SetTextColor(Color::COLOR_RED);
	pTempLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(*pTempLabel);
	YPos+=100;
}

result DialogForm::AddControls(){
	result r = E_SUCCESS;

    // Creates a ScrollPanel

    pScrollPanel = new ScrollPanel();
    pScrollPanel->Construct(clientArea);
/*
    Button* pButton = new Button();
    pButton->Construct(Rectangle(0, 0, clientArea.width, 80));
    pScrollPanel->AddControl(*pButton);

    EditField* pEdit = new EditField();
    pEdit->Construct(Rectangle(10, 400, clientArea.width-10, 80),
    EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN,
    true, 100, GROUP_STYLE_SINGLE );
    pEdit->SetGuideText("GuideText1");
	pEdit->SetTitleText("TitleText1");
	pEdit->SetText("Просто Text1");
    pScrollPanel->AddControl(*pEdit);

    pEdit = new EditField();
    pEdit->Construct(Rectangle(10, 200, clientArea.width-10, 80),
    EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN,
    true, 100, GROUP_STYLE_SINGLE );
    pEdit->SetGuideText("GuideText0");
	pEdit->SetTitleText("TitleText0");
	pEdit->SetText("Просто Text0");
    pScrollPanel->AddControl(*pEdit);



    EditField* pEdit = new EditField();
    pEdit->Construct(Rectangle(10, 600, clientArea.width-5, 80),
    EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN,
       true,  100,  GROUP_STYLE_SINGLE );

//    pEdit->Construct(Rectangle(0, 600, clientArea.width, 80),EDIT_FIELD_TITLE_STYLE_TOP, INPUT_STYLE_OVERLAY, true, 100, GROUP_STYLE_TOP );
    pEdit->SetGuideText("GuideText2");
	pEdit->SetTitleText("TitleText");
	//pEdit->SetText("Просто Text");
    pScrollPanel->AddControl(*pEdit);


*/

    // Adds a ScrollPanel to the Form
    AddControl(*pScrollPanel);

    // Note: Using the 'delete' keyword causes a memory access crash.
    // Calls RemoveControl(const Control& control) instead.
	return r;
}
result DialogForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("DialogForm::OnInitializing \n");
	return r;
}


result DialogForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void DialogForm::OnItemStateChanged(const Osp::Ui::Control & source, int index, int itemId, Osp::Ui::ItemStatus status)
{
}

void DialogForm::SetPreviousForm(Osp::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void DialogForm::OnActionPerformed(const Osp::Ui::Control & source, int actionId)
{
	switch(actionId)
	{
	case ID_ACT_CLOSE:
		{
			AppLog("Close button is clicked! \n");
			Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
			pFrame->SetCurrentForm(*pPreviousForm);
			pPreviousForm->Draw();
			pPreviousForm->Show();
			//((badaForm*)pPreviousForm)->pSearchResultInfo=null;
			pPreviousForm->SendUserEvent(1, null);
		}
		break;
	case ID_ACT_UPDATE:
		{
			AppLog("UpdateContent");
		//	UpdateContent();
			break;
		}
	/*case ID_ACT_DELETE:
		{
			DeleteContent();
			break;
		}*/
	default:
		break;
	}
}



