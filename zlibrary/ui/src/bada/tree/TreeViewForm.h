
#ifndef TREEVIEWFORM_H_
#define TREEVIEWFORM_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FContent.h>
//#include "ZLbadaTreeModel.h"
#include "ZLTreeNode.h"
#include "ZLTreeTitledNode.h"
#include <ZLTreeDialog.h>

#define ID_LIST_ITEM  			101
#define ID_LIST_TEXT_TITLE  	102
#define ID_LIST_TEXT_SUBTITLE  	103
#define ID_LIST_BITMAP  		104
#define ID_LIST_CHECKBOX  		105
#define ID_FORMAT_CUSTOM  		106

//class ZLTreeDialog;

class TreeViewForm :
	public Osp::Ui::Controls::Form,
	//public Osp::Ui::ITouchEventListener,
	public Osp::Ui::IActionEventListener,
    //public Osp::Ui::IItemEventListener,
    public Osp::Ui::ICustomItemEventListener,
	public Osp::Ui::IOrientationEventListener
	//public Osp::Base::Runtime::Thread
{
public:
	TreeViewForm();
	~TreeViewForm();
	//bool Initialize(const char *title);
	bool Initialize(ZLTreeDialog* treeDialog);
	Osp::Base::Runtime::Monitor* myMonitor;
	shared_ptr<ZLTreeDialog> __myTreeDialog;
    bool showIcons;
protected:
	// Ui
//	bool OnStart(void);
	// Called after the Run() method is called.
//	void OnStop(void);

	ZLTreeDialog* myTreeDialog;
	static const int ID_CONTEXT_ITEM = 200;
	static const int ID_CONTEXT_ITEM1 = 201;

	Osp::Ui::Controls::Form*			pPreviousForm;
	Osp::Ui::Controls::Button*			pBtnClose;
	Osp::Ui::Controls::List*			__pLstSearchList;
	Osp::Ui::Controls::Popup*			__pCommonPopup;
	Osp::Ui::Controls::ContextMenu* __pContextMenuIconText;

	Osp::Base::Collection::IList*				__pLstContentType;
	Osp::Base::Collection::IList*				__pLstContentInfo;
	Osp::Content::ContentType					__ContentType;

	void    _ClearContentInfoList();
	void CreateContextMenuListStyle(void);
	Osp::Graphics::Point TouchPosition;

public:


	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Osp::Ui::Control& source, int actionId);
//    void 	OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);
	virtual void OnOrientationChanged( const Osp::Ui::Control&  source,  Osp::Ui::OrientationStatus  orientationStatus );


    virtual void  OnTouchDoublePressed (const Osp::Ui::Control &source,	const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchFocusIn (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchFocusOut (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchLongPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchMoved (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchReleased (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);

	void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs);
    virtual void OnItemStateChanged(const Osp::Ui::Control& source, int index, int itemId, Osp::Ui::ItemStatus status);
    virtual void OnItemStateChanged(const Osp::Ui::Control& source, int index, int itemId, int elementId, Osp::Ui::ItemStatus status);



	void	LoadContentInfo(Osp::Content::ContentSearchResult* pSearchResult);

	void    updateItem(ZLTreeTitledNode &node, int index);
	void	UpdateContent();
	void	DeleteContent();
//	ZLbadaTreeModel* myModel;

protected:
	ZLTreeNode* selectedNode;
	bool exitFlag;
//    static const int ID_LIST_ITEM = 101;
//	static const int ID_LIST_TEXT_TITLE = 102;
//	static const int ID_LIST_TEXT_SUBTITLE = 103;
//	static const int ID_LIST_BITMAP = 104;
//	static const int ID_LIST_CHECKBOX = 105;
//	static const int ID_FORMAT_CUSTOM = 106;
	Osp::Graphics::Bitmap* makeIcon(Osp::Graphics::Bitmap* srcBmp);
	Osp::Graphics::Rectangle iconRect;
    Osp::Ui::Controls::CustomList* __pCustomList;
    Osp::Ui::Controls::CustomListItemFormat* __pNoIconsListItemFormat;
    Osp::Ui::Controls::CustomListItemFormat* __pCustomListItemFormat;
   // CustomListElement* __pListElement;
    result AddListItem(Osp::Ui::Controls::CustomList& customList,  Osp::Base::String title, Osp::Base::String subTitle, Osp::Graphics::Bitmap* pBitmapNormal);


public :

	void SetPreviousForm(Osp::Ui::Controls::Form* preForm);
 //   void setModel(ZLbadaTreeModel* TreeModel);
};
//inline void TreeViewForm::setModel(ZLbadaTreeModel* TreeModel) {myModel = TreeModel; };
#endif /* TREEVIEWFORM_H_ */
