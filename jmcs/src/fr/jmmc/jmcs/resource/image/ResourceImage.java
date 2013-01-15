/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.resource.image;

import fr.jmmc.jmcs.util.ImageUtils;
import javax.swing.ImageIcon;

/**
 * jMCS internal resource images.
 * @author Sylvain LAFRASSE
 */
public enum ResourceImage {

    JMMC_FAVICON("jmmc_favicon.png"),
    STATUS_HISTORY("script_start.png"), // http://www.iconseeker.com/search-icon/aspnet/script-start.html### by http://www.aspneticons.com/ (Creative Commons Attribution 3.0 License)
    HELP_ICON("help_icon.png"),
    INFO_ICON("info_icon.png"),
    DISABLED_INFO_ICON("disabled_info_icon.png"),
    WARNING_ICON("warning_icon.png"),
    UP_ARROW("up_arrow.png"),
    DOWN_ARROW("down_arrow.png");
    /** Common resource directory containing icon files */
    private final static String IMAGE_RESOURCE_COMMON_PATH = "fr/jmmc/jmcs/resource/image/";
    /** Loaded icon resource */
    private final ImageIcon _icon;

    /** Constructor */
    private ResourceImage(String iconName) {
        _icon = ImageUtils.loadResourceIcon(IMAGE_RESOURCE_COMMON_PATH + iconName);
    }

    /**
     * @return the resource image icon
     */
    public ImageIcon icon() {
        return _icon;
    }

    /**
     * For unit testing purpose only.
     * @param args
     */
    public static void main(String[] args) {
        for (ResourceImage rsc : ResourceImage.values()) {
            System.out.println("Resource '" + rsc.name() + "' -> '" + rsc.icon() + "'.");
        }
    }
}
