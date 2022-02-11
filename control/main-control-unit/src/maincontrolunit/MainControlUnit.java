package maincontrolunit;

import malscontrolplatform.MalsControlPlatform;
import srsc.exceptions.UnknownPortException;

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
        
        try {
            controlPlatform.registerModule(new SubsystemsControlUnitModule("Subsystems Control Unit Module"));
            
            controlPlatform.start();
        } catch (UnknownPortException exception) {
            System.out.println(exception.getMessage());
        }
    }

    public static void main(String[] args) {
        new MainControlUnit();
    }
    
}
