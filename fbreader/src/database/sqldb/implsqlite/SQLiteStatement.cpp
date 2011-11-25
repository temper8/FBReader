/*
 * Copyright (C) 2009-2010 Geometer Plus <contact@geometerplus.com>
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


#include "SQLiteStatement.h"
#include "SQLiteDataBase.h"
#include <FTextAsciiEncoding.h>
using namespace Osp::Text;
using namespace std;

SQLiteStatement::SQLiteStatement(Database *db, const char *zSql, const char **pzTail) {
	pDb = db;
	pEnum = 0;
	pStmt = 0;
	int i=0;
	String sql = "";
	String nVal = "";
	const char *begin = "BEGIN";
	int pos = 0;
	bool isBegin = false;
	const char *end = "END";
	bool isVal = false;
	while (zSql[i] != 0) {
		if (isVal) {
			if ((zSql[i] == ',') || (zSql[i] == ' ') ||(zSql[i] == ';') ||(zSql[i] == ')') || (zSql[i] == 0x13) || (zSql[i] == 0x10)) {
				sql.Append(zSql[i]);
				isVal = false;
				params.push_back(nVal);
				nVal = "";
			} else {
				nVal.Append(zSql[i]);
			}
		} else {
			if (zSql[i] == '@') {
				sql.Append("?");
				isVal = true;
				nVal = "@";
			} else {
				sql.Append(zSql[i]);
			}
		}
		if(isBegin) {
			if(zSql[i++]==end[pos]) {//можно добавить проверку на ограничительные символы
				pos++;
				if (end[pos]==0) {
					isBegin=false;
					pos=0;
				}
			} else {
				pos=0;
			}
		} else {
			if(zSql[i]==begin[pos]) {
				pos++;
				if (begin[pos]==0) {
					isBegin=true;
					pos=0;
				}
			} else {
				pos=0;
			}
			if (zSql[i++] == ';') {
				break;
			}
		}
	}
	if (nVal != "") {
		params.push_back(nVal);
	}
	*pzTail = &zSql[i];
	sql.Trim();
	if (sql != "") {
		pStmt = pDb->CreateStatementN(sql);
	} else {
		pStmt = 0;
	}
}
const char* SQLiteStatement::GetCString(const String& sBadaStr) const {
   // if (sBadaStr.GetLength() == 0) return null;
    ByteBuffer* bb = Osp::Base::Utility::StringUtil::StringToUtf8N(sBadaStr);
    AppLog( "SQLiteStatement::GetCString %s",(char *)bb->GetPointer());
    return (const char *)bb->GetPointer();
  /*  Osp::Text::AsciiEncoding ascii;
    int byteCount = 0;
    string* cString = null;
    ByteBuffer* pBuffer = ascii.GetBytesN(sBadaStr);
    if (pBuffer != null){
        byteCount = pBuffer->GetLimit();
        char* chPtrBuf = new char[byteCount + 1];
        if (chPtrBuf != null){
            pBuffer->GetArray((byte*)chPtrBuf, 0, byteCount);
            cString = new string(chPtrBuf);
            if (chPtrBuf != null) delete [] chPtrBuf;
        }
        if (pBuffer != null) delete pBuffer;
    }
    if (cString != null) return cString;
    return null;*/
}
int SQLiteStatement::bind_parameter_index(const char *zName){
	String parName = zName;
	int res = 0;
	int i=1;
	for (std::vector<String>::iterator it = params.begin(); it != params.end(); it++) {
		if (parName.Equals(*it, false)) {
			res = i;
			break;
		}
		i++;
	}
	return res;
}
const char *SQLiteStatement::bind_parameter_name(int num){
	std::vector<String>::iterator it = params.begin();
	it != params.end();
	it=it+(num-1);
	return GetCString(*it);
}
int SQLiteStatement::column_count(){
	if (pEnum) {
		return pEnum->GetColumnCount();
	} else {
		return 0;
	}
}
int SQLiteStatement::column_type(int iCol){
	if (pEnum) {
		switch (pEnum->GetColumnType(iCol)) {
			case DB_COLUMNTYPE_INT: return SQLITE_INTEGER;
			case DB_COLUMNTYPE_DOUBLE: return SQLITE_FLOAT;
			case DB_COLUMNTYPE_TEXT: return SQLITE_TEXT;
			case DB_COLUMNTYPE_NULL: return SQLITE_NULL;
			default: return 0;
		}
	} else {
		return 0;
	}
}
int SQLiteStatement::column_int(int iCol){
	int res;
	pEnum->GetIntAt(iCol, res);
	return res;
}
double SQLiteStatement::column_double(int iCol){
	double res;
	pEnum->GetDoubleAt(iCol, res);
	return res;
}
const unsigned char *SQLiteStatement::column_text(int iCol){
	String res;
	pEnum->GetStringAt(iCol, res);
	const unsigned char* ch = (unsigned char*)GetCString(res);
	return ch;
}
int SQLiteStatement::bind_parameter_count(){
	return params.size();
}
int SQLiteStatement::bind_null(int num){
	switch (pStmt->BindNull(num)) {
		case E_SUCCESS: return SQLITE_OK;
		default: return SQLITE_ERROR;
	}
}
int SQLiteStatement::bind_int(int num, int val){
	switch (pStmt->BindInt(num - 1, val)) {
		case E_SUCCESS: return SQLITE_OK;
		default: return SQLITE_ERROR;
	}
}
int SQLiteStatement::bind_double(int num, double val){
	switch (pStmt->BindDouble(num - 1, val)) {
		case E_SUCCESS: return SQLITE_OK;
		default: return SQLITE_ERROR;
	}
}
int SQLiteStatement::bind_text(int num, const char* val){
	switch (pStmt->BindString(num - 1, val)) {
		case E_SUCCESS: return SQLITE_OK;
		default: return SQLITE_ERROR;
	}
}
int SQLiteStatement::step(){
	int res = E_INVALID_STATE ;
	if (!pEnum) {
		pEnum = pDb->ExecuteStatementN(*pStmt);
		if (pEnum) {
			res = pEnum->MoveNext();
		} else {
			res = GetLastResult();
			if (res == E_SUCCESS) return SQLITE_DONE;
		}
	} else {
		res = pEnum->MoveNext();
	}
	switch (res) {
		case E_SUCCESS: return SQLITE_ROW;
		case E_OUT_OF_RANGE: return SQLITE_DONE;
		default: return SQLITE_ERROR;
	}
}
int SQLiteStatement::reset(){
	int res = E_SUCCESS;
	if (pEnum) {
		res = pEnum->Reset();
	}
	if (res == E_SUCCESS) {
		return SQLITE_OK;
	} else {
		return SQLITE_ERROR;
	}
}
int SQLiteStatement::finalize(){
	if (pStmt) delete pStmt;
	if (pEnum) delete pStmt;
	return SQLITE_OK;
}
int SQLiteStatement::prepare(Database *db, const char *zSql, SQLiteStatement **ppStmt, const char **pzTail) {
	if (zSql[0]==0) {
		*ppStmt = 0;
	} else {
		*ppStmt = new SQLiteStatement(db, zSql, pzTail);
		if ((**ppStmt).pStmt==0) {
			delete ppStmt;
			*ppStmt = 0;
		}
	}
	return SQLITE_OK;
}
