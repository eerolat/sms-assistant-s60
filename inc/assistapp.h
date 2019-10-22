
#ifndef __ASSISTAPP_H__
#define __ASSISTAPP_H__

#ifndef __AKNAPP_H__
#include <aknapp.h>
#endif


// UID of the application
const TUid KUidAssist={ 0x101F3CB6 };


class CAssistApp : public CAknApplication
    {
public:
protected:
private:
    CApaDocument* CreateDocumentL();
    TUid AppDllUid() const;
    };


#endif // __ASSISTAPP_H__


