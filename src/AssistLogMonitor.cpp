//
// ASSISTLOGMONITOR.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//

#include <logcli.h>
#include <logview.h>
#include <barsread.h>
#include <logwrap.rsg>
#include "assistappui.h"
#include "assistlogmonitor.h"
#include "assist.hrh"
#include <eikenv.h>


CAssistLogMonitor::CAssistLogMonitor()
    : CActive(EPriorityLow),
      iMonitorState(EInitializing),
      iNewestLogEventId(0)
    {
    }


CAssistLogMonitor::~CAssistLogMonitor()
    {
    Cancel();

    Deque();

    delete iLogView;

    delete iFilter;

    delete iLogClient;    
    iRFs.Close();
    }


void CAssistLogMonitor::ConstructL()
    {
    iMonitorState=EInitializing;

    iRFs.Connect();
    iLogClient=CLogClient::NewL(iRFs);

    iLogClient->GetString(iLogDirectionString,R_LOG_DIR_MISSED);
    
    iLogView=CLogViewEvent::NewL(*iLogClient);

    iFilter=CLogFilter::NewL();

    CActiveScheduler::Add(this);
    }


void CAssistLogMonitor::Start()
    {
    iMonitorState=EInitializing;
    
    IssueRequest();
    }


void CAssistLogMonitor::DoCancel()
    {
    if(IsActive())
        {
        iLogView->Cancel();
        iLogClient->NotifyChangeCancel();
        }
    }


void CAssistLogMonitor::IssueRequest()
    {
    if(IsActive())
        return;

    switch(iMonitorState)
        {
    case EInitializing:
        iStatus=KRequestPending;
        iLogView->SetFilterL(*iFilter, iStatus);
        break;
    case EWaitingForLogChange:
        iStatus=KRequestPending;
        iLogClient->NotifyChange(0, iStatus);
        break;
    case EFindingNewestEvent:
        iStatus=KRequestPending;
        iLogView->FirstL(iStatus);
        break;
    default:
        break;
        }
    
    SetActive();
    }


void CAssistLogMonitor::RunL()
    {
    switch(iMonitorState)
        {
    case EInitializing:
        iMonitorState=EWaitingForLogChange;
        break;
    case EWaitingForLogChange:
        {
        iMonitorState=EUpdatingRecentList;
        iLogClient->NotifyChangeCancel();

        iMonitorState=EWaitingForLogChange;
        
        TInt listCount=0;

        TRAPD(error, listCount=iLogView->CountL());

        if((error==KErrNone) && (listCount>0))
            iMonitorState=EFindingNewestEvent;
        }
        break;
    case EFindingNewestEvent:
        {
        iMonitorState=EHandlingNewEvent;

        TInt recentListCount=0;

        TRAPD(error, recentListCount=iLogView->CountL());

        if((error==KErrNone) && (recentListCount>0))
            {
            const CLogEvent& event=iLogView->Event();

            TInt logEventId=event.Id();

            if(logEventId>iNewestLogEventId)
                {
                iNewestLogEventId=logEventId;

                CAssistAppUi* appUi=static_cast<CAssistAppUi*>(CEikonEnv::Static()->AppUi());
                TBuf<KMaxTelephoneNumberLength> number=_L("");
                
//                if(event.DurationType()==KLogDurationValid)
//                    {
                    if(event.Direction()==_L("Missed call"))
                        {
                        if(appUi->ReplyToVoice())
                            {
                            if(event.Number().Length()>0)
                                number=event.Number();
                            }
                        }
//                    }
                else if(event.Description()==_L("Short message") && event.Direction()==_L("Incoming"))
                    {
                    if(appUi->ReplyToSMS())
                        {
                        if(event.Number().Length()>0)
                            number=event.Number();
                        }
                    }
//                else
//                    {
//                    CEikonEnv::Static()->InfoWinL(_L("Direction"),event.Direction());
//                    CEikonEnv::Static()->InfoWinL(_L("Description"),event.Description());
//                    }

                if(number!=_L(""))
                    static_cast<CAssistAppUi*>(CEikonEnv::Static()->AppUi())->HandleIncomingVoiceCallL(number);
                }
            }
        iMonitorState=EWaitingForLogChange;
        }
        break;
    default:
        break;
        }

    IssueRequest();
    }