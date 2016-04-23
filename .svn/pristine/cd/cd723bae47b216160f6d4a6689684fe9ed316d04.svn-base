/* *** <<< DO NOT MODIFY OR REMOVE THIS LINE - BEGIN >>> *** */
/***************************************************************************
 *
 *   This is a part of the Qisda RF Calibration and Test library.
 *
 *   This document contains propriety information, and except with written
 *   permission of Qisda Corp., such information shall not be 
 *   published, or disclosed to others, or used for any purpose, and the   
 *   document shall not be duplicated in whole or in part.  
 *
 *   Copyright (C) 2009 Qisda Corporation
 *   All Rights Reserved.
 *
 ***************************************************************************/
/* *** <<< DO NOT MODIFY OR REMOVE THIS LINE - END >>> *** */

// CriticalSection.h: interface for the CCriticalSection class.
//
//////////////////////////////////////////////////////////////////////
 
#if !defined(AFX_CRITICALSECTION_H__E73AEFEB_F51C_41E9_BF9C_6652DA0C571F__INCLUDED_)
#define AFX_CRITICALSECTION_H__E73AEFEB_F51C_41E9_BF9C_6652DA0C571F__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
class CSimpleCriticalSection
{
public:
    void Lock() { EnterCriticalSection(&m_sec); }
    void Unlock() { LeaveCriticalSection(&m_sec); }
    CSimpleCriticalSection() { InitializeCriticalSection(&m_sec); }
    ~CSimpleCriticalSection() { DeleteCriticalSection(&m_sec); }
private:
    CRITICAL_SECTION m_sec;
};
 
#endif // !defined(AFX_CRITICALSECTION_H__E73AEFEB_F51C_41E9_BF9C_6652DA0C571F__INCLUDED_)
