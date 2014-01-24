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
package com.yourcompany.example;

import fr.jmmc.jmcs.data.preference.PreferencesException;

import java.util.logging.*;

/**
 * Test application default preferences class.
 */
public class Preferences extends fr.jmmc.jmcs.data.preference.Preferences {

    /** Logger */
    private static final Logger _logger = Logger.getLogger(Preferences.class.getName());
    /** Singleton instance */
    private static Preferences _instance = null;

    /** Return the preference filename. */
    @Override
    protected String getPreferenceFilename() {
        _logger.entering("Preferences", "getPreferenceFilename");
        return "com.yourcompany.example.test.properties";
    }

    /** Return the preference revision number. */
    @Override
    protected int getPreferencesVersionNumber() {
        _logger.entering("Preferences", "getPreferencesVersionNumber");

        return 1;
    }

    /** Set preferences default values */
    @Override
    protected void setDefaultPreferences() throws PreferencesException {
        _logger.entering("Preferences", "setDefaultPreferences");

        setDefaultPreference("DEFAULT", "default");
    }

    /** Return the singleton instance */
    public static synchronized Preferences getInstance() {
        // DO NOT MODIFY !!!
        if (_instance == null) {
            _instance = new Preferences();
        }

        return _instance;

        // DO NOT MODIFY !!!
    }

    /** Privatized constructor that must be empty. */
    private Preferences() {
    }
}
