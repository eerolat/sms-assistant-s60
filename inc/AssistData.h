//
// ASSISTDATA.H - header file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
//   

#ifndef __ASSISTDATA_H__
#define __ASSISTDATA_H__

#ifndef __AKNAPP_H__
#include <aknapp.h>
#endif

#ifndef __ASSIST_HRH__
#include "assist.hrh"
#endif


class TAssistData
    {
public:
    static TAssistData* NewL();
    TBuf<KMaxTelephoneNumberLength> iRecipient;
    TBuf<KAssistMaxMessageLength> iMessage;
    TBool iActivated;
    TBool iUseDeactivation;
    TBool iUseHeader;
    TInt iReplyTo;
    TBool iAskForSendingPermission;
protected:
    TAssistData();
    };


#endif // __ASSISTDATA_H__