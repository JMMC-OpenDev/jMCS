/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: MainMenuBar.java,v 1.50 2011-04-07 10:09:24 bourgesl Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * Revision 1.49  2011/04/06 15:41:41  bourgesl
 * better exception handling
 * minor typo changes
 *
 * Revision 1.48  2011/04/05 15:20:52  bourgesl
 * use Introspection to change LAF
 *
 * Revision 1.47  2011/03/14 16:43:47  bourgesl
 * always show the Interop Menu
 *
 * Revision 1.46  2011/03/02 09:03:34  bourgesl
 * Interop menu is now ready for production
 *
 * Revision 1.45  2011/02/16 14:34:44  bourgesl
 * added Look & Feel menu only shown if the system property jmcs.laf.menu =true
 *
 * Revision 1.44  2010/11/09 12:43:57  mella
 * Add interop menu for Beta and Alpha releases
 *
 * Revision 1.43  2010/10/06 09:18:07  mella
 * Build interop menu with jsamp entry menu comming from SampManager
 *
 * Revision 1.42  2010/10/05 14:52:31  bourgesl
 * removed SampException in several method signatures
 *
 * Revision 1.41  2010/10/05 12:21:43  bourgesl
 * fixed samp exception handling
 *
 * Revision 1.40  2010/10/05 11:58:41  bourgesl
 * use internal logger
 *
 * Revision 1.39  2010/10/05 07:40:45  bourgesl
 * InteropMenu ONLY available for BETA versions (instable)
 *
 * Revision 1.38  2010/10/04 23:36:03  lafrasse
 * Added "Interop" menu handling.
 *
 * Revision 1.37  2010/09/25 12:17:10  bourgesl
 * restored imports (SAMP)
 *
 * Revision 1.36  2010/09/24 16:17:13  bourgesl
 * removed SampManager import to let the classloader open this class (JNLP)
 *
 * Revision 1.35  2010/09/24 16:05:51  bourgesl
 * removed imports for astrogrid to let the classloader open this class
 *
 * Revision 1.34  2010/09/24 12:05:15  lafrasse
 * Added preliminary support for the "Interop" menu (only in beta mode for the time being).
 *
 * Revision 1.33  2010/01/14 13:03:04  bourgesl
 * use Logger.isLoggable to avoid a lot of string.concat()
 *
 * Revision 1.32  2009/11/03 10:17:45  lafrasse
 * Code and documentation refinments.
 *
 * Revision 1.31  2009/11/02 16:28:51  lafrasse
 * Added support for RegisteredPreferencedBooleanAction in radio-button menu items.
 *
 * Revision 1.30  2009/11/02 15:03:32  lafrasse
 * Jalopization.
 *
 * Revision 1.29  2009/11/02 15:00:58  lafrasse
 * Added support for radio-button like menu items.
 *
 * Revision 1.28  2009/08/26 07:26:18  mella
 * removed unused imports
 *
 * Revision 1.27  2009/05/13 09:24:25  lafrasse
 * Added a generic "Hot News (RSS Feed)" Help menu item.
 *
 * Revision 1.26  2009/04/16 15:44:51  lafrasse
 * Jalopization.
 *
 * Revision 1.25  2009/04/14 13:12:04  mella
 * Fix code that didn't retrieve icon for non MCSAction
 *
 * Revision 1.24  2008/10/17 10:41:54  lafrasse
 * Added FAQ handling.
 *
 * Revision 1.23  2008/10/16 14:19:34  mella
 * Use new help view handling
 *
 * Revision 1.22  2008/10/16 13:59:19  lafrasse
 * Re-ordered Help menu.
 *
 * Revision 1.21  2008/10/16 07:54:07  mella
 * Clean and improve createComponent method
 *
 * Revision 1.20  2008/10/15 13:49:54  mella
 * Add default release and acknowledgment menu items
 *
 * Revision 1.19  2008/09/22 16:51:42  lafrasse
 * Enforced Icon attribute retrieval.
 *
 * Revision 1.18  2008/09/22 16:16:29  lafrasse
 * Enforced 'Preferences.." menu creation even if no action is registered as the
 * 'Preference' one.
 *
 * Revision 1.17  2008/09/18 20:59:52  lafrasse
 * Added support of RegisteredPreferencedBooleanAction.
 *
 * Revision 1.16  2008/09/05 16:19:59  lafrasse
 * Added preference entry in edit menu while not running under Mac OS X.
 *
 * Revision 1.15  2008/09/04 16:02:12  lafrasse
 * Moved to new ActionRegistrar infrastructure.
 * Code, documentation and log enhancement.
 *
 * Revision 1.14  2008/06/23 07:47:32  bcolucci
 * Use SystemUtils class from apache common lang library in order
 * to know is we are running on a MAC OS X or not instead of
 * use os.name property.
 *
 * Revision 1.13  2008/06/20 08:41:45  bcolucci
 * Remove unused imports and add class comments.
 *
 * Revision 1.12  2008/06/19 14:35:07  bcolucci
 * If you are on MAC OS X and if there is not one menuitem at least for
 * "File", you don't create the "File" menu. On Windows, we always create
 * it because there is always "Exit" menuitem.
 *
 * Revision 1.11  2008/06/19 13:32:33  bcolucci
 * Fix : generate default menus even if there is no menubar element
 * in the ApplicationData.xml
 *
 * Revision 1.10  2008/06/19 13:11:47  bcolucci
 * Modify the way to generate the menubar. Use
 * circular references into XSD schema.
 *
 * Revision 1.9  2008/06/17 12:36:04  bcolucci
 * Merge fix about "null-pointer exceptions in case no menu is defined in the XML file".
 *
 * Revision 1.8  2008/06/17 11:59:43  lafrasse
 * Hnadled 2 null-pointer exceptions in case no menu is defined in the XML file.
 *
 * Revision 1.7  2008/06/17 11:16:04  bcolucci
 * Fix some comments.
 *
 * Revision 1.6  2008/06/13 08:16:10  bcolucci
 * Add possibility to specify icon and tooltip and keep action properties.
 * Improve menus generation and use OSXAdapter.
 *
 * Revision 1.5  2008/06/12 12:34:52  bcolucci
 * Fix the order of menu items thanks to a vector which keep
 * the order from XML file.
 * Begin to implement OSXAdapter.
 *
 * Revision 1.4  2008/06/12 11:34:25  bcolucci
 * Extend the class from JMenuBar and remove static context.
 *
 * Revision 1.3  2008/06/12 09:31:53  bcolucci
 * Truly added support for complete menubar creation from XML file (last commit was about first introspection version).
 *
 * Revision 1.2  2008/06/12 07:40:54  bcolucci
 * Create functions to generate File, Edit, [Other] and Help menus with
 * some variations when we are running the application on a MAC OS X.
 *
 * Revision 1.1  2008/06/10 12:22:37  bcolucci
 * Created.
 *
 ******************************************************************************/
