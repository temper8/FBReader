/*
 * ZLbadaPaintContext.cpp
 *
 *  Created on: 13.10.2011
 *      Author: Alex
 */

#include "ZLbadaPaintContext.h"
#include "../image/ZLbadaImageManager.h"
//#include <FGraphics.h>
#include <FText.h>
using namespace Osp::Graphics;
using namespace Osp::Base::Utility;
using namespace Osp::Base;
using namespace Osp::Text;




void ZLbadaPaintContext::setFont(const std::string &family, int size, bool bold, bool italic) {
	//  AppLog("ZLbadaPaintContext::setFont %d",size );
//TODO не понял этот кусок из qt-версии, и потому заремарил
/*	if (myPainter->device() == 0) {
		myFontIsStored = true;
		myStoredFamily = family;
		myStoredSize = size;
		myStoredBold = bold;
		myStoredItalic= italic;
	} else {
	*/

	bool fontChanged = false;
	Osp::Graphics::Font *pFont = pCanvas->GetFontN();
//	Osp::Graphics::Font font;
//TODO	font =*pFont; неработает, неаккратно создаю фонт
	/*TOD font.family отключил за непонятностью что делать со шрифтами
	  	if (font.family() != family.c_str()) {
			font.setFamily(family.c_str());
			fontChanged = true;
		}
*/

	int style = ( bold ? FONT_STYLE_BOLD : FONT_STYLE_PLAIN) | ( italic ? FONT_STYLE_ITALIC : 0);

	if ((pFont->IsItalic() != italic)|(pFont->IsBold() != bold)|(pFont->GetSize() != size)) {
		pFont->Construct(style,size);
		fontChanged = true;
	}

	if (fontChanged) {
		pCanvas->SetFont(*pFont);
		mySpaceWidth = -1;
		myDescent =pFont->GetDescender();
     }

}



int ZLbadaPaintContext::width() const {
	if (!pCanvas) {
		return 0;
	}
	return pCanvas->GetBounds().width;
}

int ZLbadaPaintContext::height() const {
	if (!pCanvas) {
		return 0;
	}
	return pCanvas->GetBounds().height;
}


void ZLbadaPaintContext::clear(ZLColor color){
	pCanvas->SetBackgroundColor(Color(color.Red, color.Green, color.Blue, 0xFF));
	pCanvas->SetForegroundColor(Color::COLOR_GREY);
	pCanvas->Clear();
}

void ZLbadaPaintContext::setColor(ZLColor color, LineStyle style){
	pCanvas->SetLineStyle((style == SOLID_LINE) ? LINE_STYLE_SOLID : LINE_STYLE_MIN);
	pCanvas->SetForegroundColor(Color(color.Red, color.Green, color.Blue, 0xFF));
}

void ZLbadaPaintContext::setFillColor(ZLColor color, FillStyle style){
	//__pCanvas->SetForegroundColor(Color::COLOR_GREY);
	FillColor.SetColorComponents(color.Red, color.Green, color.Blue, 0xFF);
}

int ZLbadaPaintContext::stringWidth(const char *str, int len, bool) const {
	Osp::Base::String bada_str;
    ByteBuffer buffer;
    buffer.Construct(len + 1);
    buffer.SetArray((byte*)str, 0, len);
    buffer.SetByte('\0');
    buffer.Flip();
//	AppLog("ZLbadaPaintContext::stringWidth %s",(const char *)buffer.GetPointer());
//	StringUtil::Utf8ToString((const char *)buffer.GetPointer(), bada_str);
    Utf8Encoding utf8;
    int charCount;
    utf8.GetCharCount(buffer, charCount);
    utf8.GetString(buffer, bada_str);

    Dimension dim;
    pCanvas->GetFontN()->GetTextExtent(bada_str, charCount, dim);
//    AppLog("ZLbadaPaintContext::stringWidth %d",dim.width );
	return dim.width;
}

