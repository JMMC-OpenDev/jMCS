/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.util;

import fr.jmmc.jmcs.App;
import java.net.URL;
import java.util.MissingResourceException;
import java.util.ResourceBundle;
import javax.swing.ImageIcon;
import javax.swing.KeyStroke;
import org.apache.commons.lang.SystemUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Class used to get resources informations from one central point (XML file).
 * 
 * Applications must start to set the resource file name before any GUI construction.
 * 
 * @author Guillaume MELLA, Sylvain LAFRASSE, Laurent BOURGES.
 */
public abstract class ResourceUtils {

    /** the logger facility */
    protected static final Logger _logger = LoggerFactory.getLogger(ResourceUtils.class.getName());
    /** Resource filename, that must be overloaded by subclasses */
    private static String _resourceName = "fr/jmmc/jmcs/resource/Resources";
    /** Cached resource bundle */
    private static ResourceBundle _resources = null;
    /** Flag to indicate whether the resource bundle is resolved or not */
    private static boolean _resolved = false;
    /** Store whether the execution platform is a Mac or not */
    private static boolean MAC_OS_X = SystemUtils.IS_OS_MAC_OSX;

    /**
     * Indicates the property file where informations will be extracted.
     * The property file must end with .properties filename extension. But the
     * given name should omit the extension.
     *
     * @param name Indicates property file to use.
     */
    public static void setResourceName(final String name) {
        _logger.debug("Application will grab resources from '{}'", name);

        _resourceName = name;
        _resolved = false;
    }

    /**
     * Get content from resource file.
     *
     * @param resourceName name of resource
     *
     * @return the content of the resource or null indicating error
     */
    public static String getResourceProperty(final String resourceName) {
        return getResourceProperty(resourceName, false);
    }

    /**
     * Get content from resource file.
     *
     * @param resourceKey name of resource
     * @param quietIfNotFound true to not log at warning level i.e. debug level
     *
     * @return the content of the resource or null indicating error
     */
    public static String getResourceProperty(final String resourceKey, final boolean quietIfNotFound) {
        if (_resources == null) {

            if (!_resolved) {
                _logger.debug("getResource for '{}'", _resourceName);
                try {
                    // update the resolve flag to avoid redundant calls to getBundle when no bundle is available:
                    _resolved = true;
                    _resources = ResourceBundle.getBundle(_resourceName);
                } catch (MissingResourceException mre) {
                    if (quietIfNotFound) {
                        _logger.debug("Resource bundle can't be found : {}", mre.getMessage());
                    } else {
                        _logger.warn("Resource bundle can't be found : {}", mre.getMessage());
                    }
                }
            }

            if (_resources == null) {
                return null;
            }
        }

        _logger.debug("getResource for '{}'", resourceKey);
        try {
            return _resources.getString(resourceKey);
        } catch (MissingResourceException mre) {
            if (quietIfNotFound) {
                _logger.debug("Entry can't be found : {}", mre.getMessage());
            } else {
                _logger.warn("Entry can't be found : {}", mre.getMessage());
            }
        }

        return null;
    }

    /**
     * Get the text of an action.
     *
     * @param actionName the actionInstanceName
     *
     * @return the associated text
     */
    public static String getActionText(final String actionName) {
        return getResourceProperty("actions.action." + actionName + ".text", true);
    }

    /**
     * Get the description of an action.
     *
     * @param actionName the actionInstanceName
     *
     * @return the associated description
     */
    public static String getActionDescription(final String actionName) {
        return getResourceProperty("actions.action." + actionName + ".description", true);
    }

    /**
     * Get the tool-tip text of widget related to the common widget group.
     *
     * @param widgetName the widgetInstanceName
     *
     * @return the tool-tip text
     */
    public static String getToolTipText(final String widgetName) {
        return getResourceProperty("widgets.widget." + widgetName + ".tooltip", true);
    }

