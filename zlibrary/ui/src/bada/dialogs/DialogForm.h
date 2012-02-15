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
#include <shared_ptr.h>
#include <ZLOptionsDialog.h>

#define	ID_ACT_UPDATE	1700
#define ID_ACT_DELETE	1701
#define ID_ACT_CLOSE	1702
#define ID_BUTTON_CHECKED    1801
#define ID_BUTTON_UNCHECKED  1802

#define ID_LIST_ITEM  			101
#define ID_LIST_TEXT_TITLE  	102
#define ID_LIST_TEXT_SUBTITLE  	103
#define ID_LIST_BITMAP  		104
#define ID_LIST_CHECKBOX  		105
#define ID_LIST_CUSTOM  		106
#define ID_LIST_BITMAP1  		107
#define ID_LIST_BITMAP2  		108
#define ID_LIST_BITMAP3  		109
#define ID_LIST_BITMAP4  		110
#define ID_LIST_TEXT_BITMAP1  		111
#define ID_LIST_TEXT_BITMAP2  		112
#define ID_LIST_TEXT_BITMAP3  		113
#define ID_LIST_TEXT_BITMAP4  		114
#define ID_LIST_BACKGROUND  		115


class SpinOptionPopup;
class SpinOptionView;
class ComboOptionPopup;
class ComboOptionView;
class ColorComboOptionPopup;
class ColorOptionView;
class ZLbadaOptionsDialog;
class ZLbadaOptionView;

class OptionListItem : public Osp::Ui::Controls::CustomListItem {
public:
	OptionListItem(ZLbadaOptionView*  badaOptionView);
	void OnActionPerformed(int actionId);
	ZLbadaOptionView* mybadaOptionView;
};

class DialogForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
    public Osp::Ui::IGroupedItemEventListener {

public:
	DialogForm();
	virtual ~DialogForm();

	bool Initialize(const char *title, bool showApplyButton);
	void SetPreviousForm(Osp::Ui::Controls::Form* preForm);
	//result  AddControls();
	result  AddTab(const char *title);
//protected:
	// Ui
//	int YPos;
//	Osp::Ui::Controls::ScrollPanel* pScrollPanel;
	Osp::Ui::Controls::Form*	pPreviousForm;
	//Osp::Graphics::Rectangle clientArea;
	SpinOptionPopup* __pSpinOptionPopup;
	ComboOptionPopup*	__pComboOptionPopup;
	ColorComboOptionPopup*	__pColorComboOptionPopup;
	//shared_ptr<ZLOptionsDialog>
	shared_ptr<ZLOptionsDialog> __badaOptionsDialog;
	Osp::Graphics::Bitmap* buttonBmp;
	Osp::Graphics::Bitmap* buttonBmp2;
   int GroupCount;
    Osp::Ui::Controls::GroupedList* __pCustomList;
   // Osp::Ui::Controls::CustomList* __pCustomList;
    Osp::Ui::Controls::CustomListItemFormat* __pComboViewListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pStringViewListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pSpinViewListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pBooleanListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pCustomListItemFormat2;
    Osp::Ui::Controls::CustomListItemFormat* __pColorListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pImageViewListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pButtonViewListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pStaticTextListItemFormat;
 //  virtual void OnItemStateChanged(const Osp::Ui::Control& source, int index, int itemId, int elementId, Osp::Ui::ItemStatus status);
 //  virtual void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);
    virtual void  OnItemStateChanged (const Osp::Ui::Control &source, int groupIndex, int itemIndex, int itemId, Osp::Ui::ItemStatus status);
    virtual void  OnItemStateChanged (const Osp::Ui::Control &source, int groupIndex, int itemIndex, int itemId, int elementId, Osp::Ui::ItemStatus status);


public:

	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Osp::Ui::Control& source, int actionId);
    void 	OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs);
	void ShowComboOptionPopup(ComboOptionView* pComboOptionView);
	void ShowColorComboOptionPopup(ColorOptionView* pColorOptionView);
	void ShowSpinOptionPopup(SpinOptionView* pSpinOptionView);

	void DeleteOptionPopup();

};


#endif /* DIALOGFORM_H_ */
