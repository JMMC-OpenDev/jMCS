/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fest.common;

import fr.jmmc.jmcs.App;
import fr.jmmc.jmcs.gui.component.MessagePane;
import java.awt.Frame;
import java.awt.image.BufferedImage;
import java.util.Arrays;
import java.util.logging.Level;
import org.fest.swing.core.ComponentFoundCondition;
import org.fest.swing.core.EmergencyAbortListener;
import org.fest.swing.core.matcher.FrameMatcher;
import org.fest.swing.fixture.FrameFixture;
import org.fest.swing.fixture.JOptionPaneFixture;
import static org.fest.swing.launcher.ApplicationLauncher.*;
import org.fest.swing.timing.Condition;
import static org.fest.swing.timing.Pause.*;
import org.junit.AfterClass;
import org.junit.BeforeClass;

/**
 * This class extends FestSwingCustomJUnitTestCase to start / stop one Jmcs application
 * @author bourgesl
 */
public class JmcsFestSwingJUnitTestCase extends FestSwingCustomJUnitTestCase {

    /* members */
    /** application window fixture */
    protected FrameFixture window;
    /** emergency abort listener associated to 'Ctrl + Shift + A' key combination */
    private EmergencyAbortListener listener;

    /**
     * Public constructor required by JUnit
     */
    public JmcsFestSwingJUnitTestCase() {
        super();
    }

    /**
     * Set up the Swing application.
     * This method is called <strong>after</strong> executing <code>{@link #setUpOnce()}</code>.
     */
    @BeforeClass
    public static void onSetUpOnce() {

        MessagePane.showWarning("Please do not touch the mouse while FEST tests run !\n\nHaut les mains ^_^");

        // Use main thread to start Jmcs application using subclass.main() :
        if (App.getSharedInstance() == null) {

            // disable use of System.exit() :
            App.setAvoidSystemExit(true);

            if (JmcsApplicationSetup.applicationClass != null) {
                if (logger.isLoggable(Level.INFO)) {
                    logger.info("onSetUpOnce : starting application : " + JmcsApplicationSetup.applicationClass);
                }

                if (JmcsApplicationSetup.arguments != null) {
                    if (logger.isLoggable(Level.INFO)) {
                        logger.info("onSetUpOnce : using arguments      : " + Arrays.toString(JmcsApplicationSetup.arguments));
                    }

                    application(JmcsApplicationSetup.applicationClass).withArgs(JmcsApplicationSetup.arguments).start();

                } else {

                    application(JmcsApplicationSetup.applicationClass).start();
                }

                // Waits for slapshscreen to hide ...
                pause(new Condition("AppReady") {
                    /**
                     * Checks if the condition has been satisfied.
                     * @return <code>true</code> if the condition has been satisfied, otherwise <code>false</code>.
                     */
                    @Override
                    public boolean test() {
                        return App.isReady();
                    }
                });

                pauseMedium();

                // To be sure that application frame is available:
                App.getFrame();
            }

            if (logger.isLoggable(Level.INFO)) {
                logger.info("onSetUpOnce : started application = " + App.getSharedInstance());
            }

            if (App.getSharedInstance() == null) {
                throw new RuntimeException("unable to start application : " + JmcsApplicationSetup.applicationClass);
            }
        }
    }

    /**
     * Free other resources like the Swing application.
     * This method is called <strong>after</strong> executing <code>{@link #tearDownOnce()}</code>.
     */
    @AfterClass
    public static void onTearDownOnce() {
        final App app = App.getSharedInstance();
        if (app != null) {
            if (logger.isLoggable(Level.INFO)) {
                logger.info("onTearDownOnce : exit application = " + app);
            }

            app.cleanup();
        }
    }

    /**
     * Return the application
     * @return application
     */
    protected static App getApplication() {
        return App.getSharedInstance();
    }

