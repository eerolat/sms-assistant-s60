//
// ASSISTABOUTCONTAINER.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//

#include <barsread.h>
#include <gulcolor.h>
#include <eikenv.h>
#include <eiklabel.h>
#include <eikimage.h>
#include <assist.rsg>
#include "assistappui.h"
#include "assistaboutcontainer.h"
#include "assist.hrh"
#include "assist.mbg"


_LIT(KPictureFileName,"assist.mbm");


void CAssistAboutContainer::ConstructL()
    {
    TFileName imageFileName;
    TFileName applicationName=static_cast<CAssistAppUi*>(CEikonEnv::Static()->AppUi())->Application()->AppFullName();
    TParse parse;
    parse.Set(applicationName,NULL,NULL);

    imageFileName=parse.Drive();
    imageFileName+=parse.Path();
    imageFileName+=KPictureFileName;

    iMessage=new(ELeave)CEikLabel;
    iLogo=new(ELeave)CEikImage;
    
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader,R_ASSIST_ABOUT_APPLICATION_TEXT);
    iMessage->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy(); // reader
    iLogo->CreatePictureFromFileL(imageFileName,EMbmAssistAssistaboutnoteicon,EMbmAssistAssistaboutnoteiconm);

    CreateWindowL();

    ActivateL();
    }


CAssistAboutContainer::~CAssistAboutContainer()
    {
    delete iMessage;
    delete iLogo;
    }


TInt CAssistAboutContainer::CountComponentControls() const
    {
    return 2;
    }


CCoeControl* CAssistAboutContainer::ComponentControl(TInt aIndex) const
    {
    CCoeControl* control=NULL;

    switch (aIndex)
        {
    case 0:
        control=iMessage;
        break;
    case 1:
        control=iLogo;
        break;
    default:
        break;
        }

    return control;
    }


void CAssistAboutContainer::SizeChanged()
    {
    const TInt KControlSpacing=10;

    TRect rect=Rect();

    TSize messageSize=iMessage->MinimumSize();
    TSize logoSize=iLogo->MinimumSize();

    rect.iTl.iY+=(rect.Height()-(messageSize.iHeight+KControlSpacing+logoSize.iHeight))/2;
    rect.iTl.iX+=(rect.Width()-messageSize.iWidth)/2;
    rect.iBr=rect.iTl+messageSize;
    iMessage->SetRect(rect);

    rect=Rect();
    rect.iTl.iY+=(rect.Height()-(messageSize.iHeight+KControlSpacing+logoSize.iHeight))/2;
    rect.iTl.iY+=messageSize.iHeight+KControlSpacing;
    rect.iTl.iX+=(rect.Width()-logoSize.iWidth)/2;
    rect.iBr=rect.iTl+logoSize;
    iLogo->SetRect(rect);
    }


void CAssistAboutContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);

    CColorList& colors=iEikonEnv->ColorList();
    TRgb rgbColor=colors.Color(EColorWindowBackground);
	gc.SetBrushColor(rgbColor);
    gc.DrawRect(aRect);
    }