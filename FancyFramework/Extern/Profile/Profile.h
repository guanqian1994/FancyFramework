/* Copyright (C) Zichang Bu, 2013. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Zichang Bu, 2013"
 * 
 *           file : Profile.h
 *  Creation date : August 29, 2013
 *          email : buzichang@vip.qq.com
 */

#ifndef PROFILE_H_
#define PROFILE_H_

#include <cassert>
#include <string>
#include <vector>
#include <map>

#define PROFILE_USE_WCHAR
#define BUFFERSIZE 1024
#define PROFILE(name) ProfileItem profileItem(name);

typedef double PNumber;

#ifdef PROFILE_USE_WCHAR
typedef wchar_t PChar;
typedef std::wstring PStr;
#else
typedef char PChar;
typedef std::string PStr;
#endif

struct ProfileSampleHistory {
    PNumber ave;
    PNumber min;
    PNumber max;
    PNumber frameTime;
    size_t frameAccumulator;
    size_t sampleAccumulator;
};

struct ProfileSample {
    ProfileSample()
        : valid(false), pHistory(NULL) {}
    bool valid;
    PStr name;
    size_t accumulator;
    PNumber timeConsuming;
    int parent;
    int parentsNum;
    int self;
    ProfileSampleHistory *pHistory;
};

class ProfileItem;
class Profile {    
    friend class ProfileItem;
public:
    Profile();
    ~Profile();
    void Begin();
    void End();
    PNumber GetTime();
    // reset all sample history data
    void Reset()                            { m_resetFlag = true;     }
    void SetDelay(PNumber t)                { m_delay = t;            }
    PChar *GetReportStr() const             { return m_pBuffer;       }
    void SetProfileLevel(size_t level)      { m_profileLevel = level; } 
    size_t GetProfileLevel() const          { return m_profileLevel;  }
    static Profile &GetSingleton(void)      { return *m_pSingletonPtr;}
    static Profile *GetSingletonPtr(void)   { return m_pSingletonPtr; }
private:
    ProfileSample *CheckSample(const PStr &name, int parent);
    ProfileSampleHistory *CheckHistory(const PStr &name);
    std::vector<ProfileItem*> &GetStack() { return m_profileStack; };
    void ResetWritePos();
    void WriteBuffer(const PChar *str);
    void WriteBuffer(const PStr &str);
    bool m_isOpen;
    bool m_resetFlag;
    PChar *m_pBuffer;
    PChar *m_pWritePos;
    size_t m_profileLevel;
    PNumber m_delay;
    PNumber m_delayStep;
    PNumber m_startTime;
    PNumber m_secsPerTick;
    std::vector<ProfileItem*> m_profileStack;
    std::vector<ProfileSample*> m_profileSampleSet;
    std::map<PStr, ProfileSampleHistory*> m_profileHistorySet;
    static Profile *m_pSingletonPtr;
};

class ProfileItem {
public:
    ProfileItem(const PStr &name, Profile *pProfile = Profile::GetSingletonPtr());
    ~ProfileItem();
private:
    PNumber m_startTime;
    Profile *m_pProfile;
    ProfileSample *m_sample;
};

#endif