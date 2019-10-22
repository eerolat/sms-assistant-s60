//
// ASSISTIDLEVIEW.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//


#include <barsread.h>
#include <eikmenup.h>
#include <aknviewappui.h>
#include <aknnavi.h>
#include <aknnavide.h>
#include <aknnotewrappers.h>
#include "assistappui.h"
#include "assistcontainer.h"
#include "assistidleview.h"
#include "assistdeactivationtimer.h"
#include "assistdata.h"
#include "assist.hrh"
#include <assist.rsg>
#include <eikmenub.h>


CAssistIdleView::CAssistIdleView(TAssistData* aData)
    :iData(aData)
    {
    }


CAssistIdleView::~CAssistIdleView()
    {
    if (iIdleContainer)
        {
        AppUi()->RemoveFromStack(iIdleContainer);
        delete iIdleContainer;
        iIdleContainer=NULL;
        }

    if(iNaviDecoratorActive)
        {
        iNaviPane->Pop(iNaviDecoratorActive);
        delete iNaviDecoratorActive;
        }
    if(iNaviDecoratorInactive)
        {
        iNaviPane->Pop(iNaviDecoratorInactive);
        delete iNaviDecoratorInactive;
        }
    }


void CAssistIdleView::ConstructL()
    {
    BaseConstructL(R_ASSIST_IDLE_VIEW);

    if(iData->iAskForSendingPermission)
        {
        if(LaunchStartupNoteL())
            {
            iData->iAskForSendingPermission=EFalse;
            static_cast<CAssistAppUi*>(AppUi())->SaveL();
            }
        else
            HandleCommandL(EEikCmdExit);
        }
    }


void CAssistIdleView::HandleCommandL(TInt aCommand)
    {
    CEikAppUi* eikAppUi=CEikonEnv::Static()->EikAppUi();

    switch (aCommand)
        {
        case EAssistCmdActivate:
            {
            if(!iData->iMessage.Length())
                {
                if(!LaunchMessageWarningNoteL())
                    break;
                }
            
            if(iData->iUseDeactivation)
                {
                TTime deactivationTime=QueryDeactivationTimeL();
                static_cast<CAssistAppUi*>(AppUi())->SetDeactivationTimerL(deactivationTime);
                }

            TInt messageTotalLength=iData->iMessage.Length();
            if(iData->iUseHeader)
                {
                HBufC* messageHeader=iEikonEnv->AllocReadResourceLC(R_ASSIST_MESSAGE_HEADER);
                messageTotalLength+=messageHeader->Length();
                CleanupStack::PopAndDestroy(); // messageHeader
                }
            if(messageTotalLength>KAssistMaxMessageLength)
                LaunchLongMessageNoteL();

            iData->iActivated=ETrue;
            static_cast<CAssistAppUi*>(AppUi())->SaveL();
            static_cast<CAssistAppUi*>(AppUi())->ResetLogL();
            static_cast<CAssistAppUi*>(AppUi())->StartLogMonitor();

            iNaviPane->PushL(*iNaviDecoratorActive);
            iIdleContainer->SetState(CAssistContainer::EActive);
            iIdleContainer->SizeChanged();
            break;
            }
        case EAssistCmdDeactivate:
            {
            static_cast<CAssistAppUi*>(AppUi())->StopLogMonitor();
            iData->iActivated=EFalse;
            static_cast<CAssistAppUi*>(AppUi())->SaveL();

            iNaviPane->PushL(*iNaviDecoratorInactive);
            iIdleContainer->SetState(CAssistContainer::EInactive);
            iIdleContainer->SizeChanged();
            iIdleContainer->DrawNow();
            break;
            }
        case EAssistCmdConfigure:
            {
            if(iData->iActivated)
                {
                if(LaunchDeactivationWarningNoteL())
                    {
                    iData->iActivated=EFalse;
                    iNaviPane->PushL(*iNaviDecoratorInactive);
                    }
                else
                    break;
                }
            eikAppUi->HandleCommandL(EAssistCmdConfigure);    
            break;
            }
        case EAknSoftkeyBack:
            SendApplicationToBackgroundL();
            break;
        case EAssistCmdExit:
            {
            if(iData->iActivated)
                {
                if(LaunchExitNoteL())
                    eikAppUi->HandleCommandL(EEikCmdExit);
                break;
                }
            eikAppUi->HandleCommandL(EEikCmdExit);
            break;
            }
        default:
            eikAppUi->HandleCommandL(aCommand);
            break;      
        }
    }


