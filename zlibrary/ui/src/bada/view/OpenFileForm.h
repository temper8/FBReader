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
    public Osp::Ui::IItemEventListener,
    public Osp::Ui::IAnimationEventListener,
    public Osp::Base::Runtime::IRunnable
{
public:
	OpenFileForm();
	~OpenFileForm();
	bool Initialize(void);

protected:
	// Ui
	Object* Run(void);
	static const int ID_SEARCH_DONE			= 300;

	Osp::Ui::Controls::Form*			pPreviousForm;
	Osp::Ui::Controls::Button*			pBtnClose;
	Osp::Ui::Controls::List*			__pLstSearchList;
	Osp::Ui::Controls::Popup*			__pCommonPopup;

	Osp::Base::Collection::IList*				__pLstContentType;
	Osp::Base::Collection::IList*				__pLstContentInfo;
	Osp::Content::ContentType					__ContentType;

 	Osp::Ui::Controls::Popup*			__pProgressPopup;
    Osp::Base::Runtime::Thread* 		__pThread;
	Osp::Ui::Controls::Animation* 		__pAnimation;
	Osp::Base::Collection::ArrayList* 	__pAnimationFrameList;

	void    _ClearContentInfoList();

public:


	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Osp::Ui::Control& source, int actionId);
    void 	OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);
	virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs);
	virtual void OnAnimationStopped(const Osp::Ui::Control& source);


	void	SetPreviousForm(Osp::Ui::Controls::Form* preForm);
	void	LoadContentInfo(Osp::Content::ContentSearchResult* pSearchResult);
    void    StartSearch();
	void 	ShowProgressPopup(const bool show);
	void	UpdateContent();
	void	DeleteContent();

};

#endif /* OPENFILEFORM_H_ */
