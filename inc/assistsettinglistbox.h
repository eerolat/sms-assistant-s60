//
// ASSISTSETTINGLISTBOX.H - header file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
//   


#ifndef __ASSISTSETTINGLISTBOX_H__
#define __ASSISTSETTINGLISTBOX_H__

#ifndef __AKNSETTINGITEMLIST_H__
#include <AknSettingItemList.h>
#endif


class CAssistSettingView;
class TAssistData;


class CAssistSettingListbox : public CAknSettingItemList
    {
public:
    CAknSettingItem* CreateSettingItemL(TInt identifier);
    void SetData(TAssistData* aData);
private:
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    void SizeChanged();
private:
    TAssistData* iData;  // Doesn't own anything
    };


#endif // __ASSISTSETTINGLISTBOX_H__