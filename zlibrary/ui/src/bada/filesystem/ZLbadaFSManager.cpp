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

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <set>

#include <ZLStringUtil.h>

#include "ZLbadaFSManager.h"
#include "ZLbadaFSDir.h"
#include "ZLbadaFileInputStream.h"
#include "ZLbadaFileOutputStream.h"

#include <FBase.h>
#include <FIo.h>

using namespace Osp::Base;
using namespace Osp::Io;


//--------------
ZLbadaFSManager::ZLbadaFSManager():ZLFSManager() {
	AppLog("ZLbadaFSManager::ZLbadaFSManager");
	//connect(&myWatcher, SIGNAL(directoryChanged(QString)), SLOT(onPathChanged(QString)));
	//connect(&myWatcher, SIGNAL(fileChanged(QString)), SLOT(onPathChanged(QString)));
}




std::string ZLbadaFSManager::convertFilenameToUtf8(const std::string &name) const {
	if (name.empty()) {
		return name;
	}
	// AppLog("ZLbadaFSManager::convertFilenameToUtf8");
	// AppLog("name = %s",name.c_str());

	 return name;
	//QString qString = QString::fromLocal8Bit(name.c_str());
	//return (qString == QString::null) ? "" : (const char*)qString.toUtf8();
}
/*
std::string ZLbadaFSManager::mimeType(const std::string &path) const {
	// TODO: implement
	 AppLog("ZLbadaFSManager::mimeType");
	return std::string();
}

*/

shared_ptr<ZLMimeType> ZLbadaFSManager::mimeType(const std::string &path) const {
	// TODO: implement
	 AppLog("ZLbadaFSManager::mimeType");
	return ZLMimeType::EMPTY;
}

//---------------


static std::string getPwdDir() {
	char *pwd = getenv("PWD");
	return (pwd != 0) ? pwd : "";
}

static std::string getHomeDir() {
	char *home = getenv("HOME");
	return (home != 0) ? home : "";
}

ZLFileInfo ZLbadaFSManager::fileInfo(const std::string &path) const {
	ZLFileInfo info;
	struct stat fileStat;
    result r = E_SUCCESS;
    FileAttributes attr;
    r = File::GetAttributes(path.c_str(), attr);
   //TODO if(IsFailed(r)) goto CATCH;

	//info.Exists = stat(path.c_str(), &fileStat) == 0; stat - не работает
    info.Exists = (r==E_SUCCESS);

	AppLog("ZLbadaFSManager::fileInfo %s",path.c_str());
	if (info.Exists) {
		info.Size = attr.GetFileSize();//fileStat.st_size;
		//AppLog("ZLbadaFSManager::fileInfo.Size %d",fileStat.st_size);
		AppLog("ZLbadaFSManager::fileInfo.Size %d",info.Size);
		//AppLog("ZLbadaFSManager::fileInfo.st_mode %x",fileStat.st_mode);
		info.IsDirectory = attr.IsDirectory();//S_ISDIR(fileStat.st_mode);
		if (info.IsDirectory) AppLog("ZLbadaFSManager::fileInfo.IsDirectory");
	}
	return info;
}

