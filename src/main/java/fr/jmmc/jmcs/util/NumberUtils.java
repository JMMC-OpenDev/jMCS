/*******************************************************************************
 *                 jMCS project ( http://www.jmmc.fr/dev/jmcs )
 *******************************************************************************
 * Copyright (c) 2013, CNRS. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     - Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     - Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     - Neither the name of the CNRS nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without
 *       specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL CNRS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/
package fr.jmmc.jmcs.util;

import java.text.DecimalFormat;
import java.text.NumberFormat;

/**
 * Handles double number comparisons with absolute error and number helper methods
 * http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
 *
 * @author Laurent BOURGES.
 */
public final class NumberUtils {

    /** Smallest positive number used in double comparisons (rounding). */
    public final static double EPSILON = 1e-6d;
    /* shared Double instances */
    /** shared Double = NaN instance */
    public final static Double DBL_NAN = Double.valueOf(Double.NaN);
    /** shared Double = 0 instance */
    public final static Double DBL_ZERO = Double.valueOf(0d);
    /** shared Double = 1 instance */
    public final static Double DBL_ONE = Double.valueOf(1d);
    /** default formatter */
    private final static NumberFormat _fmtDef = NumberFormat.getInstance();
    /** scientific formatter */
    private final static NumberFormat _fmtScience = new DecimalFormat("0.0##E0");

    /**
     * Private constructor
     */
    private NumberUtils() {
        super();
    }

    /**
     * Copied from JDK8:
     * Returns {@code true} if the argument is a finite floating-point
     * value; returns {@code false} otherwise (for NaN and infinity
     * arguments).
     *
     * @param value the {@code double} value to be tested
     * @return {@code true} if the argument is a finite
     * floating-point value, {@code false} otherwise.
     */
    public static boolean isFinite(final float value) {
        return Math.abs(value) <= Float.MAX_VALUE;
    }

    /**
     * Returns {@code true} if the argument is a finite floating-point
     * value and greater or equals to 0; returns {@code false} otherwise (for negative and NaN and infinity
     * arguments).
     * @param value the {@code double} value to be tested
     * @return {@code true} if the argument is a finite positive
     * floating-point value, {@code false} otherwise.
     */
    public static boolean isFinitePositive(final float value) {
        return isFinite(value) && (value >= 0f);
    }

    /**
     * Copied from JDK8:
     * Returns {@code true} if the argument is a finite floating-point
     * value; returns {@code false} otherwise (for NaN and infinity
     * arguments).
     *
     * @param value the {@code double} value to be tested
     * @return {@code true} if the argument is a finite
     * floating-point value, {@code false} otherwise.
     */
    public static boolean isFinite(final double value) {
        return Math.abs(value) <= Double.MAX_VALUE;
    }

    /**
     * Returns {@code true} if the argument is a finite floating-point
     * value and greater or equals to 0; returns {@code false} otherwise (for negative and NaN and infinity
     * arguments).
     * @param value the {@code double} value to be tested
     * @return {@code true} if the argument is a finite positive
     * floating-point value, {@code false} otherwise.
     */
    public static boolean isFinitePositive(final double value) {
        return isFinite(value) && (value >= 0d);
    }

    /**
     * Adjust the given double value to keep only 3 decimal digits
     * @param value value to adjust
     * @return double value with only 3 decimal digits
     */
    public static double trimTo3Digits(final double value) {
        return ((long) (1e3d * value)) / 1e3d;
    }

    /**
     * Adjust the given double value to keep only 5 decimal digits
     * @param value value to adjust
     * @return double value with only 5 decimal digits
     */
    public static double trimTo5Digits(final double value) {
        return ((long) (1e5d * value)) / 1e5d;
    }

    /**
     * Adjust the given double value to keep only 9 decimal digits
     * @param value value to adjust
     * @return double value with only 9 decimal digits
     */
    public static double trimTo9Digits(final double value) {
        return ((long) (1e9d * value)) / 1e9d;
    }

    /**
     * Format the given double value using custom formaters:
     * - '0'     if abs(val) < 1e-9
     * - 0.000   if 1e-3 < abs(val) < 1e6
     * - 0.0##E0 else
     * 
     * Note: this method is not thread safe (synchronization must be performed by callers)
     * 
     * @param val double value
     * @return formatted value
     */
    public static String format(final double val) {
        final double abs = Math.abs(val);

        if (abs < 1e-9d) {
            // means zero:
            return "0";
        }

        if (abs < 1e-3d || abs > 1e6d) {
            return FormatterUtils.format(_fmtScience, val);
        }
        return FormatterUtils.format(_fmtDef, val);
    }

    /**
     * Returns true if two doubles are considered equal.  
     * Test if the absolute difference between two doubles has a difference less than EPSILON.
     *
     * @param a double to compare.
     * @param b double to compare.
     * @return true true if two doubles are considered equal.
     */
    public static boolean equals(final float a, final float b) {
        return equals(a, b, EPSILON);
    }

    /**
     * Returns true if two doubles are considered equal. 
     * 
     * Test if the absolute difference between the two doubles has a difference less then a given
     * double (epsilon).
     *
     * @param a double to compare.
     * @param b double to compare
     * @param epsilon double which is compared to the absolute difference.
     * @return true if a is considered equal to b.
     */
    public static boolean equals(final float a, final float b, final float epsilon) {
        return (a == b) ? true : (Math.abs(a - b) < epsilon);
    }

