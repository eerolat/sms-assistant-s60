//
// ASSISTAPP.CPP - source file for SMS Assistant application
// Copyright (c) 2001-2005 Tuomas Eerola
//   

#include "assistapp.h"
#include "assistdocument.h"

TUid CAssistApp::AppDllUid() const
    {
    return KUidAssist;
    }

CApaDocument* CAssistApp::CreateDocumentL()
    {
    return CAssistDocument::NewL(*this);
    }

EXPORT_C CApaApplication* NewApplication()
    {
    return new CAssistApp;
    }

GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
    {
    return KErrNone;
    }

