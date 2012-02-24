#include <unistd.h>

#include <ZLibrary.h>
#include <ZLTimeManager.h>

#include "ZLbadaProgressDialog.h"
//#include "ZLQtTreeDialog.h" // for TreeActionListener
//#include "ZLQtUtil.h"
#include "ZLbadaDialogManager.h"

#include <FBase.h>
#include <FUi.h>
#include <FMedia.h>

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
//using namespace Osp::Content;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;
using namespace Osp::Media;

/*
LoadingIcon::LoadingIcon(QWidget* parent) : QLabel(parent), myAngle(0) {
    const int ICON_WIDT H = 60;
    const int ICON_HEIGHT = ICON_WIDTH;
    QString iconFile = QString::fromStdString(ZLibrary::ApplicationImageDirectory()) +
                       QString::fromStdString(ZLibrary::FileNameDelimiter) +
                       "loading_icon.svg";
    qDebug() << "LoadingIcon" << iconFile;
    myTimer = new QTimer(this);
    myPixmap = QPixmap(iconFile);
    myPixmap = myPixmap.scaled(QSize(ICON_WIDTH, ICON_HEIGHT), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
    connect(myTimer,SIGNAL(timeout()), this, SLOT(rotate()));
    this->hide();

}

void LoadingIcon::moveToPosition(QSize size) {
    move( (size.width() - myPixmap.width()) / 2,
          (size.height() - myPixmap.height()) / 2
        );
}

void LoadingIcon::start() {
    this->show();
    const int REFRESH_TIME = 100;
    myTimer->start(REFRESH_TIME);
}

void LoadingIcon::finish() {
    qDebug() << Q_FUNC_INFO;
    myTimer->stop();
    this->hide();
}

void LoadingIcon::rotate() {
    qDebug() << this->size();
    const int ANGLE_SPEED = 360/10;
    myAngle += ANGLE_SPEED;
    if (myAngle >= 360) {
        myAngle -= 360;
    }
    QPixmap tmpPixmap(myPixmap.size());
    tmpPixmap.fill(Qt::transparent);
    QPainter painter(&tmpPixmap);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.translate(myPixmap.width()/2,myPixmap.height()/2);
    painter.rotate(qreal(myAngle));
    painter.translate(-myPixmap.width()/2,-myPixmap.height()/2);
    painter.drawPixmap(0,0,myPixmap);
    painter.end();
    this->setPixmap(tmpPixmap);
    QWidget::raise();
}
*/
ZLbadaProgressDialog::ZLbadaProgressDialog(const ZLResourceKey &key) : ZLProgressDialog(key), myRunnable(null) {

}

static const double COEF_PROGRESS_BAR_WIDTH = 0.75;

Osp::Base::Object* ZLbadaProgressDialog::Run(void){
	myRunnable->run();
	return null;
}

