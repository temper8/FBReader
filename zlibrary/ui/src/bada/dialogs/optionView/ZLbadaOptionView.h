/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __ZLBADAOPTIONVIEW_H__
#define __ZLBADAOPTIONVIEW_H__


#include <ZLOptionsDialog.h>
#include <ZLOptionEntry.h>
#include "../../../../../core/src/dialogs/ZLOptionView.h"
#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FContent.h>
#include "../DialogForm.h"
#include "../ZLbadaDialogContent.h"
//class ZLbadaDialogContent;

class SpinOptionView;
class ComboOptionView;
class ColorOptionView;

class ZLbadaOptionView : public ZLOptionView {

protected:
	ZLbadaOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn) : ZLOptionView(name, tooltip, option), myTab(tab), myRow(row), myFromColumn(fromColumn), myToColumn(toColumn) {}

	void _show();
	void _hide();
	void _setActive(bool active);

protected:
	int groupIndex;
	int itemIndex;
	int myRow, myFromColumn, myToColumn;
public :

	ZLbadaDialogContent *myTab;
	virtual void OnActionPerformed(int actionId) = 0;
	//std::vector<QWidget*> myWidgets;
};

class ChoiceOptionView : public ZLbadaOptionView {

public:
	ChoiceOptionView(const std::string &name, const std::string &tooltip, ZLChoiceOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
	~ChoiceOptionView() { }

protected:
	void _createItem();
	//void _setActive(bool active);
	void _onAccept() const;

private:
	virtual void OnActionPerformed(int actionId);
//	QGroupBox *myGroupBox;
//	QRadioButton **myButtons;
};

class BooleanOptionView : public ZLbadaOptionView {

public:
	BooleanOptionView(const std::string &name, const std::string &tooltip, ZLBooleanOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}

protected:
	void _createItem();
	//void _setActive(bool active);
	void _onAccept() const;
    bool checkState;
private:
	virtual void OnActionPerformed(int actionId);
//	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	void onStateChanged(bool);

private:
//	Osp::Ui::Controls::CheckButton *myCheckButton;
};

class Boolean3OptionView : public ZLbadaOptionView {

public:
	Boolean3OptionView(const std::string &name, const std::string &tooltip, ZLBoolean3OptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}

protected:
	void _createItem();
	//void _setActive(bool active);
	void _onAccept() const;
	virtual void OnActionPerformed(int actionId);
//private Q_SLOTS:
//	void onStateChanged(int) const;

private:
//	Osp::Ui::Controls::CheckButton *myCheckButton;
};

class StringOptionView :  public ZLbadaOptionView,
						  public Osp::Ui::ITextEventListener {

public:
	StringOptionView(const std::string &name, const std::string &tooltip, ZLStringOptionEntry *option, ZLbadaDialogContent *tab, bool passwordMode, int row, int fromColumn, int toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn), myPasswordMode(passwordMode) {}

private:
	void _createItem();
	//void _setActive(bool active);
	void _onAccept() const;
	void reset();
	virtual void OnActionPerformed(int actionId);
//private Q_SLOTS:
//	void onValueEdited(const QString &value);

private:
//	Osp::Ui::Controls::EditField* myEditField;
	//char *myLineEdit;
	Osp::Ui::Controls::Keypad *__pKeypad;
	OptionListItem* pItem;
	const bool myPasswordMode;
	std::string myValue;
    virtual void OnTextValueChanged(const Osp::Ui::Control& source);
    virtual void OnTextValueChangeCanceled(const Osp::Ui::Control& source);
    void ShowKeypad();
};

class SpinOptionPopup	: public Osp::Ui::Controls::Popup,
						  public Osp::Ui::IAdjustmentEventListener,
						  public Osp::Ui::IActionEventListener{
public:
	SpinOptionPopup(void);
	virtual ~SpinOptionPopup(void);
	result Construct(const Osp::Ui::Controls::Form* pParentForm, SpinOptionView* parentSpinOptionView);

protected:
	static const int ID_BUTTON_CREATE = 100;
	static const int ID_BUTTON_CANCEL = 101;
	int tmpValue;
public:
	static const int categoryNameMaxLength = 100;	// The maximum length of category name is 100 characters.

public:
//	Osp::Ui::Controls::Slider* pSlider;
	Osp::Ui::Controls::Form* 		__pParentForm;
	SpinOptionView* 		__parentSpinOptionView;

private:
    virtual void OnAdjustmentValueChanged(const Osp::Ui::Control& source, int adjustment);
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

};

class SpinOptionView : public ZLbadaOptionView, public Osp::Ui::IAdjustmentEventListener  {

public:
	SpinOptionView(const std::string &name, const std::string &tooltip, ZLSpinOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
	const std::string &title() const {return ZLOptionView::name();};
	int initialValue() const {return ((ZLSpinOptionEntry&)*myOption).initialValue();};
	int minValue() const {return ((ZLSpinOptionEntry&)*myOption).minValue();};
	int maxValue() const {return ((ZLSpinOptionEntry&)*myOption).maxValue();};
	int step() const {return ((ZLSpinOptionEntry&)*myOption).step();};
protected:
	void _createItem();
	int myValue;
	void _onAccept() const;
    void OnAdjustmentValueChanged(const Osp::Ui::Control& source, int adjustment);
    virtual void OnActionPerformed(int actionId);
private:
    void UpdateItem();
//	Osp::Ui::Controls::EditField* myEditField;
//	Osp::Ui::Controls::Slider* pSlider;
//	OptionListItem* pItem;
	//QSpinBox *mySpinBox;
	friend class SpinOptionPopup;
};



class ComboOptionPopup	: public Osp::Ui::Controls::Popup, public Osp::Ui::IActionEventListener{
public:
	ComboOptionPopup(void);
	virtual ~ComboOptionPopup(void);
	result Construct(const Osp::Ui::Controls::Form* pParentForm, ComboOptionView* parentComboOptionView);

protected:
	static const int ID_BUTTON_CREATE = 100;
	static const int ID_BUTTON_CANCEL = 101;

public:
	static const int categoryNameMaxLength = 100;	// The maximum length of category name is 100 characters.

public:
	Osp::Ui::Controls::Form* 		__pParentForm;
	ComboOptionView* 		__parentComboOptionView;
	Osp::Ui::Controls::List*		__pComboList;

private:

	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

};

//public Osp::Ui::Controls::Panel,
class ComboOptionView : public ZLbadaOptionView,
						public Osp::Ui::IActionEventListener,
						public Osp::Ui::IItemEventListener  {

public:
	ComboOptionView(const std::string &name, const std::string &tooltip, ZLComboOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn){}

	const std::string &title() const {return ZLOptionView::name();};
	shared_ptr<ZLOptionEntry> option() const 	{ return  myOption;};

private:
	void _createItem();
	//void _setActive(bool active);
	void _onAccept() const;
	void reset();
	OptionListItem* pItem;
    int selected;
    std::string comboValue;
private:
	virtual void OnActionPerformed(int actionId);
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
    void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);

