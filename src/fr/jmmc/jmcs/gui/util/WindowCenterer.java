/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.gui.util;

import java.awt.Dimension;
import java.awt.DisplayMode;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Point;
import java.awt.Window;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Facility static class to properly center a window
 * on the main screen (handle multiple screen setups).
 * 
 * @author Brice COLUCCI, Guillaume MELLA, Laurent BOURGES.
 */
public class WindowCenterer {

    /** Logger */
    private static final Logger _logger = LoggerFactory.getLogger(WindowCenterer.class.getName());
    /** Screen width */
    private static int _screenWidth = 0;
    /** Screen height */
    private static int _screenHeight = 0;

    /**
     * Get screen properties
     * @throws NullPointerException on some platform (virtual box)
     */
    public static void getScreenProperties() throws NullPointerException {
        // Get main screen size
        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        GraphicsDevice gs = ge.getDefaultScreenDevice();
        DisplayMode dm = gs.getDisplayMode();
        _screenWidth = dm.getWidth();
        _screenHeight = dm.getHeight();
    }

    /**
     * Center the given JFrame on the main screen realestate.
     *
     * If the JFrame is bigger than the main screen, it will be moved to the upper-left main screen corner.
     *
     * @param frameToCenter the JFrame we want to center
     */
    public static void centerOnMainScreen(final Window frameToCenter) {
        // next try catch is mandatory to catach null pointer excpetion that
        // can occure on some virtual machine emulation (at least virtualBox)
        try {
            getScreenProperties();

            // Dimension of the JFrame
            Dimension frameSize = frameToCenter.getSize();

            // Get centering point
            Point point = getCenteringPoint(frameSize);

            frameToCenter.setLocation(point);

            _logger.debug("The window has been centered");

        } catch (NullPointerException npe) {
            _logger.warn("Could not center window");
        }
    }

    /**
     * Returns the centered point in order to center a frame on the screen
     * @param frameDimension frame size
     * @return centered point
     * @throws NullPointerException on some platform (virtual box)
     */
    public static Point getCenteringPoint(final Dimension frameDimension)
            throws NullPointerException {
        getScreenProperties();

        int x = (_screenWidth - frameDimension.width) / 2;
        x = Math.max(x, 0);

        int y = (_screenHeight - frameDimension.height) / 2;
        y = Math.max(y, 0);

        return new Point(x, y);
    }

    /**
     * Private constructor
     */
    private WindowCenterer() {
        super();
    }
}
/*___oOo___*/
