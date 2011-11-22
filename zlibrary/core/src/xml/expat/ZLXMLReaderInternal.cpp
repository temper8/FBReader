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
#include <FBase.h>
#include <string.h>

#include <ZLFile.h>
#include <ZLInputStream.h>
#include <ZLEncodingConverter.h>

#include "ZLXMLReaderInternal.h"
#include "../ZLXMLReader.h"
#include <stdlib.h>

//void ZLXMLReaderInternal::fCharacterDataHandler(void *userData, const char *text, int len) {
//void fCharacterDataHandler(void *userData, const char *text, int len) {
void fCharacterDataHandler(void *userData,	const xmlChar *text, int len) {
	char buf[100];
//	AppLog("ZLXMLReaderInternal::fCharacterDataHandler");
	ZLXMLReader &reader = *(ZLXMLReader*)userData;
	if (!reader.isInterrupted()) {
		reader.characterDataHandler((const char*)text, len);

		if (len<50) {
			memset(buf, 0, 99);
		    strncpy(buf, (const char*)text, len);
	//		AppLog("fCharacterDataHandler text=%s",buf);
		}
	//	AppLog("fCharacterDataHandler len = %d",len);
	}
}

//void ZLXMLReaderInternal::fStartElementHandler(void *userData, const char *name, const char **attributes) {
//typedef void(* startElementSAXFunc)(void *ctx, const xmlChar *name, const xmlChar **atts)
//void fStartElementHandler(void *userData, const char *name, const char **attributes) {
void fStartElementHandler2(void *userData, const char *name, const char **attributes) {

//	AppLog("fStartElementHandler2::name=%s",(const char*)name);
//	if (*attributes!=0) 	AppLog("fStartElementHandler:: attr = %s::%s",(const char*)attributes[0],(const char*)attributes[1]);
//	else {AppLog("A!=0"); return;}
	ZLXMLReader &reader = *(ZLXMLReader*)userData;
	//AppLog("ZLXMLReader &reader");
	if (!reader.isInterrupted()) {
		//AppLog("!reader.isInterrupted()");
		if (reader.processNamespaces()) {
			int count = 0;
			//AppLog("int count = 0");
			//AppLog("attr = %s::%s",(const char*)attributes[0],(const char*)attributes[1]);
			for (const char **a = (const char**)attributes; (*a != 0) && (*(a + 1) != 0); a += 2) {
				AppLog("*a=%s",*a);
				if (strncmp(*a, "xmlns:", 6) == 0) {
					if (count == 0) {
						reader.myNamespaces.push_back(
							new std::map<std::string,std::string>(*reader.myNamespaces.back())
						);
					}
					++count;
					const std::string id(*a + 6);
					const std::string reference(*(a + 1));
					(*reader.myNamespaces.back())[id] = reference;
				}
			}
			if (count == 0) {
				reader.myNamespaces.push_back(reader.myNamespaces.back());
			} else {
				reader.namespaceListChangedHandler();
			}
		}
	//	AppLog("reader.startElementHandler");
		if (attributes!=0)
		{
	//		AppLog("reader.startElementHandler if ");
			reader.startElementHandler((const char*)name, (const char**)attributes);
		}
		else
		{
			AppLog("reader.startElementHandler if attributes==0 сюда не должен попадать");
			const char* c[1];
			*c=0;
			reader.startElementHandler((const char*)name, c);
		}
	//	AppLog("reader.startElementHandler 2 ");

	}
}
void fStartElementHandler(void *userData, const xmlChar *name, const xmlChar **attributes){
//	AppLog("fStartElementHandler  name = %s",(const char*)name);

	if (attributes!=0)		{
			fStartElementHandler2(userData, (const char*)name, (const char**)attributes);
	    }
		else
		{
			const char* c[1];
			*c=0;
			fStartElementHandler2(userData, (const char*)name, c);
		}
}
//void ZLXMLReaderInternal::fEndElementHandler(void *userData, const char *name) {
//typedef void(* endElementSAXFunc)(void *ctx, const xmlChar *name)
//void fEndElementHandler(void *userData, const char *name) {
void fEndElementHandler(void *userData, const xmlChar *name) {
//	AppLog("fEndElementHandler name = %s",(const char*)name );
	ZLXMLReader &reader = *(ZLXMLReader*)userData;
	if (!reader.isInterrupted()) {
	//	AppLog("reader.endElementHandler");
		reader.endElementHandler((const char*)name);
	//	AppLog("reader.endElementHandler ok");
		if (reader.processNamespaces()) {
	//		AppLog("reader.processNamespaces ok");
			shared_ptr<std::map<std::string,std::string> > oldMap = reader.myNamespaces.back();
	//		AppLog("reader.myNamespaces.pop_back()");
			reader.myNamespaces.pop_back();
			if (reader.myNamespaces.back() != oldMap) {
			//	AppLog("reader.namespaceListChangedHandler()");
				reader.namespaceListChangedHandler();
			}
		}
	}
}

static xmlDocPtr ParseEntity;

