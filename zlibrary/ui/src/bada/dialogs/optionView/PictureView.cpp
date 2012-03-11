
#include <cctype>


#include <ZLStringUtil.h>
#include <ZLDialogManager.h>
//#include "../util/ZLQtKeyUtil.h"

#include "ZLbadaOptionView.h"
#include "ZLOptionEntry.h"
#include "../ZLbadaDialogContent.h"
#include "../DialogForm.h"
#include "../../image/ZLbadaImageManager.h"

#include <FIo.h>

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Content;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;

class ButtonAction : public Osp::Ui::Controls::ICustomListElement {
public :
	ButtonAction(PictureView* holder, Bitmap* Bmp1, Bitmap* Bmp2);
	~ButtonAction();
    void SetCaption(std::string &text);
	void SetAction(shared_ptr<ZLRunnableWithKey> action);
	bool OnActionPerformed(int actionId);
	bool visible;

private :
	Osp::Graphics::EnrichedText* pEnrichedText;
	PictureView* myHolder;
	shared_ptr<ZLRunnableWithKey> myAction;
	Bitmap* myButtonBmp1;
	Bitmap* myButtonBmp2;
	result DrawElement(const Osp::Graphics::Canvas& canvas, const Osp::Graphics::Rectangle& rect, Osp::Ui::Controls::CustomListItemStatus itemStatus);

};
bool ButtonAction::OnActionPerformed(int actionId){
	AppLog("myAction->run %d",actionId);
	if (!myAction.isNull()) {
		//std::string text = myAction->text(ZLResource::resource("networkView")["bookNode"]);
		std::string text = myAction->key().Name;
		AppLog("OnActionPerformed= %s", text.c_str());
		myAction->run();
		if (text=="readDemo") 	return true;
		if (text=="read") 	return true;
	}
	return false;
}

void  ButtonAction::SetAction(shared_ptr<ZLRunnableWithKey> action){
	myAction=action;
	std::string text = myAction->text(ZLResource::resource("networkView")["bookNode"]);
	AppLog("SetActiont %s", text.c_str());
	SetCaption(text);
	visible = true;
}

ButtonAction::~ButtonAction(){
	AppLog("~ButtonAction  1");
	if(pEnrichedText) {
		AppLog("~ButtonAction  2");
		delete pEnrichedText;
	}
	AppLog("~ButtonAction  3");
}

ButtonAction::ButtonAction(PictureView* holder, Bitmap* Bmp1, Bitmap* Bmp2):myHolder(holder), myAction(null), myButtonBmp1(Bmp1), myButtonBmp2(Bmp2)
	{
	 result r = E_SUCCESS;
	 TextElement* pTextElement1 = null;
    pTextElement1 = new TextElement();
	pEnrichedText = new EnrichedText();
    r = pEnrichedText->Construct(Dimension(220, 50));
    //if (IsFailed(r))   {  goto CATCH;  }
    pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
    pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
    pEnrichedText->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);


    r = pTextElement1->Construct("Text Buuton");
    	//if (IsFailed(r))    	    { 	    	        goto CATCH;	    	    }
   	pTextElement1->SetTextColor(Color::COLOR_BLACK);
       	{
       	Font font;
       	font.Construct(FONT_STYLE_PLAIN, 25);
       	pTextElement1->SetFont(font);
      	}
    pEnrichedText->Add(*pTextElement1);
}

void ButtonAction::SetCaption(std::string &text){
	result r = E_SUCCESS;
	TextElement* pTextElement1 = null;
	AppLog("SetCaption  1 %s",text.c_str());
	pEnrichedText->RemoveAllTextElements(true);
	//pEnrichedText->RemoveAll(false);
	AppLog("SetCaption  2");
    pTextElement1 = new TextElement();
    r = pTextElement1->Construct(text.c_str());
    	//if (IsFailed(r))    	    { 	    	        goto CATCH;	    	    }
   	pTextElement1->SetTextColor(Color::COLOR_BLACK);
       	{
       	Font font;
       	font.Construct(FONT_STYLE_PLAIN, 25);
       	pTextElement1->SetFont(font);
      	}
    pEnrichedText->Add(*pTextElement1);
}

