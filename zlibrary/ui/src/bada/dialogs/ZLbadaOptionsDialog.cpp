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

ZLbadaOptionsDialog::ZLbadaOptionsDialog(const ZLResource &resource, shared_ptr<ZLRunnable> applyAction, bool showApplyButton) :  ZLOptionsDialog(resource, applyAction) {
	AppLog("ZLbadaOptionsDialog resource = %s",resource.name().c_str());

}

ZLbadaOptionsDialog::~ZLbadaOptionsDialog() {
	// TODO Auto-generated destructor stub
}

ZLDialogContent &ZLbadaOptionsDialog::createTab(const ZLResourceKey &key){
  AppLog("ZLbadaOptionsDialog::createTab = %s",key.Name.c_str());
  ZLbadaDialogContent *tab = new ZLbadaDialogContent(myDialogForm, tabResource(key));
  //ZLQtDialogContent *tab = new ZLQtDialogContent(new QWidget(myTabWidget), tabResource(key));
  //myTabWidget->addTab(tab->widget(), ::qtString(tab->displayName()));
  myTabs.push_back(tab);
  return *tab;
}

bool ZLbadaOptionsDialog::run(){
  AppLog("ZLbadaOptionsDialog::run()");
  return true;
}

const std::string &ZLbadaOptionsDialog::selectedTabKey() const {
	 AppLog("&ZLbadaOptionsDialog::selectedTabKey()");
	 return std::string();
}

void ZLbadaOptionsDialog::selectTab(const ZLResourceKey &key){
	 AppLog("&ZLbadaOptionsDialog::selectTab()= %s",key.Name.c_str());
}

