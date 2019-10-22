//
// ASSISTIDLEVIEW.H - header file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
//   


#ifndef __ASSISTIDLEVIEW_H__
#define __ASSISTIDLEVIEW_H__

#ifndef AKNVIEW_H
#include <aknview.h>
#endif


class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CAssistContainer;
class TAssistData;


class CAssistIdleView : public CAknView
    {
public:
    CAssistIdleView(TAssistData* aData);
    ~CAssistIdleView();
    void ConstructL();
    void HandleCommandL(TInt aCommand);
    void DynInitMenuPaneL(TInt aMenuId,CEikMenuPane* aMenuPane);
    TUid Id() const;
protected:
private:
    void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
    void DoDeactivate();
    TBool LaunchStartupNoteL();
    TBool LaunchMessageWarningNoteL();
    void LaunchLongMessageNoteL();
    TBool LaunchExitNoteL();
    TBool LaunchDeactivationWarningNoteL();
    void LaunchAboutNoteL();
    TTime QueryDeactivationTimeL();
    void SendApplicationToBackgroundL();
private:
    CAknNavigationControlContainer* iNaviPane;
    CAknNavigationDecorator* iNaviDecoratorActive;
    CAknNavigationDecorator* iNaviDecoratorInactive;
    CAssistContainer* iIdleContainer;
    TAssistData* iData;  // Doesn't own anything
    };


#endif // __ASSISTIDLEVIEW_H__