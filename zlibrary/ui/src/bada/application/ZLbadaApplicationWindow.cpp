/*
 * ZLBadaApplicationWindow.cpp
 *
 *  Created on: 11.10.2011
 *      Author: Alex
 */

#include "ZLbadaApplicationWindow.h"
#include "../view/ZLbadaViewWidget.h"
#include <ZLView.h>
#include "../library/ZLbadaLibraryImplementation.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

ZLbadaApplicationWindow::ZLbadaApplicationWindow(ZLApplication *a): ZLApplicationWindow(a) {
	// TODO Auto-generated constructor stub


}

ZLbadaApplicationWindow::~ZLbadaApplicationWindow() {
	// TODO Auto-generated destructor stub
}



ZLViewWidget *ZLbadaApplicationWindow::createViewWidget() {

	AppLog("createViewWidget");
	ZLView::Angle Angle = ZLView::DEGREES0;// application().AngleStateOption.value();
	ZLbadaViewWidget *viewWidget = new ZLbadaViewWidget(Angle);

	// Create a form
	badaForm *pB2Form = new badaForm(*viewWidget);
	pB2Form->Initialize();
	pB2Form->SetOrientation(ORIENTATION_AUTOMATIC_FOUR_DIRECTION);

	// Add the form to the frame
	ZLbadaLibraryImplementation::myBadaApp->TestTest();
	Frame *pFrame = ZLbadaLibraryImplementation::myBadaApp->GetAppFrame()->GetFrame();
	pFrame->AddControl(*pB2Form);
	AppLog("pFrame->AddControl(*pB2Form)");
	// Set the current form
	pFrame->SetCurrentForm(*pB2Form);
	AppLog("SetCurrentForm(*pB2Form)");
	viewWidget->bForm = pB2Form;



//	QVBoxLayout *layout = new QVBoxLayout(main);
//	layout->addWidget(viewWidget->widget(), 1);

//	myRightButtonResource = CLOSE_BUTTON;
//	myCST = new UTIL_CST(main, ZLibrary::ApplicationName().c_str(), "CST_Menu", myRightButtonResource);
//	myCST->setFixedSize(ZGlobal::getCstR().size());
	//layout->addWidget(myCST);
//	myCST->getLeftBtn()->setPopup(myMenu);
//	myMainWindow->connectCSTButtons(myCST);

	//myMainWindow->setCentralWidget(main);
	return viewWidget;
}
