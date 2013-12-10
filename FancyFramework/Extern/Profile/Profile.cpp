/* Copyright (C) Zichang Bu, 2013.
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Zichang Bu, 2013"
 *
 *           file : Profile.cpp
 *  Creation date : August 29, 2013
 *          email : buzichang@vip.qq.com
 */

#define  _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "Profile.h"
#include <windows.h>

#define NOPARENT_SAMPLE -1
#define INITIAL_MIN 999999.f

#ifdef PROFILE_USE_WCHAR
#define SPRINTF swprintf
#define STRCPY wcscpy
#define STRLEN wcslen
#else
#define SPRINTF sprintf
#define STRCPY strcpy
#define STRLEN strlen
#endif

Profile *Profile::m_pSingletonPtr = NULL;

Profile::Profile()
    : m_isOpen(true),
      m_resetFlag(false),
      m_profileLevel(128),
      m_delay(0.5f),
      m_delayStep(0.5f) {
    assert(!m_pSingletonPtr);
    m_pSingletonPtr = this;
    m_pBuffer = new PChar[BUFFERSIZE];
    memset(m_pBuffer, 0, BUFFERSIZE * sizeof(PChar));
    LARGE_INTEGER freq;
    ::QueryPerformanceFrequency(&freq);
    m_secsPerTick = 1.0 / freq.QuadPart;
}

Profile::~Profile() {
    delete [] m_pBuffer;
    for (std::vector<ProfileSample*>::iterator iter = m_profileSampleSet.begin();
        iter != m_profileSampleSet.end(); ++iter)
        delete *iter;
    for (std::map<PStr, ProfileSampleHistory*>::iterator iter = m_profileHistorySet.begin();
        iter != m_profileHistorySet.end(); ++iter)
        delete iter->second;
    m_pSingletonPtr = NULL;
}

PNumber Profile::GetTime() {
    LARGE_INTEGER time;
    ::QueryPerformanceCounter(&time);
    return time.QuadPart * m_secsPerTick;
}

void Profile::Begin() {
    if (!m_isOpen)
        return;
    m_isOpen = false;

    for (size_t i = 0; i != m_profileSampleSet.size(); ++i) {
        m_profileSampleSet[i]->valid = false;
        m_profileSampleSet[i]->pHistory = NULL;
    }

    assert(m_profileStack.size() == 0);
    m_startTime = GetTime();
}

void Profile::End() {
    if (m_isOpen)
        return;
    m_isOpen = true;
    PNumber frameTime = GetTime() - m_startTime;
    assert(m_profileStack.size() == 0);

    {
        ProfileSample *pCurSample = NULL;
        ProfileSampleHistory *pCurHistory = NULL;
        PNumber curTimePercentage;
        for (std::vector<ProfileSample*>::iterator iter = m_profileSampleSet.begin();
            iter != m_profileSampleSet.end(); ++iter) {
            pCurSample = *iter;
            if (pCurSample->valid == false)
                continue;
            pCurHistory = pCurSample->pHistory;
            pCurHistory->sampleAccumulator += pCurSample->accumulator;
            pCurHistory->frameTime = pCurSample->timeConsuming;
            curTimePercentage = pCurHistory->frameTime / frameTime;
            pCurHistory->ave =
                (pCurHistory->ave * pCurHistory->frameAccumulator + curTimePercentage) / (pCurHistory->frameAccumulator + 1);
            ++pCurHistory->frameAccumulator;

            if (pCurHistory->min > curTimePercentage)
                pCurHistory->min = curTimePercentage;
            if (pCurHistory->max < curTimePercentage)
                pCurHistory->max = curTimePercentage;
        }
    }

    if (m_resetFlag) {
        for (std::map<PStr, ProfileSampleHistory*>::iterator iter = m_profileHistorySet.begin();
            iter != m_profileHistorySet.end(); ++iter) {
            memset(iter->second, 0, sizeof(ProfileSampleHistory));
            iter->second->min = INITIAL_MIN;
        }
        m_resetFlag = false;
    }

    m_delayStep += frameTime;
    if (m_delayStep >= m_delay) {
        ResetWritePos();
#ifdef PROFILE_USE_WCHAR
        WriteBuffer(L"  Ave   :   Min   :   Max   :   Cur   :   # : Profile Name\n");
        WriteBuffer(L"-------------------------------------------------\n" );
#else
        WriteBuffer( "  Ave   :   Min   :   Max   :   Cur   :   # : Profile Name\n");
        WriteBuffer( "-------------------------------------------------\n" );
#endif
        PChar line[256], name[256], indentedName[256];
        PChar ave[16], min[16], max[16], cur[16], num[16];

        ProfileSample *pCurSample = NULL;
        ProfileSampleHistory *pCurHistory;
        for (size_t i = 0; i != m_profileSampleSet.size(); ++i) {
            pCurSample = m_profileSampleSet[i];
            if (pCurSample->valid == false)
                continue;
            pCurHistory = m_profileSampleSet[i]->pHistory;
#ifdef PROFILE_USE_WCHAR
            SPRINTF(ave, L"%6.2f%%", pCurHistory->ave * 100.0f);
            SPRINTF(min, L"%6.2f%%", pCurHistory->min * 100.0f);
            SPRINTF(max, L"%6.2f%%", pCurHistory->max * 100.0f);
            SPRINTF(cur, L"%6.2f%%", pCurSample->timeConsuming / frameTime * 100.0f);
            SPRINTF(num, L"%3d", pCurSample->accumulator );

            STRCPY(indentedName, pCurSample->name.c_str());
            for(int i = 0; i < pCurSample->parentsNum; ++i ) {
                SPRINTF(name, L"    %s", indentedName);
                STRCPY(indentedName, name);
            }

            SPRINTF(line, L"%5s : %5s : %5s : %5s : %3s : %s (%.2fms)\n", ave, min, max, cur, num, indentedName, pCurHistory->frameTime * 1000.0f);
            WriteBuffer(line);
#else
            SPRINTF(ave, "%6.2f%%", pCurHistory->ave * 100.0f);
            SPRINTF(min, "%6.2f%%", pCurHistory->min * 100.0f);
            SPRINTF(max, "%6.2f%%", pCurHistory->max * 100.0f);
            SPRINTF(cur, "%6.2f%%", pCurHistory->frameTime / frameTime * 100.0f);
            SPRINTF(num, "%3d", pCurSample->accumulator );

            STRCPY(indentedName, pCurSample->name.c_str());
            for(int i = 0; i < pCurSample->parentsNum; ++i ) {
                SPRINTF(name, "    %s", indentedName);
                STRCPY(indentedName, name);
            }

            SPRINTF(line, "%5s : %5s : %5s : %5s : %3s : %s (%.2fms)\n", ave, min, max, cur, num, indentedName, pCurHistory->frameTime * 1000.0f);
            WriteBuffer(line);
#endif

        }
        m_delayStep -= m_delay;
    }
}

