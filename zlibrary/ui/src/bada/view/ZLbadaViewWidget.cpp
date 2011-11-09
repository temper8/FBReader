/*
 * ZLBadaViewWidget.cpp
 *
 *  Created on: 12.10.2011
 *      Author: Alex
 */

#include "ZLbadaViewWidget.h"
#include "badaForm.h"

ZLbadaViewWidget::ZLbadaViewWidget(ZLView::Angle initialAngle): ZLViewWidget(initialAngle) {
	// TODO Auto-generated constructor stub

}

ZLbadaViewWidget::~ZLbadaViewWidget() {
	// TODO Auto-generated destructor stub
}

//void ZLbadaViewWidget::setView(shared_ptr<ZLView> view){
//	badaForm->myView = view;
//}

void ZLbadaViewWidget::repaint() {
	AppLog("ZLbadaViewWidget::repaint()");
	// Draw and Show the form
	bForm->Draw();
	AppLog("pB2Form->Draw()");
	bForm->Show();
	AppLog("pB2Form->Show()");

}

