package maincontrolunit;

import malscontrolplatform.MalsControlPlatform;

/**
 *
 * @author atlas144
 */
public class MainControlUnit {
    
    private final String webHost = "localhost";
    private final short webPort = 8080;
    
    private final MalsControlPlatform controlPlatform;
    
    public MainControlUnit() {
        controlPlatform = new MalsControlPlatform(webHost, webPort);
        
        // register modules
        
        controlPlatform.start();
    }

    public static void main(String[] args) {
        new MainControlUnit();
    }
    
}