result ButtonAction::DrawElement(const Osp::Graphics::Canvas& canvas, const Osp::Graphics::Rectangle& rect, Osp::Ui::Controls::CustomListItemStatus itemStatus)
{
	result r = E_SUCCESS;
	if (!visible) return r;
//	AppLog("DrawElement");
	Osp::Graphics::Canvas* pCanvas = const_cast<Osp::Graphics::Canvas*>(&canvas);
//	AppLog("pCanvas");
	switch(itemStatus) {
	case  CUSTOM_LIST_ITEM_STATUS_NORMAL:
		    pCanvas->DrawBitmap(rect,*myButtonBmp1);
			break;
	case  CUSTOM_LIST_ITEM_STATUS_SELECTED:
	    pCanvas->DrawBitmap(rect,*myButtonBmp2);
		    break;
	case  CUSTOM_LIST_ITEM_STATUS_FOCUSED:
	    pCanvas->DrawBitmap(rect,*myButtonBmp2);
			break;
	default : break;
	}

/*	pCanvas->SetLineWidth(5);
	pCanvas->SetForegroundColor(Osp::Graphics::Color::COLOR_GREEN);
	if (pCanvas->DrawRectangle(rect) != E_SUCCESS)
		return r;
*/

	//pCanvas->SetForegroundColor(Osp::Graphics::Color::COLOR_BLACK);
	if (pCanvas->DrawText(Osp::Graphics::Point(rect.x, rect.y+10), *pEnrichedText) != E_SUCCESS)
		//return r;

	return r;
}

PictureView::PictureView(const std::string &name, const std::string &tooltip, ZLPictureOptionEntry *option, ZLbadaDialogContent *tab,int row,int fromColumn,int  toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn), myActions(option->myActions) {
	 AppLog("PictureView::PictureView");
	 //myNode = option->node();
	  AppLog("PictureView::PictureView 1");

	  myImage = option->image();
    AppLog("PictureView::PictureView 2");
}

PictureView::~PictureView(){
	  AppLog("~PictureView 1");
	delete myBottonActions[0];
	delete myBottonActions[1];
	delete myBottonActions[2];
	delete myBottonActions[3];
	  AppLog("~PictureView 2");
}

void PictureView::updateActions(){
	std::string s0 = "Button0";
	std::string s1 = "Button1";
	//myBottonActions[0]->SetCaption(s0);
	//myBottonActions[1]->SetCaption(s1);
	//myBottonActions[2]->SetCaption(s0);
	///myBottonActions[3]->SetCaption(s1);
	myBottonActions[0]->visible = false;
	myBottonActions[1]->visible = false;
	myBottonActions[2]->visible = false;
	myBottonActions[3]->visible = false;

	int actionsCount = myActions.size();
	AppLog("actionsCount %d", actionsCount);

	actionsCount = myActions.size();
	AppLog("after init actionsCount %d", actionsCount);
	actionsCount =0;
	for (int i =1; i<myActions.size();i++){
		shared_ptr<ZLRunnableWithKey> a = myActions[i];
		if (a->makesSense()&&(actionsCount<4)) { AppLog("makesSense true %d",actionsCount);
			myBottonActions[actionsCount++]->SetAction(a);
		}
		else AppLog("makesSense false");
	}
}

void PictureView::_createItem() {
    AppLog("PictureView::_createItem");
    if (myImage.isNull()) {
        return;
    }
    Bitmap *pBmp = new Bitmap;
    pBmp->Construct(Dimension(200,300), BITMAP_PIXEL_FORMAT_ARGB8888);

	shared_ptr<ZLImage> cover = myImage;
	if (cover.isNull()) {	AppLog("cover.isNull()");}
	else
			{
			shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*cover);
			if (!coverData.isNull()) {
				//pBitmapLeftIcon = 	((ZLbadaImageData&)coverData).pBitmap;
				//Bitmap *pBmp;
				ZLImageData &image = *coverData;
				Bitmap *tmpBmp = 	((ZLbadaImageData&)image).pBitmap;
				int imageWidth = tmpBmp->GetWidth();
				int imageHeight = tmpBmp->GetHeight();
				AppLog("image w = %d, h = %d", imageWidth, imageHeight);
				pBmp->Merge(Point(0,0), *tmpBmp, Rectangle(0,0,imageWidth,imageHeight));
			}
			else
			 {	AppLog("coverData.isNull()");}

			}

	myBottonActions[0] = new ButtonAction(this, myTab->form()->buttonBmp, myTab->form()->buttonBmp2);
	myBottonActions[1] = new ButtonAction(this, myTab->form()->buttonBmp, myTab->form()->buttonBmp2);
	myBottonActions[2] = new ButtonAction(this, myTab->form()->buttonBmp, myTab->form()->buttonBmp2);
	myBottonActions[3] = new ButtonAction(this, myTab->form()->buttonBmp, myTab->form()->buttonBmp2);
