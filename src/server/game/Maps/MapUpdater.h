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

#ifndef SF_MAP_UPDATER_H_INCLUDED
#define SF_MAP_UPDATER_H_INCLUDED

#include <condition_variable>
#include <mutex>
#include <thread>

#include "ProducerConsumerQueue.h"

class Map;
class UpdateRequest;

extern thread_local Map* CurrentMap;

class MapUpdater
{
    public:

        MapUpdater();
        virtual ~MapUpdater();

        friend class MapUpdateRequest;

        int schedule_update(Map& map, uint32 diff);

        int wait();

        void activate(size_t num_threads);

        void deactivate();

        bool activated();

    private:
        void WorkerThread();

        std::vector<std::thread> _workerThreads;
        std::atomic<bool> _cancelationToken;        
        ProducerConsumerQueue<UpdateRequest*> _queue;
        std::mutex m_mutex;
        std::condition_variable m_condition;
        size_t pending_requests;

        void update_finished();
};

#endif //_MAP_UPDATER_H_INCLUDED
