#ifndef gwtTEXTFIELD_H
#define gwtTEXTFIELD_H
/*******************************************************************************
* JMMC project
*
* "@(#) $Id: gwtTEXTFIELD.h,v 1.1 2004-11-25 14:27:52 gzins Exp $"
*
* who       when         what
* --------  -----------  -------------------------------------------------------
* mella     16-Sep-2004  Created
*
*
*******************************************************************************/

/**
 * \file
 * gwtTEXTFIELD class declaration file.
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