int ZLbadaPaintContext::spaceWidth() const {
	if (mySpaceWidth == -1) {
		Dimension dim;
		pCanvas->GetFontN()->GetTextExtent(L" ", 1, dim);
		mySpaceWidth = dim.width;
	}
	return mySpaceWidth;
}
int ZLbadaPaintContext::stringHeight() const{
	//return myPainter->font().pointSize() + 2;
	return pCanvas->GetFontN()->GetMaxHeight();
}

int ZLbadaPaintContext::descent() const{
	return myDescent;
}

void ZLbadaPaintContext::drawString(int x, int y, const char *str, int len, bool rtl){
	Osp::Base::String bada_str;
    ByteBuffer buffer;
    buffer.Construct(len + 1);
    buffer.SetArray((byte*)str, 0, len);
    buffer.SetByte('\0');
    buffer.Flip();
//	AppLog("ZLbadaPaintContext::stringWidth %s",(const char *)buffer.GetPointer());
//	StringUtil::Utf8ToString((const char *)buffer.GetPointer(), bada_str);
    Utf8Encoding utf8;
    int charCount;
    utf8.GetCharCount(buffer, charCount);
    utf8.GetString(buffer, bada_str);
 //   AppLog("charCount = %d : len = %d", charCount,len);
	pCanvas->DrawText(Point(x, y-pCanvas->GetFontN()->GetMaxHeight()), bada_str,charCount);
}

void ZLbadaPaintContext::fillRectangle(int x0, int y0, int x1, int y1){
	pCanvas->FillRectangle(FillColor, Rectangle(x0, y0, x1-x0, y1-y0));
}

void ZLbadaPaintContext::drawFilledCircle(int x, int y, int r) {
	pCanvas->DrawEllipse(Rectangle(x - r, y - r, 2 * r + 1, 2 * r + 1));
}

void ZLbadaPaintContext::drawLine(int x0, int y0, int x1, int y1) {
	pCanvas->DrawLine(Point(x0, y0), Point(x1, y1));
}

void ZLbadaPaintContext::drawImage(int x, int y, const ZLImageData &image) {
	Bitmap *pBmp;
	AppLog("draw image start");
	pBmp = 	((ZLbadaImageData&)image).pBitmap;
	AppLog("init bmp");
    int imageWidth = pBmp->GetWidth();
    int imageHeight = pBmp->GetHeight();
	AppLog("draw image w = %d, h = %d", imageWidth, imageHeight);

	pCanvas->DrawBitmap(Point(x, y), *pBmp);
}

void ZLbadaPaintContext::drawImage(int x, int y, const ZLImageData &image, int width, int height, ScalingType type) {
	Bitmap *pBmp;
	pBmp = 	((ZLbadaImageData&)image).pBitmap;
	if (pBmp == 0) {
		return;
	}
	//TODO ScalingType ни как не обрабатывается

	// const QImage &scaled = qImage->scaled(	QSize(

	int w =	imageWidth(image, width, height, type);
	int h = imageHeight(image, width, height, type);
	//	Qt::KeepAspectRatio,
	//	Qt::SmoothTransformation
	//myPainter->drawImage(x, y - scaled.height(), scaled);
	AppLog("draw image w = %d, h = %d", width, height);
	AppLog("draw image2 w = %d, h = %d", w, h);
	pCanvas->DrawBitmap(Rectangle(x,y-h,w,h),*pBmp);
	//pCanvas->DrawBitmap(Point(x, y-pBmp->GetHeight()), *pBmp);

}


ZLbadaPaintContext::ZLbadaPaintContext() {
	// TODO Auto-generated constructor stub
	AppLog("ZLbadaPaintContext::ZLbadaPaintContext()");
	mySpaceWidth = -1;
	myDescent = 0;
	myFontIsStored = false;
}

ZLbadaPaintContext::~ZLbadaPaintContext() {
	// TODO Auto-generated destructor stub
}
