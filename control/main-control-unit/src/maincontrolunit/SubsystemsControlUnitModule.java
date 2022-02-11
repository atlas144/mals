package maincontrolunit;

import malscontrolplatform.TaskModule;
import malscontrolplatform.intercommunicationmodule.Message;
import srsc.SRSC;
import srsc.exceptions.MissingPayloadException;
import srsc.exceptions.SerialBufferFullException;
import srsc.exceptions.UnknownPacketTypeException;
import srsc.exceptions.UnknownPortException;
import srsc.packet.PayloadSize;

/**
 *
 * @author atlas144
 */
public class SubsystemsControlUnitModule extends TaskModule {
    
    private final SRSC srsc;
    private final SubsystemsControlUnitPacketCallback subsystemsControlUnitPacketCallback;

    public SubsystemsControlUnitModule(String moduleName) throws UnknownPortException {
        super(moduleName);
        
        srsc = new SRSC((byte) 0);
        subsystemsControlUnitPacketCallback = new SubsystemsControlUnitPacketCallback(intercommunicationModule);
    }

    @Override
    protected void setup() {
        srsc.definePacketType((byte) 0x60, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x61, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x62, PayloadSize.BYTE);
        srsc.definePacketType((byte) 0x63, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x64, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x65, PayloadSize.BYTE);
        srsc.definePacketType((byte) 0x66, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x67, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x68, PayloadSize.BYTE);
        srsc.definePacketType((byte) 0x69, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x70, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x71, PayloadSize.BYTE);
        srsc.definePacketType((byte) 0x72, PayloadSize.SHORT);
        srsc.definePacketType((byte) 0x73, PayloadSize.BYTE);
        srsc.definePacketType((byte) 0x74, PayloadSize.SHORT);
        srsc.definePacketType((byte) 0x75, PayloadSize.SHORT);
        srsc.definePacketType((byte) 0x76, PayloadSize.INT);
        srsc.definePacketType((byte) 0x77, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x78, PayloadSize.COMMAND);
        srsc.definePacketType((byte) 0x79, PayloadSize.INT);
        srsc.definePacketType((byte) 0x80, PayloadSize.INT);
        srsc.registerOnPacketArrivedCallback(subsystemsControlUnitPacketCallback);
        srsc.begin();
        intercommunicationModule.subscribe("robot/propulsive/motor/1/direction/forward", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/1/direction/backwards", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/1/pwm", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/2/direction/forward", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/2/direction/backwards", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/2/pwm", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/3/direction/forward", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/3/direction/backwards", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/3/pwm", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/4/direction/forward", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/4/direction/backwards", this);
        intercommunicationModule.subscribe("robot/propulsive/motor/4/pwm", this);
    }

    @Override
    protected void loop() {
        try {
            Message message = messageQueue.take();
            
            switch (message.getTopic()) {
                case "robot/propulsive/motor/1/direction/forward":
                    srsc.writePacket((byte) 0x60);
                    break;
                case "robot/propulsive/motor/1/direction/backwards":
                    srsc.writePacket((byte) 0x61);
                    break;
                case "robot/propulsive/motor/1/pwm":
                    srsc.writePacket((byte) 0x62, Integer.valueOf(message.getPayload()));
                    break;
                case "robot/propulsive/motor/2/direction/forward":
                    srsc.writePacket((byte) 0x63);
                    break;
                case "robot/propulsive/motor/2/direction/backwards":
                    srsc.writePacket((byte) 0x64);
                    break;
                case "robot/propulsive/motor/2/pwm":
                    srsc.writePacket((byte) 0x65, Integer.valueOf(message.getPayload()));
                    break;
                case "robot/propulsive/motor/3/direction/forward":
                    srsc.writePacket((byte) 0x66);
                    break;
                case "robot/propulsive/motor/3/direction/backwards":
                    srsc.writePacket((byte) 0x67);
                    break;
                case "robot/propulsive/motor/3/pwm":
                    srsc.writePacket((byte) 0x68, Integer.valueOf(message.getPayload()));
                    break;
                case "robot/propulsive/motor/4/direction/forward":
                    srsc.writePacket((byte) 0x69);
                    break;
                case "robot/propulsive/motor/4/direction/backwards":
                    srsc.writePacket((byte) 0x70);
                    break;
                case "robot/propulsive/motor/4/pwm":
                    srsc.writePacket((byte) 0x71, Integer.valueOf(message.getPayload()));
                    break;
                default:
                    throw new AssertionError();
            }
        } catch (UnknownPacketTypeException | SerialBufferFullException | MissingPayloadException exception) {
            System.out.println(exception.getMessage());
        } catch (InterruptedException ex) {}
    }
    
}