std::string ZLbadaFSManager::resolveSymlink(const std::string &path) const {
//	AppLog("ZLbadaFSManager::resolveSymlink %s",path.c_str());
	return path;
}
	/*
	std::set<std::string> names;
	std::string current = path;
	for (int i = 0; i < 256; ++i) {
		names.insert(current);

		std::string buffer(2048, '\0');
		int len = readlink(current.c_str(), (char*)buffer.data(), 2048);
		if ((len == 2048) || (len <= 0)) {
			return current;
		}
		buffer.erase(len);
		if (buffer[0] != '/') {
			buffer = parentPath(current) + '/' + buffer;
		}
		normalizeRealPath(buffer);
		if (names.find(buffer) != names.end()) {
			return buffer;
		}
		current = buffer;
	}
	return "";

}
*/
void ZLbadaFSManager::normalizeRealPath(std::string &path) const {
	static std::string HomeDir = getHomeDir();
	static std::string PwdDir = getPwdDir();

	if (path.empty()) {
		path = PwdDir;
	} else if (path[0] == '~') {
		if ((path.length() == 1) || (path[1] == '/')) {
			path = HomeDir + path.substr(1);
		}
	} else if (path[0] != '/') {
		path = PwdDir + '/' + path;
	}
	int last = path.length() - 1;
	while ((last > 0) && (path[last] == '/')) {
		--last;
	}
	if (last < (int)path.length() - 1) {
		path = path.substr(0, last + 1);
	}

	int index;
	while ((index = path.find("/../")) != -1) {
		int prevIndex = std::max((int)path.rfind('/', index - 1), 0);
		path.erase(prevIndex, index + 3 - prevIndex);
	}
	int len = path.length();
	if ((len >= 3) && (path.substr(len - 3) == "/..")) {
		int prevIndex = std::max((int)path.rfind('/', len - 4), 0);
		path.erase(prevIndex);
	}
	while ((index = path.find("/./")) != -1) {
		path.erase(index, 2);
	}
	while (path.length() >= 2 &&
				 path.substr(path.length() - 2) == "/.") {
		path.erase(path.length() - 2);
	}
	while ((index = path.find("//")) != -1) {
		path.erase(index, 1);
	}
}

ZLFSDir *ZLbadaFSManager::createNewDirectory(const std::string &path) const {
	std::vector<std::string> subpaths;
	std::string current = path;

	while (current.length() > 1) {
		struct stat fileStat;
		if (stat(current.c_str(), &fileStat) == 0) {
			if (!S_ISDIR(fileStat.st_mode)) {
				return 0;
			}
			break;
		} else {
			subpaths.push_back(current);
			int index = current.rfind('/');
			if (index == -1) {
				return 0;
			}
			current.erase(index);
		}
	}

	for (int i = subpaths.size() - 1; i >= 0; --i) {
		if (mkdir(subpaths[i].c_str(), 0x1FF) != 0) {
			return 0;
		}
	}
	return createPlainDirectory(path);
}

ZLFSDir *ZLbadaFSManager::createPlainDirectory(const std::string &path) const {
	return new ZLbadaFSDir(path);
}

ZLInputStream *ZLbadaFSManager::createPlainInputStream(const std::string &path) const {
	return new ZLbadaFileInputStream(path);
}

ZLOutputStream *ZLbadaFSManager::createOutputStream(const std::string &path) const {
	return new ZLbadaFileOutputStream(path);
}

bool ZLbadaFSManager::removeFile(const std::string &path) const {
	return unlink(path.c_str()) == 0;
}

int ZLbadaFSManager::findArchiveFileNameDelimiter(const std::string &path) const {
	return path.rfind(':');
}

static const std::string RootPath = "/";

shared_ptr<ZLDir> ZLbadaFSManager::rootDirectory() const {
	return createPlainDirectory(RootPath);
}

const std::string &ZLbadaFSManager::rootDirectoryPath() const {
	return RootPath;
}

std::string ZLbadaFSManager::parentPath(const std::string &path) const {
	if (path == RootPath) {
		return path;
	}
	int index = findLastFileNameDelimiter(path);
	return (index <= 0) ? RootPath : path.substr(0, index);
}

bool ZLbadaFSManager::canRemoveFile(const std::string &path) const {
//	AppLog("ZLbadaFSManager::canRemoveFile %s",path.c_str());
	result r = E_SUCCESS;
	FileAttributes attr;
    r = File::GetAttributes(path.c_str(), attr);
	//TODO   if(IsFailed(r)) goto CATCH;
   return !attr.IsReadOnly();
//	return access(parentPath(path).c_str(), W_OK) == 0;
}

