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

#include "ZLbadaTime.h"

using namespace Osp::Base;
using namespace Osp::Base::Runtime;



ZLbadaTimeManager::ZLbadaTimeManager(): ZLUnixTimeManager() {
	AppLog("ZLbadaTimeManager::ZLbadaTimeManager()" );
}

void ZLbadaTimeManager::OnTimerExpired(Timer& timer){
	AppLog("OnTimerExpired");
	shared_ptr<ZLRunnable> task = myTasks.find(&timer)->second;
	task->run();
	//TODO timer.Start(1000);
}

void ZLbadaTimeManager::addTask(shared_ptr<ZLRunnable> task, int interval) {
	AppLog("ZLbadaTimeManager::addTask interval=%d",interval );
	removeTask(task);
	if ((interval > 0) && !task.isNull()) {
		Timer* _pTimer = new Timer;
		_pTimer->Construct(*this);
		//int id = startTimer(interval);
		myTimers[task] = _pTimer;
		myTasks[_pTimer] = task;
		_pTimer->Start(interval);

	}

}

void ZLbadaTimeManager::removeTaskInternal(shared_ptr<ZLRunnable> task) {
	AppLog("ZLbadaTimeManager::removeTaskInternal" );
	std::map<shared_ptr<ZLRunnable>,Timer*>::iterator it = myTimers.find(task);
	if (it != myTimers.end()) {
		myTasks.erase(myTasks.find(it->second));
		myTimers.erase(it);
		delete it->second;
	}

}

//void ZLbadaTimeManager::timerEvent(QTimerEvent *event) {
//	AppLog("ZLbadaTimeManager::timerEvent" );
	//myTasks[event->timerId()]->run();
//}
