/*
 * ZLbadaPaintContext.cpp
 *
 *  Created on: 13.10.2011
 *      Author: Alex
 */

#include "ZLbadaPaintContext.h"
#include "../image/ZLbadaImageManager.h"
//#include <FGraphics.h>

#include <FIo.h>
#include <FText.h>

using namespace Osp::Graphics;
using namespace Osp::Base::Utility;
using namespace Osp::Base;
using namespace Osp::Text;
using namespace Osp::Io;

void ZLbadaPaintContext::fillFamiliesList(std::vector<std::string> &families) const {
	AppLog( "fillFamiliesList");
    Osp::Base::Collection::IList* FontList;
    FontList = Osp::Graphics::Font::GetSystemFontListN();
	int Count = FontList->GetCount();
	AppLog( "fillFamiliesList %d", Count);
	//bool helveticaFlag = false;
	for (int i =0; i<Count; i++) {
		Osp::Base::String* f = (Osp::Base::String*)FontList->GetAt(i);
		Utf8Encoding utf8;
		ByteBuffer* pBB = utf8.GetBytesN(*f);
		std::string  family(( const char*)pBB->GetPointer(),f->GetLength());
		AppLog( "family name = %s",family.c_str()) ;
		//if (family == HELVETICA) {
		//	helveticaFlag = true;
		//}
		families.push_back(family);
	}
	//if (!helveticaFlag) {
//		families.push_back(HELVETICA);
//	}
	FontList->RemoveAll(true);

	for (std::map<std::string, std::string>::const_iterator it=myFontsList.begin() ; it != myFontsList.end(); it++ ){
		std::string  family((*it).first);
		families.push_back(family);
		AppLog( "myFontsList = %s",family.c_str()) ;
	}

}

const std::string ZLbadaPaintContext::realFontFamilyName(std::string &fontFamily) const {
//	AppLog( "realFontFamilyName %s",fontFamily.c_str());
	/*
	QString fullName = QFontInfo(QFont(fontFamily.c_str())).family();
	if (fullName.isNull() || fullName.isEmpty()) {
		fullName = QFontInfo(QFont::defaultFont()).family();
		if (fullName.isNull() || fullName.isEmpty()) {
			return HELVETICA;
		}
	}*/
	return fontFamily;//fullName.left(fullName.find(" [")).ascii();
}

Osp::Graphics::Font* ZLbadaPaintContext::loadExternalFont(const std::string &family, const std::string &path, int style, int size)
	{
	Osp::Graphics::Font* pFont;
	pFont = new Osp::Graphics::Font;
	File file;
/*	if (fontData!=0) 	{
		AppLog("delete fontData;");
	  	 delete fontData;
	}
if (fontData ==0 )
{
	fontData = new Osp::Base::ByteBuffer;
	result r = E_SUCCESS;
    r = file.Construct( Osp::Base::String(path.c_str()), L"rb");
    file.Seek(FILESEEKPOSITION_END,0);
    int fileSize = file.Tell();
    file.Seek(FILESEEKPOSITION_BEGIN,0);
    //if(IsFailed(r))  goto CATCH;
    AppLog("fileSize = %d",fileSize);
    fontData->Construct(fileSize);
    r = file.Read(*fontData);
    //if(IsFailed(r))  goto CATCH;

    AppLog("r = %d",r);
}*/
    AppLog("loadExternalFont size = %d",size);
    AppLog("loadExternalFont style = %d",style);

//	if (pFont->Construct(*fontData,style,size) != E_SUCCESS){
	if (pFont->Construct(Osp::Base::String(path.c_str()),style,size) != E_SUCCESS){
				AppLog("loadExternalFont not E_SUCCESS");
				delete pFont;
				delete fontData;
				fontData = 0;
				return null;
			}

	AppLog("loadExternalFont E_SUCCESS");
/*    ByteBuffer* bb;
	Osp::Base::String fontFaceName;
	 fontFaceName=pFont->GetFaceName();
	 AppLog("GetFaceName");
	 bb = Osp::Base::Utility::StringUtil::StringToUtf8N(fontFaceName);
	 AppLog( "fontFaceName1 %s",(char *)bb->GetPointer());
			//	AppLog("add font to cache");
	 AppLog("add font to cache");
	 int fountCount = fontsCache.size();
	 std::string userFontName;
	 switch(fountCount){
		case  0: userFontName = "UserMemoryFont0"; break;
		case  1: userFontName = "UserMemoryFont1"; break;
		case  2: userFontName = "UserMemoryFont2"; break;
		case  3: userFontName = "UserMemoryFont3"; break;
		case  4: userFontName = "UserMemoryFont4"; break;
		case  5: userFontName = "UserMemoryFont5"; break;
		case  6: userFontName = "UserMemoryFont6"; break;
		case  7: userFontName = "UserMemoryFont7"; break;
		case  8: userFontName = "UserMemoryFont8"; break;
	 }

	 AppLog("userFontName %s",userFontName.c_str());
	 fontsCache.insert(std::make_pair(family,userFontName));
	 */
	 return pFont;
}

