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

#include "MapUpdater.h"
#include "Map.h"
#include "MapInstanced.h"

thread_local Map* CurrentMap = nullptr;

class UpdateRequest
{
public:
    UpdateRequest() = default;
    virtual ~UpdateRequest() = default;

    virtual int call() = 0;
};


class MapUpdateRequest : public UpdateRequest
{
    private:

        Map& m_map;
        MapUpdater& m_updater;
        uint32 m_diff;

    public:

        MapUpdateRequest(Map& m, MapUpdater& u, uint32 d)
            : m_map(m), m_updater(u), m_diff(d)
        {
        }

        virtual int call()
        {
            CurrentMap = &m_map;
            m_map.Update (m_diff);
            CurrentMap = nullptr;
            m_updater.update_finished();
            return 0;
        }
};

MapUpdater::MapUpdater(): pending_requests(0)
{
}


MapUpdater::~MapUpdater()
{
    deactivate();
}

void MapUpdater::activate(size_t num_threads)
{
    for (size_t i = 0; i < num_threads; ++i)
    {
        _workerThreads.push_back(std::thread(&MapUpdater::WorkerThread, this));
    }    
}

void MapUpdater::deactivate()
{
    _cancelationToken = true;

    wait();

    _queue.Cancel();

    for (auto& thread : _workerThreads)
    {
        thread.join();
    }

}

int MapUpdater::wait()
{
    std::unique_lock<std::mutex> guard(m_mutex);

    while (pending_requests > 0)
        m_condition.wait(guard);

    guard.unlock();
    return 0;
}

int MapUpdater::schedule_update(Map& map, uint32 diff)
{

    std::lock_guard<std::mutex> guard(m_mutex);

    ++pending_requests;

    _queue.Push(new MapUpdateRequest(map, *this, diff));

    return 0;
}

bool MapUpdater::activated()
{
    return _workerThreads.size() > 0;
}

void MapUpdater::update_finished()
{

    std::lock_guard<std::mutex> lock(m_mutex);

    --pending_requests;

    m_condition.notify_all();

}

void MapUpdater::WorkerThread()
{
    while (1)
    {
        UpdateRequest* request = nullptr;

        _queue.WaitAndPop(request);
        if (_cancelationToken)
            return;

        request->call();

        delete request;
    }
}
