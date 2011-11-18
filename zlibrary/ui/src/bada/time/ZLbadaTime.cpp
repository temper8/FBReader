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

ZLbadaTimeManager::ZLbadaTimeManager(): ZLUnixTimeManager() {
	AppLog("ZLbadaTimeManager::ZLbadaTimeManager()" );
}

void ZLbadaTimeManager::addTask(shared_ptr<ZLRunnable> task, int interval) {
	AppLog("ZLbadaTimeManager::addTask interval=%d",interval );
/*	removeTask(task);
	if ((interval > 0) && !task.isNull()) {
		int id = startTimer(interval);
		myTimers[task] = id;
		myTasks[id] = task;
	}
	*/
}

void ZLbadaTimeManager::removeTaskInternal(shared_ptr<ZLRunnable> task) {
	AppLog("ZLbadaTimeManager::removeTaskInternal" );
	/*
	std::map<shared_ptr<ZLRunnable>,int>::iterator it = myTimers.find(task);
	if (it != myTimers.end()) {
		killTimer(it->second);
		myTasks.erase(myTasks.find(it->second));
		myTimers.erase(it);
	}
	*/
}

//void ZLbadaTimeManager::timerEvent(QTimerEvent *event) {
//	AppLog("ZLbadaTimeManager::timerEvent" );
	//myTasks[event->timerId()]->run();
//}
