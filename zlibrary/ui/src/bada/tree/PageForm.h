#ifndef __PAGEFORM_H__
#define __PAGEFORM_H__

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FContent.h>

#include <shared_ptr.h>
#include <ZLDialogContent.h>
#include <ZLApplication.h>
#include <ZLTreePageNode.h>


class PageForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
    public Osp::Ui::IItemEventListener

{
public:
	PageForm();
	~PageForm();
	bool Initialize(const ZLTreePageNode& pageNode);

protected:
	// Ui
	Osp::Ui::Controls::Form*			pPreviousForm;
	Osp::Ui::Controls::Button*			pBtnClose;
	Osp::Ui::Controls::List*			__pLstSearchList;
	Osp::Ui::Controls::Popup*			__pCommonPopup;

	Osp::Base::Collection::IList*				__pLstContentType;
	Osp::Base::Collection::IList*				__pLstContentInfo;
	Osp::Content::ContentType					__ContentType;



public:


	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Osp::Ui::Control& source, int actionId);
    void 	OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);



	void	SetPreviousForm(Osp::Ui::Controls::Form* preForm);
	void	LoadContentInfo(Osp::Content::ContentSearchResult* pSearchResult);



};
/*
class ZLQtPageDialog : public QDialog {
    Q_OBJECT

public:
    ZLQtPageDialog(const ZLTreePageNode& pageNode, QWidget* parent = 0);
    ~ZLQtPageDialog();

public:
    bool run();

private:
    shared_ptr<ZLDialogContent> myContent;
    const ZLTreePageNode& myPageNode;
    TreeNodeActionsMenu* myPageMenu;
};

class NodePictureWidget : public PictureWidget {
    Q_OBJECT
public:
    NodePictureWidget(const ZLTreePageNode& pageNode, QWidget* parent = 0);
public slots:
    void refresh();
private:
    ImageProvider* myImageProvider;
    const ZLTreePageNode& myPageNode;
};
*/
#endif // __PAGEFORM_H__