void CAssistIdleView::SendApplicationToBackgroundL()
    {
    RWsSession wsSession;
    wsSession.Connect();
    TInt numWindowGroups=wsSession.NumWindowGroups();
    if(numWindowGroups>1)
        {
        TInt ownWindowGroupId=wsSession.GetFocusWindowGroup();
        wsSession.SetWindowGroupOrdinalPosition(ownWindowGroupId,numWindowGroups-1);
        }
    wsSession.Close();
    }


TBool CAssistIdleView::LaunchStartupNoteL()
    {
    TBool returnValue=EFalse;
    HBufC* message=iEikonEnv->AllocReadResourceLC(R_ASSIST_STARTUP_NOTE_TEXT);    
    CAknQueryDialog* dlg=CAknQueryDialog::NewL();
    CleanupStack::PushL(dlg);
    dlg->SetPromptL(*message);
    CleanupStack::Pop(); // dlg

    if(!dlg->ExecuteLD(R_CONFIRMATION_QUERY))
        {
        CAknNoteDialog* dlg=new(ELeave)CAknNoteDialog();
        if(dlg->ExecuteLD(R_OK_QUERY))
            returnValue=EFalse;
        }
    else
        returnValue=ETrue;

    CleanupStack::PopAndDestroy(); // message
    return returnValue;
    }


TBool CAssistIdleView::LaunchMessageWarningNoteL()
    {
    TBool returnValue=EFalse;
    HBufC* message=iEikonEnv->AllocReadResourceLC(R_ASSIST_NO_MESSAGE_NOTE_TEXT);    
    CAknQueryDialog* dlg=CAknQueryDialog::NewL();
    CleanupStack::PushL(dlg);
    dlg->SetPromptL(*message);
    CleanupStack::Pop(); // dlg
    if(dlg->ExecuteLD(R_CONFIRMATION_QUERY))
        {
        returnValue=ETrue;
        }
    CleanupStack::PopAndDestroy(); // message
    return returnValue;
    }


void CAssistIdleView::LaunchLongMessageNoteL()
    {
    HBufC* message=iEikonEnv->AllocReadResourceLC(R_ASSIST_LONG_MESSAGE_NOTE_TEXT);    
    CAknInformationNote* note=new(ELeave)CAknInformationNote;
    note->ExecuteLD(*message);
    CleanupStack::PopAndDestroy(); // message
    }


TBool CAssistIdleView::LaunchDeactivationWarningNoteL()
    {
    TBool returnValue=EFalse;
    HBufC* message=iEikonEnv->AllocReadResourceLC(R_ASSIST_DEACTIVATION_WARNING_NOTE_TEXT);    
    CAknQueryDialog* dlg=CAknQueryDialog::NewL();
    CleanupStack::PushL(dlg);
    dlg->SetPromptL(*message);
    CleanupStack::Pop(); // dlg
    if(dlg->ExecuteLD(R_CONFIRMATION_QUERY))
        {
        returnValue=ETrue;
        }
    CleanupStack::PopAndDestroy(); // message
    return returnValue;
    }


TBool CAssistIdleView::LaunchExitNoteL()
    {
    TBool returnValue=EFalse;
    HBufC* message=iEikonEnv->AllocReadResourceLC(R_ASSIST_EXIT_NOTE_TEXT);    
    CAknQueryDialog* dlg=CAknQueryDialog::NewL();
    CleanupStack::PushL(dlg);
    dlg->SetPromptL(*message);
    CleanupStack::Pop(); // dlg
    if(dlg->ExecuteLD(R_CONFIRMATION_QUERY))
        {
        returnValue=ETrue;
        }
    CleanupStack::PopAndDestroy(); // message
    return returnValue;
    }