void ZLbadaPaintContext::printFaceName(Osp::Graphics::Font* font){
ByteBuffer* bb;
Osp::Base::String fontFaceName;
fontFaceName=font->GetFaceName();
bb = Osp::Base::Utility::StringUtil:: StringToUtf8N(fontFaceName);
AppLog( "fontFaceName2 %s",(char *)bb->GetPointer());
delete bb;
}

void ZLbadaPaintContext::setFont2(const std::string &family, int size, bool bold, bool italic){
	setFont2(defaultFont,size,bold,italic);
}
void ZLbadaPaintContext::setFont(const std::string &family, int size, bool bold, bool italic) {
//	AppLog( "setFont %s",family.c_str());
//	AppLog( "setFont size %d, %d, %d ",size,bold,italic);
//	AppLog( "setFont family %s",family.c_str());
	bool fontChanged = false;

	if (myStoredFamily != family) fontChanged = true;
	int style = ( bold ? FONT_STYLE_BOLD : FONT_STYLE_PLAIN) | ( italic ? FONT_STYLE_ITALIC : 0);
	if ((myStoredItalic != italic)|(myStoredBold != bold)|(myStoredSize != size)) {
		fontChanged = true;
	}
	if (!fontChanged) { return;}


	myStoredSize = size;
	myStoredBold = bold ;
	myStoredItalic = italic;

	std::string fontPath;
	Osp::Graphics::Font* font;
	std::map<std::string, std::string>::const_iterator it = myFontsList.find(family);
	if (it != myFontsList.end()) {
		fontPath = it->second;
		//AppLog("fontFamily %s",fontPath.c_str());
		font = new Osp::Graphics::Font;
		if (font->Construct(Osp::Base::String(fontPath.c_str()),style,size) != E_SUCCESS){
					AppLog("font == NULL");
					font = new Osp::Graphics::Font;
					font->Construct(style,size);
				}
	//	printFaceName(font);
	}
	else
	  {
		font = new Osp::Graphics::Font;
		if (font->Construct(String(family.c_str()),style,size) != E_SUCCESS){
			delete font;
			font = null;
			//AppLog( "loadDefaultFont ");
			font = loadDefaultFont(style,size);
			if (font == null) {
				font = new Osp::Graphics::Font;
				AppLog( "Construct bada font ");
				font->Construct(style,size);
			}
		}
   }

	font->SetCharSpace(2);
	//AppLog("getCharSpace %d",font->GetCharSpace());
	//AppLog("maxh=%d, getsize=%d, getas=%d, getdes=%d", font->GetMaxHeight(), font->GetSize(), font->GetAscender(), font->GetDescender());
//	pCanvas->SetFont(*font);
	mySpaceWidth = -1;
	myDescent = font->GetDescender();
	myStoredFamily = family;
//	AppLog("add font to cache");
	//fontsCache.insert(std::make_pair(family,font));
	 if (myFont!=0) delete myFont;
	 myFont = font;
	// pCanvas->SetFont();
	 if (myFont!=0)  pCanvas->SetFont(*myFont);
}


