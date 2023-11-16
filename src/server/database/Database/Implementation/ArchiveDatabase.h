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

#ifndef _ARCHIVEDATABASE_H
#define _ARCHIVEDATABASE_H

#include "MySQLConnection.h"

enum ArchiveDatabaseStatements : uint32
{
    /*  Naming standard for defines:
        {DB}_{SEL/INS/UPD/DEL/REP}_{Summary of data changed}
        When updating more than one field, consider looking at the calling function
        name for a suiting suffix.
    */

    ARCH_INS_CURRENCY_TRANSACTIONS,


    MAX_ARCHIVEDATABASE_STATEMENTS
};

class TC_DATABASE_API ArchiveDatabaseConnection : public MySQLConnection
{
public:
    typedef ArchiveDatabaseStatements Statements;

    //- Constructors for sync and async connections
    ArchiveDatabaseConnection(MySQLConnectionInfo& connInfo);
    ArchiveDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo);
    ~ArchiveDatabaseConnection();

    //- Loads database type specific prepared statements
    void DoPrepareStatements() override;
};

#endif
