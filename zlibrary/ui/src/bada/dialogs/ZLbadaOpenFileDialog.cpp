/*
 * Copyright (C) 2010 Geometer Plus <contact@geometerplus.com>
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

//#include <qfiledialog.h>

#include "ZLbadaOpenFileDialog.h"


ZLbadaOpenFileDialog::ZLbadaOpenFileDialog(const std::string &title, const std::string &directoryPath, const std::string &filePath, const Filter &filter) {
//	myDialog = new QFileDialog();
//	myDialog->setCaption(QString::fromUtf8(title.c_str()));
//	myDialog->setDir(QString::fromUtf8(directoryPath.c_str()));
//	myDialog->setSelection(QString::fromUtf8(filePath.c_str()));
}

ZLbadaOpenFileDialog::~ZLbadaOpenFileDialog() {
//	delete myDialog;
}

bool ZLbadaOpenFileDialog::runInternal() {
//	return myDialog->exec();
}

std::string ZLbadaOpenFileDialog::filePath() const {
//	QString path = myDialog->selectedFile();
//	return path.isNull() ? std::string() : (const char*)path.utf8();
}

std::string ZLbadaOpenFileDialog::directoryPath() const {
//	return (const char*)myDialog->dir()->absPath().utf8();
}

void ZLbadaOpenFileDialog::setPosition(int x, int y) {
//	myDialog->move(x, y);
}

void ZLbadaOpenFileDialog::setSize(int width, int height) {
//	myDialog->resize(width, height);
}

int ZLbadaOpenFileDialog::x() const {
//	return myDialog->x();
}

int ZLbadaOpenFileDialog::y() const {
//	return myDialog->y();
}

int ZLbadaOpenFileDialog::width() const {
//	return myDialog->width();
}

int ZLbadaOpenFileDialog::height() const {
//	return myDialog->height();
}
