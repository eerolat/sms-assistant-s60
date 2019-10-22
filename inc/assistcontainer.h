//
// ASSISTCONTAINER.H - header file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//  

#ifndef __ASSISTCONTAINER_H__
#define __ASSISTCONTAINER_H__

#include <coecntrl.h>

class CEikImage;

class CAssistContainer : public CCoeControl
    {
public: // Constructors and destructor.
    enum TState 
        {
        EInactive,
        EActive
        };
    void ConstructL();
    ~CAssistContainer();
    void SetState(TState aState);
    void SizeChanged();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
private: // From CCoeControl.
    void Draw(const TRect& aRect) const;
private:
    CCoeControl* iCurrentStatusIndicator; // Doesn't own anything
    CEikImage* iStatusIndicatorActive;
    CEikImage* iStatusIndicatorInactive;
    };

#endif // __ASSISTCONTAINER_H__
