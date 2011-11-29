/*
 * ZLBadaOptionsDialog.cpp
 *
 *  Created on: 23.11.2011
 *      Author: Alex
 */

#include "ZLbadaOptionsDialog.h"
#include "ZLResource.h"
#include <FBase.h>
#include "ZLbadaDialogContent.h"
#include "DialogForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Collection;

ZLbadaOptionsDialog::ZLbadaOptionsDialog(Form   *PreviousForm, const ZLResource &resource, shared_ptr<ZLRunnable> applyAction, bool showApplyButton) :  ZLOptionsDialog(resource, applyAction){
	AppLog("ZLbadaOptionsDialog resource = %s",resource.name().c_str());
	result r = E_SUCCESS;
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	myDialogForm = new DialogForm;
	myDialogForm->Initialize(resource.name().c_str());
	AppLog("myDialogForm->Initialize()");
	r = pFrame->AddControl(*myDialogForm);
	r = pFrame->SetCurrentForm(*myDialogForm);
	AppLog("pFrame->SetCurrentForm(*myDialogForm);");
	myDialogForm->SetPreviousForm(PreviousForm);
}

ZLbadaOptionsDialog::~ZLbadaOptionsDialog() {
	// TODO Auto-generated destructor stub
}

ZLDialogContent &ZLbadaOptionsDialog::createTab(const ZLResourceKey &key){
  AppLog("ZLbadaOptionsDialog::createTab = %s",key.Name.c_str());
  ZLbadaDialogContent *tab = new ZLbadaDialogContent(myDialogForm, tabResource(key));
  myDialogForm->AddTab(key.Name.c_str());
  //ZLQtDialogContent *tab = new ZLQtDialogContent(new QWidget(myTabWidget), tabResource(key));
  //myTabWidget->addTab(tab->widget(), ::qtString(tab->displayName()));
  myTabs.push_back(tab);
  return *tab;
}

bool ZLbadaOptionsDialog::run(){
  AppLog("ZLbadaOptionsDialog::run()");
	result r = E_SUCCESS;
	//AppLog("CreateDalogForm %s",name);

	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	r = pFrame->Draw();
	AppLog("pFrame->Draw();");
	r = pFrame->Show();
	AppLog("pFrame->Show()");
  return true;
}

const std::string &ZLbadaOptionsDialog::selectedTabKey() const {
	 AppLog("&ZLbadaOptionsDialog::selectedTabKey()");
	 return std::string();
}

void ZLbadaOptionsDialog::selectTab(const ZLResourceKey &key){
	 AppLog("&ZLbadaOptionsDialog::selectTab()= %s",key.Name.c_str());
}

