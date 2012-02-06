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

class ZLbadaProgressDialog : public ZLProgressDialog,
							 public Osp::Base::Runtime::IRunnable
							 {
public:
		ZLbadaProgressDialog(const ZLResourceKey &key);

                void run(ZLRunnable &runnable);
               // void run(TreeActionListener* listener); // for wait dialog while loading book

		void setMessage(const std::string &message);

private:
		ZLRunnable* myRunnable;
		Osp::Base::Object* Run(void);
		//ZLQtWaitDialog* myDialog;
	 	//Osp::Ui::Controls::Popup*			__pProgressPopup;
	    Osp::Base::Runtime::Thread* 		__pThread;
		//Osp::Ui::Controls::Animation* 		__pAnimation;
		//Osp::Base::Collection::ArrayList* 	__pAnimationFrameList;

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
