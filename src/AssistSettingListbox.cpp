//
// ASSISTSETTINGLISTBOX.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//


#include <akntextsettingpage.h>
#include "assistdata.h"
#include "assistsettinglistbox.h"
#include "assist.hrh"


void CAssistSettingListbox::SetData(TAssistData* aData)
    {
    iData=aData;
    }


TKeyResponse CAssistSettingListbox::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if(aType!=EEventKey)
        {
        return EKeyWasNotConsumed;
        }

    CAknSettingItemList::OfferKeyEventL(aKeyEvent, aType);
    
    return EKeyWasConsumed;
    }


void CAssistSettingListbox::SizeChanged()
    {
    if(ListBox()) 
        {
        ListBox()->SetRect(Rect());
        }
    }


CAknSettingItem* CAssistSettingListbox::CreateSettingItemL(TInt aIdentifier)
    {
    CAknSettingItem* settingItem=NULL;

    switch (aIdentifier)
        {
    case EReplyMessageSetting:
        {
        settingItem=new(ELeave)CAknTextSettingItem(aIdentifier, iData->iMessage);
        TInt flags=settingItem->SettingPageFlags();
        settingItem->SetSettingPageFlags(flags | CAknTextSettingPage::EPredictiveTextEntryPermitted);
        break;
        }
    case EReplyToSetting:
        settingItem=new(ELeave)CAknEnumeratedTextPopupSettingItem(aIdentifier, iData->iReplyTo);
        break;
    case EAutomaticDeactivationSetting:
        settingItem=new(ELeave)CAknBinaryPopupSettingItem(aIdentifier, iData->iUseDeactivation);
        break;
    case EReplyHeaderUseSetting:
        settingItem=new(ELeave)CAknBinaryPopupSettingItem(aIdentifier, iData->iUseHeader);
        break;
    default:
        break;
        }
    
    return settingItem;
    }