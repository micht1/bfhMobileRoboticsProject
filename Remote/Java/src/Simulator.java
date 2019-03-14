import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import ch.bfh.roboticsLab.util.ZMQPublisher;
import ch.bfh.roboticsLab.util.ZMQResponder;
import ch.bfh.roboticsLab.yellow.YellowProtoBuffer;
import ch.bfh.roboticsLab.yellow.YellowProtoBuffer.TelecommandAcknowledge.Acknowledge;

/**
 * Simulate Yellow telemetry with 0MQ and reply ok to any command.  
 * 
 * @author gabriel.gruener@bfh.ch
 */
public class Simulator {

  public static final int port = 2000;
  public static final int PUBLISH_INTERVAL = 200;

  ZMQPublisher publisher;
  private Future<?> future;
  
  ZMQResponder responder;

  public Simulator() {

    ScheduledExecutorService executor = Executors.newScheduledThreadPool(1);

    final double[] irSensors = new double[] { 0.0, 0.0, 0.0 };
    final YellowProtoBuffer.IRSensor.Builder irBuilder = YellowProtoBuffer.IRSensor.newBuilder();
    final YellowProtoBuffer.IRSensors.Builder irsBuilder = YellowProtoBuffer.IRSensors.newBuilder();

    final long now = System.currentTimeMillis();
    publisher = new ZMQPublisher(port);
    future = executor.scheduleAtFixedRate(new Runnable() {
      @Override public void run() {

        irsBuilder.clear();
        for (int i = 0; i < irSensors.length; i++) {
          irSensors[i] += ((double) i + 1) / 100.0;
          if (irSensors[i] > 0.5) irSensors[i] = 0.0;
          irBuilder.setDistance((float) irSensors[i]);
          irsBuilder.addSensor(irBuilder.build());
        }

        publisher.publish(YellowProtoBuffer.Telemetry.newBuilder().setTimestamp((int) (System.currentTimeMillis() - now)).setIr(irsBuilder.build())
            .build().toByteArray());
      }
    }, 0, PUBLISH_INTERVAL, TimeUnit.MILLISECONDS);
    
    responder = new ZMQResponder(port+1) {
      @Override public byte[] respond(byte[] incoming) {
        byte [] response = null;
        try {
          YellowProtoBuffer.Telecommand command = YellowProtoBuffer.Telecommand.parseFrom(incoming);
          System.out.println("Received command: "+command);
          response = YellowProtoBuffer.TelecommandAcknowledge.newBuilder().setAcknowledge(Acknowledge.OK).build().toByteArray();
        } catch (Exception e) {
          e.printStackTrace();
        }
        return response;
      }
    };

  }

  @Override protected void finalize() throws Throwable {
    if (future != null) future.cancel(true);
    publisher = null;
  }

  public static void main(String[] args) {

    new Simulator();
  }

}