xmlEntityPtr fgetEntity(	void * 	user_data, 	const xmlChar * name){
	AppLog("fgetEntity %s",name );
	//ZLXMLReader &reader = *(ZLXMLReader*)userData;
	xmlEntityPtr ep = xmlGetPredefinedEntity(name);
	if (ep) return ep;
	//if (strncmp((const char*)name, "FBReaderVersion", 14) == 0) {
	AppLog("FBReaderVersion !!!!!!!");
	//return  xmlGetPredefinedEntity(name);
	//const xmlChar *const xmlChar *c="lt"="lt";
	ep = xmlGetDocEntity( ParseEntity, name);
	if (ep) return ep;
	AppLog("Облом с  xmlGetDocEntity!!!!!!!");
	return xmlGetPredefinedEntity((xmlChar *)"lt");
}

int fHasInternalSubsetSAXFunc (void *ctx)
{
	AppLog("fHasInternalSubsetSAXFunc" );
	return 0;
}


int fHasExternalSubsetSAXFunc (void *ctx)
{
	AppLog("fHasExternalSubsetSAXFunc" );
	return 0;
}


void fWarningSAXFunc (void *ctx,
				const char *msg, ...)
{
	AppLog("fWarningSAXFunc msg = %s",msg );
}
xmlParserInputPtr fResolveEntitySAXFunc (void *ctx, const xmlChar *publicId, const xmlChar *systemId)
{
	AppLog("fResolveEntitySAXFunc" );
	return null;
}

void fEntityDeclSAXFunc (void *ctx, 	const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId, xmlChar *content)
{
	AppLog("fEntityDeclSAXFunc" );
}
void fUnparsedEntityDeclSAXFunc(void *ctx, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName)
{
	AppLog("fUnparsedEntityDeclSAXFunc" );
}


/*
static int fUnknownEncodingHandler(void*, const XML_Char *name, XML_Encoding *encoding) {
	ZLEncodingConverterInfoPtr info = ZLEncodingCollection::Instance().info(name);
	if (!info.isNull()) {
		shared_ptr<ZLEncodingConverter> converter = info->createConverter();
		//converter
		if (!converter.isNull() && converter->fillTable(encoding->map)) {
			return XML_STATUS_OK;
		}
	}
	return XML_STATUS_ERROR;
}


//static void parseDTD(XML_Parser parser, const std::string &fileName) {
static void parseDTD(xmlSAXHandlerPtr sax, const std::string &fileName) {
	AppLog("XML_ParserCreate");
	xmlSAXParseEntity(xmlSAXHandlerPtr sax, filename.c_str());
	XML_Parser entityParser = XML_ExternalEntityParserCreate(parser, 0, 0);
	ZLFile dtdFile(fileName);
	shared_ptr<ZLInputStream> entityStream = dtdFile.inputStream();
	if (!entityStream.isNull() && entityStream->open()) {
		const size_t BUFSIZE = 2048;
		char buffer[BUFSIZE];
		size_t length;
		do {
			length = entityStream->read(buffer, BUFSIZE);
			if (XML_Parse(entityParser, buffer, length, 0) == XML_STATUS_ERROR) {
				break;
			}
		} while (length == BUFSIZE);
	}
	XML_ParserFree(entityParser);
}
*/
ZLXMLReaderInternal::ZLXMLReaderInternal(ZLXMLReader &reader, const char *encoding) : myReader(reader) {
	AppLog("XML_ParserCreate");
//	myParser = XML_ParserCreate(encoding);
//	pMySaxhandler  = &mySaxHandler;
	myInitialized = false;
}

ZLXMLReaderInternal::~ZLXMLReaderInternal() {
	AppLog("XML_ParserFree");
	xmlCleanupParser();
//	XML_ParserFree(myParser);
}


void fErrorSAXFunc (void *ctx, const char *msg, ...)
{
    va_list args;

    va_start(args, msg);
    //g_logv("XML", G_LOG_LEVEL_CRITICAL, msg, args);
    AppLog("fErrorSAXFunc ");
    AppLog(msg, args);
    va_end(args);

}

void fFatalErrorSAXFunc (void *ctx,	const char *msg, ...)
{
	AppLog("fErrorSAXFunc %s", msg);
}