TTime CAssistIdleView::QueryDeactivationTimeL()
    {
    TTime homeTime;
    TTimeIntervalHours timeIncrement(1);
    homeTime.HomeTime();
    TTime editorTime(homeTime);
    editorTime+=timeIncrement;

    CAknTimeQueryDialog* dlg=new(ELeave)CAknTimeQueryDialog(editorTime);
    dlg->ExecuteLD(R_DEACTIVATIONTIME_QUERY);

    TDateTime homeDateTime=homeTime.DateTime();
    TDateTime editorDateTime=editorTime.DateTime();
    
    editorDateTime.SetYear(homeDateTime.Year());
    editorDateTime.SetMonth(homeDateTime.Month());
    editorDateTime.SetDay(homeDateTime.Day());
    editorDateTime.SetSecond(0);
    editorDateTime.SetMicroSecond(0);

    TTime timerLaunchTime=TTime(editorDateTime);

    if(timerLaunchTime<homeDateTime)
        {
        TTimeIntervalDays dayIncrement(1);
        timerLaunchTime+=dayIncrement;
        }

    return timerLaunchTime;
    }


void CAssistIdleView::DynInitMenuPaneL(TInt aMenuId,CEikMenuPane* aMenuPane)
    {
    if(aMenuId==R_ASSIST_OPTIONS_MENU)
        {
        if(iData->iActivated)
            aMenuPane->SetItemDimmed(EAssistCmdActivate,ETrue);
        else
            aMenuPane->SetItemDimmed(EAssistCmdDeactivate,ETrue);
        }
    }


void CAssistIdleView::DoActivateL(const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
    {
    CEikStatusPane* statusPane=AppUi()->StatusPane();
    iNaviPane=static_cast<CAknNavigationControlContainer*>(statusPane->ControlL(TUid::Uid(EEikStatusPaneUidNavi)));

    TResourceReader reader;

    if(!iNaviDecoratorActive)
        {
        iCoeEnv->CreateResourceReaderLC(reader,R_ASSIST_NAVI_LABEL_ACTIVE);
        iNaviDecoratorActive=iNaviPane->CreateNavigationLabelL(reader);
        CleanupStack::PopAndDestroy();  // reader
        }
    if(!iNaviDecoratorInactive)
        {
        iCoeEnv->CreateResourceReaderLC(reader,R_ASSIST_NAVI_LABEL_INACTIVE);
        iNaviDecoratorInactive=iNaviPane->CreateNavigationLabelL(reader);
        CleanupStack::PopAndDestroy();  // reader
        }

    if(iIdleContainer)
        AppUi()->RemoveFromStack(iIdleContainer);
    delete iIdleContainer;
    iIdleContainer = NULL;

    iIdleContainer=new(ELeave)CAssistContainer();
    AppUi()->AddToStackL(*this,iIdleContainer);
    iIdleContainer->ConstructL();

    if(iData->iActivated)
        {
        iNaviPane->PushL(*iNaviDecoratorActive);
        iIdleContainer->SetState(CAssistContainer::EActive);
        }
    else
        {
        iNaviPane->PushL(*iNaviDecoratorInactive);
        iIdleContainer->SetState(CAssistContainer::EInactive);
        }

    iIdleContainer->SetRect(ClientRect());
    iIdleContainer->ActivateL();
    iIdleContainer->DrawNow();
    }


void CAssistIdleView::DoDeactivate()
    {
    if(iIdleContainer)
        {
        AppUi()->RemoveFromViewStack(*this,iIdleContainer);
        delete iIdleContainer;
        iIdleContainer=NULL;
        }
    }


TUid CAssistIdleView::Id() const
    {
    return TUid::Uid(KAssistIdleViewId);
    }