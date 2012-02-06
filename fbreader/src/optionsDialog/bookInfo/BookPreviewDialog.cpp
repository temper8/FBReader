/*
 * BookPreviewDialog.cpp
 *
 *  Created on: 28.01.2012
 *      Author: Alex
 */
#include <algorithm>

#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>
#include <ZLOptionEntry.h>
#include <ZLFile.h>
#include <ZLLanguageList.h>
#include <ZLStringUtil.h>

#include <optionEntries/ZLStringInfoEntry.h>
#include <optionEntries/ZLSimpleOptionEntry.h>
#include <optionEntries/ZLLanguageOptionEntry.h>

#include "BookInfoDialog.h"

#include "../../library/Library.h"
#include "../../encodingOption/EncodingOptionEntry.h"
#include "../../library/Book.h"
#include "../../library/Tag.h"
#include "../../library/Author.h"
#include "BookPreviewDialog.h"
#include <FBase.h>
#include "../../tree/FBNode.h"
#include "../../fbreader/FBReader.h"
#include "../../formats/FormatPlugin.h"
#include "PreviewEntries.h"
/*
class StringEntry2 : public ZLStringOptionEntry {

public:
	StringEntry2(const std::string &value);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);

private:
	const std::string &myString;
};

StringEntry2::StringEntry2(const std::string &value) : myString(value) {
}

const std::string &StringEntry2::initialValue() const {
	return myString;
}

void StringEntry2::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}
*/

class BookPreviewTitleEntry : public ZLStringOptionEntry {

public:
	BookPreviewTitleEntry(BookPreviewDialog &dialog);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);

private:
	BookPreviewDialog &myPreviewDialog;
};

BookPreviewTitleEntry::BookPreviewTitleEntry(BookPreviewDialog &dialog) : myPreviewDialog(dialog) {
}

const std::string &BookPreviewTitleEntry::initialValue() const {
	return myPreviewDialog.myBook->title();
}

void BookPreviewTitleEntry::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}



class BookOpenAction : public ZLRunnable {

public:
	BookOpenAction(shared_ptr<Book> book);
	void run();

private:
	shared_ptr<Book> myBook;
};

BookOpenAction::BookOpenAction(shared_ptr<Book> book) : myBook(book) {}

void BookOpenAction::run() {
	AppLog("BookOpenAction::run");
	//Book &book = *myPreviewDialog.myBook;
	FBReader &fbreader = FBReader::Instance();
	fbreader.openBook(myBook);
	fbreader.showBookTextView();
	//AppLog("BookOpenAction %s",book.title().c_str());
}

class AuthorFunctor {
public:
    std::string operator()(shared_ptr<Author> author) const;
};

BookPreviewDialog::BookPreviewDialog(shared_ptr<Book> book) : myBook(book)  {
	// TODO Auto-generated constructor stub
	myDialog = ZLDialogManager::Instance().createOptionsDialog(ZLResourceKey("InfoDialog"), new BookOpenAction(myBook));

	ZLDialogContent &commonTab = myDialog->createTab(ZLResourceKey("Common"));
	AppLog("myDialog->createTab");
	shared_ptr<ZLImage> bookImage;

	//shared_ptr<FormatPlugin> plugin = PluginCollection::Instance().plugin(*myBook);
	//if (!plugin.isNull()) {
	//	bookImage = plugin->coverImage(myBook->file());
	//	}
	//else
		bookImage = FBNode::defaultCoverImage("booktree-book.png");
//	commonTab.addOption(ZLResourceKey("cover"), new ZLPictureOptionEntry(bookImage));


	ZLDialogContent &BookInfoTab = myDialog->createTab(ZLResourceKey("BookInfo"));
	//commonTab.addOption(ZLResourceKey("title"), new BookPreviewTitleEntry(*this));
	BookInfoTab.addOption(ZLResourceKey("title"), new StaticTextEntry(myBook->title()));
	AppLog("commonTab.addOption title");
	//ZLStringUtil::join(book->authors(), AuthorFunctor(), FBNode::COMMA_JOIN_SEPARATOR);
	std::string authors = ZLStringUtil::join(myBook->authors(),AuthorFunctor(), FBNode::COMMA_JOIN_SEPARATOR);
	BookInfoTab.addOption(ZLResourceKey("authors"), new StaticTextEntry(authors));
	BookInfoTab.addOption(ZLResourceKey("seriesTitle"), new StaticTextEntry(myBook->seriesTitle()));

	//commonTab.addOption(ZLResourceKey("file"), new ZLStringInfoEntry(ZLFile::fileNameToUtf8(book->file().path())));
	ZLDialogContent &SummaryTab = myDialog->createTab(ZLResourceKey("Summary"));
	//SummaryTab.addOption(ZLResourceKey("title"), new StaticTextEntry(myBook.Summary));
	SummaryTab.addOption(ZLResourceKey("file"), new ZLStringInfoEntry(ZLFile::fileNameToUtf8(book->file().path())));
	AppLog("commonTab.addOption file");

}

BookPreviewDialog::~BookPreviewDialog() {
	// TODO Auto-generated destructor stub
}
