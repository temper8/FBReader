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

//#include <qapplication.h>
//#include <qmessagebox.h>
//#include <qfiledialog.h>
//#include <qclipboard.h>





//#include "ZLQtDialogContent.h"
//#include "ZLQtProgressDialog.h"
//#include "ZLQtUtil.h"

//#include "../image/ZLQtImageManager.h"

#include <FBase.h>
#include <FContent.h>
#include "../application/ZLbadaApplicationWindow.h"
#include "../view/badaForm.h"
#include "../view/ZLbadaViewWidget.h"
#include "ZLbadaDialog.h"
#include "ZLbadaDialogManager.h"
#include "ZLbadaOpenFileDialog.h"
#include "ZLbadaOptionsDialog.h"

using namespace Osp::Ui::Controls;

void ZLbadaDialogManager::createApplicationWindow(ZLApplication *application) const {
	myApplicationWindow = new ZLbadaApplicationWindow(application);
}


shared_ptr<ZLDialog> ZLbadaDialogManager::createDialog(const ZLResourceKey &key) const {
	return new ZLbadaDialog(resource()[key]);
}

shared_ptr<ZLOptionsDialog> ZLbadaDialogManager::createOptionsDialog(const ZLResourceKey &key, shared_ptr<ZLRunnable> applyAction, bool showApplyButton) const {
	return new ZLbadaOptionsDialog(resource()[key], applyAction, showApplyButton);
}


shared_ptr<ZLOpenFileDialog> ZLbadaDialogManager::createOpenFileDialog(const ZLResourceKey &key, const std::string &directoryPath, const std::string &filePath, const ZLOpenFileDialog::Filter &filter) const {
	ZLbadaOpenFileDialog *b= new ZLbadaOpenFileDialog(dialogTitle(key), directoryPath, filePath, filter);
	AppLog("ZLbadaDialogManager::createOpenFileDialog");
	b->pSearchResultInfo = myApplicationWindow->viewWidget().mybadaForm->pSearchResultInfo;

	return b;
}

void ZLbadaDialogManager::informationBox(const std::string &title, const std::string &message) const {
//	QMessageBox::information(
//		qApp->mainWidget(),
//		::qtString(title),
//		::qtString(message),
//		::qtButtonName(OK_BUTTON)
//	);
}

void ZLbadaDialogManager::errorBox(const ZLResourceKey &key, const std::string &message) const {
/*	QMessageBox::critical(
		qApp->mainWidget(),
		::qtString(dialogTitle(key)),
		::qtString(message),
		::qtButtonName(OK_BUTTON)
	);*/
}
/*
int ZLbadaDialogManager::questionBox(const ZLResourceKey &key, const std::string &message, const ZLResourceKey &button0, const ZLResourceKey &button1, const ZLResourceKey &button2) const {
	return QMessageBox::question(
		qApp->mainWidget(),
		::qtString(dialogTitle(key)),
		::qtString(message),
		::qtButtonName(button0),
		::qtButtonName(button1),
		::qtButtonName(button2)
	);
}

shared_ptr<ZLProgressDialog> ZLQtDialogManager::createProgressDialog(const ZLResourceKey &key) const {
	return new ZLQtProgressDialog(key);
}

bool ZLQtDialogManager::isClipboardSupported(ClipboardType type) const {
	return true;
}

void ZLQtDialogManager::setClipboardText(const std::string &text, ClipboardType type) const {
	if (!text.empty()) {
		qApp->clipboard()->setText(
			::qtString(text),
			(type == CLIPBOARD_MAIN) ? QClipboard::Clipboard : QClipboard::Selection
		);
	}
}

void ZLQtDialogManager::setClipboardImage(const ZLImageData &imageData, ClipboardType type) const {
	qApp->clipboard()->setImage(
		(ZLQtImageData&)imageData,
		(type == CLIPBOARD_MAIN) ? QClipboard::Clipboard : QClipboard::Selection
	);
}
*/