    /**
     * Returns true if two doubles are considered equal.  
     * Test if the absolute difference between two doubles has a difference less than EPSILON.
     *
     * @param a double to compare.
     * @param b double to compare.
     * @return true true if two doubles are considered equal.
     */
    public static boolean equals(final double a, final double b) {
        return equals(a, b, EPSILON);
    }

    /**
     * Returns true if two doubles are considered equal. 
     * 
     * Test if the absolute difference between the two doubles has a difference less then a given
     * double (epsilon).
     *
     * @param a double to compare.
     * @param b double to compare
     * @param epsilon double which is compared to the absolute difference.
     * @return true if a is considered equal to b.
     */
    public static boolean equals(final double a, final double b, final double epsilon) {
        return (a == b) ? true : (Math.abs(a - b) < epsilon);
    }

    /**
     * Returns true if the first double is considered greater than the second
     * double.  
     * 
     * Test if the difference of first minus second is greater than EPSILON.
     *
     * @param a first double
     * @param b second double
     * @return true if the first double is considered greater than the second
     *              double
     */
    public static boolean greaterThan(final double a, final double b) {
        return greaterThan(a, b, EPSILON);
    }

    /**
     * Returns true if the first double is considered greater than the second
     * double.
     *
     * Test if the difference of first minus second is greater then
     * a given double (epsilon).
     *
     * @param a first double
     * @param b second double
     * @param epsilon double which is compared to the absolute difference.
     * @return true if the first double is considered greater than the second
     *              double
     */
    public static boolean greaterThan(final double a, final double b, final double epsilon) {
        return a + epsilon - b > 0d;
    }

    /**
     * Returns true if the first double is considered less than the second
     * double.
     *
     * Test if the difference of second minus first is greater than EPSILON.
     *
     * @param a first double
     * @param b second double
     * @return true if the first double is considered less than the second
     *              double
     */
    public static boolean lessThan(final double a, final double b) {
        return greaterThan(b, a, EPSILON);
    }

    /**
     * Returns true if the first double is considered less than the second
     * double.  Test if the difference of second minus first is greater then
     * a given double (epsilon).  Determining the given epsilon is highly
     * dependant on the precision of the doubles that are being compared.
     *
     * @param a first double
     * @param b second double
     * @param epsilon double which is compared to the absolute difference.
     * @return true if the first double is considered less than the second
     *              double
     */
    public static boolean lessThan(final double a, final double b, final double epsilon) {
        return a - epsilon - b < 0d;
    }

    /**
     * From OpenJDK7 Integer class:
     *
     * Compares two {@code int} values numerically.
     * The value returned is identical to what would be returned by:
     * <pre>
     *    Integer.valueOf(x).compareTo(Integer.valueOf(y))
     * </pre>
     *
     * @param  x the first {@code int} to compare
     * @param  y the second {@code int} to compare
     * @return the value {@code 0} if {@code x == y};
     *         a value less than {@code 0} if {@code x < y}; and
     *         a value greater than {@code 0} if {@code x > y}
     * @since 1.7
     */
    public static int compare(final int x, final int y) {
        return (x < y) ? -1 : ((x == y) ? 0 : 1);
    }

    /**
     * Returns an {@code Integer} instance representing the specified
     * {@code int} value.  If a new {@code Integer} instance is not
     * required, this method should generally be used in preference to
     * the constructor, as this method is likely
     * to yield significantly better space and time performance by
     * caching frequently requested values.
     *
     * This method will always cache values in the range -128 to 128 * 1024,
     * inclusive, and may cache other values outside of this range.
     *
     * @see Integer#Integer(int)
     * @param  i an {@code int} value.
     * @return an {@code Integer} instance representing {@code i}.
     */
    public static Integer valueOf(final int i) {
        return IntegerCache.get(i);
    }

    /**
     * Returns an {@code Integer} object holding the
     * value of the specified {@code String}. The argument is
     * interpreted as representing a signed decimal integer, exactly
     * as if the argument were given to the method. The result is an
     * {@code Integer} object that represents the integer value
     * specified by the string.
     *
     * <p>In other words, this method returns an {@code Integer}
     * object equal to the value of:
     *
     * <blockquote>
     *  {@code new Integer(Integer.parseInt(s))}
     * </blockquote>
     *
     * @see Integer#parseInt(java.lang.String)
     * @param      s   the string to be parsed.
     * @return     an {@code Integer} object holding the value
     *             represented by the string argument.
     * @exception  NumberFormatException  if the string cannot be parsed
     *             as an integer.
     */
    public static Integer valueOf(final String s) throws NumberFormatException {
        return IntegerCache.get(Integer.parseInt(s, 10));
    }

    /**
     * Integer Cache to support the object identity semantics of auto-boxing for values between
     * -128 and HIGH value (inclusive).
     */
    private static final class IntegerCache {

        /** lower value */
        static final int low = -1024;
        /** higher value */
        static final int high = 128 * 1024;
        /** Integer cache */
        static final Integer cache[];

        static {
            // high value may be configured by system property (NumberUtils.IntegerCache.high)

            cache = new Integer[(high - low) + 1];
            int j = low;
            for (int k = 0, len = cache.length; k < len; k++) {
                cache[k] = new Integer(j++);
            }
        }

        /**
         * Return cached Integer instance or new one
         * @param i integer value
         * @return cached Integer instance or new one 
         */
        static Integer get(final int i) {
            if (i >= low && i <= high) {
                return cache[i + (-low)];
            }
            return new Integer(i);
        }

        /**
         * Forbidden constructor
         */
        private IntegerCache() {
        }
    }
}
