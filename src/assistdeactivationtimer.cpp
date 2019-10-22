//
// ASSISTDEACTIVATIONTIMER.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//

#include <eikappui.h>
#include "assistdeactivationtimer.h"
#include "assist.hrh"


CAssistDeactivationTimer::CAssistDeactivationTimer()
    : CTimer(EPriorityLow)
    {
    }


CAssistDeactivationTimer* CAssistDeactivationTimer::NewL(CEikAppUi& aAppUi)
    {
	CAssistDeactivationTimer* timer=new(ELeave)CAssistDeactivationTimer();
    CleanupStack::PushL(timer);
    timer->ConstructL();
    CleanupStack::Pop();
	CActiveScheduler::Add(timer);
    timer->SetCallback(aAppUi);
    return timer;
    }


void CAssistDeactivationTimer::SetCallback(CEikAppUi& aAppUi)
    {
    iAppUi=&aAppUi;
    }


void CAssistDeactivationTimer::RunL()
    {
    iAppUi->HandleCommandL(EAssistCmdAutomaticDeactivation);
    }