    /**
     * Get the accelerator (aka. keyboard short cut) of an action .
     *
     * @param actionName the actionInstanceName
     *
     * @return the associated accelerator
     */
    public static KeyStroke getActionAccelerator(final String actionName) {
        // Get the accelerator string description from the Resource.properties file
        String keyString = getResourceProperty("actions.action." + actionName + ".accelerator", true);

        if (keyString == null) {
            return null;
        }

        // If the execution is on Mac OS X
        if (MAC_OS_X) {
            // The 'command' key (aka Apple key) is used
            keyString = "meta " + keyString;
        } else {
            // The 'control' key ise used elsewhere
            keyString = "ctrl " + keyString;
        }

        // Get and return the KeyStroke from the accelerator string description
        KeyStroke accelerator = KeyStroke.getKeyStroke(keyString);

        if (_logger.isDebugEnabled()) {
            _logger.debug("keyString['{}'] = '{}' -> accelerator = '{}'.",
                    actionName, keyString, accelerator);
        }

        return accelerator;
    }

    /**
     * Get the icon of an action.
     *
     * @param actionName the actionInstanceName
     *
     * @return the associated icon
     */
    public static ImageIcon getActionIcon(final String actionName) {
        // Get back the icon image path
        String iconPath = getResourceProperty("actions.action." + actionName + ".icon", true);
        return ImageUtils.loadResourceIcon(iconPath);
    }

    /**
     * Get path from resource filename located in the following path:
     * $package(this App class)$/resource/fileName
     *
     * @param fileName name of searched file.
     *
     * @return resource path
     */
    public static String getPathFromResourceFilename(final String fileName) {
        return getPathFromResourceFilename(App.getInstance().getClass(), fileName);
    }

    /**
     * Get URL from resource filename located in the following path:
     * $package(this App class)$/resource/fileName
     *
     * @param fileName name of searched file.
     *
     * @return resource URL
     */
    public static URL getUrlFromResourceFilename(final String fileName) {
        return getURLFromResourceFilename(App.getInstance().getClass(), fileName);
    }

    /**
     * Get URL from resource filename located in the class loader using the following path:
     * $package(appClass)$/resource/fileName
     *
     * For example: getURLFromResourceFilename(App.class, fileName) uses the path:
     * fr/jmmc/jmcs/resource/$fileName$
     *
     * @param appClass any App class or subclass
     * @param fileName name of searched file.
     *
     * @return resource file URL, or null.
     */
    public static URL getURLFromResourceFilename(final Class<? extends App> appClass, final String fileName) {
        final String filePath = getPathFromResourceFilename(appClass, fileName);
        if (filePath == null) {
            return null;
        }
        _logger.debug("filePath = '{}'.", filePath);
        final URL fileURL = appClass.getClassLoader().getResource(filePath);
        if (fileURL == null) {
            _logger.warn("Cannot find resource from '{}' file.", filePath);
            return null;
        }
        _logger.debug("fileURL = '{}'.", fileURL);
        return UrlUtils.fixJarURL(fileURL);
    }

    /**
     * Get Path from resource filename located in the class loader using the following path:
     * $package(appClass)$/resource/fileName
     *
     * For example: getPathFromResourceFilename(App.class, fileName) uses the path:
     * fr/jmmc/jmcs/resource/$fileName$
     *
     * @param appClass any App class or subclass
     * @param fileName name of searched file.
     *
     * @return resource path, or null.
     */
    private static String getPathFromResourceFilename(final Class<? extends App> appClass, final String fileName) {
        if (appClass == null) {
            return null;
        }
        final Package p = appClass.getPackage();
        final String packageName = p.getName();
        final String packagePath = packageName.replace(".", "/");
        final String filePath = packagePath + "/resource/" + fileName;
        _logger.debug("filePath = '{}'.", filePath);
        return filePath;
    }

    /**
     * Private constructor
     */
    private ResourceUtils() {
        super();
    }
}
/*___oOo___*/
