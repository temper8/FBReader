#ifndef _BADAFORM_H_
#define _BADAFORM_H_

#include <string>

#include <FBase.h>
#include <FUi.h>
//#include "ZLView.h"
#include <FGraphics.h>
#include <FContent.h>

class ZLbadaViewWidget;
class DialogForm;

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
	int MenuItemCount;
	//static const int ID_BUTTON_OK = 101;
	Osp::Ui::Controls::Button *__pButtonOk;
	static const int ID_OPTIONKEY = 100;
	static const int ID_OPTIONMENU_ITEM0 = 200;

	Osp::Ui::Controls::OptionMenu* __pOptionMenu;
	std::string ActionIdList[16];
	Osp::Graphics::Canvas* myCanvas;
	Osp::Graphics::Canvas* capturedCanvas;
	Osp::Graphics::Bitmap* pCapturedBitmap;
	Osp::Graphics::Bitmap* pNextPageBitmap;
	Osp::Graphics::Point startTouchPosition;
	Osp::Graphics::Rectangle formRect;
public:
	int ScreenHeight;
	int ScreenWidth;
	bool showNewPage;
//	DialogForm* CreateDalogForm(const char* name);
	DialogForm* CreateDalogForm(void);
    void AddMenuItem(const std::string &name,const  std::string &id);
    Osp::Content::ContentSearchResult* pSearchResultInfo;
	void goOpenFileForm();
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
	void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs);
};

#endif	//_BADAFORM_H_
