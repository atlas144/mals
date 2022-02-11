package maincontrolunit;

import malscontrolplatform.intercommunicationmodule.IntercommunicationModule;
import malscontrolplatform.intercommunicationmodule.Priority;
import srsc.PacketArrivedCallback;
import srsc.packet.Packet;

/**
 *
 * @author atlas144
 */
public class SubsystemsControlUnitPacketCallback implements PacketArrivedCallback {
    
    private final IntercommunicationModule intercommunicationModule;
    
    public SubsystemsControlUnitPacketCallback(IntercommunicationModule intercommunicationModule) {
        this.intercommunicationModule = intercommunicationModule;
    }

    @Override
    public void onPacketArrived(Packet packet) {
        switch (packet.getPacketTypeIdentifier()) {
            case 0x72: {
                intercommunicationModule.publish("module/sensoric/lidar/1/distance", String.valueOf(packet.getPayload()), Priority.IMPORTANT);
                break;
            } case 0x73: {
                intercommunicationModule.publish("module/sensoric/lidar/1/steps", String.valueOf(packet.getPayload()), Priority.NORMAL);
                break;
            } case 0x74: {
                byte[] binaryPayload = packet.getBinaryPayload();
                
                intercommunicationModule.publish("module/sensoric/sonar/1/distance", String.valueOf(binaryPayload[0]), Priority.IMPORTANT);
                intercommunicationModule.publish("module/sensoric/sonar/2/distance", String.valueOf(binaryPayload[1]), Priority.IMPORTANT);
                break;
            } case 0x75: {
                byte[] binaryPayload = packet.getBinaryPayload();
                
                intercommunicationModule.publish("module/sensoric/sonar/3/distance", String.valueOf(binaryPayload[0]), Priority.IMPORTANT);
                intercommunicationModule.publish("module/sensoric/sonar/4/distance", String.valueOf(binaryPayload[1]), Priority.IMPORTANT);
                break;
            } case 0x76: {
                byte[] binaryPayload = packet.getBinaryPayload();
                
                intercommunicationModule.publish("module/sensoric/lineTrackingSensor/1/value/1", String.valueOf(binaryPayload[0]), Priority.NORMAL);
                intercommunicationModule.publish("module/sensoric/lineTrackingSensor/1/value/2", String.valueOf(binaryPayload[1]), Priority.NORMAL);
                intercommunicationModule.publish("module/sensoric/lineTrackingSensor/1/value/3", String.valueOf(binaryPayload[2]), Priority.NORMAL);
                break;
            } case 0x77: {
                intercommunicationModule.publish("module/sensoric/bumper/1/contact", "", Priority.CRITICAL);
                break;
            } case 0x78: {
                intercommunicationModule.publish("module/sensoric/bumper/2/contact", "", Priority.CRITICAL);
                break;
            } case 0x79: {
                intercommunicationModule.publish("module/sensoric/gps/1/lat", String.valueOf(packet.getPayload()), Priority.NORMAL);
                break;
            } case (byte) 0x80: {
                intercommunicationModule.publish("module/sensoric/gps/1/long", String.valueOf(packet.getPayload()), Priority.NORMAL);
                break;
            } default: {
            }
        }
    }
    
}
