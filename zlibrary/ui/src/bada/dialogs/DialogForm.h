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
#define ID_FORMAT_CUSTOM  		106

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
	bool showApplyButton;
	bool Initialize(const char *title);
	void SetPreviousForm(Osp::Ui::Controls::Form* preForm);
	//result  AddControls();
	result  AddTab(const char *title);
//protected:
	// Ui
//	int YPos;
//	Osp::Ui::Controls::ScrollPanel* pScrollPanel;
	Osp::Ui::Controls::Form*	pPreviousForm;
	//Osp::Graphics::Rectangle clientArea;
	ComboOptionPopup*	__pComboOptionPopup;
	ColorComboOptionPopup*	__pColorComboOptionPopup;
	ZLbadaOptionsDialog* __badaOptionsDialog;

   int GroupCount;
    Osp::Ui::Controls::GroupedList* __pCustomList;
   // Osp::Ui::Controls::CustomList* __pCustomList;
    Osp::Ui::Controls::CustomListItemFormat* __pCustomListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pCustomListItemFormat1;
    Osp::Ui::Controls::CustomListItemFormat* __pCustomListItemFormat2;
    Osp::Ui::Controls::CustomListItemFormat* __pColorListItemFormat;
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
	void DeleteComboOptionPopup();

};


#endif /* DIALOGFORM_H_ */
