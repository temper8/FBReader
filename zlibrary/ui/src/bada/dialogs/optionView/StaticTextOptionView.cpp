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
#include <FText.h>

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Utility;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Content;
using namespace Osp::Graphics;
using namespace Osp::Text;

int stringLength(const char *str, int len){
    Osp::Base:: String bada_str;
    ByteBuffer buffer;
    buffer.Construct(len + 1);
    buffer.SetArray(( byte*)str, 0, len);
    buffer.SetByte( '\0');
    buffer.Flip();
    Utf8Encoding utf8;
    int charCount;
    utf8.GetCharCount(buffer, charCount);
  return charCount;
}

void StaticTextOptionView::_createItem() {
	std::string myText = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
	const char *text = myText.c_str();
//	QLabel *label = new QLabel(::qtString(text), myTab->widget());
//	myWidgets.push_back(label);
//	myTab->addItem(label, myRow, myFromColumn, myToColumn);
	std::string caption = ZLOptionView::name()+ ": ";

	AppLog("StaticTextOptionView::_createItem()");
	pItem = new OptionListItem(this);
	AppLog("myText.length = %d",myText.length());
	int len = stringLength(text, myText.length());
	AppLog("myText.length = %d",len);
	int n = len / 20;
	int h = 45;
	if (n>1) h=n*45;
	int textHeight;
	size_t found=caption.find("????");
	AppLog("found = %d",found);
	 if (found)  textHeight=initText(caption.c_str(),myText, 2000);
	 	 	 else textHeight=initText(null,myText, 2000);
	AppLog("textHeight = %d",textHeight);
	pItem->Construct(textHeight+10);

    pItem->SetItemFormat(*myTab->form()->__pStaticTextListItemFormat);
 //   pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
//	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(text));
	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
 //   pItem->SetCheckBox(ID_LIST_CHECKBOX);
    pItem->SetElement(ID_LIST_CUSTOM, *this);
	AppLog("	SetElement ID_LIST_CUSTOM		");
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);

	int groupIndex = myTab->form()->GroupCount-1;
	int itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	myTab->form()->__pCustomList->SetItemEnabled(groupIndex,itemIndex,false);
}

void StaticTextOptionView::_onAccept() const {
}

void StaticTextOptionView::OnActionPerformed(int actionId){}

result StaticTextOptionView::DrawElement(const Osp::Graphics::Canvas& canvas, const Osp::Graphics::Rectangle& rect, Osp::Ui::Controls::CustomListItemStatus itemStatus)
{
	result r = E_SUCCESS;
	AppLog("DrawElement");
	Osp::Graphics::Canvas* pCanvas = const_cast<Osp::Graphics::Canvas*>(&canvas);
	AppLog("pCanvas");
/*	pCanvas->SetLineWidth(5);
	pCanvas->SetForegroundColor(Osp::Graphics::Color::COLOR_GREEN);
	if (pCanvas->DrawRectangle(rect) != E_SUCCESS)
		return r;
*/
	pCanvas->SetForegroundColor(Osp::Graphics::Color::COLOR_WHITE);
	if (pCanvas->DrawText(Osp::Graphics::Point(rect.x+20, rect.y+5), *pEnrichedText) != E_SUCCESS)
		return r;

	return r;
}

void StaticTextOptionView::addParagraph(std::string &text){
	  result r = E_SUCCESS;
    TextElement* pTextElement2 = pTextElement2 = new TextElement();
    r = pTextElement2->Construct(text.c_str());
    //if (IsFailed(r))   {      goto CATCH;   }
    pTextElement2->SetTextColor(Color::COLOR_GREY);
    {
        Font font;
        font.Construct(FONT_STYLE_PLAIN, 30);
        pTextElement2->SetFont(font);
    }
    // Creates a bitmap and scales the size
    //pBitmap = Application::GetInstance()->GetAppResource()->GetBitmapN(L"example.bmp");
   // pBitmap->Scale(Dimension(40, 40));

    // Adds the TextElement and the bitmap to the EnrichedText
    pEnrichedText->Add(*pTextElement2);
  //  pEnrichedText->Add(*pBitmap);
}
int StaticTextOptionView::initText(const char *caption, std::string &text, int height){
	   result r = E_SUCCESS;
	  //  EnrichedText* pEnrichedText = null;
	    TextElement* pTextElement1 = null;
	   // TextElement* pTextElement2 = null;
	    int found;
	    int found2;
	    std::string p;
	  //  Bitmap* pBitmap = null;

	    // Creates an EnrichedText instance and sets the attributes
	    pEnrichedText = new EnrichedText();
	    r = pEnrichedText->Construct(Dimension(470, height ));
	    if (IsFailed(r))
	    {
	        goto CATCH;
	    }
	    pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
	    pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
	    pEnrichedText->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);
	  //  pEnrichedText->SetTextAbbreviationEnabled(true);

	    // Create a TextElement and set attributes.
	    if (caption) {
	    	pTextElement1 = new TextElement();
	    	r = pTextElement1->Construct(caption);
	    	if (IsFailed(r))
	    	    {
	    	        goto CATCH;
	    	    }
	    	pTextElement1->SetTextColor(Color::COLOR_WHITE);
	    	{
	    	Font font;
	    	font.Construct(FONT_STYLE_BOLD, 30);
	    	pTextElement1->SetFont(font);
	    	}
	    	pEnrichedText->Add(*pTextElement1);
	    }


	    found=text.find("<p>");
	    if (found) 	addParagraph(text);
	    else
	    {
	    	AppLog("found0 = %d",found);
	    	do
	    	{
	    	found2=text.find("</p>",found);
	    	AppLog("found2 = %d",found2);
	    	p.assign(text,found+3,found2-found-3);
	    	p.append("\n");
	    	addParagraph(p);
	    	found=text.find("<p>",found2-3);
	    	AppLog("found = %d",found);
	    	}
	    	while (found>0);

	    }


		    // Cleans up
	   // pEnrichedText->RemoveAll(true);
	   // delete pEnrichedText;
		AppLog("GetTotalLineCount  = %d",pEnrichedText->GetTotalLineCount());
	    return pEnrichedText->GetTotalLineHeight();

	CATCH:
	    if (pEnrichedText)
	    {
	      //  pEnrichedText->RemoveAll(true);
	       // delete pEnrichedText;
	    }

	    return 0;

}
