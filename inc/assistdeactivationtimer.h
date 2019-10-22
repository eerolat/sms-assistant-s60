//
// ASSISTDEACTIVATIONTIMER.H - source file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
// 


#ifndef __ASSISTDEACTIVATIONTIMER_H__
#define __ASSISTDEACTIVATIONTIMER_H__

#if !defined(__E32BASE_H__) 
#include <e32base.h>
#endif


class CEikAppUi;


class CAssistDeactivationTimer : public CTimer
    {
public:
    static CAssistDeactivationTimer* NewL(CEikAppUi& aAppUi);
protected:
    CAssistDeactivationTimer();
private:
    void SetCallback(CEikAppUi& aAppUi);
    void RunL();
private:
    CEikAppUi* iAppUi;
    };


#endif // __ASSISTDEACTIVATIONTIMER_H__