void ZLbadaProgressDialog::ConstructAnimationFrameList(void){
	Image *pImage = new Image();
	result r = pImage->Construct();
		//Bitmap *pBitmap1 = pAppResource->GetBitmapN("/blue/progressing00_big.png");
		Bitmap *pBitmap1 = pImage->DecodeN("/Res/icons/ani/progressing00.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap2 = pImage->DecodeN("/Res/icons/ani/progressing01.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap3 = pImage->DecodeN("/Res/icons/ani/progressing02.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap4 = pImage->DecodeN("/Res/icons/ani/progressing03.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap5 = pImage->DecodeN("/Res/icons/ani/progressing04.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap6 = pImage->DecodeN("/Res/icons/ani/progressing05.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap7 = pImage->DecodeN("/Res/icons/ani/progressing06.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap8 = pImage->DecodeN("/Res/icons/ani/progressing07.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);

		// Creates AnimationFrame.
		AnimationFrame *pAniFrame1 = new AnimationFrame(*pBitmap1, 100);
		AnimationFrame *pAniFrame2 = new AnimationFrame(*pBitmap2, 100);
		AnimationFrame *pAniFrame3 = new AnimationFrame(*pBitmap3, 100);
		AnimationFrame *pAniFrame4 = new AnimationFrame(*pBitmap4, 100);
		AnimationFrame *pAniFrame5 = new AnimationFrame(*pBitmap5, 100);
		AnimationFrame *pAniFrame6 = new AnimationFrame(*pBitmap6, 100);
		AnimationFrame *pAniFrame7 = new AnimationFrame(*pBitmap7, 100);
		AnimationFrame *pAniFrame8 = new AnimationFrame(*pBitmap8, 100);


		__pAnimationFrameList = new ArrayList();
		__pAnimationFrameList->Construct();
		__pAnimationFrameList->Add(*pAniFrame1);
		__pAnimationFrameList->Add(*pAniFrame2);
		__pAnimationFrameList->Add(*pAniFrame3);
		__pAnimationFrameList->Add(*pAniFrame4);
		__pAnimationFrameList->Add(*pAniFrame5);
		__pAnimationFrameList->Add(*pAniFrame6);
		__pAnimationFrameList->Add(*pAniFrame7);
		__pAnimationFrameList->Add(*pAniFrame8);

}

void ZLbadaProgressDialog::OnAnimationStopped(const Control& source)
{
	AppLog("OnAnimationStopped");
	if(__pAnimation)
		__pAnimation->Play();
}
bool ZLbadaProgressDialog::OnStart(void){
	AppLog("ZLbadaProgressDialog::OnStart()");
	return true;
}

//bool ZLbadaProgressDialog::OnStop(void){
//	AppLog("ZLbadaProgressDialog::OnStart()");
//}

void ZLbadaProgressDialog::run(ZLRunnable &runnable) {
	AppLog("ZLbadaProgressDialog run");
	result r;
	//myRunnable = &runnable;
	Osp::Ui::Controls::Popup* __pPopup = new Osp::Ui::Controls::Popup();
	if (__pPopup) {
			r = __pPopup->Construct(true, Osp::Graphics::Dimension(400,250));
			AppLog("r = %d",r);
			r =__pPopup->SetTitleText(L"Please wait...");
			AppLog("r = %d",r);
			//ConstructAnimationFrameList();
			//Rectangle popupFormArea = __pPopup->GetClientAreaBounds();
			//__pAnimation = new Animation();
			//__pAnimation->Construct(Rectangle(popupFormArea.width/2-60, 20, 120, 120), *__pAnimationFrameList);
			//__pAnimation->AddAnimationEventListener(*this);
			//__pPopup->AddControl(*__pAnimation);
			r = __pPopup->SetShowState(true);
			AppLog("r = %d",r);
			r = __pPopup->Show();
			AppLog("r = %d",r);
			if (r==0)	{
					//	 Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
					//	  Start();
			 	 	 //	 __pAnimation->Play();
						}
			else {
				delete __pPopup;
				__pPopup = null;
				AppLog("delete __pPopup");
			}
	}
	/*if (r == E_SUCCESS) {
		__pThread = new Osp::Base::Runtime::Thread();
			__pThread->Construct(*this);
			result r = __pThread->Start();
	}
	else
		*/
		runnable.run();
		AppLog("ZLbadaProgressDialog f");
	if (__pPopup)  {
					//if (r==0) Stop();
					__pPopup->SetShowState(false);
					delete __pPopup;
					AppLog("delete __pPopup");
	}

}
/*
void ZLbadaProgressDialog::run(TreeActionListener* listener) {
                if (!listener) {
                    return;
                }
                if (listener->isFinished()) {
                    qDebug() << Q_FUNC_INFO << "is finished yet!";
                    return;
                }
                ZLQtDialogManager& dialogManager = static_cast<ZLQtDialogManager&>(ZLQtDialogManager::Instance());
                myDialog = new ZLQtWaitDialog(messageText(),dialogManager.getParentWidget());

                QObject::connect(listener, SIGNAL(finishedHappened(std::string)), myDialog, SLOT(close()));
                myDialog->exec();

                delete myDialog;
                myDialog = 0;
}
*/

void ZLbadaProgressDialog::setMessage(const std::string &message) {
	AppLog("ZLbadaProgressDialog setMessage %s", message.c_str());
	/*
		if (myDialog == 0) {
				return;
		}

		myDialog->myLabel->setText(::qtString(message));

		myDialog->myLayout->invalidate();
		myDialog->repaint();
		qApp->processEvents();
		*/
}


/*

ZLQtWaitDialog::ZLQtWaitDialog(const std::string &message, QWidget* parent) : QDialog(parent) {

	   // for what reasons we use processEvents here?
	   // qApp->processEvents();

                myLayout = new QVBoxLayout;

                QHBoxLayout* layout = new QHBoxLayout;

                myLabel = new QLabel(oneWordWrapped(::qtString(message)));
                myLabel->setFont(MenuItemParameters::getWaitMessageFont());
                //myLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		myLabel->setWordWrap(true);

                myLoadingIcon = new LoadingIcon;
                myLoadingIcon->start();

//		myProgressBar = new QProgressBar;
//		myProgressBar->setRange(0,0);
//                myProgressBar->setFixedWidth(qApp->desktop()->geometry().width()*COEF_PROGRESS_BAR_WIDTH);

                layout->setAlignment(Qt::AlignHCenter);
                layout->addWidget(myLoadingIcon);
                layout->addWidget(myLabel);
                //myLayout->addWidget(myProgressBar);
                layout->setSpacing(10);

                myLayout->addLayout(layout);
                myLayout->addSpacing(myLoadingIcon->size().height()); // to be on bottom of center line

                myLayout->setAlignment(Qt::AlignVCenter);

		this->setLayout(myLayout);

		//setWindowFlags(windowFlags() | Qt::WindowSoftkeysVisibleHint);

#ifdef __SYMBIAN__
        //setWindowFlags(windowFlags() | Qt::WindowSoftkeysVisibleHint);
        setWindowState(Qt::WindowFullScreen);
#else
        setFixedSize(360,300);
#endif

//        qApp->processEvents();
//        usleep(5000);
//        qApp->processEvents();


}

 void ZLQtWaitDialog::paintEvent(QPaintEvent *event) {
        //myLayout->invalidate();
	QDialog::paintEvent(event);
 }

 void ZLQtWaitDialog::resizeEvent(QResizeEvent *event) {
    //myProgressBar->setFixedWidth(event->size().width()*COEF_PROGRESS_BAR_WIDTH);
    QDialog::resizeEvent(event);
 }

ZLQtWaitDialog::~ZLQtWaitDialog() {
}

QString ZLQtWaitDialog::oneWordWrapped(QString string) {
    const static QString SPACE = " ";
    const static QString WRAP = "\n";
    QString result = string.trimmed();

    int index = 0;
    while ((index = result.indexOf(SPACE + SPACE)) != -1) {
        result.replace(SPACE + SPACE, SPACE);
    }

    result.replace(SPACE, WRAP);
    return result;
}
*/
