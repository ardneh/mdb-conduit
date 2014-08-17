// AUTO-GENERATED FILE DO NOT EDIT
// See src/mongo/db/auth/generate_action_types.py
/*    Copyright 2012 10gen Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <iosfwd>
#include <map>
#include <string>

#include "mongo/base/status.h"
#include "mongo/platform/cstdint.h"

namespace mongo {

    struct ActionType {
    public:

        explicit ActionType(uint32_t identifier) : _identifier(identifier) {};
        ActionType() {};

        uint32_t getIdentifier() const {
            return _identifier;
        }

        bool operator==(const ActionType& rhs) const;

        std::string toString() const;

        // Takes the string representation of a single action type and returns the corresponding
        // ActionType enum.
        static Status parseActionFromString(const std::string& actionString, ActionType* result);

        // Takes an ActionType and returns the string representation
        static std::string actionToString(const ActionType& action);

        static const ActionType addShard;
        static const ActionType anyAction;
        static const ActionType appendOplogNote;
        static const ActionType applicationMessage;
        static const ActionType auditLogRotate;
        static const ActionType authCheck;
        static const ActionType authSchemaUpgrade;
        static const ActionType authenticate;
        static const ActionType changeCustomData;
        static const ActionType changePassword;
        static const ActionType changeOwnPassword;
        static const ActionType changeOwnCustomData;
        static const ActionType cleanupOrphaned;
        static const ActionType closeAllDatabases;
        static const ActionType collMod;
        static const ActionType collStats;
        static const ActionType compact;
        static const ActionType connPoolStats;
        static const ActionType connPoolSync;
        static const ActionType convertToCapped;
        static const ActionType cpuProfiler;
        static const ActionType createCollection;
        static const ActionType createDatabase;
        static const ActionType createIndex;
        static const ActionType createRole;
        static const ActionType createUser;
        static const ActionType cursorInfo;
        static const ActionType dbHash;
        static const ActionType dbStats;
        static const ActionType diagLogging;
        static const ActionType dropAllRolesFromDatabase;
        static const ActionType dropAllUsersFromDatabase;
        static const ActionType dropCollection;
        static const ActionType dropDatabase;
        static const ActionType dropIndex;
        static const ActionType dropRole;
        static const ActionType dropUser;
        static const ActionType emptycapped;
        static const ActionType enableProfiler;
        static const ActionType enableSharding;
        static const ActionType find;
        static const ActionType flushRouterConfig;
        static const ActionType fsync;
        static const ActionType getCmdLineOpts;
        static const ActionType getLog;
        static const ActionType getParameter;
        static const ActionType getShardMap;
        static const ActionType getShardVersion;
        static const ActionType grantRole;
        static const ActionType grantPrivilegesToRole;
        static const ActionType grantRolesToRole;
        static const ActionType grantRolesToUser;
        static const ActionType hostInfo;
        static const ActionType impersonate;
        static const ActionType indexStats;
        static const ActionType inprog;
        static const ActionType insert;
        static const ActionType internal;
        static const ActionType invalidateUserCache;
        static const ActionType killCursors;
        static const ActionType killop;
        static const ActionType listDatabases;
        static const ActionType listShards;
        static const ActionType logRotate;
        static const ActionType moveChunk;
        static const ActionType netstat;
        static const ActionType planCacheIndexFilter;
        static const ActionType planCacheRead;
        static const ActionType planCacheWrite;
        static const ActionType reIndex;
        static const ActionType remove;
        static const ActionType removeShard;
        static const ActionType renameCollection;
        static const ActionType renameCollectionSameDB;
        static const ActionType repairDatabase;
        static const ActionType replSetConfigure;
        static const ActionType replSetGetStatus;
        static const ActionType replSetHeartbeat;
        static const ActionType replSetReconfig;
        static const ActionType replSetStateChange;
        static const ActionType resync;
        static const ActionType revokeRole;
        static const ActionType revokePrivilegesFromRole;
        static const ActionType revokeRolesFromRole;
        static const ActionType revokeRolesFromUser;
        static const ActionType serverStatus;
        static const ActionType setParameter;
        static const ActionType shardCollection;
        static const ActionType shardingState;
        static const ActionType shutdown;
        static const ActionType splitChunk;
        static const ActionType splitVector;
        static const ActionType storageDetails;
        static const ActionType top;
        static const ActionType touch;
        static const ActionType unlock;
        static const ActionType update;
        static const ActionType updateRole;
        static const ActionType updateUser;
        static const ActionType validate;
        static const ActionType viewRole;
        static const ActionType viewUser;

        enum ActionTypeIdentifier {
            addShardValue,
            anyActionValue,
            appendOplogNoteValue,
            applicationMessageValue,
            auditLogRotateValue,
            authCheckValue,
            authSchemaUpgradeValue,
            authenticateValue,
            changeCustomDataValue,
            changePasswordValue,
            changeOwnPasswordValue,
            changeOwnCustomDataValue,
            cleanupOrphanedValue,
            closeAllDatabasesValue,
            collModValue,
            collStatsValue,
            compactValue,
            connPoolStatsValue,
            connPoolSyncValue,
            convertToCappedValue,
            cpuProfilerValue,
            createCollectionValue,
            createDatabaseValue,
            createIndexValue,
            createRoleValue,
            createUserValue,
            cursorInfoValue,
            dbHashValue,
            dbStatsValue,
            diagLoggingValue,
            dropAllRolesFromDatabaseValue,
            dropAllUsersFromDatabaseValue,
            dropCollectionValue,
            dropDatabaseValue,
            dropIndexValue,
            dropRoleValue,
            dropUserValue,
            emptycappedValue,
            enableProfilerValue,
            enableShardingValue,
            findValue,
            flushRouterConfigValue,
            fsyncValue,
            getCmdLineOptsValue,
            getLogValue,
            getParameterValue,
            getShardMapValue,
            getShardVersionValue,
            grantRoleValue,
            grantPrivilegesToRoleValue,
            grantRolesToRoleValue,
            grantRolesToUserValue,
            hostInfoValue,
            impersonateValue,
            indexStatsValue,
            inprogValue,
            insertValue,
            internalValue,
            invalidateUserCacheValue,
            killCursorsValue,
            killopValue,
            listDatabasesValue,
            listShardsValue,
            logRotateValue,
            moveChunkValue,
            netstatValue,
            planCacheIndexFilterValue,
            planCacheReadValue,
            planCacheWriteValue,
            reIndexValue,
            removeValue,
            removeShardValue,
            renameCollectionValue,
            renameCollectionSameDBValue,
            repairDatabaseValue,
            replSetConfigureValue,
            replSetGetStatusValue,
            replSetHeartbeatValue,
            replSetReconfigValue,
            replSetStateChangeValue,
            resyncValue,
            revokeRoleValue,
            revokePrivilegesFromRoleValue,
            revokeRolesFromRoleValue,
            revokeRolesFromUserValue,
            serverStatusValue,
            setParameterValue,
            shardCollectionValue,
            shardingStateValue,
            shutdownValue,
            splitChunkValue,
            splitVectorValue,
            storageDetailsValue,
            topValue,
            touchValue,
            unlockValue,
            updateValue,
            updateRoleValue,
            updateUserValue,
            validateValue,
            viewRoleValue,
            viewUserValue,

            actionTypeEndValue, // Should always be last in this enum
        };

        static const int NUM_ACTION_TYPES = actionTypeEndValue;

    private:

        uint32_t _identifier; // unique identifier for this action.
    };

    // String stream operator for ActionType
    std::ostream& operator<<(std::ostream& os, const ActionType& at);

} // namespace mongo
