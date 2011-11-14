#ifndef _B2FORM_H_
#define _B2FORM_H_

#include <FBase.h>
#include <FUi.h>
//#include "ZLView.h"
#include <FGraphics.h>

class ZLbadaViewWidget;


class badaForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::ITouchEventListener,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IOrientationEventListener
{

// Construction
public:
	badaForm(ZLbadaViewWidget &Holder);
	virtual ~badaForm(void);
	bool Initialize(void);

// Implementation
protected:
	static const int ID_BUTTON_OK = 101;
	Osp::Ui::Controls::Button *__pButtonOk;
	static const int ID_OPTIONKEY = 100;
	static const int ID_OPTIONMENU_ITEM1 = 200;
	static const int ID_OPTIONMENU_ITEM2 = 201;
	static const int ID_OPTIONMENU_ITEM3 = 202;
	static const int ID_OPTIONMENU_ITEM4 = 203;
	static const int ID_OPTIONMENU_ITEM5 = 204;
	static const int ID_OPTIONMENU_ITEM6 = 205;
	Osp::Ui::Controls::OptionMenu* __pOptionMenu;

public:

	ZLbadaViewWidget &myHolder;
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	virtual void OnOrientationChanged( const Osp::Ui::Control&  source,  Osp::Ui::OrientationStatus  orientationStatus );

	virtual void  OnTouchDoublePressed (const Osp::Ui::Control &source,	const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchFocusIn (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchFocusOut (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchLongPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchMoved (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchReleased (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);

};

#endif	//_B2FORM_H_
