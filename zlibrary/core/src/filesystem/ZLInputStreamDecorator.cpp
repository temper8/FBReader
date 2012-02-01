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

#include "ZLInputStream.h"
#include <FBase.h>

ZLInputStreamDecorator::ZLInputStreamDecorator(shared_ptr<ZLInputStream> decoratee) : myBaseStream(decoratee), myBaseOffset(0) {
}

bool ZLInputStreamDecorator::open() {
	bool result = myBaseStream->open();
	myBaseOffset = myBaseStream->offset();
	return result;
}

size_t ZLInputStreamDecorator::read(char *buffer, size_t maxSize) {
	//AppLog("  ZLInputStreamDecorator::read");
	myBaseStream->seek(myBaseOffset, true);
	size_t result = myBaseStream->read(buffer, maxSize);
	myBaseOffset = myBaseStream->offset();
	return result;
}

void ZLInputStreamDecorator::close() {
	myBaseStream->close();
}

void ZLInputStreamDecorator::seek(int offset, bool absoluteOffset) {
//	AppLog("  ZLInputStreamDecorator::seek %d",offset);
	if (absoluteOffset) {
	//	AppLog("  ZLInputStreamDecorator::seek 1");
		myBaseStream->seek(offset, true);
	} else {
	//	AppLog("  ZLInputStreamDecorator::seek 2");
		myBaseStream->seek(myBaseOffset + offset, true);
	}
	myBaseOffset = myBaseStream->offset();
}

size_t ZLInputStreamDecorator::offset() const {
	return myBaseOffset;
}

size_t ZLInputStreamDecorator::sizeOfOpened() {
	return myBaseStream->sizeOfOpened();
}
