//
// ASSISTPHONEMONITOR.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
//

#include <etel.h>
#include "assistappui.h"
#include "assistlogmonitor.h"
#include "assistphonemonitor.h"

CAssistPhoneMonitor::CAssistPhoneMonitor()
    : CActive(EPriorityLow),
      iLastIncomingCallNumber(KNullDesC);
    {
    }


CAssistPhoneMonitor::~CAssistPhoneMonitor()
    {
    iLogReader->Cancel();
    delete iLogReader;

    Deque();
    iLine.Close();
    iPhone.Close();
    iServer.Close();
    }


void CAssistPhoneMonitor::ConstructL()
    {
    _LIT(KTsyName,"Phonetsy.tsy");

    iServer.Connect();
    
    iServer.LoadPhoneModule(KTsyName);
	TInt enumphone = 1;

    iServer.EnumeratePhones(enumphone);

	RTelServer::TPhoneInfo info;
	iServer.GetPhoneInfo(0,info);

    iPhone.Open(iServer,info.iName);

    RPhone::TLineInfo lineInfo;
	iPhone.GetLineInfo(0,lineInfo);

    iLine.Open(iPhone,lineInfo.iName);

    iLogReader=new(ELeave)CAssistLogMonitor(iLastIncomingCallNumber);
    iLogReader->ConstructL();

    CActiveScheduler::Add(this);
    
    IssueRequest();
    }


void CAssistPhoneMonitor::DoCancel()
    {
    if(IsActive())
        iLine.NotifyIncomingCallCancel();
    }


void CAssistPhoneMonitor::IssueRequest()
    {
    if(IsActive())
        return;
    
    iLine.NotifyIncomingCall(iStatus,iIncomingCallName);
    
    SetActive();
    }


void CAssistPhoneMonitor::RunL()
    {
    iLogReader->GetNewestNumber();

#pragma message("TE: Hardcoded wait to be removed")

    User::Wait(5000000);

    CEikonEnv::Static()->InfoWinL(_L("Call"),iLastIncomingCallNumber);
    static_cast<CAssistAppUi*>(CEikonEnv::Static()->AppUi())->HandleIncomingVoiceCallL(iLastIncomingCallNumber);

    IssueRequest();
    }