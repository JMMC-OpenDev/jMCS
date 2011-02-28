/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: SplashScreen.java,v 1.9 2011-02-08 11:01:25 bourgesl Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * Revision 1.8  2008/08/28 15:41:34  lafrasse
 * iChanged program version label.
 * Corrected log messages and dicumentation.
 *
 * Revision 1.7  2008/06/20 08:41:45  bcolucci
 * Remove unused imports and add class comments.
 *
 * Revision 1.6  2008/05/20 08:49:24  bcolucci
 * Improved thread delay definition.
 *
 * Revision 1.5  2008/05/16 12:44:54  bcolucci
 * Threaded it.
 * Removed unecessary try/cath.
 *
 * Revision 1.4  2008/04/24 15:55:57  mella
 * Added applicationDataModel to constructor.
 *
 * Revision 1.3  2008/04/22 09:17:36  bcolucci
 * Corrected user name to bcolucci in CVS $Log (was fgalland).
 *
 * Revision 1.2  2008/04/22 09:14:15  bcolucci
 * Removed unused setRelativePosition().
 *
 * Revision 1.1  2008/04/16 14:15:27  bcolucci
 * Creation.
 *
 ******************************************************************************/
package fr.jmmc.mcs.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.util.logging.Logger;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.Timer;

/**
 * This class opens a new splashscreen window. Informations of this window
 * have been taken from the XML file called <b>ApplicationData.xml</b>.
 * This file is saved into the application module which extends <b>App</b>
 * class. There is a default XML file which having the same name and which is
 * saved into the <b>App</b> module in order to avoid important bugs.
 *
 * To acces to the XML informations, this class uses
 * <b>ApplicationDataModel</b> class. It's a class which has got getters
 * in order to do that and which has been written to abstract the way
 * to acces to these informations.
 */
public class SplashScreen extends JFrame
{

    /** default serial UID for Serializable interface */
    private static final long serialVersionUID = 1;
    /** Logger */
    private static final Logger _logger = Logger.getLogger(SplashScreen.class.getName());

    /* members */
    /** Splash screen has got the same model than about box */
    private final ApplicationDataModel _applicationDataModel;
    /** Logo label */
    private final JLabel _logoLabel = new JLabel();
    /** Panel */
    private final JPanel _panel = new JPanel();
    /** Program name label */
    private final JLabel _programNameLabel = new JLabel();
    /** Program version label */
    private final JLabel _programVersionLabel = new JLabel();

    /**
     * Creates a new SplashScreen object.
     */
    public SplashScreen()
    {
        _applicationDataModel = App.getSharedApplicationDataModel();
    }

    /**
     * Create the window fullfilled with all the information included in the Application data model.
     */
    public void display()
    {
        if (_applicationDataModel != null) {
            // Draw window
            setAllProperties();

            pack();
            WindowCenterer.centerOnMainScreen(this);

            // Show window :
            setVisible(true);

            // Use Timer to wait 2,5s before closing this dialog :
            final Timer timer = new Timer(2500, new ActionListener()
            {

                /**
                 * Handle the timer call
                 * @param ae action event
                 */
                public void actionPerformed(final ActionEvent ae)
                {
                    // Just call close to hide and dispose this frame :
                    close();
                }
            });

            // timer runs only once :
            timer.setRepeats(false);
            timer.start();
        }
    }

    /**
     * Close this splash screen
     */
    public void close()
    {
        setVisible(false);
        dispose();
    }

    /**
     * Calls all "set properties" methods
     */
    private void setAllProperties()
    {
        setLogoLabelProperties();
        setProgramNameLabelProperties();
        setProgramVersionLabelProperties();
        setPanelProperties();
        setFrameProperties();

        _logger.fine("Every JFrame properties have been initialized");
    }

    /** Sets panel properties */
    private void setPanelProperties()
    {
        _panel.setBorder(BorderFactory.createLineBorder(Color.GRAY, 1));
        _panel.setLayout(new BorderLayout());
        _panel.add(_logoLabel, BorderLayout.PAGE_START);
        _panel.add(_programNameLabel, BorderLayout.CENTER);
        _panel.add(_programVersionLabel, BorderLayout.PAGE_END);

        _logger.fine("Every panel properties have been initialized");
    }

    /** Sets logo properties */
    private void setLogoLabelProperties()
    {
        _logoLabel.setHorizontalAlignment(SwingConstants.CENTER);

        _logoLabel.setIcon(
                new ImageIcon(getClass().getResource(_applicationDataModel.getLogoURL())));

        _logger.fine("Every logo label properties have been initialized");
    }

    /** Sets program name label properties */
    private void setProgramNameLabelProperties()
    {
        _programNameLabel.setFont(new Font(null, 1, 30));
        _programNameLabel.setHorizontalAlignment(SwingConstants.CENTER);

        _programNameLabel.setText(_applicationDataModel.getProgramName());

        _logger.fine(
                "Every program name label properties have been initialized");
    }

    /** Sets program version label properties */
    private void setProgramVersionLabelProperties()
    {
        _programVersionLabel.setHorizontalAlignment(SwingConstants.CENTER);

        // Pattern : "v{version} - {copyright}"
        _programVersionLabel.setText("Version "
                + _applicationDataModel.getProgramVersion()
                + " - " + _applicationDataModel.getCopyrightValue());

        _logger.fine(
                "Every program version label properties have been initialized");
    }

    /** Sets frame properties */
    private void setFrameProperties()
    {
        getContentPane().add(_panel, BorderLayout.CENTER);

        setTitle(_applicationDataModel.getProgramName());
        setResizable(false);
        setUndecorated(true);
        setAlwaysOnTop(true);
    }
}
/*___oOo___*/
