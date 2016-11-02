/** \copyright The MIT License */
#include "WhatIsMedium.hpp"

#include <CStdio>

#include <live555/HashTable.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

Medium::Medium(UsageEnvironment& env)
    : fEnviron(env), fNextTask(nullptr) {
    MediaLookupTable::ourMedia(env)->generateNewName(fMediumName, mediumNameMaxLen);
    env.setResultMsg(fMediumName);

    MediaLookupTable::ourMedia(env)->addNew(this, fMediumName);
}

Medium::~Medium() {
    fEnviron.taskScheduler().unscheduleDelayedTask(fNextTask);
}

Boolean Medium::lookupByName(UsageEnvironment& env, char const* mediumName,
                             Medium*& resultMedium) {
    resultMedium = MediaLookupTable::ourMedia(env)->lookup(mediumName);
    if (resultMedium == nullptr) {
        env.setResultMsg("Medium ", mediumName, " does not exist");
        return False;
    }

    return True;
}

void Medium::close(UsageEnvironment& env, char const* name) {
    MediaLookupTable::ourMedia(env)->remove(name);
}

void Medium::close(Medium* medium) {
    if (medium == nullptr) return;

    close(medium->envir(), medium->name());
}

Boolean Medium::isSource() const {
    return False;
}

Boolean Medium::isSink() const {
    return False;
}

Boolean Medium::isRTCPInstance() const {
    return False;
}

Boolean Medium::isRTSPClient() const {
    return False;
}

Boolean Medium::isRTSPServer() const {
    return False;
}

Boolean Medium::isMediaSession() const {
    return False;
}

Boolean Medium::isServerMediaSession() const {
    return False;
}

_Tables* _Tables::getOurTables(UsageEnvironment& env, Boolean createIfNotPresent) {
    if (env.liveMediaPriv == nullptr && createIfNotPresent) {
        env.liveMediaPriv = new _Tables(env);
    }
    return static_cast<_Tables*>(env.liveMediaPriv);
}

void _Tables::reclaimIfPossible() const {
    if (mediaTable == nullptr && socketTable == nullptr) {
        fEnv.liveMediaPriv = nullptr;
        delete this;
    }
}

_Tables::_Tables(UsageEnvironment& env)
    : mediaTable(nullptr), socketTable(nullptr), fEnv(env) {}

_Tables::~_Tables() {}


MediaLookupTable* MediaLookupTable::ourMedia(UsageEnvironment& env) {
    auto ourTables = _Tables::getOurTables(env);
    if (ourTables->mediaTable == nullptr) {
        ourTables->mediaTable = new MediaLookupTable(env);
    }
    return ourTables->mediaTable;
}

Medium* MediaLookupTable::lookup(char const* name) const {
    return static_cast<Medium*>(fTable->Lookup(name));
}

void MediaLookupTable::addNew(Medium* medium, char* mediumName) const {
    fTable->Add(mediumName, static_cast<void*>(medium));
}

void MediaLookupTable::remove(char const* name) const {
    auto medium = lookup(name);
    if (medium != nullptr) {
        fTable->Remove(name);
        if (fTable->IsEmpty()) {
            // We can also delete ourselves (to reclaim space):
            _Tables* ourTables = _Tables::getOurTables(fEnv);
            delete this;
            ourTables->mediaTable = nullptr;
            ourTables->reclaimIfPossible();
        }

        delete medium;
    }
}

void MediaLookupTable::generateNewName(char* mediumName, unsigned) {
    sprintf(mediumName, "liveMedia%d", fNameGenerator++);
}

MediaLookupTable::MediaLookupTable(UsageEnvironment& env)
    : fEnv(env), fTable(HashTable::create(STRING_HASH_KEYS)), fNameGenerator(0) {}

MediaLookupTable::~MediaLookupTable() {
    delete fTable;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
