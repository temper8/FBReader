/*
 * DialogForm.h
 *
 *  Created on: 24.11.2011
 *      Author: Alex
 */

#ifndef DIALOGFORM_H_
#define DIALOGFORM_H_
#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FContent.h>


class DialogForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
    public Osp::Ui::IItemEventListener {

public:
	DialogForm();
	virtual ~DialogForm();
	bool Initialize(const char *title);
	void SetPreviousForm(Osp::Ui::Controls::Form* preForm);
	result  AddControls();
	result  AddTab(const char *title);
//protected:
	// Ui
	int YPos;
	Osp::Ui::Controls::ScrollPanel* pScrollPanel;
	Osp::Ui::Controls::Form*	pPreviousForm;
	Osp::Graphics::Rectangle clientArea;

public:

	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Osp::Ui::Control& source, int actionId);
    void 	OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);


};


#endif /* DIALOGFORM_H_ */
