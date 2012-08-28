/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/
package fr.jmmc.jmcs.util;

import java.io.File;
import java.io.IOException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Test some FileUtils methods.
 * @author mella
 */
public class TestFileUtils {

    /** logger */
    private final static Logger logger = LoggerFactory.getLogger(TestFileUtils.class.getName());

    public static void main(String[] args) {
        try {
            File f1 = FileUtils.getTempFile("toto", "txt");
            FileUtils.writeFile(f1, "ABCDEFGHABCDEFGHABCDEFGHABCDEFGHABCDEFGHABCDEFGHABCDEFGHABCDEFGH");
            File f2 = FileUtils.getTempFile("toto", ".txt.gz");
            FileUtils.zip(f1, f2);
            System.out.println("f1 = " + f1);
            System.out.println("f1.length() = " + f1.length());
            System.out.println("f2 = " + f2);
            System.out.println("f2.length() = " + f2.length());
            System.out.println("f2.read() = " + FileUtils.readFile(f2));

        } catch (IOException ioe) {
            logger.error("exception:", ioe);
        }

    }
}
