/*
 * OpenFileForm.h
 *
 *  Created on: 15.11.2011
 *      Author: Alex
 */

#ifndef OPENFILEFORM_H_
#define OPENFILEFORM_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FContent.h>

class OpenFileForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
    public Osp::Ui::IItemEventListener

{
public:
	OpenFileForm();
	~OpenFileForm();
	bool Initialize(void);

protected:
	// Ui
	Osp::Ui::Controls::Form*			pPreviousForm;
	Osp::Ui::Controls::Button*			pBtnClose;
	Osp::Ui::Controls::List*			__pLstSearchList;
	Osp::Ui::Controls::Popup*			__pCommonPopup;

	Osp::Base::Collection::IList*				__pLstContentType;
	Osp::Base::Collection::IList*				__pLstContentInfo;
	Osp::Content::ContentType					__ContentType;

	void    _ClearContentInfoList();
public:
	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Osp::Ui::Control& source, int actionId);
    void 	OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);



	void	SetPreviousForm(Osp::Ui::Controls::Form* preForm);
	void	LoadContentInfo(Osp::Content::ContentSearchResult* pSearchResult);

	void	UpdateContent();
	void	DeleteContent();

};

#endif /* OPENFILEFORM_H_ */
