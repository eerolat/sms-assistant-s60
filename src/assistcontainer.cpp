//
// ASSISTCONTAINER.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//   


#include <gulcolor.h>
#include <eikenv.h>
#include <eikimage.h>
#include "assistappui.h"
#include "assist.hrh"
#include "assist.mbg"
#include "assistcontainer.h"


_LIT(KPictureFileName,"assist.mbm");


void CAssistContainer::ConstructL()
    {
    TFileName imageFileName;
    TFileName applicationName=static_cast<CAssistAppUi*>(CEikonEnv::Static()->AppUi())->Application()->AppFullName();
    TParse parse;
    parse.Set(applicationName,NULL,NULL);

    imageFileName=parse.Drive();
    imageFileName+=parse.Path();
    imageFileName+=KPictureFileName;

    iStatusIndicatorActive=new(ELeave)CEikImage;
    iStatusIndicatorInactive=new(ELeave)CEikImage;

    iStatusIndicatorActive->CreatePictureFromFileL(imageFileName,EMbmAssistActive,EMbmAssistActivem);
    iStatusIndicatorInactive->CreatePictureFromFileL(imageFileName,EMbmAssistInactive,EMbmAssistActivem);
    iCurrentStatusIndicator=iStatusIndicatorInactive;

    CreateWindowL();

    ActivateL();
    }


CAssistContainer::~CAssistContainer()
    {
    delete iStatusIndicatorActive;
    delete iStatusIndicatorInactive;
    }


void CAssistContainer::SetState(TState aState)
    {
    if(aState==EActive)
        iCurrentStatusIndicator=iStatusIndicatorActive;
    else
        iCurrentStatusIndicator=iStatusIndicatorInactive;
    }


TInt CAssistContainer::CountComponentControls() const
    {
    return 1;
    }

CCoeControl* CAssistContainer::ComponentControl(TInt aIndex) const
    {
    if(aIndex==0)
        return iCurrentStatusIndicator;
    else
        return NULL;
    }


void CAssistContainer::SizeChanged()
    {
    TRect rect=Rect();
    TSize size=iCurrentStatusIndicator->MinimumSize();
    rect.iTl.iY+=(rect.Height()-size.iHeight)/2;
    rect.iTl.iX+=(rect.Width()-size.iWidth)/2;
    rect.iBr=rect.iTl+size;
    iCurrentStatusIndicator->SetRect(rect);
    }


void CAssistContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);

    CColorList& colors=iEikonEnv->ColorList();
    TRgb rgbColor=colors.Color(EColorWindowBackground);
	gc.SetBrushColor(rgbColor);
    gc.DrawRect(aRect);
    }