//    Bitmap *buttonBmp = new Bitmap;
 //   buttonBmp->Construct(*myTab->form()->buttonBmp, Osp::Graphics::Rectangle(0,0,300,52));
//    Bitmap *buttonBmp2 = new Bitmap;
 //   buttonBmp2->Construct(*myTab->form()->buttonBmp2, Osp::Graphics::Rectangle(0,0,300,52));
	//ZLButtonOptionEntry &entry = (ZLButtonOptionEntry&)*myOption;
	updateActions();
	OptionListItem* pItem = new OptionListItem(this);
	pItem->Construct(330);
	pItem->SetItemFormat(*myTab->form()->__pImageViewListItemFormat);
	pItem->SetElement(ID_LIST_BACKGROUND, String(""));
	pItem->SetElement(ID_LIST_BITMAP1, *myBottonActions[0]);
	pItem->SetElement(ID_LIST_BITMAP2, *myBottonActions[1]);
	pItem->SetElement(ID_LIST_BITMAP3, *myBottonActions[2]);
	pItem->SetElement(ID_LIST_BITMAP4, *myBottonActions[3]);
	//*myTab->form()->__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP4,false);
//	*myTab->form()->__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP4, true);
	//pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
	//pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
	pItem->SetElement(ID_LIST_BITMAP, *pBmp, pBmp);
	//pItem->SetCheckBox(ID_LIST_CHECKBOX);
	//pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);

	groupIndex = myTab->form()->GroupCount-1;
	itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	AppLog("groupIndex =%d itemIndex=%d",groupIndex,itemIndex);
	//myTab->form()->__pCustomList->GetLastCheckedItemIndex( groupIndex, itemIndex);
	//checkState = ((ZLBooleanOptionEntry&)*myOption).initialState();
//	myTab->form()->__pCustomList->SetItemEnabled(groupIndex,itemIndex,false);


	AppLog("PictureView::_createItem() end");
}

void PictureView::_onAccept() const {
	AppLog("PictureView::_onAccept()");
}

void PictureView::OnActionPerformed(const Control& source, int actionId)
{
	AppLog("PictureView::OnActionPerformed 1 %d",actionId);
}

void PictureView::OnActionPerformed(int actionId){
	AppLog("PictureView::OnActionPerformed 2 %d",actionId);
	bool exitFlag=false;
	bool needUpdate= false;
	   switch (actionId)
	    {
	        case ID_LIST_BITMAP1:
	        	if (myBottonActions[0]->visible)
	        	{
	        		exitFlag=myBottonActions[0]->OnActionPerformed(actionId);
	        		needUpdate= true;
	        	}
	        	break;
	        case ID_LIST_BITMAP2:
	        	if (myBottonActions[1]->visible)
	        	{
	        		exitFlag=myBottonActions[1]->OnActionPerformed(actionId);
	        		needUpdate= true;
	        	}
	        	break;
	        case ID_LIST_BITMAP3:
	        	if (myBottonActions[2]->visible)
	        	{
	        		needUpdate= true;
	        		exitFlag=myBottonActions[2]->OnActionPerformed(actionId);
	        	}
	        	break;
	        case ID_LIST_BITMAP4:
	        	if (myBottonActions[3]->visible){
	        		needUpdate= true;
	        		exitFlag=myBottonActions[3]->OnActionPerformed(actionId);
	        	}
	          	break;
	        default:
	        	break;
	    }
	   AppLog("PictureView::OnActionPerformed 2222 %d",actionId);
	   if (exitFlag) {
			myTab->form()->pPreviousForm->SendUserEvent(2, null);
			return;
	   }
	   if (needUpdate) 	{
		   updateActions();
		   myTab->form()->__pCustomList->RefreshItem( groupIndex,itemIndex );
		   myTab->form()->RequestRedraw(true);
		   //	myTab->form()->RequestRedraw(true);
		   //myTab->form()->Draw();
	   }



}
