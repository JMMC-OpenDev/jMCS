#ifndef gwtSUBPANEL_H
#define gwtSUBPANEL_H
/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: gwtSUBPANEL.h,v 1.2 2005-02-15 12:17:52 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * mella     16-Sep-2004  Created
 *
 ******************************************************************************/

/**
 * \file
 * gwtSUBPANEL class declaration file.
 */


#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif

#include "gwtCONTAINER.h"
#include "gwtCOMMAND.h"

/*
 * Class declaration
 */

/**
 * Constructs a new gwtSUBPANEL.
 */
class gwtSUBPANEL : public gwtCONTAINER, public gwtCOMMAND
{
public:
    gwtSUBPANEL();
    gwtSUBPANEL(string text);
    gwtSUBPANEL(string text, string help);
    ~gwtSUBPANEL();
    virtual string GetXmlBlock();
    void SetWidgetId(string id);
    virtual void Changed(string value);
    virtual void SetText(string text);
    
protected:

private:    
    
};

#endif /*!gwtSUBPANEL_H*/

/*___oOo___*/