Osp::Graphics::Font* ZLbadaPaintContext::loadDefaultFont( int style, int size){
	AppLog("ZLbadaPaintContext::loadDefaultFont()");
	Osp::Graphics::Font* font = null;
	std::map<std::string, std::string>::const_iterator it = myFontsList.find(defaultFont);
	if (it != myFontsList.end()) {
		std::string fontPath;
		fontPath = it->second;
		//font = loadExternalFont(defaultFont,fontPath,style,size);
		font = new Osp::Graphics::Font;
		if (font->Construct(String(fontPath.c_str()),style,size) != E_SUCCESS){
				AppLog("defaultFontLoaded not E_SUCCESS");
				delete font;
				font = null;
			}
	}
	return font;
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
	//pCanvas->SetLineStyle((style == SOLID_LINE) ? LINE_STYLE_SOLID : LINE_STYLE_MIN);
	pCanvas->SetLineStyle(LINE_STYLE_SOLID);
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
    myFont->GetTextExtent(bada_str, charCount, dim);
    //pCanvas->GetFontN()->GetTextExtent(bada_str, charCount, dim);
//    AppLog("ZLbadaPaintContext::stringWidth %d",dim.width );
	return dim.width;//+charCount;
}

int ZLbadaPaintContext::spaceWidth() const {
	//if (mySpaceWidth == -1)
	if (myFont==0) mySpaceWidth =-1;
	else
	{
		Dimension dim;
	//	AppLog("spaceWidth");
		myFont->GetTextExtent(L" ", 1, dim);
		//pCanvas->GetFontN()->GetTextExtent(L" ", 1, dim);
		mySpaceWidth = dim.width;
	}
	return mySpaceWidth;
}

int ZLbadaPaintContext::stringHeight() const{
	//return myPainter->font().pointSize() + 2;
//	AppLog("stringHeight");
	if (myFont==0) return 0;
	return myFont->GetMaxHeight();
	//return pCanvas->GetFontN()->GetMaxHeight();
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
 //   DrawEnrichedTex(x, y-myFont->GetMaxHeight(),bada_str );

 /*   Canvas* pDrawingCanvas = new Canvas;
    pDrawingCanvas->Construct();
    pDrawingCanvas->SetBackgroundColor(Color::COLOR_WHITE);
    pDrawingCanvas->SetForegroundColor(Color::COLOR_BLACK);
    pDrawingCanvas->Clear();
    if (myFont!=0)  pDrawingCanvas->SetFont(*myFont);
    pDrawingCanvas->DrawText(Point(0, 0), bada_str);

    pCanvas->Copy(Point(x,y),*pDrawingCanvas,Rectangle(0,0,100,25));
    delete pDrawingCanvas;*/

	pCanvas->DrawText(Point(x, y-myFont->GetMaxHeight()), bada_str);
//	pCanvas->DrawText(Point(x, y-myFont->GetMaxHeight()), bada_str, charCount);
//	pCanvas->DrawText(Point(x, y), bada_str,charCount);
}

void ZLbadaPaintContext::DrawEnrichedTex(int x, int y,Osp::Base::String &text ){
    result r = E_SUCCESS;
    EnrichedText* pEnrichedText = null;
    TextElement* pTextElement1 = null;
    pEnrichedText = new EnrichedText();
    r = pEnrichedText->Construct(Dimension(300, 100));
    pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT );
     pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
     pEnrichedText->SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
     pEnrichedText->SetTextAbbreviationEnabled(true);


    pTextElement1 = new TextElement();
    r = pTextElement1->Construct(text);
   // if (IsFailed(r))  {  goto CATCH;  }
    pTextElement1->SetTextColor(Color::COLOR_BLUE);

       //   Font font;
      //    font.Construct(FONT_STYLE_BOLD, 40);
    pTextElement1->SetFont(*myFont);

   pEnrichedText->Add(*pTextElement1);
   int width, height;
   pEnrichedText->GetSize(width, height);
   pCanvas->FillRectangle(Color::COLOR_GREY, Rectangle(x, y, width, 1));



   pCanvas->DrawText(Point(x, y), *pEnrichedText);
   pEnrichedText->RemoveAll(true);
   delete pEnrichedText;
}