package fr.jmmc.mcs.gui;

import fr.jmmc.mcs.interop.SampCapabilityAction;
import fr.jmmc.mcs.interop.SampManager;
import fr.jmmc.mcs.util.ActionRegistrar;
import fr.jmmc.mcs.util.RegisteredPreferencedBooleanAction;
import fr.jmmc.mcs.util.Urls;

import org.apache.commons.lang.SystemUtils;

import java.awt.Component;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


import java.net.URL;

import java.util.Hashtable;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.JSeparator;
import javax.swing.KeyStroke;
import javax.swing.LookAndFeel;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.text.DefaultEditorKit;

/**
 * This class which extends from JMenuBar, generates all menus from the
 * <b>ApplicationData.xml</b> file.
 *
 * In all cases, it generates default menus.
 *
 * To access to the XML informations, this class uses <b>ApplicationDataModel</b>
 * class. It's a class which has got getters in order to do that and which has
 * been written to abstract the way to access to these informations.
 */
public class MainMenuBar extends JMenuBar
{

    /** default serial UID for Serializable interface */
    private static final long serialVersionUID = 1;
    /**
     * This System property controls the Look & Feel menu (useful for debugging purposes).
     * To show this menu, add "-Djmcs.laf.menu=true" to your JVM options.
     */
    public final static String SYSTEM_PROPERTY_LAF_MENU = "jmcs.laf.menu";
    /** Logger */
    private static final Logger _logger = Logger.getLogger("fr.jmmc.mcs.gui.MainMenuBar");
    /** Store wether we are running under Mac OS X or not */
    private final boolean _isRunningUnderMacOSX =  SystemUtils.IS_OS_MAC_OSX;
    /** Table where are stocked the menus */
    private final Hashtable<String, JMenu> _menusTable;
    /** Store a proxy to the shared ActionRegistrar facility */
    private final ActionRegistrar _registrar;
    /** Store a proxy to the parent frame */
    private final JFrame _frame;

