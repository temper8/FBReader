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

//#include <ZLFile.h>
#include <ZLInputStream.h>
#include <ZLEncodingConverter.h>

#include "ZLXMLReaderInternal.h"
#include "../ZLXMLReader.h"

//void ZLXMLReaderInternal::fCharacterDataHandler(void *userData, const char *text, int len) {
//void fCharacterDataHandler(void *userData, const char *text, int len) {
void fCharacterDataHandler(void *userData,	const xmlChar *text, int len) {
//	AppLog("ZLXMLReaderInternal::fCharacterDataHandler");
	ZLXMLReader &reader = *(ZLXMLReader*)userData;
	if (!reader.isInterrupted()) {
		reader.characterDataHandler((const char*)text, len);
	//	AppLog("fCharacterDataHandler text=%s",(const char*)text);
	//	AppLog("fCharacterDataHandler len = %d",len);
	}
}

//void ZLXMLReaderInternal::fStartElementHandler(void *userData, const char *name, const char **attributes) {
//typedef void(* startElementSAXFunc)(void *ctx, const xmlChar *name, const xmlChar **atts)
//void fStartElementHandler(void *userData, const char *name, const char **attributes) {
void fStartElementHandler2(void *userData, const char *name, const char **attributes) {

	AppLog("fStartElementHandler::name=%s",(const char*)name);
//	if (*attributes!=0) 	AppLog("fStartElementHandler:: attr = %s::%s",(const char*)attributes[0],(const char*)attributes[1]);
//	else {AppLog("A!=0"); return;}
	ZLXMLReader &reader = *(ZLXMLReader*)userData;
	//AppLog("ZLXMLReader &reader");
	if (!reader.isInterrupted()) {
		//AppLog("!reader.isInterrupted()");
		if (reader.processNamespaces()) {
			int count = 0;
			AppLog("int count = 0");
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
		reader.endElementHandler((const char*)name);
		if (reader.processNamespaces()) {
			shared_ptr<std::map<std::string,std::string> > oldMap = reader.myNamespaces.back();
			reader.myNamespaces.pop_back();
			if (reader.myNamespaces.back() != oldMap) {
				reader.namespaceListChangedHandler();
			}
		}
	}
}
/*
static int fUnknownEncodingHandler(void*, const XML_Char *name, XML_Encoding *encoding) {
	ZLEncodingConverterInfoPtr info = ZLEncodingCollection::Instance().info(name);
	if (!info.isNull()) {
		shared_ptr<ZLEncodingConverter> converter = info->createConverter();
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

void ZLXMLReaderInternal::init(const char *encoding) {
	if (myInitialized) {
		xmlCleanupParser();
//		XML_ParserReset(myParser, encoding);
	}
	AppLog("ZLXMLReaderInternal::init");
	myInitialized = true;
	//XML_UseForeignDTD(myParser, XML_FALSE);
	MySaxhandler.initialized = XML_PARSER_START;

	AppLog("XML_UseForeignDTD %d",xmlSubstituteEntitiesDefault(1));
	const std::vector<std::string> &dtds = myReader.externalDTDs();
	for (std::vector<std::string>::const_iterator it = dtds.begin(); it != dtds.end(); ++it) {
		//myDTDStreamLocks.insert(ZLFile(*it).inputStream());
		AppLog("parseDTD %s",((std::string)*it).c_str());
	//	xmlSAXParseEntity(&MySaxhandler,((std::string)*it).c_str());
	//	parseDTD(myParser, *it);
	}

//	XML_SetUserData(myParser, &myReader);
	AppLog("XML_SetUserData");
	//if (encoding != 0) {
		//XML_SetEncoding(myParser, encoding);
//	XML_SetEncoding(myParser, "");
	//}

	AppLog("XML_SetEncoding");
	MySaxhandler.startElement = fStartElementHandler;
	MySaxhandler.endElement = fEndElementHandler;
	MySaxhandler.characters = fCharacterDataHandler;

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
