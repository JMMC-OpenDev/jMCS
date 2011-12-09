/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.gui;

import fr.jmmc.jmcs.data.ApplicationDataModel;
import fr.jmmc.jmcs.network.BrowserLauncher;
import fr.jmmc.jmcs.App;
import fr.jmmc.jmcs.util.ImageUtils;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

import java.util.List;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JEditorPane;
import javax.swing.JLabel;
import javax.swing.JRootPane;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.KeyStroke;
import javax.swing.SwingConstants;
import javax.swing.event.HyperlinkEvent;
import javax.swing.event.HyperlinkListener;

/**
 * This class opens a new About window. Informations of this window
 * have been taken from the XML file called <b>ApplicationData.xml</b>.
 * This file is saved into the application module which extends <b>App</b>
 * class. There is a default XML file which having the same name and which is
 * saved into the <b>App</b> module in order to avoid important bugs.
 *
 * To access to the XML informations, this class uses
 * <b>ApplicationDataModel</b> class. It's a class which has got getters
 * in order to do that and which has been written to abstract the way
 * to access to these informations.
 *
 * @author Brice COLUCCI, Sylvain LAFRASSE, Guillaume MELLA.
 */
public class AboutBox extends JDialog implements HyperlinkListener {

    /** Logger */
    private static final Logger _logger = LoggerFactory.getLogger(AboutBox.class.getName());
    /** default serial UID for Serializable interface */
    private static final long serialVersionUID = 1L;
    /** Model of the about box */
    private ApplicationDataModel _applicationDataModel = null;
    /** Logo label */
    private JLabel _logoLabel = new JLabel();
    /** Copyright label */
    private JLabel _copyrightLabel = new JLabel();
    /** Container of the text area */
    private JScrollPane _descriptionScrollPane = new JScrollPane();
    /** Text area (HTML) */
    private JEditorPane _descriptionEditorPane = new JEditorPane();
    /** Label of compilation info (date and compiler) */
    private JLabel _compilationInfoLabel = new JLabel();
    /** Link label */
    private JEditorPane _linkLabel = new JEditorPane();
    /** Label of program name */
    private JLabel _programNameLabel = new JLabel();
    /** Label of program version */
    private JLabel _programVersionLabel = new JLabel();
    /** Help : JFrame design
     *
     *  +-[contentPane()]----------------------------------------------------+
     *  |  _logoLabel                                                        |
     *  +--------------------------------------------------------------------+
     *  |  +-[_descriptionSplit]------------------------------------------+  |
     *  |  |  +-[_upSpaceSplit]----------------------------------------+  |  |
     *  |  |  |  space                                                 |  |  |
     *  |  |  +--------------------------------------------------------+  |  |
     *  |  |  |  +-[_downSpaceSplit]--------------------------------+  |  |  |
     *  |  |  |  |  +-[_compilationInfoSplit]--------------------+  |  |  |  |
     *  |  |  |  |  |  +-[_linkAndProgramInfoSplit]-----------+  |  |  |  |  |
     *  |  |  |  |  |  | +-[_ProgramNameAndVersionSplit]---+  |  |  |  |  |  |
     *  |  |  |  |  |  | | _programNameLabel               |  |  |  |  |  |  |
     *  |  |  |  |  |  | +---------------------------------+  |  |  |  |  |  |
     *  |  |  |  |  |  | | _programVersionLabel            |  |  |  |  |  |  |
     *  |  |  |  |  |  | +---------------------------------+  |  |  |  |  |  |
     *  |  |  |  |  |  +--------------------------------------+  |  |  |  |  |
     *  |  |  |  |  |  | _linkLabel                           |  |  |  |  |  |
     *  |  |  |  |  |  +--------------------------------------+  |  |  |  |  |
     *  |  |  |  |  +--------------------------------------------+  |  |  |  |
     *  |  |  |  |  |  _compilationInfoLabel                     |  |  |  |  |
     *  |  |  |  |  +--------------------------------------------+  |  |  |  |
     *  |  |  |  +--------------------------------------------------+  |  |  |
     *  |  |  |  |  space                                           |  |  |  |
     *  |  |  |  +--------------------------------------------------+  |  |  |
     *  |  |  +--------------------------------------------------------+  |  |
     *  |  +--------------------------------------------------------------+  |
     *  |  |  _descriptionScrollPane                                      |  |
     *  |  +--------------------------------------------------------------+  |
     *  +--------------------------------------------------------------------+
     *  |  _copyrightLabel                                                   |
     *  +--------------------------------------------------------------------+
     */
    /** Split with program name and version */
    private JSplitPane _programNameAndVersionSplit = new JSplitPane();
    /** Split with _link and program info */
    private JSplitPane _linkAndProgramInfoSplit = new JSplitPane();
    /** Split with (link and program split) and compilation */
    private JSplitPane _compilationInfoSplit = new JSplitPane();
    /** Split with ((link and program split) and compilation) and space */
    private JSplitPane _downSpaceSplit = new JSplitPane();
    /** Split with (((link and program split) and compilation) and space) and space */
    private JSplitPane _upSpaceSplit = new JSplitPane();
    /** Split with ((((link and program split) and compilation)
     * and space) and space) and text area container
     */
    private JSplitPane _descriptionSplit = new JSplitPane();

