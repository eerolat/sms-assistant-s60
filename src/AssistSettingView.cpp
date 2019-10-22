//
// ASSISTSETTINGVIEW.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
//


#include <eikmenub.h>
#include <aknviewappui.h>
#include "assistsettinglistbox.h"
#include "assistsettingview.h"
#include "assist.hrh"
#include <assist.rsg>


CAssistSettingView::CAssistSettingView(TAssistData* aData)
    :iData(aData)
    {
    }


CAssistSettingView::~CAssistSettingView()
    {
    if (iListBox)
        {
        AppUi()->RemoveFromStack(iListBox);
        }

    delete iListBox;
    }


void CAssistSettingView::ConstructL()
    {
    BaseConstructL(R_ASSIST_SETTING_VIEW);
    }


TUid CAssistSettingView::Id() const
    {
    return TUid::Uid(KAssistSettingViewId);
    }


void CAssistSettingView::HandleCommandL(TInt aCommand)
    {
    CEikAppUi* eikAppUi=CEikonEnv::Static()->EikAppUi();

    switch(aCommand)
        {
    case EAknSoftkeyDone:
        AppUi()->ProcessCommandL(EAssistCmdActivateIdle);
        break;
    case EAssistCmdChange:
        iListBox->HandleListBoxEventL(iListBox->ListBox(),MEikListBoxObserver::EEventEnterKeyPressed);
        break;
    default:
        eikAppUi->HandleCommandL(aCommand);
        break;
        }
    }


void CAssistSettingView::DoActivateL(const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/ )
    {
    if (iListBox)
        {
        AppUi()->RemoveFromStack(iListBox);
        }
    delete iListBox;
    iListBox = NULL;

    iListBox=new(ELeave)CAssistSettingListbox;
    iListBox->SetData(iData);
    iListBox->SetMopParent(this);
    iListBox->ConstructFromResourceL(R_SETTINGS_ITEM_LIST);
    AppUi()->AddToStackL(*this,iListBox);
    iListBox->MakeVisible(ETrue);
    iListBox->SetRect(ClientRect());
    iListBox->ActivateL();
    iListBox->DrawNow();
    }


void CAssistSettingView::DoDeactivate()
    {
    iListBox->StoreSettingsL();

    if(iListBox)
        AppUi()->RemoveFromStack(iListBox);

    delete iListBox;
    iListBox=NULL;
    }
