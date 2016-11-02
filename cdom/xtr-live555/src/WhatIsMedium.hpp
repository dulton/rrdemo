/** \file
 *  \brief Medium 是什么鬼.
 *  \sa <http://live555.com/liveMedia/doxygen/html/classMedium.html>
 *  \author zhengrr
 *  \date 2016-10-24 – 11-1
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_WHATISMEDIUM_HPP
#define _RRDEMOCDOMLIVE555_WHATISMEDIUM_HPP

#include <live555/Hashtable.hh>
#include <live555/UsageEnvironment.hh>

#define mediumNameMaxLen 30

namespace rrdemo {
namespace cdom {
namespace live555 {

class Medium {
public:
    static Boolean lookupByName(UsageEnvironment& env,
                                char const* mediumName,
                                Medium*& resultMedium);
    static void close(UsageEnvironment& env, char const* mediumName);
    static void close(Medium* medium);

    UsageEnvironment& envir() const { return fEnviron; }

    char const* name() const { return fMediumName; }

    virtual Boolean isSource() const;
    virtual Boolean isSink() const;
    virtual Boolean isRTCPInstance() const;
    virtual Boolean isRTSPClient() const;
    virtual Boolean isRTSPServer() const;
    virtual Boolean isMediaSession() const;
    virtual Boolean isServerMediaSession() const;

protected:
    friend class MediaLookupTable;
    explicit Medium(UsageEnvironment& env);
    virtual ~Medium();

    TaskToken& nextTask() {
        return fNextTask;
    }

private:
    UsageEnvironment& fEnviron;
    char fMediumName[mediumNameMaxLen];
    TaskToken fNextTask;
};

class MediaLookupTable {
public:
    static MediaLookupTable* ourMedia(UsageEnvironment& env);
    HashTable const& getTable() const { return *fTable; }

protected:
    explicit MediaLookupTable(UsageEnvironment& env);
    virtual ~MediaLookupTable();

private:
    friend class Medium;

    Medium* lookup(char const* name) const;

    void addNew(Medium* medium, char* mediumName) const;
    void remove(char const* name) const;

    void generateNewName(char* mediumName, unsigned maxLen);

    UsageEnvironment& fEnv;
    HashTable* fTable;
    unsigned fNameGenerator;
};


class _Tables {
public:
    static _Tables* getOurTables
        (UsageEnvironment& env, Boolean createIfNotPresent = True);
    void reclaimIfPossible() const;

    MediaLookupTable* mediaTable;
    void* socketTable;

protected:
    explicit _Tables(UsageEnvironment& env);
    virtual ~_Tables();

private:
    UsageEnvironment& fEnv;
};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_WHATISMEDIUM_HPP