ProfileSample *Profile::CheckSample(const PStr &name, int parent) {
    ProfileSample *pCurSample = NULL;
    size_t i = 0;
    for (; i != m_profileSampleSet.size(); ++i) {
        pCurSample = m_profileSampleSet[i];
        if (pCurSample->valid == false) {
            break;
        } else if (pCurSample->parent == parent && pCurSample->name == name) {
            return pCurSample;
        }
    }
    if (i == m_profileSampleSet.size()) {
        // can't seek a valid sample, then create a new one
        m_profileSampleSet.push_back(new ProfileSample);
        pCurSample = m_profileSampleSet.back();
    }
    // init sample data
    pCurSample->accumulator = 0;
    pCurSample->name = name;
    pCurSample->parent = parent;
    pCurSample->self = i;
    pCurSample->timeConsuming = 0.f;
    pCurSample->valid = true;
    pCurSample->parentsNum = 0;
    return pCurSample;
}

ProfileSampleHistory *Profile::CheckHistory(const PStr &name) {
    std::map<PStr, ProfileSampleHistory*>::iterator result = m_profileHistorySet.find(name);
    if (result == m_profileHistorySet.end()) {
        ProfileSampleHistory *pHistory = new ProfileSampleHistory;
        assert(m_profileHistorySet.insert(std::make_pair(name, pHistory)).second);
        pHistory->ave = 0.f;
        pHistory->max = 0.f;
        pHistory->min = INITIAL_MIN;
        pHistory->frameTime = 0.f;
        pHistory->frameAccumulator = 0;
        pHistory->sampleAccumulator = 0;
        return pHistory;
    }
    return result->second;
}

void Profile::ResetWritePos() {
    m_pWritePos = m_pBuffer;
}

void Profile::WriteBuffer(const PChar *str) {
    STRCPY(m_pWritePos, str);
    m_pWritePos += STRLEN(str);
}

void Profile::WriteBuffer(const PStr &str) {
    STRCPY(m_pWritePos, str.c_str());
    m_pWritePos += str.size();
}

/*****************************************************************************/

ProfileItem::ProfileItem(const PStr &name, Profile *pProfile)
    : m_pProfile(pProfile),
      m_sample(NULL) {
    assert(!m_pProfile->m_isOpen);
    std::vector<ProfileItem*> &stack = m_pProfile->GetStack();
    if (m_pProfile->GetProfileLevel() <= stack.size())
        return;
    if (m_pProfile->GetStack().empty()) {
        m_sample = m_pProfile->CheckSample(name, NOPARENT_SAMPLE);
        if (m_sample->pHistory == NULL)
            m_sample->pHistory = m_pProfile->CheckHistory(name);
    } else {
        m_sample = m_pProfile->CheckSample(name, m_pProfile->GetStack().back()->m_sample->self);
        if (m_sample->pHistory == NULL) {
            PStr parentName;
            for (std::vector<ProfileItem*>::iterator iter = stack.begin(); iter != stack.end(); ++iter) {
                parentName += (*iter)->m_sample->name +
#ifdef PROFILE_USE_WCHAR
                    L".";
#else
                    ".";
#endif
            }
            m_sample->pHistory = m_pProfile->CheckHistory(parentName + name);
        }
    }
    m_sample->parentsNum = stack.size();
    stack.push_back(this);
    m_startTime = m_pProfile->GetTime();
}

ProfileItem::~ProfileItem() {
    if (m_sample == NULL)
        return;
    // update sample
    ++m_sample->accumulator;
    m_sample->timeConsuming += m_pProfile->GetTime() - m_startTime;

    assert(m_pProfile->GetStack().back() == this);
    m_pProfile->GetStack().pop_back();
}