    /**
     * Load the application information from ApplicationDataModel and display
     * its content in the window.
     */
    public AboutBox() {
        this(null, false);
    }

    /**
     * Load the application information from ApplicationDataModel and display
     * its content in the window.
     * Set the parent frame.
     *
     * @param frame parent frame
     */
    public AboutBox(Frame frame) {
        this(frame, false);
    }

    /**
     * Load the application information from ApplicationDataModel and display
     * its content in the window.
     * Set the parent frame and specify if this dialog is modal or not.
     *
     * @param frame parent frame
     * @param modal if true, this dialog is modal
     */
    public AboutBox(Frame frame, boolean modal) {
        super(frame, modal);

        // Get application data model
        ApplicationDataModel applicationDataModel = App.getSharedApplicationDataModel();

        if (applicationDataModel != null) {
            _applicationDataModel = applicationDataModel;

            // Launch all methods which set properties of components
            setAllProperties();

            // Show window
            setVisible(true);
        }
    }

    /**
     * Handle window closing when using either Escape or ctrl-W keys.
     */
    protected JRootPane createRootPane() {

        JRootPane rootPane = new JRootPane();

        // Trap Escape key
        KeyStroke escapeStroke = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0);
        // Trap command-W key
        KeyStroke metaWStroke = KeyStroke.getKeyStroke(MainMenuBar.getSystemCommandKey() + "W");