    /**
     * Instantiate all defaults menus, plus application-specific ones.
     *
     * @param frame the JFrame against which the menubar is linked.
     */
    public MainMenuBar(final JFrame frame)
    {
        // Get the parent frame
        _frame = frame;

        // Member initilization
        _menusTable = new Hashtable<String, JMenu>();
        _registrar = ActionRegistrar.getInstance();

        // Get the application data model
        ApplicationDataModel applicationDataModel = App.getSharedApplicationDataModel();

        // Contains the name of the others menus
        Vector<String> otherMenus = new Vector<String>();

        // If it's null, we exit
        if (applicationDataModel != null) {
            // Get the menubar element from XML
            fr.jmmc.mcs.gui.castor.Menubar menuBar = applicationDataModel.getMenubar();

            // If it's null, we exit
            if (menuBar != null) {
                // Get the menu elements from menubar
                fr.jmmc.mcs.gui.castor.Menu[] menus = menuBar.getMenu();

                // If it's null, we exit
                if (menus != null) {
                    for (fr.jmmc.mcs.gui.castor.Menu menu : menus) {
                        // Get menu label
                        String currentMenuLabel = menu.getLabel();

                        if (_logger.isLoggable(Level.FINE)) {
                            _logger.fine("Make '" + currentMenuLabel + "' menu.");
                        }

                        // Keep it if it's an other menu
                        if (!currentMenuLabel.equals("File")
                                && !currentMenuLabel.equals("Edit")
                                && !currentMenuLabel.equals("Interop")
                                && !currentMenuLabel.equals("Help")) {
                            otherMenus.add(currentMenuLabel);

                            if (_logger.isLoggable(Level.FINE)) {
                                _logger.fine("Add '" + currentMenuLabel
                                        + "' to other menus vector.");
                            }
                        }

                        // Get the component according to the castor menu object
                        JMenu completeMenu = (JMenu) recursiveParser(menu,
                                null, true, null); // It is a JMenu, has no button group

                        // Put it in the menu table
                        _menusTable.put(currentMenuLabel, completeMenu);

                        if (_logger.isLoggable(Level.FINE)) {
                            _logger.fine("Put '" + completeMenu.getName()
                                    + "' into the menus table.");
                        }
                    }
                }
            }
        }

        createFileMenu();

        createEditMenu();

        // Create others (application-specifics) menus
        for (String menuLabel : otherMenus) {
            add(_menusTable.get(menuLabel));

            if (_logger.isLoggable(Level.FINE)) {
                _logger.fine("Add '" + menuLabel + "' menu into the menubar.");
            }
        }

        // Create Interop menu :
        createInteropMenu();

        final String lafMenu = System.getProperty(SYSTEM_PROPERTY_LAF_MENU);
        if (lafMenu != null && "true".equals(lafMenu)) {
            createLAFMenu();
        }

        createHelpMenu();
    }

    /** Create the 'File' menu. */
    private void createFileMenu()
    {
        // Create menu
        JMenu fileMenu = new JMenu("File");

        // There is one menu item at least
        boolean haveMenu = false;

        // Get file menu from table
        JMenu file = _menusTable.get("File");

        if (file != null) {
            Component[] components = file.getMenuComponents();

            if (components.length > 0) {
                haveMenu = true;

                // Add each component
                for (Component currentComponent : components) {
                    fileMenu.add(currentComponent);
                }

                if (!_isRunningUnderMacOSX) {
                    fileMenu.add(new JSeparator());
                }
            }
        }

        if (!_isRunningUnderMacOSX) {
            fileMenu.add(_registrar.getQuitAction());
            haveMenu = true;
        }

        // Add menu to menubar if there is a menuitem at least
        if (haveMenu) {
            add(fileMenu);
            _logger.fine("Add 'File' menu into the menubar.");
        }
    }

