//
// ASSISTABOUTCONTAINER.H - header file for SMS Assistant application
// Copyright (c) 2001-2003 Tuomas Eerola
// 


#ifndef __ASSISTABOUTCONTAINER_H__
#define __ASSISTABOUTCONTAINER_H__

#ifndef __COECNTRL_H__
#include <coecntrl.h>
#endif


class CEikLabel;
class CEikImage;


class CAssistAboutContainer : public CCoeControl
    {
public:
    void ConstructL();
    ~CAssistAboutContainer();
    void SizeChanged();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
private:
    void Draw(const TRect& aRect) const;
private:
    CEikLabel* iMessage;
    CEikImage* iLogo;
    };

#endif // __ASSISTABOUTCONTAINER_H__

