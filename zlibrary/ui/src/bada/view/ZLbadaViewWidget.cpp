/*
 * ZLBadaViewWidget.cpp
 *
 *  Created on: 12.10.2011
 *      Author: Alex
 */

#include "ZLbadaViewWidget.h"
#include "badaForm.h"

void ZLbadaViewWidget::doAction(std::string &actionId){
	myWindows->application().doAction(actionId);
}

ZLbadaViewWidget::ZLbadaViewWidget(ZLView::Angle initialAngle): ZLViewWidget(initialAngle) {
}

ZLbadaViewWidget::~ZLbadaViewWidget() {

}

//void ZLbadaViewWidget::setView(shared_ptr<ZLView> view){
//	badaForm->myView = view;
//}

void ZLbadaViewWidget::repaint() {
	AppLog("ZLbadaViewWidget::repaint()");
	// Draw and Show the form
	mybadaForm->Draw();
	AppLog("mybadaForm->Draw()");
	mybadaForm->Show();
	AppLog("mybadaForm->Show()");

}

void ZLbadaViewWidget::setScrollbarEnabled(ZLView::Direction direction, bool enabled){
	AppLog("ZLbadaViewWidget::setScrollbarEnabled");
}

void ZLbadaViewWidget::setScrollbarPlacement(ZLView::Direction direction, bool standard){
	AppLog("ZLbadaViewWidget::setScrollbarPlacement");
}
void ZLbadaViewWidget::setScrollbarParameters(ZLView::Direction direction, size_t full, size_t from, size_t to){
	AppLog("ZLbadaViewWidget::setScrollbarParameters");
}