        // Close window on either strike
        ActionListener actionListener = new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                _logger.debug("Hiding about box on keyboard shortcut.");
                setVisible(false);
            }
        };
        rootPane.registerKeyboardAction(actionListener, escapeStroke, JComponent.WHEN_IN_FOCUSED_WINDOW);
        rootPane.registerKeyboardAction(actionListener, metaWStroke, JComponent.WHEN_IN_FOCUSED_WINDOW);
        return rootPane;
    }

    /**
     * Instantiate and draw all the GUI.
     */
    private void setAllProperties() {
        // Widgets Setup
        setupLogo();
        setupProgramNameLabel();
        setupProgramVersionLabel();
        setupLinkLabel();
        //setupCompilationInfoLabel();
        setupDescriptionTextarea();
        setupCopyrightLabel();

        // Layout Setup
        setTextareaSplitProperties();
        setUpSpaceSplitProperties();
        setDownSpaceSplitProperties();
        setCompilationInfoSplitProperties();
        setLinkAndProgramSplitProperties();
        setProgramNameAndVersionSplitProperties();

        // Window setup
        setupWindow();

        _logger.debug("All the properties of the frame have been initialized");
    }

    /** Sets logo label properties */
    private void setupLogo() {
        // Create the Icon with the company image from ApplicationData.xml
        String logoURL = _applicationDataModel.getCompanyLogoResourcePath();
        if (logoURL != null) {
            // Get and scale image
            ImageIcon logo = new ImageIcon(getClass().getResource(logoURL));
            logo = ImageUtils.getScaledImageIcon(logo, 81, 300);
            _logoLabel.setIcon(logo);
            _logoLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 10));

            // Center label content
            _logoLabel.setHorizontalAlignment(SwingConstants.CENTER);
            _logoLabel.setOpaque(false);

            _logger.debug("All the logo label properties have been initialized");

            // Launch the default browser with the given link
            _logoLabel.addMouseListener(new MouseAdapter() {

                @Override
                public void mouseClicked(MouseEvent evt) {
                    String mainWebPageURL = _applicationDataModel.getMainWebPageURL();

                    // Open the url in web browser
                    BrowserLauncher.openURL(mainWebPageURL);
                }
            });

            _logger.debug("Mouse click event placed on logo label");

            // Show hand cursor when mouse is moving on logo
            _logoLabel.addMouseMotionListener(new MouseMotionAdapter() {

                @Override
                public void mouseMoved(MouseEvent evt) {
                    _logoLabel.setCursor(Cursor.getPredefinedCursor(
                            Cursor.HAND_CURSOR));
                }
            });

            _logger.debug("Mouse move event placed on logo label");
        } else {
            _logger.warn("No company logo found");
        }
    }

    /** Sets copyright label properties */
    private void setupCopyrightLabel() {
        _copyrightLabel.setHorizontalAlignment(SwingConstants.CENTER);
        _copyrightLabel.setText(_applicationDataModel.getCopyrightValue());

        _logger.debug("All the copyright label properties have been initialized");
    }

    /** Sets text area (SWING HTML) properties */
    private void setupDescriptionTextarea() {
        // Set properties
        _descriptionEditorPane.setEditable(false);
        _descriptionEditorPane.setMargin(new Insets(5, 5, 5, 5));
        _descriptionEditorPane.setContentType("text/html");
        _descriptionEditorPane.addHyperlinkListener(this);

        // The textarea should have the same width than the logo
        Dimension textareaDimension = new Dimension(300, 170);
        _descriptionEditorPane.setPreferredSize(textareaDimension);
        _logger.debug("All the textarea properties have been initialized");

        // HTML generation
        String generatedHtml = "<html><head></head><body>";
        String authors = _applicationDataModel.getAuthors();
        if ((authors != null) && (authors.length() > 0)) {
            generatedHtml += "Brought to you by " + authors + ".<BR><BR>";
        }
        generatedHtml += "<I>If this software was helpful for your study or research work, please include the mandatory acknowledgment (available from the Help menu) in your publications.</I><BR><BR>";

        // Get the Text value
        String textValue = _applicationDataModel.getTextValue();
        if ((textValue != null) && (textValue.length() > 0)) {
            generatedHtml += textValue;
            generatedHtml += "<br><br>";
        }

        // Generate a HTML string with each package informations
        List<String> packagesInfo = _applicationDataModel.getPackagesInfo();
        String packageHtml = "";

        // For each package
        int nbElems = packagesInfo.size();
        if (nbElems > 0) {
            packageHtml += "<i>Dependencies</i>:<br>";
        }

        /* We have a step of 3 because for each
        package we have a name, a link and a description */
        for (int i = 0; i < nbElems; i += 3) {
            String name = packagesInfo.get(i);
            String link = packagesInfo.get(i + 1);
            String description = packagesInfo.get(i + 2);

            // We check if there is a link
            if (link == null) {
                packageHtml += name;
            } else {
                packageHtml += ("<a href='" + link + "'>" + name + "</a>");
            }

            packageHtml += (" : <i>" + description + "</i><br>");
        }

        generatedHtml += (packageHtml + "</body></html>");

        _descriptionEditorPane.setText(generatedHtml);
        // Show first line of editor pane, and not its last line as by default !
        _descriptionEditorPane.setCaretPosition(0);

        _logger.debug("The content of textarea has been inserted.");

        // Link pane only if anything to display
        _descriptionScrollPane.setViewportView(_descriptionEditorPane);
    }

    /**
     * Handle URL link clicked in the JEditorPane.
     *
     * @param event the received event.
     */
    @Override
    public void hyperlinkUpdate(HyperlinkEvent event) {
        // When a link is clicked
        if (event.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
            // Get the clicked URL
            String clickedURL = event.getURL().toExternalForm();

            // Open the url in web browser
            BrowserLauncher.openURL(clickedURL);
        }
    }

    /** Sets link label properties */
    private void setupLinkLabel() {
        // Set properties
        _linkLabel.setEditable(false);
        _linkLabel.setOpaque(false);
        _linkLabel.addHyperlinkListener(this);
        _linkLabel.setContentType("text/html");

        String link = _applicationDataModel.getLinkValue();
        String linkHTML = "<a href='" + link + "'>" + link + "</a>";

        _linkLabel.setText("<html><head></head><body><center>" + linkHTML
                + "</center></body></html>");

        _logger.debug("All the link label properties have been initialized");
    }

    /** Sets program name label properties */
    private void setupProgramNameLabel() {
        // Get program informations
        String name = _applicationDataModel.getProgramName();

        _programNameLabel.setHorizontalAlignment(SwingConstants.CENTER);
        _programNameLabel.setText(name);
        _programNameLabel.setFont(new Font("Dialog", 1, 23));

        _logger.debug("All the program info label properties have been initialized");
    }

    /** Sets program version label properties */
    private void setupProgramVersionLabel() {
        // Get program informations
        String version = "Version " + _applicationDataModel.getProgramVersion();

        _programVersionLabel.setHorizontalAlignment(SwingConstants.CENTER);
        _programVersionLabel.setText(version);

        _logger.debug("All the program info label properties have been initialized");
    }

    /** Sets compilation info label properties */
    private void setupCompilationInfoLabel() {
        // Get compilation information
        String compilationDate = _applicationDataModel.getCompilationDate();
        String compilatorVersion = _applicationDataModel.getCompilatorVersion();
        String compilationInfo = "Build the " + compilationDate + " with "
                + compilatorVersion;

        _compilationInfoLabel.setHorizontalAlignment(SwingConstants.CENTER);
        _compilationInfoLabel.setText(compilationInfo);

        _logger.debug("All the compilation info label properties have been initialized");
    }

    /** Set program name and version split properties */
    private void setProgramNameAndVersionSplitProperties() {
        // Set properties
        _programNameAndVersionSplit.setBorder(null);
        _programNameAndVersionSplit.setDividerSize(0);
        _programNameAndVersionSplit.setOrientation(JSplitPane.VERTICAL_SPLIT);
        _programNameAndVersionSplit.setTopComponent(_programNameLabel);
        _programNameAndVersionSplit.setBottomComponent(_programVersionLabel);

        _logger.debug("All the link and program split properties have been initialized");
    }

    /** Set link and program info split properties */
    private void setLinkAndProgramSplitProperties() {
        // Set properties
        _linkAndProgramInfoSplit.setBorder(null);
        _linkAndProgramInfoSplit.setDividerSize(0);
        _linkAndProgramInfoSplit.setOrientation(JSplitPane.VERTICAL_SPLIT);
        _linkAndProgramInfoSplit.setTopComponent(_programNameAndVersionSplit);
        _linkAndProgramInfoSplit.setBottomComponent(_linkLabel);

        _logger.debug("All the link and program split properties have been initialized");
    }

    /** Set compilation info split properties */
    private void setCompilationInfoSplitProperties() {
        // Set properties
        _compilationInfoSplit.setBorder(null);
        _compilationInfoSplit.setDividerSize(0);
        _compilationInfoSplit.setDividerLocation(-1);
        _compilationInfoSplit.setOrientation(JSplitPane.VERTICAL_SPLIT);
        _compilationInfoSplit.setTopComponent(_linkAndProgramInfoSplit);
        _compilationInfoSplit.setBottomComponent(_compilationInfoLabel);

        _logger.debug("All the compilation info split properties have been initialized");
    }

    /** Set down space split properties */
    private void setDownSpaceSplitProperties() {
        // Set properties
        _downSpaceSplit.setBorder(null);
        _downSpaceSplit.setDividerSize(0);
        _downSpaceSplit.setDividerLocation(-1);
        _downSpaceSplit.setOrientation(JSplitPane.VERTICAL_SPLIT);
        _downSpaceSplit.setTopComponent(_compilationInfoSplit);
        _downSpaceSplit.setBottomComponent(new JLabel(" "));

        _logger.debug("All the down space split properties have been initialized");
    }

    /** Set up space split properties */
    private void setUpSpaceSplitProperties() {
        // Set properties
        _upSpaceSplit.setBorder(null);
        _upSpaceSplit.setDividerSize(0);
        _upSpaceSplit.setDividerLocation(-1);
        _upSpaceSplit.setOrientation(JSplitPane.VERTICAL_SPLIT);
        _upSpaceSplit.setTopComponent(new JLabel(" "));
        _upSpaceSplit.setBottomComponent(_downSpaceSplit);

        _logger.debug("All the up space split properties have been initialized");
    }

    /** Set text area split properties */
    private void setTextareaSplitProperties() {
        // Set properties
        _descriptionSplit.setBorder(null);
        _descriptionSplit.setDividerSize(0);
        _descriptionSplit.setDividerLocation(-1);
        _descriptionSplit.setOrientation(JSplitPane.VERTICAL_SPLIT);
        _descriptionSplit.setTopComponent(_upSpaceSplit);
        _descriptionSplit.setBottomComponent(_descriptionScrollPane);

        _logger.debug("All the textarea split properties have been initialized");
    }

    /** Sets frame properties and make the window visible */
    private void setupWindow() {
        // Set the window title
        String programName = _applicationDataModel.getProgramName();
        String windowTitle = "About " + programName + "...";
        setTitle(windowTitle);

        // Disable window resizing
        setResizable(false);

        // Window layout
        Container contentPane = getContentPane();
        contentPane.add(_logoLabel, BorderLayout.PAGE_START);
        contentPane.add(_descriptionSplit, BorderLayout.CENTER);
        contentPane.add(_copyrightLabel, BorderLayout.PAGE_END);
        pack();

        // Center window on main screen
        WindowCenterer.centerOnMainScreen(this);

        _logger.debug("All the frame properties have been initialized");
    }
}
/*___oOo___*/
