//
// ASSISTDATA.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//


#include "assistdata.h"
#include "assist.hrh"


TAssistData* TAssistData::NewL()
    {
    TAssistData* self=new(ELeave)TAssistData();
    return self;
    }


TAssistData::TAssistData()
    : iRecipient(KNullDesC), iMessage(KNullDesC), iActivated(EFalse), iUseDeactivation(EFalse), iUseHeader(ETrue), iReplyTo(EAll), iAskForSendingPermission(ETrue)
    {
    }
