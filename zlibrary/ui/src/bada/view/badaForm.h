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
	public Osp::Ui::IOrientationEventListener,
	public Osp::Ui::IKeyEventListener,
	public Osp::Base::Runtime::ITimerEventListener  {

// Construction
	public:
		enum DrawMode {
			DRAW_BLACK_SCREEN = 0,
			SLIDE_NEXT = 1,
			SLIDE_PREV = 2,
			DRAW_CURRENT_PAGE = 3,
		};
	public:
		DrawMode myDrawMode;
		static badaForm &Instance();

	private:
		static badaForm *ourInstance;


public:
	badaForm(void);
	virtual ~badaForm(void);
	bool Initialize();
	bool Initialize(ZLbadaViewWidget* Holder);

// Implementation
protected:
	bool applicationWindowsNotInited;
	int MenuItemCount;
	//static const int ID_BUTTON_OK = 101;
	Osp::Ui::Controls::Button *__pButtonOk;
	static const int ID_OPTIONKEY = 100;
	static const int ID_OPTIONMENU_ITEM0 = 200;

	Osp::Ui::Controls::OptionMenu* __pOptionMenu;
	std::string ActionIdList[16];
	Osp::Graphics::Canvas* pCanvas;
//	Osp::Graphics::Canvas* myCanvas;
	Osp::Graphics::Canvas* capturedCanvas;
	Osp::Graphics::Bitmap* pCapturedBitmap;
	Osp::Graphics::Bitmap* pNextPageBitmap;
	Osp::Graphics::Point startTouchPosition;
	Osp::Graphics::Rectangle formRect;
	Osp::Graphics::Rectangle srcRect;
//	int touchMove;
//	bool showNewPage;
	bool needRepaintHolder;
	bool endOfBook;
	bool prevPage;
	bool touchMoved;
	int apiVersion;
	result GetSystemInfomation(void);
	Osp::Base::Runtime::Timer* myTimer;
	int dx;
	int vx;
	void PrevPage();
	void NextPage();
	void OnTimerExpired(Osp::Base::Runtime::Timer& timer);

public:
	int ScreenHeight;
	int ScreenWidth;

//	DialogForm* CreateDalogForm(const char* name);
	DialogForm* CreateDalogForm(void);
    void AddMenuItem(const std::string &name,const  std::string &id);
    Osp::Content::ContentSearchResult* pSearchResultInfo;
	void goOpenFileForm();
	ZLbadaViewWidget* myHolder;

	void setOrientation(int angle);

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

	virtual void  OnKeyLongPressed (const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode);
	virtual void  OnKeyPressed (const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode);
	virtual void  OnKeyReleased (const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode);


};

#endif	//_BADAFORM_H_
