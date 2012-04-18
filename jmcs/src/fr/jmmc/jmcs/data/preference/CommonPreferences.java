/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.data.preference;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Singleton object which handles common preferences.
 * 
 * @author Guillaume MELLA, Laurent BOURGES.
 */
public final class CommonPreferences extends Preferences {

    /** Singleton instance */
    private static CommonPreferences _singleton = null;
    /** Logger */
    private static final Logger _logger = LoggerFactory.getLogger(CommonPreferences.class.getName());
    /* Preferences */
    /** Store the filename of the common preference file */
    public static final String PREFERENCES_FILENAME = "fr.jmmc.jmcs.properties";
    /**  Name of the preference which stores the user email in the feedback report */
    public static final String FEEDBACK_REPORT_USER_EMAIL = "feedback_report.user_email";
    /** Name of the preference which stores the flag to display or not the splash screen */
    public static final String SHOW_STARTUP_SPLASHSCREEN = "startup.splashscreen.show";

    /* Proxy settings */
    /** HTTP proxy host */
    public static final String HTTP_PROXY_HOST = "http.proxyHost";
    /** HTTP proxy port */
    public static final String HTTP_PROXY_PORT = "http.proxyPort";

    /**
     * Private constructor that must be empty.
     */
    private CommonPreferences() {
        super();
    }

    /**
     * Return the singleton instance of CommonPreferences.
     *
     * @return the singleton preference instance
     */
    public static CommonPreferences getInstance() {
        // Build new reference if singleton does not already exist
        // or return previous reference
        if (_singleton == null) {
            _logger.debug("CommonPreferences.getInstance()");

            _singleton = new CommonPreferences();
        }

        return _singleton;
    }

    /**
     * Define the default properties used to reset default preferences.
     *
     * @throws PreferencesException if any preference value has a unsupported class type
     */
    @Override
    protected void setDefaultPreferences() throws PreferencesException {
        // Display the splash screen during app launch.
        setDefaultPreference(SHOW_STARTUP_SPLASHSCREEN, true);
        setDefaultPreference(HTTP_PROXY_HOST, "");
        setDefaultPreference(HTTP_PROXY_PORT, "");
        setDefaultPreference(FEEDBACK_REPORT_USER_EMAIL, "");
    }

    /**
     * Return the preference filename.
     *
     * @return preference filename.
     */
    @Override
    protected String getPreferenceFilename() {
        return PREFERENCES_FILENAME;
    }

    /**
     *  Return preference version number.
     *
     * @return preference version number.
     */
    @Override
    protected int getPreferencesVersionNumber() {
        return 1;
    }

    /**
     * Run this program to generate the common preference file.
     * @param args NC
     */
    public static void main(String[] args) {
        try {
            CommonPreferences.getInstance().saveToFile();
        } catch (PreferencesException pe) {
            _logger.error("Property failure: ", pe);
        }
    }
}
