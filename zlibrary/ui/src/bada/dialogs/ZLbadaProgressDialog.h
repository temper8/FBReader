#ifndef __ZLBADAPROGRESSDIALOG_H__
#define __ZLBADAPROGRESSDIALOG_H__



#include <ZLProgressDialog.h>
#include <ZLRunnable.h>

#include <FBase.h>
#include <FUi.h>


//#include "ZLQtTreeDialog.h"
/*
class LoadingIcon : public QLabel {
    Q_OBJECT
public:
    LoadingIcon(QWidget* parent=0);
    void moveToPosition(QSize size);
public slots:
    void start();
    void finish();
private slots:
    void rotate();
private:
    int myAngle;
    QPixmap myPixmap;
    QTimer* myTimer;
};

class ZLQtWaitDialog : public QDialog {

public:
                ZLQtWaitDialog(const std::string &message, QWidget* parent=0);
		~ZLQtWaitDialog();
		void paintEvent(QPaintEvent *event);
                void resizeEvent(QResizeEvent *event);

private:
                static QString oneWordWrapped(QString string);

private:
                QVBoxLayout* myLayout;
		QLabel* myLabel;
                LoadingIcon* myLoadingIcon;
                //QProgressBar* myProgressBar;

friend class ZLbadaProgressDialog;
};

*/

//using namespace  Osp::Base::Runtime;
class AnimationThread:  public Osp::Base::Runtime::Thread,
						public Osp::Ui::IAnimationEventListener {
public:
	AnimationThread(void);
	~AnimationThread(void);
	result Construct(Osp::Ui::Controls::Animation* 		__pAnimation);
	result Construct(Osp::Base::Collection::ArrayList* 	__pAnimationFrameList);
	bool OnStart(void);
	Osp::Ui::Controls::Animation* 		myAnimation;
	Osp::Ui::Controls::Popup*			myProgressPopup;
 	Osp::Base::Runtime::Monitor*        myMonitor;
private:
//	void ConstructAnimationFrameList(void);
	Osp::Base::Collection::ArrayList* 	myAnimationFrameList;
	virtual void OnAnimationStopped(const Osp::Ui::Control& source);

};
/*
class TimerThread: public Osp::Base::Runtime::ITimerEventListener,
				  // public Osp::Base::Runtime::IRunnable,
				   public Osp::Ui::IAnimationEventListener,
				   public Osp::Base::Runtime::Thread {
public:
	TimerThread(void);
	~TimerThread(void);
	result Construct(Osp::Ui::Controls::Popup*	pProgressPopup);

public:

	bool OnStart(void);
	void GopStop(void);

public:
	void OnTimerExpired(Osp::Base::Runtime::Timer& timer);

private:
	Osp::Ui::Controls::Popup*	myProgressPopup;
	int count;
	Osp::Base::Runtime::Timer* __pTimer;
	void ConstructAnimationFrameList(void);
	Osp::Ui::Controls::Animation* 		__pAnimation;
	 Osp::Base::Collection::ArrayList* 	__pAnimationFrameList;
	virtual void OnAnimationStopped(const Osp::Ui::Control& source);
	//Osp::Base::Object* Run(void);
};
*/
class ZLbadaProgressDialog : public ZLProgressDialog,

							// public Osp::Base::Runtime::Thread,
							// public Osp::Base::Runtime::ITimerEventListener
							public Osp::Base::Runtime::IRunnable
							 {
public:
		ZLbadaProgressDialog(const ZLResourceKey &key);

        void run(ZLRunnable &runnable);
               // void run(TreeActionListener* listener); // for wait dialog while loading book

		void setMessage(const std::string &message);

private:


		ZLRunnable* myRunnable;

		void ConstructAnimationFrameList(void);
		static Osp::Base::Collection::ArrayList* 	__pAnimationFrameList;
	 	Osp::Ui::Controls::Popup*			__pProgressPopup;
	    //Osp::Base::Runtime::Thread* 		__pThread;
	 	Osp::Base::Runtime::Monitor*        __pMonitor;
	 //   TimerThread*  __pTimerThread;
		//Osp::Ui::Controls::Animation* 		__pAnimation;
		//Osp::Base::Collection::ArrayList* 	__pAnimationFrameList;
	//    Osp::Base::Runtime::Timer* __pTimer;
	//    void OnTimerExpired(Osp::Base::Runtime::Timer& timer);
	//	bool OnStart(void);
		void OnStop(void);
		Osp::Base::Object* Run(void);
};

/*
class ThreadRunnable : public QThread  {
 public:
		ThreadRunnable(ZLRunnable* runnable): QThread(0), myRunnable(runnable) { }
		void run() {
			myRunnable->run();
		}
private:
	ZLRunnable* myRunnable;

};

*/

#endif // __ZLBADAPROGRESSDIALOG_H__