    /** Create the 'Edit' menu. */
    private void createEditMenu()
    {
        // Create menu
        JMenu editMenu = new JMenu("Edit");

        // Add cut action
        Action cutAction = new DefaultEditorKit.CutAction();
        cutAction.putValue(Action.NAME, "Cut");
        cutAction.putValue(Action.ACCELERATOR_KEY,
                KeyStroke.getKeyStroke(getPrefixKey() + "X"));
        editMenu.add(cutAction);

        // Add copy action
        Action copyAction = new DefaultEditorKit.CopyAction();
        copyAction.putValue(Action.NAME, "Copy");
        copyAction.putValue(Action.ACCELERATOR_KEY,
                KeyStroke.getKeyStroke(getPrefixKey() + "C"));
        editMenu.add(copyAction);

        // Add paste action
        Action pasteAction = new DefaultEditorKit.PasteAction();
        pasteAction.putValue(Action.NAME, "Paste");
        pasteAction.putValue(Action.ACCELERATOR_KEY,
                KeyStroke.getKeyStroke(getPrefixKey() + "V"));
        editMenu.add(pasteAction);

        // Get edit menu from table
        JMenu edit = _menusTable.get("Edit");

        if (edit != null) {
            Component[] components = edit.getMenuComponents();

            if (components.length > 0) {
                editMenu.add(new JSeparator());

                // Add each component
                for (Component currentComponent : components) {
                    editMenu.add(currentComponent);
                }
            }
        }

        if (!_isRunningUnderMacOSX) {
            Action preferenceAction = _registrar.getPreferenceAction();

            if (preferenceAction != null) {
                editMenu.add(new JSeparator());

                editMenu.add(preferenceAction);
            }
        }

        // Add menu to menubar
        add(editMenu);
        _logger.fine("Add 'Edit' menu into the menubar.");
    }

    /** Create the 'Interop' menu. */
    private void createInteropMenu()
    {
        // Create menu
        JMenu interopMenu = new JMenu("Interop");

        // Add auto-toggling menu entry to regiter/unregister to/from hub
        interopMenu.add(SampManager.createToggleRegisterAction());

        // To visually monitor hub activity
        interopMenu.add(SampManager.createShowMonitorAction());

        // Get interop menu from table
        JMenu interop = _menusTable.get("Interop");

        // Add app-specific menu entries (if any)
        if (interop != null) {
            Component[] components = interop.getMenuComponents();

            if (components.length > 0) {
                interopMenu.add(new JSeparator());

                // Add each component
                for (Component currentComponent : components) {
                    // Get menuitem initialised from ApplicationData
                    JMenuItem menuItem = (JMenuItem) currentComponent;
                    // @TODO : cast SAMP-flagged menus only !
                    SampCapabilityAction action = (SampCapabilityAction) (menuItem.getAction());
                    // get previously created menu by samp action
                    JMenu menu = SampManager.getMenu(action);
                    // set text coming from applicationData.xml
                    menu.setText(menuItem.getText());

                    interopMenu.add(menu);
                }
            }
        }

        // Add menu to menubar
        add(interopMenu);

        // Keep this menu invisible until (at least) one capability is registered
        SampManager.hookMenu(interopMenu);
        _logger.fine("Add 'Interop' into the menubar.");
    }

    /** Create the 'Look & Feel' menu. */
    private void createLAFMenu()
    {
        // Create menu
        final JMenu lafMenu = new JMenu("Look & Feel");

        final ActionListener lafActionListener = new ActionListener()
        {

            /**
             * Invoked when an action occurs.
             */
            public void actionPerformed(final ActionEvent ae)
            {
                final String className = ae.getActionCommand();
                final String currentClassName = UIManager.getLookAndFeel().getClass().getName();

                if (!className.equals(currentClassName)) {
                    try {
                        if (_logger.isLoggable(Level.INFO)) {
                            _logger.info("use Look and Feel : " + className);
                        }

                        final LookAndFeel newLaf = (LookAndFeel) Introspection.getInstance(className);

                        UIManager.setLookAndFeel(newLaf);

                        final Frame mainFrame = App.getFrame();

                        SwingUtilities.updateComponentTreeUI(mainFrame);
                        mainFrame.pack();

                    } catch (UnsupportedLookAndFeelException ulafe) {
                        throw new RuntimeException("Change LAF failed : " + className, ulafe);
                    }
                }
            }
        };

        JMenuItem menuItem;

        for (UIManager.LookAndFeelInfo lookAndFeelInfo : UIManager.getInstalledLookAndFeels()) {

            menuItem = new JMenuItem(lookAndFeelInfo.getName());
            menuItem.setActionCommand(lookAndFeelInfo.getClassName());
            menuItem.addActionListener(lafActionListener);

            lafMenu.add(menuItem);
        }

        add(lafMenu);
    }

