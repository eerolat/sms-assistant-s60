//
// ASSISTABOUTVIEW.H - header file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
//   


#ifndef __ASSISTABOUTVIEW_H__
#define __ASSISTABOUTVIEW_H__


#ifndef AKNVIEW_H
#include <aknview.h>
#endif


class CAssistAboutContainer;


class CAssistAboutView : public CAknView
    {
public:
    ~CAssistAboutView();
    void ConstructL();
    void HandleCommandL(TInt aCommand);
    TUid Id() const;
protected:
private:
    void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
    void DoDeactivate();
private:
    CAssistAboutContainer* iContainer;
    };


#endif // __ASSISTABOUTVIEW_H__