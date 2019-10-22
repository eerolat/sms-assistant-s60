//
// ASSISTABOUTVIEW.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//


#include <eikmenub.h>
#include <aknviewappui.h>
#include "assistaboutcontainer.h"
#include "assistaboutview.h"
#include "assist.hrh"
#include <assist.rsg>


CAssistAboutView::~CAssistAboutView()
    {
    delete iContainer;
    }


void CAssistAboutView::ConstructL()
    {
    BaseConstructL(R_ASSIST_ABOUT_VIEW);
    }


TUid CAssistAboutView::Id() const
    {
    return TUid::Uid(KAssistAboutViewId);
    }


void CAssistAboutView::HandleCommandL(TInt aCommand)
    {
    CEikAppUi* eikAppUi=CEikonEnv::Static()->EikAppUi();

    switch(aCommand)
        {
    case EAknSoftkeyBack:
        AppUi()->ProcessCommandL(EAssistCmdActivateIdle);
        break;
    default:
        eikAppUi->HandleCommandL(aCommand);
        break;
        }
    }


void CAssistAboutView::DoActivateL(const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/ )
    {
    delete iContainer;
    iContainer=NULL;

    iContainer=new(ELeave)CAssistAboutContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL();
    iContainer->MakeVisible(ETrue);
    iContainer->SetRect(ClientRect());
    iContainer->ActivateL();
    iContainer->DrawNow();
    }


void CAssistAboutView::DoDeactivate()
    {
    delete iContainer;
    iContainer=NULL;
    }