    /** Create the 'Help' menu. */
    private void createHelpMenu()
    {
        // Create menu
        JMenu helpMenu = new JMenu("Help");

        // Add helpview action
        helpMenu.add(App.showHelpAction());

        helpMenu.add(new JSeparator());

        // Add feedback action
        helpMenu.add(App.feedbackReportAction());

        // Get help menu from table
        JMenu help = _menusTable.get("Help");

        if (help != null) {
            Component[] components = help.getMenuComponents();

            if (components.length > 0) {
                helpMenu.add(new JSeparator());

                // Add each component
                for (Component currentComponent : components) {
                    helpMenu.add(currentComponent);
                }
            }
        }

        helpMenu.add(new JSeparator());

        // Add acknowledgement action
        helpMenu.add(App.acknowledgementAction());

        helpMenu.add(new JSeparator());

        // Add hot news action
        helpMenu.add(App.showHotNewsAction());

        // Add release action
        helpMenu.add(App.showReleaseAction());

        // Add Faq action
        helpMenu.add(App.showFaqAction());

        if (!_isRunningUnderMacOSX) {
            helpMenu.add(new JSeparator());

            // Add aboutbox action
            helpMenu.add(App.aboutBoxAction());
        }

        // Add menu to menubar
        add(helpMenu);
        _logger.fine("Add 'Help' into the menubar.");
    }

    /**
     * Recursively instantiate each application-specific menu element.
     *
     * @param menu castor Menu object to instantiate.
     * @param parent parent component, null for the root element.
     * @param createMenu create a JMenu if true, specific menu items otherwise.
     * @param buttonGroup a ButtonGroup in which radio-buttons should be added, null
     * otherwise.
     *
     * @return the instantiated JComponent according to the XML menu hierarchy.
     */
    private JComponent recursiveParser(fr.jmmc.mcs.gui.castor.Menu menu,
            JComponent parent, boolean createMenu, ButtonGroup buttonGroup)
    {
        // Create the current component
        JComponent component = createComponent(menu, createMenu, buttonGroup);

        // Add it to the parent if any
        if (parent != null) {
            parent.add(component);

            if (_logger.isLoggable(Level.FINE)) {
                _logger.fine("'" + component.getName() + "' linked to '"
                        + parent.getName() + "'.");
            }
        }

        // Get submenus
        fr.jmmc.mcs.gui.castor.Menu[] submenus = menu.getMenu();
        ButtonGroup group = null;

        if (submenus != null) {
            if (menu.getRadiogroup() != null) {
                group = new ButtonGroup();
            }

            for (fr.jmmc.mcs.gui.castor.Menu submenu : submenus) {
                // The submenu will be a jmenu?
                boolean isMenu = ((submenu.getMenu()).length > 0);

                // Recursive call on submenu
                recursiveParser(submenu, component, isMenu, group);
            }
        }

        // Return the hightest component
        return component;
    }

