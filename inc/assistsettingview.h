//
// ASSISTSETTINGVIEW.H - header file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
//   


#ifndef __ASSISTSETTINGVIEW_H__
#define __ASSISTSETTINGVIEW_H__


#ifndef AKNVIEW_H
#include <aknview.h>
#endif


class CAssistSettingListbox;
class TAssistData;


class CAssistSettingView : public CAknView
    {
public:
    CAssistSettingView(TAssistData* aData);
    ~CAssistSettingView();
    void ConstructL();
    void HandleCommandL(TInt aCommand);
    TUid Id() const;
protected:
private:
    void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
    void DoDeactivate();
private:
    CAssistSettingListbox* iListBox;
    TAssistData* iData;  // Doesn't own anything
    };


#endif // __ASSISTSETTINGVIEW_H__