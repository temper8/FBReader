/*
 * OptionsDialogActions.cpp
 *
 *  Created on: 11.12.2011
 *      Author: Alex
 */

#include "OptionsDialogActions.h"
#include "../fbreader/FBReader.h"
#include "lookAndFeel/LookAndFeelOptionsDialog.h"
#include "reading/ReadingOptionsDialog.h"
#include "system/SystemOptionsDialog.h"
#include "library/LibraryOptionsDialog.h"
#include "color/ColorOptionsDialog.h"
#include "textStyle/TextStyleOptionsDialog.h"
#include "text/TextOptionsDialog.h"
#include "ZLOptionsDialog.h"

//TextStyleOptionsDialogAction   +
//ColorOptionsDialogAction       +
//ShowLibraryOptionsDialogAction       +
//ShowNetworkOptionsDialogAction       -
//ShowSystemOptionsDialogAction        +
//ShowReadingOptionsDialogAction       +
//ShowLookAndFeelOptionsDialogAction   +

TextStyleOptionsDialogAction::TextStyleOptionsDialogAction(ZLTextStyleDecoration &decoration) : myTextStyleDecoration(decoration)  {
}

void TextStyleOptionsDialogAction::run() {
	if (TextStyleOptionsDialog(myTextStyleDecoration).dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey TextStyleOptionsDialogAction::key() const {
	return ZLResourceKey("TextStyleOptionsDialog");
}


ColorOptionsDialogAction::ColorOptionsDialogAction()  {
}

void ColorOptionsDialogAction::run() {
	if (ColorOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey ColorOptionsDialogAction::key() const {
	return ZLResourceKey("ColorOptionsDialog");
}


LibraryOptionsDialogAction::LibraryOptionsDialogAction()  {
}

void LibraryOptionsDialogAction::run() {
	if (LibraryOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey LibraryOptionsDialogAction::key() const {
	return ZLResourceKey("LibraryOptionsDialog");
}


SystemOptionsDialogAction::SystemOptionsDialogAction()  {
}

void SystemOptionsDialogAction::run() {
	if (SystemOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey SystemOptionsDialogAction::key() const {
	return ZLResourceKey("SystemOptionsDialog");
}



ReadingOptionsDialogAction::ReadingOptionsDialogAction()  {
}

void ReadingOptionsDialogAction::run() {
	if (ReadingOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey ReadingOptionsDialogAction::key() const {
	return ZLResourceKey("text");
}


LookAndFeelOptionsDialogAction::LookAndFeelOptionsDialogAction()  {
}

void LookAndFeelOptionsDialogAction::run() {
	if (LookAndFeelOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey LookAndFeelOptionsDialogAction::key() const {
	return ZLResourceKey("LookAndFeelOptionsDialog");
}

TextOptionsDialogAction::TextOptionsDialogAction()  {
}

void TextOptionsDialogAction::run() {
	if (TextOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey TextOptionsDialogAction::key() const {
	return ZLResourceKey("text");
}