    /**
     * Define the window fixture before each JUnit Test method.
     */
    @Override
    protected void onSetUp() {
        listener = EmergencyAbortListener.registerInToolkit();

        window = getFrame(App.getFrame());
    }

    /**
     * Clean up resources of the window fixture after each JUnit Test method.
     */
    @Override
    protected void onTearDown() {
        listener.unregister();

        // robot is already cleaned up in FestSwingCustomTestCaseTemplate
    }


    /*
     --- Utility methods  ---------------------------------------------------------
     */
    /**
     * Return a frame fixture given its title
     * @param title frame title
     * @return frame fixture
     */
    protected final FrameFixture getFrame(final String title) {

        // IMPORTANT: note the call to 'robot()'
        // we must use the Robot from FestSwingCustomTestCaseTemplate

        final FrameMatcher matcher = FrameMatcher.withTitle(title).andShowing();

        final String description = "frame to be found using matcher " + matcher;

        final ComponentFoundCondition condition = new ComponentFoundCondition(description, robot().finder(), matcher);

        pause(condition, LONG_DELAY);

        final FrameFixture frameFixture = new FrameFixture(robot(), (Frame) condition.found());

        // shows the frame to test
        frameFixture.show();
        frameFixture.moveToFront();

        return frameFixture;
    }

    /**
     * Return a frame fixture given its name
     * @param frame frame to hook
     * @return frame fixture
     */
    protected final FrameFixture getFrame(final Frame frame) {
        // IMPORTANT: note the call to 'robot()'
        // we must use the Robot from FestSwingCustomTestCaseTemplate
        final FrameFixture frameFixture = new FrameFixture(robot(), frame);

        // shows the frame to test
        frameFixture.show();
        frameFixture.moveToFront();

        return frameFixture;
    }

    /**
     * Close File overwrite confirm dialog clicking on "Replace" button
     */
    protected final void confirmDialogFileOverwrite() {
        try {
            // if file already exists, a confirm message appears :
            final JOptionPaneFixture optionPane = window.optionPane();

            if (optionPane != null) {
                // confirm file overwrite :
                optionPane.buttonWithText("Replace").click();
            }

        } catch (RuntimeException re) {
            // happens when the confirm message does not occur :
            if (logger.isLoggable(Level.FINE)) {
                logger.log(Level.FINE, "lookup failure : ", re);
            }
        }
    }

    /**
     * Close Save confirm dialog clicking on "Don't Save" button
     */
    protected final void confirmDialogDontSave() {
        // close confirm dialog :
        window.optionPane().buttonWithText("Don't Save").click();
    }

    /**
     * Close any option pane
     * @return true if a message was closed
     */
    protected final boolean closeMessage() {
        try {
            // if a message appears :
            final JOptionPaneFixture optionPane = window.optionPane();

            if (optionPane != null) {
                // click OK :
                optionPane.okButton().click();

                return true;
            }

        } catch (RuntimeException re) {
            // happens when the confirm message does not occur :
            if (logger.isLoggable(Level.FINE)) {
                logger.log(Level.FINE, "lookup failure : ", re);
            }
        }
        return false;
    }

    /**
     * Capture a screenshot of the application window, crop it and save it using the given file name
     * @param fileName the file name (including the png extension)
     * @param x the X coordinate of the upper-left corner of the
     *          specified rectangular region
     * @param y the Y coordinate of the upper-left corner of the
     *          specified rectangular region
     * @param w the width of the specified rectangular region (<=0 indicates to use the width of screenshot image)
     * @param h the height of the specified rectangular region (<=0 indicates to use the height of screenshot image)
     */
    protected final void saveCroppedScreenshotOf(final String fileName, final int x, final int y, final int w, final int h) {
        final BufferedImage image = takeScreenshotOf(window);

        final int width = (w <= 0) ? image.getWidth() : w;
        final int height = (h <= 0) ? image.getHeight() : h;

        final BufferedImage croppedImage = image.getSubimage(x, y, width, height);

        saveImage(croppedImage, fileName);
    }
}
