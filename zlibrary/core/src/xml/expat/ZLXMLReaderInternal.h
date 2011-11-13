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

#ifndef __ZLXMLREADERINTERNAL_H__
#define __ZLXMLREADERINTERNAL_H__

//#include <expat.h>
#include "FXml.h"
#include "FBase.h"
using namespace Osp::Xml;
//#include "xmlstring.h"

#include <set>
/*
xmlParserInputPtr ResolveEntitySAXFunc (void *ctx, const xmlChar *publicId, const xmlChar *systemId);
void InternalSubsetSAXFunc (void *ctx, const xmlChar *name, const xmlChar *ExternalID, const xmlChar *SystemID);
void ExternalSubsetSAXFunc (void *ctx, const xmlChar *name, const xmlChar *ExternalID, const xmlChar *SystemID);
xmlEntityPtr GetEntitySAXFunc (void *ctx, const xmlChar *name);
xmlEntityPtr GetParameterEntitySAXFunc (void *ctx, const xmlChar *name);

void EntityDeclSAXFunc (void *ctx, 	const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId, xmlChar *content);
void NotationDeclSAXFunc(void *ctx,  const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId);
void AttributeDeclSAXFunc(void *ctx, const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree);
void ElementDeclSAXFunc(void *ctx, const xmlChar *name, int type, xmlElementContentPtr content);
void UnparsedEntityDeclSAXFunc(void *ctx, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName);
void SetDocumentLocatorSAXFunc (void *ctx, 	xmlSAXLocatorPtr loc);
void StartDocumentSAXFunc (void *ctx);
void EndDocumentSAXFunc (void *ctx);
void StartElementSAXFunc (void *ctx, const xmlChar *name, const xmlChar **atts);
void EndElementSAXFunc (void *ctx, const xmlChar *name);
void AttributeSAXFunc (void *ctx, const xmlChar *name, const xmlChar *value);
void ReferenceSAXFunc (void *ctx, const xmlChar *name);
void CharactersSAXFunc (void *ctx, const xmlChar *ch, int len);
void IgnorableWhitespaceSAXFunc (void *ctx, const xmlChar *ch, int len);
void ProcessingInstructionSAXFunc (void *ctx, const xmlChar *target, const xmlChar *data);
void CommentSAXFunc (void *ctx, const xmlChar *value);
void CdataBlockSAXFunc (void *ctx, const xmlChar *value, int len);
void WarningSAXFunc (void *ctx, const char *msg, ...);
void ErrorSAXFunc (void *ctx, const char *msg, ...);
void FatalErrorSAXFunc (void *ctx, const char *msg, ...);
int IsStandaloneSAXFunc (void *ctx);
int HasInternalSubsetSAXFunc (void *ctx);
int HasExternalSubsetSAXFunc (void *ctx);


xmlSAXHandler mySaxHandler = {
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    null,
    0,
    null,
    null,
    null,
    null
};


*/








class ZLXMLReader;

class ZLXMLReaderInternal {

private:
//	static void fStartElementHandler(void *userData, const char *name, const char **attributes);
//	static void fEndElementHandler(void *userData, const char *name);
//	static void fCharacterDataHandler(void *userData, const char *text, int len);

public:
	ZLXMLReaderInternal(ZLXMLReader &reader, const char *encoding);
	~ZLXMLReaderInternal();
	void init(const char *encoding = 0);
	bool parseBuffer(const char *buffer, size_t len);

private:
	ZLXMLReader &myReader;
	xmlSAXHandler MySaxhandler;

	//XML_Parser myParser;
	bool myInitialized;

	std::set<shared_ptr<ZLInputStream> > myDTDStreamLocks;
};

#endif /* __ZLXMLREADERINTERNAL_H__ */