    /**
     * Create the component according to the castor Menu object.
     *
     * @param menu castor Menu object to instantiate.
     * @param isMenu create a JMenu if true, specific menu items otherwise.
     * @param buttonGroup used to only have a single menu item selected at any
     * time, if not null.
     *
     * @return the instantiated JComponent according to the XML description.
     */
    private JComponent createComponent(fr.jmmc.mcs.gui.castor.Menu menu,
            boolean isMenu, ButtonGroup buttonGroup)
    {
        // Component to create
        JMenuItem item = null;

        // Attributes
        boolean hasLabel = (menu.getLabel() != null);
        boolean hasClasspath = (menu.getClasspath() != null);
        boolean hasAction = (menu.getAction() != null);
        boolean isCheckbox = (menu.getCheckbox() != null);

        // flag new component as separator or not
        boolean isSeparator = !(isMenu || hasClasspath || hasAction);

        // Is it a separator?
        if (isSeparator) {
            _logger.fine("Component is a separator.");

            return new JSeparator();
        }

        // Get action
        AbstractAction action = _registrar.get(menu.getClasspath(),
                menu.getAction());

        // Set attributes
        setAttributes(menu, action);

        // Is it a checkbox ?
        if (isCheckbox) {
            _logger.fine("Component is a JCheckBoxMenuItem.");
            item = new JCheckBoxMenuItem(action);

            if (action instanceof RegisteredPreferencedBooleanAction) {
                _logger.fine(
                        "Component is bound to a RegisteredPreferencedBooleanAction.");
                ((RegisteredPreferencedBooleanAction) action).addBoundButton((JCheckBoxMenuItem) item);
            }

            if (isMenu) {
                _logger.warning(
                        "The current menuitem is a checkbox AND a sub-menu, which is impossible !!!");

                return null;
            }
        } else if (buttonGroup != null) // Is it a radio-button ?
        {
            _logger.fine("Component is a JRadioButtonMenuItem.");
            item = new JRadioButtonMenuItem(action);

            // Put the radiobutton menu item in a the ButtonGroup to only have a single one selected at any time.
            buttonGroup.add((JRadioButtonMenuItem) item);

            if (action instanceof RegisteredPreferencedBooleanAction) {
                _logger.fine(
                        "Component is bound to a RegisteredPreferencedBooleanAction.");
                ((RegisteredPreferencedBooleanAction) action).addBoundButton((JRadioButtonMenuItem) item);
            }

            if (isMenu) {
                _logger.warning(
                        "The current menuitem is a radiobutton AND a sub-menu, which is impossible !!!");

                return null;
            }
        } else if (isMenu) // is it a menu containig other menu item ?
        {
            _logger.fine("Component is a JMenu.");
            item = new JMenu(action);
        } else // It is a menu item.
        {
            _logger.fine("Component is a JMenuItem.");
            item = new JMenuItem(action);
        }

        // If the menu object has its own name
        if (menu.getLabel() != null) {
            // Superseed the name of the item associated action
            item.setText(menu.getLabel());
        }

        return item;
    }

    /**
     * Set menu attributes (all but the label).
     *
     * @param menu castor Menu object to get data from.
     * @param action Action instance to modify.
     */
    private void setAttributes(fr.jmmc.mcs.gui.castor.Menu menu, Action action)
    {
        if ((menu == null) || (action == null)) {
            return;
        }

        // Set action accelerator
        String accelerator = menu.getAccelerator();

        if (accelerator != null) {
            String keyStrokeString = getPrefixKey() + accelerator;
            action.putValue(Action.ACCELERATOR_KEY,
                    KeyStroke.getKeyStroke(keyStrokeString));
        }

        // Set action tooltip
        String xmlTooltip = menu.getDescription();
        String actionTooltip = (String) action.getValue(Action.SHORT_DESCRIPTION);

        if ((actionTooltip == null) && (xmlTooltip != null)) {
            action.putValue(Action.SHORT_DESCRIPTION, xmlTooltip);
        }

        // Set action icon
        String icon = menu.getIcon();

        if (icon != null) {
            // Open XML file at path
            URL iconURL = getClass().getResource(icon);

            if (iconURL != null) {
                action.putValue(Action.SMALL_ICON,
                        new ImageIcon(Urls.fixJarURL(iconURL)));
            } else {
                if (_logger.isLoggable(Level.WARNING)) {
                    _logger.warning("Can't find iconUrl : " + icon);
                }
            }
        }

        if (_logger.isLoggable(Level.FINE)) {
            _logger.fine("Attributes set on '" + menu.getLabel() + "'.");
        }
    }

    /**
     * Return prefix key for accelerator
     *
     * @return prefix key
     */
    private String getPrefixKey()
    {
        return (_isRunningUnderMacOSX) ? "meta " : "ctrl ";
    }
}
/*___oOo___*/