/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: gwtTABLE.cpp,v 1.1 2005-01-27 18:09:35 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * mella     16-Sep-2004  Created
 * gzins     12-Dec-2004  Fixed gcc 3.4 error 
 *
 ******************************************************************************/

/**
 * \file
 * Definition of gwtTABLE class.
 */

static char *rcsId="@(#) $Id: gwtTABLE.cpp,v 1.1 2005-01-27 18:09:35 gzins Exp $"; 
static void *use_rcsId = ((void)&use_rcsId,(void *) &rcsId);


/* 
 * System Headers 
 */
#include <iostream>
#include <vector>
using namespace std;
/*
 * MCS Headers 
 */
#include "mcs.h"
#include "log.h"
#include "err.h"


/*
 * Local Headers 
 */
#include "gwtTABLE.h"
#include "gwtPrivate.h"
#include "gwt.h"


/*
 * Class constructor
 */

/** 
 * Constructs a gwtTABLE. The inner table vector is initialized using
 * given dimensions.
 * \param rows number of rows
 * \param columns number of columns
 */
gwtTABLE::gwtTABLE(int rows, int columns)
{
    // prepare data two dimension array
    _rows=rows;
    _columns=columns;
    _cells = new  string *[rows];
    int i;
    // build colums arrays
    for (i=0;i<_rows;i++)
    {
        _cells[i] = new string[columns];
    }

    // prepare columnHeader array
    _columnHeaders = new string[columns];
}

/*
 * Class destructor
 */

gwtTABLE::~gwtTABLE()
{
    // delete the two dimension cell array
    int i;
    for (i=0;i<_rows;i++)
    {
        delete []_cells[i];
    }
    delete [] _cells;

    // delete the columnHeaders array
    delete _columnHeaders;
}

/*
 * Public methods
 */

string gwtTABLE::GetXmlBlock()
{
    logExtDbg("gwtTABLE::GetXmlBlock()");
    string s;
    s.append("<TABLE");
    AppendXmlAttributes(s);
    s.append(">\n");

    int r,c;
    // append Column headers 
    s.append("<CHEADER>");
    for (c=0; c<_columns ; c++)
    {
        s.append("<FIELD ");
        // append the value if the header colum does exist
        if( ! _columnHeaders[c].empty())
        {
           s.append("name=\"");
           s.append(_columnHeaders[c]);
           s.append("\"");
        }
        s.append("\"/>\n");
    }  
    s.append("</CHEADER>");

    // append data
    s.append("<DATA>");
    for (r=0; r<_rows ; r++)
    {
        s.append("<TR>\n\t");
        for (c=0; c<_columns ; c++)
        {
            s.append("<TD>");
            s.append(_cells[r][c]); 
            s.append("</TD>");
        }  
        s.append("\n</TR>\n");
    }    
    s.append("</DATA>");
    s.append("</TABLE>");
    return s;
}

/**
 * Set the value of a given cell.
 * \param row
 * \param column
 * \param value
 */
void gwtTABLE::SetCell(int row, int column, string value)
{
    logExtDbg("gwtTABLE::SetCell()");
    _cells[row][column].assign(value);
}

/**
 * Get the value of a requested cell.
 * \param row
 * \param column
 * \return the value of the requested cell.
 */
string gwtTABLE::GetCell(int row, int column)
{
    logExtDbg("gwtTABLE::GetCell()");
    return _cells[row][column];
}

/**
 * Set the title of a given column.
 * \param column the column number (first one corresponds to 0)
 * \param title the title of the column
 */
void gwtTABLE::SetColumnHeader(int column, string title)
{
    _columnHeaders[column]=title;    
}

/*
 * Protected methods
 */



/*
 * Private methods
 */



/*___oOo___*/
