/*
 * HttpTread.h
 *
 *  Created on: 15.01.2012
 *      Author: Alex
 */

#ifndef HTTPTREAD_H_
#define HTTPTREAD_H_

#include <FApp.h>
#include <FUi.h>
#include <FNet.h>
#include <FSystem.h>
#include <FBase.h>
#include <ZLNetworkRequest.h>


class HttpMonitor : public Osp::Base::Runtime::Monitor
{
public:

	HttpMonitor();
	~HttpMonitor();
	int count;
	 void  AddRef(void);
	 void  DelRef(void);

private:
	 Osp::Base::Runtime::Mutex* __pMutex;

};

class HttpThread :	public Osp::Base::Runtime::Thread,
					public Osp::Net::Http::IHttpTransactionEventListener,
					public Osp::Base::Runtime::ITimerEventListener
{
public:
	HttpThread(HttpMonitor* pMonitor, ZLNetworkRequest &request);
	~HttpThread();
	HttpMonitor* myMonitor;
	ZLNetworkRequest* myRequest;
	// Initializes the instance of HttpThread
	result Construct();
	Osp::Net::Http::HttpSession*	__pSession;

	// Called before the Run() method is called.
	// Can decide whether it can be run or not by returning true or false.
	// If this method returns false, the thread is terminated immediately.
	bool OnStart(void);
	// Called after the Run() method is called.
	void OnStop(void);
	// Called when the timer expires.
//	void OnTimerExpired(Timer& timer);

public:
	// Timer time out for the expire of timer.
	static const int	TIMER_TIMEOUT = 15000;

	void OnUserEventReceivedN (RequestId requestId, Osp::Base::Collection::IList *pArgs);

private:
	///////////////////////////////////////////////////////////
	// IHttpTransactionEventListener
	///////////////////////////////////////////////////////////
	void OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	void OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, result r);
	void OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	void OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs);
	void OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction);
	void OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, Osp::Base::String* pCert);
	void OnTimerExpired(Osp::Base::Runtime::Timer& timer);
	Osp::Base::Runtime::Timer*		__pTimer;
};



#endif /* HTTPTREAD_H_ */
