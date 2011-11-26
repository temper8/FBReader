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

bool DialogForm::Initialize()
{
	AppLog("DialogForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|
	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);
	SetTitleText(L"DialogForm");

//	AddSoftkeyActionListener(SOFTKEY_0, *this);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
//	SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);

	return true;
}



DialogForm::DialogForm() {
	// TODO Auto-generated constructor stub

}

DialogForm::~DialogForm() {
	// TODO Auto-generated destructor stub
}

result DialogForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("DialogForm::OnInitializing \n");
	SetSoftkeyText(SOFTKEY_1, L"Back");
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
			pPreviousForm->SendUserEvent(0, null);


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