int	fxmlCharEncodingInputFunc(unsigned char * out, int * outlen,
					 const unsigned char * in,  int * inlen)
{
	//AppLog("fxmlCharEncodingInputFunc inlen=%d",*inlen);
//	AppLog("fxmlCharEncodingInputFunc start inlen =%d, outlen =%d",*inlen, *outlen);
//	if (out!=0) {AppLog("fxmlCharEncodingInputFunc out!=0 %s");}
	//AppLog("fxmlCharEncodingInputFunc in=%s",in);
	ZLEncodingConverterInfoPtr info = ZLEncodingCollection::Instance().info("windows-1251");
	if (!info.isNull()) {
		shared_ptr<ZLEncodingConverter> converter = info->createConverter();
		if (!converter.isNull()) {
		//	AppLog("in =%s",in);
			std::string myBuffer;
			converter->convert(myBuffer, (const char*)in, (const char*)(in + *inlen));
			//TODO проверка на размер буффера
			*outlen = myBuffer.length();
			//*outlen = *inlen;
			//AppLog("fxmlCharEncodingInputFunc len =%d, size =%d",*outlen, myBuffer.size());
		//	out =(unsigned char*)malloc(*outlen);
			//memcpy(out,(char*)myBuffer.c_str(),*outlen);
			memcpy(out,(char*)myBuffer.data(),*outlen);
			//memcpy(out,(char*)in,*outlen);
	//		AppLog("fxmlCharEncodingInputFunc inlen =%d, outlen =%d",*inlen, *outlen);
	//		AppLog("out =%s",out);
			return *outlen;
		}
	};
	return -1;

}
int	fxmlCharEncodingOutputFunc(unsigned char * out, int * outlen,
					 const unsigned char * in,  int * inlen)
{
	AppLog("xmlCharEncodingOutputFunc");
}

void ZLXMLReaderInternal::init(const char *encoding) {
	if (myInitialized) {
	//	xmlCleanupParser();
//		XML_ParserReset(myParser, encoding);
	}
	AppLog("ZLXMLReaderInternal::init");
	myInitialized = true;
	//XML_UseForeignDTD(myParser, XML_TRUE);
	MySaxhandler.initialized = 1;//XML_PARSER_DTD;//XML_PARSER_START;
	//MySaxhandler.
	AppLog("XML_UseForeignDTD %d",xmlSubstituteEntitiesDefault(0));
	const std::vector<std::string> &dtds = myReader.externalDTDs();
	for (std::vector<std::string>::const_iterator it = dtds.begin(); it != dtds.end(); ++it) {
	//	myDTDStreamLocks.insert(ZLFile(*it).inputStream());
		AppLog("parseDTD %s",((std::string)*it).c_str());
		//ParseEntity=xmlSAXParseEntity(&MySaxhandler,((std::string)*it).c_str());
		ParseEntity=xmlParseEntity(((std::string)*it).c_str());
		if (ParseEntity) AppLog("xmlParseEntity OK"); else AppLog("xmlParseEntity bad");

	//	parseDTD(myParser, *it);
	}

//	XML_SetUserData(myParser, &myReader);
	AppLog("XML_SetUserData");
	if (encoding != 0) {
		AppLog("encoding %s",encoding);}
	//if (encoding != 0) {
		//XML_SetEncoding(myParser, encoding);
//	XML_SetEncoding(myParser, "");
	//}
//	AppLog("xmlSAXVersion %d",xmlSAXVersion(&MySaxhandler,2));
	//xmlInitCharEncodingHandlers	();
	xmlNewCharEncodingHandler("windows-1251",fxmlCharEncodingInputFunc,fxmlCharEncodingOutputFunc);

	AppLog("XML_SetEncoding");
	MySaxhandler.startElement = fStartElementHandler;
	MySaxhandler.endElement = fEndElementHandler;
	MySaxhandler.characters = fCharacterDataHandler;
	MySaxhandler.warning =	fWarningSAXFunc;
	MySaxhandler.hasExternalSubset = fHasInternalSubsetSAXFunc;
	MySaxhandler.hasInternalSubset = fHasExternalSubsetSAXFunc;
	MySaxhandler.resolveEntity = fResolveEntitySAXFunc;
	MySaxhandler.unparsedEntityDecl = fUnparsedEntityDeclSAXFunc;
	MySaxhandler.getEntity = fgetEntity;
	MySaxhandler.error = fErrorSAXFunc;
	MySaxhandler.fatalError = fFatalErrorSAXFunc;

//MySaxhandler.elementDecl
//	= fEntityDeclSAXFunc;


	//pMySaxhandler->startElement = fStartElementHandler;
	//pMySaxhandler->endElement = fEndElementHandler;
	//pMySaxhandler->characters = fCharacterDataHandler;
	//pMySaxhandler->warning = fCharacterDataHandler;
	//pMySaxhandler->error = fUnknownEncodingHandler;

	//XML_SetStartElementHandler(myParser, fStartElementHandler);
	//XML_SetEndElementHandler(myParser, fEndElementHandler);
	//XML_SetCharacterDataHandler(myParser, fCharacterDataHandler);
	//XML_SetUnknownEncodingHandler(myParser, fUnknownEncodingHandler, 0);
}

bool ZLXMLReaderInternal::parseBuffer(const char *buffer, size_t len) {
	//XMLPUBFUN int XMLCALL xmlSAXUserParseMemory (xmlSAXHandlerPtr sax, void *user_data, const char *buffer, int size)

	int r = xmlSAXUserParseMemory (&MySaxhandler, &myReader, buffer, len);
	AppLog("xmlSAXUserParseMemory len = %d , r=%d", len, r);
	return true;
	//return XML_Parse(myParser, buffer, len, 0) != XML_STATUS_ERROR;
}
