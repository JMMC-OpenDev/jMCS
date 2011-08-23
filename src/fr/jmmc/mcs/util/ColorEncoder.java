/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.mcs.util;

import java.awt.Color;


/**
 * DOCUMENT ME!
 * 
 * @author Guillaume MELLA.
 */
public class ColorEncoder
{
    /**
     * DOCUMENT ME!
     *
     * @param i DOCUMENT ME!
     *
     * @return DOCUMENT ME!
     */
    private static String hexForInt(int i)
    {
        if (i == 0)
        {
            return "00";
        }

        return Integer.toHexString(i);
    }

    /** Converts a String to an integer and returns the specified opaque Color.
     * This method handles string formats that are used to represent octal and
     * hexidecimal numbers.
     * @param c The color to encode
     * @return the encoded string for given color
     */
    public static String encode(Color c)
    {
        String ret = "#";
        ret += hexForInt(c.getRed());
        ret += hexForInt(c.getGreen());
        ret += hexForInt(c.getBlue());

        return ret;
    }
}
