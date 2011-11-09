/*
 * ZLbadaLibraryImplementation.h
 *
 *  Created on: 11.10.2011
 *      Author: Alex
 */

#ifndef ZLBADALIBRARYIMPLEMENTATION_H_
#define ZLBADALIBRARYIMPLEMENTATION_H_

#include "../view/badaApp.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

#include <ZLApplication.h>
#include <ZLibrary.h>
//#include <ZLLanguageUtil.h>

//#include "../../../../core/src/unix/library/ZLibraryImplementation.h"
#include "ZLibraryImplementation.h"


//#include "../filesystem/ZLQtFSManager.h"
#include "../filesystem/ZLbadaFSManager.h"

#include "../time/ZLbadaTime.h"
#include "../dialogs/ZLbadaDialogManager.h"
//#include "../image/ZLQtImageManager.h"
//#include "../view/ZLQtPaintContext.h"

//#include "../../unix/message/ZLUnixMessage.h"
#include "../../unix/message/ZLUnixMessage.h"

#include "../../../../core/src/util/ZLKeyUtil.h"

//#include "ZLKeyUtil.h"

#include <XMLConfig.h>
//#include "../../../../core/src/unix/iconv/IConvEncodingConverter.h"
//#include "../../../../core/src/unix/curl/ZLCurlNetworkManager.h"

class ZLbadaLibraryImplementation : public ZLibraryImplementation {

private:
	ArrayList* pArgs;
	//static Osp::App::Application* Bada2App;
	void init(int &argc, char **&argv);
	ZLPaintContext *createContext();
	void run(ZLApplication *application);

public:
	static badaApp*  myBadaApp;
    static ZLApplication* ZLApp;
	static void createApplicationWindow();
	static void SetZLApplication(ZLApplication* a) { ZLApp = a; };
	static void SetBada2App(badaApp* b);
	ZLbadaLibraryImplementation();
	~ZLbadaLibraryImplementation();
};


#endif /* ZLBADALIBRARYIMPLEMENTATION_H_ */
