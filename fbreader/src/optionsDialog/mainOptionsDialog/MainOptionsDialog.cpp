/*
 * MainOptionsDialog.cpp
 *
 *  Created on: 28.11.2011
 *      Author: Alex
 */

#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>

#include "../../fbreader/FBReader.h"

#include "MainOptionsDialog.h"
#include <FBase.h>


MainOptionsDialog::MainOptionsDialog(): AbstractOptionsDialog(ZLResourceKey("PreferenceDialog"), true) {
	// TODO Auto-generated constructor stub
	AppLog("MainOptionsDialog::MainOptionsDialog()");
	ZLDialogContent &libraryTab = dialog().createTab(ZLResourceKey("Preference"));

	Library &library = Library::Instance();
	libraryTab.addOption(ZLResourceKey("bookPath"), library.PathOption);
	libraryTab.addOption(ZLResourceKey("lookInSubdirectories"), library.ScanSubdirsOption);
	libraryTab.addOption(ZLResourceKey("collectBooksWithoutMetaInfo"), library.CollectAllBooksOption);
	//	libraryTab.addOption(ZLResourceKey("downloadDirectory"), NetworkLinkCollection::Instance().DirectoryOption);

}

MainOptionsDialog::~MainOptionsDialog() {
	// TODO Auto-generated destructor stub
}
