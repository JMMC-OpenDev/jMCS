#ifndef gwtTEXTFIELD_H
#define gwtTEXTFIELD_H
/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: gwtTEXTFIELD.h,v 1.3 2005-02-15 12:33:49 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/02/15 12:17:52  gzins
 * Added CVS log as file modification history
 *
 * mella     16-Sep-2004  Created
 *
 ******************************************************************************/

/**
 * \file
 * Declaration of gwtTEXTFIELD class.
 */


#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif

#include "gwtWIDGET.h"

/*
 * Class declaration
 */

/**
 * Constructs a new gwtTEXTFIELD.
 */
class gwtTEXTFIELD : public gwtWIDGET
{
public:
    gwtTEXTFIELD();
    gwtTEXTFIELD(string text, string help);
    ~gwtTEXTFIELD();
    virtual string GetXmlBlock();
    virtual void SetText(string text);
    virtual string GetText();
    virtual void Changed(string value);
protected:
    virtual void SetWidgetId(string id);

private:    
    
};




#endif /*!gwtTEXTFIELD_H*/

/*___oOo___*/