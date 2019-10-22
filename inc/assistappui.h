//
// ASSISTAPPUI.H - header file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//  


#ifndef __ASSISTAPPUI_H__
#define __ASSISTAPPUI_H__

#ifndef __AKNVIEWAPPUI_H__
#include <aknviewappui.h>
#endif

#if !defined(__EIKAPP_H__)
#include <eikapp.h>
#endif

#if !defined(__EIKDOC_H__)
#include <eikdoc.h>
#endif

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__COECCNTX_H__)
#include <coeccntx.h>
#endif

#if !defined(__AKNAPPUI_H__)
#include <aknappui.h>
#endif

#if !defined(__MSVAPI_H__)
#include <msvapi.h>
#endif

class CClientMtmRegistry;
class CMsvSession;
class CBaseMtm;
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CAssistContainer;
class CAssistLogMonitor;
class CAssistDeactivationTimer;
class TAssistData;


class CAssistAppUi : public CAknViewAppUi, public MMsvSessionObserver
    {
public:
    CAssistAppUi();
    void ConstructL();
    ~CAssistAppUi();
    void ExternalizeL(RWriteStream& aOut) const;
    void InternalizeL(RReadStream& aIn);
    void SaveL();
    TStreamId StoreL( CStreamStore& aStore) const;
    void RestoreL(const CStreamStore& aStore, TStreamId aId);
    void HandleIncomingVoiceCallL(TDesC& aCallingNumber);
    void SetDeactivationTimerL(TTime aLaunchTime);
    void StartLogMonitor();
    void StopLogMonitor();
    void ResetLogL();
    TBool ReplyToVoice() const;
    TBool ReplyToSMS() const;
    TBool ReplyToMMS() const;
protected:
private:
    void CompleteConstructL();
    void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
    TMsvId CreateNewMessageL();
    void SetEntryL(TMsvId aEntryId);
    TBool SendSMSReplyMessageL();
    TMsvId MoveMessageEntryL(TMsvId aTarget);
    void SetScheduledSendingStateL(CMsvEntrySelection* aSelection);
    TBool DeleteSentEntry(TMsvId aEntryId);
    void HandleCommandL(TInt aCommand);
    TBool LaunchExitNoteL();
    void LaunchAboutNoteL();
    void ConfigureApplicationL();
    void AboutApplicationL();
    void ConfigureDeactivationL();
    void SendApplicationToBackgroundL();
    void SaveIniFileL();
    void LoadIniFileL();
    TBool IsNumberInLogL(TDesC* aNumber) const;
    void AddNumberToLogL(TDesC* aNumber);
    void MessageReceivedL(TMsvId aEntryId);
private: // Data.
    TMsvId iMsvId;
    CMsvSession* iSession;
    CBaseMtm* iMtm;
    CClientMtmRegistry* iMtmReg;
    CAssistContainer* iAppContainer;
    CAssistLogMonitor* iLogMonitor;
    CAssistDeactivationTimer* iDeactivationTimer;
    TAssistData* iData;
    TTime iDeactivationTime;
    };

#endif // __ASSISTAPPUI_H__
