/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef  TASK_SCHEDULER_H
#define  TASK_SCHEDULER_H

#include "Common.h"
#include "Timer.h"
#include "LockedQueue.h"
#include <memory>

class ThreadPool;
class TaskBase;
class CallbackTask;

//! Class for realtime task scheduling
class TaskMgr
{
public:

    ~TaskMgr();

    //! Not singleton.
    //! Just global accessor for main thread scheduler.
    static TaskMgr* Default();

    //! Set time (in milliseconds) for executing task cycle.
    //! No garantees that it will be max time of Update() call.
    void SetMaxTickTime(uint32 ms)
    {
        _max = std::chrono::milliseconds(ms);
    }

    //! Executing task cycle.
    //! Update state of current tasks.
    //! Objects of executed tasks will be deleted.
    //! If the current work time will be longer than the _max,
    //! the cycle will be interrupted and the remaining tasks will be completed no earlier than next Update() call.
    //! Need to call this method in context which associated with scheduler.
    void Update();

    //! Add task to queue.
    //! Thread-safe.
    //! Guarantees that task will be executed not earlier than next update.
    void ScheduleInvocation(std::function<void()> func);
    void ScheduleInvocation(TaskBase* task);

    static void Async(std::function<void()> func);

    static void Stop();

private:
    typedef std::shared_ptr<TaskBase> TaskObject;
    LockedQueue<TaskObject> _queue;
    std::list<TaskObject> _tasks;
    std::chrono::milliseconds _max = std::chrono::milliseconds(25);
    static std::unique_ptr<ThreadPool> _pool;
};

//! Object linked to task.
//! Provides safe interaction with task.
class TaskToken
{
public:
    //! Is task canceled.
    bool IsCanceled() const
    {
        return _canceled;
    }

    //! Cancel the task.
    //! It means that continuation of task will not execute.
    void Cancel()
    {
        _canceled = true;
    }

    //! If token expired - task allready executed and token can be removed.
    bool IsExpired() const
    {
        return _expired;
    }

    //! Delink from task.
    void Delink()
    {
        _expired = true;
    }

private:
    bool _canceled = false;
    bool _expired = false;
};

typedef std::shared_ptr<TaskToken> CancelationToken;

//! Base class for objects whose actions can be scheduled.
class Schedulable
{
public:
    virtual ~Schedulable()
    {
        CancelAll();
    }

    //! Drops all active task
    void CancelAll()
    {
        for (auto&& tok : _tokens)
            tok->Cancel();
        _tokens.clear();
    }

    //! Adds a new action for a tracking and a possible safe cancelation.
    void NewAction(TaskBase* task);

private:
    std::list<CancelationToken> _tokens;
};

#endif //TASK_SCHEDULER_H