void ZLbadaPaintContext::fillRectangle(int x0, int y0, int x1, int y1){
	pCanvas->FillRectangle(FillColor, Rectangle(x0, y0, x1-x0+1, y1-y0+1));
}

void ZLbadaPaintContext::drawFilledCircle(int x, int y, int r) {
	pCanvas->DrawEllipse(Rectangle(x - r, y - r, 2 * r + 1, 2 * r + 1));
}

void ZLbadaPaintContext::drawLine(int x0, int y0, int x1, int y1) {
	pCanvas->DrawLine(Point(x0, y0), Point(x1, y1));
}

void ZLbadaPaintContext::drawImage(int x, int y, const ZLImageData &image) {
	Bitmap *pBmp;
	pBmp = 	((ZLbadaImageData&)image).pBitmap;
    int imageWidth = pBmp->GetWidth();
    int imageHeight = pBmp->GetHeight();
//	AppLog("draw image w = %d, h = %d", imageWidth, imageHeight);
	pCanvas->DrawBitmap(Point(x, y), *pBmp);
}

void ZLbadaPaintContext::drawImage(int x, int y, const ZLImageData &image, int width, int height, ScalingType type) {
	Bitmap *pBmp;
	pBmp = 	((ZLbadaImageData&)image).pBitmap;
	if (pBmp == 0) {
		return;
	}
	//TODO ScalingType ни как не обрабатывается

	int w =	imageWidth(image, width, height, type);
	int h = imageHeight(image, width, height, type);
	//	Qt::KeepAspectRatio,
	//	Qt::SmoothTransformation
	pCanvas->DrawBitmap(Rectangle(x,y-h,w,h),*pBmp);
}

void ZLbadaPaintContext::collectFiles(std::map<std::string, std::string> &names, const char* path ) {
   //TODO collectFiles
	 AppLog("ZLbadaPaintContext::collectFiles") ;
    Directory dir;
    DirEnumerator *pDirEnum = null;
    result r = E_SUCCESS;

    // Opens the directory
    r = dir.Construct(path);
	 AppLog(" dir.Construct %s",path) ;
    if(IsFailed(r))  AppLog("IsFailed");

       //goto CATCH;

    // Reads all the directory entries
    pDirEnum = dir.ReadN();
  //  if(!pDirEnum)
  //      goto CATCH;
    while(pDirEnum->MoveNext() == E_SUCCESS)
    {
        DirEntry dirEntry = pDirEnum->GetCurrentDirEntry();
        Osp::Base::String str = dirEntry.GetName();
       // AppLog("dirEntry name Length = %d",str.GetLength()) ;
        Utf8Encoding utf8;
       	ByteBuffer* pBB = utf8.GetBytesN(str);
        std::string  shortName((const char*)pBB->GetPointer(),str.GetLength());
        AppLog("dirEntry name = %s",shortName.c_str()) ;
        if (shortName !="." && shortName !="..")	{
        	std::string fullName;
        	fullName = path + shortName;
        	AppLog("fullName = %s",fullName.c_str());
        	names.insert(std::make_pair(shortName,fullName));
        }

       // names.push_back(shortName);
    }

    // Deletes the enumerator
    delete pDirEnum;

    AppLog("Succeeded");
}

void ZLbadaPaintContext::initMyFontsList(){
//	myFontsList
	 AppLog("initMyFontsList");
	collectFiles(myFontsList,"/Res/Fonts/");
}

ZLbadaPaintContext::ZLbadaPaintContext():myFont(0), defaultFont("LiberationSerif-Regular.ttf"),myStoredFamily("xxx"), defaultFontLoaded(false) {
	// TODO Auto-generated constructor stub
	AppLog("ZLbadaPaintContext::ZLbadaPaintContext()");
	mySpaceWidth = -1;
	myDescent = 0;
	myFontIsStored = false;
	initMyFontsList();
	fontData = 0;
}

ZLbadaPaintContext::~ZLbadaPaintContext() {
	// TODO Auto-generated destructor stub
}