 //   void 	OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs);

	//void onStateChanged(bool) const;
private :
	void onValueSelected(int index);
//	void onValueEdited(const QString &value);

private:

//	Osp::Ui::Controls::EditField* myEditField;
//	Osp::Ui::Controls::CheckButton *myCheckButton;
//	ComboOptionPopup*	__pComboOptionPopup;

	//QComboBox *myComboBox;
};
/*
class KeyOptionView : public QObject, public ZLQtOptionView {

Q_OBJECT

public:
	KeyOptionView(const std::string &name, const std::string &tooltip, ZLKeyOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLQtOptionView(name, tooltip, option, tab, row, fromColumn, toColumn), myComboBox(0), myKeyEditor(0) {}

private:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;
	void reset();

private Q_SLOTS:
	void onValueChanged(int);

private:
	QComboBox *myComboBox;
	QLineEdit *myKeyEditor;
	std::string myCurrentKey;

friend class KeyLineEdit;
};
*/
class ColorComboOptionPopup	: public Osp::Ui::Controls::Popup,
							  public Osp::Ui::IAdjustmentEventListener,
							  public Osp::Ui::IActionEventListener{
public:
	ColorComboOptionPopup(void);
	virtual ~ColorComboOptionPopup(void);
	result Construct(const Osp::Ui::Controls::Form* pParentForm, ColorOptionView* parentColorOptionView);

protected:
	static const int ID_BUTTON_CREATE = 100;
	static const int ID_BUTTON_CANCEL = 101;

public:
	static const int categoryNameMaxLength = 100;	// The maximum length of category name is 100 characters.

public:
	Osp::Ui::Controls::Form* 		__pParentForm;
	ColorOptionView* 		__parentColorOptionView;
	Osp::Ui::Controls::List*		__pComboList;

private:
	ZLColor tmpColor;
	Osp::Ui::Controls::Slider* sliderR;
	Osp::Ui::Controls::Slider* sliderG;
	Osp::Ui::Controls::Slider* sliderB;
	Osp::Ui::Controls::Panel* panelColor;
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
    virtual void OnAdjustmentValueChanged(const Osp::Ui::Control& source, int adjustment);

};



class ColorOptionView : public ZLbadaOptionView,
						public Osp::Ui::Controls::ICustomListElement,
						public Osp::Ui::IActionEventListener,
						public Osp::Ui::IItemEventListener  {

public:
	ColorOptionView(const std::string &name, const std::string &tooltip, ZLColorOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
	void Update();
private:
	void _createItem();
	void _onAccept() const;
	void reset();
	OptionListItem* pItem;
//	QSlider *createColorSlider(QGridLayout *layout, int index, const ZLResource &resource, int value);

//private Q_SLOTS:
//	void onSliderMove(int);
	virtual void OnActionPerformed(int actionId);
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
    void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);

private:
	static std::vector<std::string> ourStrings;
	static std::vector<ZLColor> ourColors;
	static void addColor(const std::string &name, ZLColor color);
	static void initVectors();
//	QSlider *myRSlider, *myGSlider, *myBSlider;
//	QLabel *myColorBar;
	ZLColor myColor;
	result DrawElement(const Osp::Graphics::Canvas& canvas, const Osp::Graphics::Rectangle& rect, Osp::Ui::Controls::CustomListItemStatus itemStatus);
	friend class ColorComboOptionPopup;
};


class StaticTextOptionView : public ZLbadaOptionView,
							 public Osp::Ui::Controls::ICustomListElement
							 {

public:
	StaticTextOptionView(const std::string &name, const std::string &tooltip, ZLStaticTextOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn), myCaption(0), myLabel(0) {}

private:
	void _createItem();
	void _onAccept() const;

private:
	Osp::Graphics::EnrichedText* pEnrichedText;
	void addParagraph(std::string &text);
	int initText(const char *caption, std::string &text,  int height);
	result DrawElement(const Osp::Graphics::Canvas& canvas, const Osp::Graphics::Rectangle& rect, Osp::Ui::Controls::CustomListItemStatus itemStatus);
	OptionListItem* pItem;
	Osp::Base::String *myCaption;
	Osp::Base::String *myLabel;
	virtual void OnActionPerformed(int actionId);
};

class ButtonAction;

class PictureView : public ZLbadaOptionView,
					public Osp::Ui::IActionEventListener
					{

public:
        PictureView(const std::string &name, const std::string &tooltip, ZLPictureOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn);
        ~PictureView();
        void updateActions();
private:
        void _createItem();
        void _onAccept() const;

private:

    	const  std::vector<shared_ptr<ZLRunnableWithKey> > &myActions;
        ButtonAction* myBottonActions[4];
        shared_ptr<ZLImage> myImage;
        //shared_ptr<ZLTreeTitledNode> myNode;
      //  const ZLTreeTitledNode* myNode;
        Osp::Graphics::Bitmap* makeCover(Osp::Graphics::Bitmap* srcBmp);
    	virtual void OnActionPerformed(int actionId);
    	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
};

class ButtonView : public ZLbadaOptionView,
				   public Osp::Ui::IActionEventListener{

public:
		ButtonView(const std::string &name, const std::string &tooltip, ZLButtonOptionEntry *option, ZLbadaDialogContent *tab, int row, int fromColumn, int toColumn);

private:
        void _createItem();
        void _onAccept() const;

private:
        shared_ptr<ZLRunnableWithKey> myAction;
    	virtual void OnActionPerformed(int actionId);
    	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
};
#endif /* __ZLBADAOPTIONVIEW_H__ */
