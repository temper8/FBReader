/*
 * ZLBadaOptionsDialog.h
 *
 *  Created on: 23.11.2011
 *      Author: Alex
 */

#ifndef ZLBADAOPTIONSDIALOG_H_
#define ZLBADAOPTIONSDIALOG_H_

#include <FBase.h>
#include "DialogForm.h"
#include "ZLOptionsDialog.h"


class ZLbadaOptionsDialog: public ZLOptionsDialog {
public:
	ZLbadaOptionsDialog(Osp::Ui::Controls::Form   *PreviousForm, const ZLResource &resource, shared_ptr<ZLRunnable> applyAction, bool showApplyButton);
	virtual ~ZLbadaOptionsDialog();

public:
	virtual ZLDialogContent &createTab(const ZLResourceKey &key);
	virtual bool run();
	DialogForm *myDialogForm;
	void apply();

protected:
//	Osp::Ui::Controls::Form   &myPreviousForm;
	virtual const std::string &selectedTabKey() const;
	virtual void selectTab(const ZLResourceKey &key);
	virtual bool runInternal();


};

#endif /* ZLBADAOPTIONSDIALOG_H_ */
