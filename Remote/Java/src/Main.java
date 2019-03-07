
/*
 * Main.java
 */

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Observable;
import java.util.Observer;

import ch.bfh.roboticsLab.util.ZMQSubscriber;
import ch.bfh.roboticsLab.yellow.SerialClient;
import ch.bfh.roboticsLab.yellow.Telemetry;
import ch.bfh.roboticsLab.yellow.YellowProtoBuffer;

/**
 * Test the capabilities of the ch.bfh.roboticsLab.yellow.Reader
 * 
 * @author gabriel.gruener@bfh.ch
 */
public class Main {

  public static byte[] createMessage(Telemetry telemetry) throws IOException {

    YellowProtoBuffer.Telemetry.Builder tb = YellowProtoBuffer.Telemetry.newBuilder();
    YellowProtoBuffer.Odometry.Builder ob = YellowProtoBuffer.Odometry.newBuilder();

    YellowProtoBuffer.Pose.Builder pb = YellowProtoBuffer.Pose.newBuilder();
    YellowProtoBuffer.Pose p = pb.setX(telemetry.odometry.pose.x).setY(telemetry.odometry.pose.y).setAlpha(telemetry.odometry.pose.alpha).build();

    YellowProtoBuffer.CovarianceMatrix.Builder cmb = YellowProtoBuffer.CovarianceMatrix.newBuilder();
    int n = telemetry.odometry.covarianceMatrix.p.length;
    int m = telemetry.odometry.covarianceMatrix.p[0].length;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        cmb.addP(telemetry.odometry.covarianceMatrix.p[i][j]);

    YellowProtoBuffer.Lidar.Builder lb = YellowProtoBuffer.Lidar.newBuilder();
    YellowProtoBuffer.LidarPoint.Builder lpb = YellowProtoBuffer.LidarPoint.newBuilder();
    for (int i = 0; i < 360; i++) {
      lpb.setAngle(i).setDistance(1).setQuality(2);
      lb.addPoints(lpb.build());
    }
    //// Yellow.LidarPoint lp = lpb.build();
    // Yellow.Telemetry t = tb.setOdometry(o).setLidar(l).build();
    YellowProtoBuffer.Telemetry t = tb.setOdometry(ob.setPose(p).setCovarianceMatrix(cmb.build()).build()).setLidar(lb.build()).build();
    ByteArrayOutputStream out = new ByteArrayOutputStream();
    t.writeTo(out);
    return out.toByteArray();
  }

  public static void main(String[] args) {

    if (true) {
      try {
        if (true) {
          SerialClient robot = SerialClient.getInstance();
          int counter = 0;
          int timestamp = 0;
          System.out.println("\nListening...");
          while (true) {
            try {
              Thread.sleep(100);
              Telemetry telemetry = robot.receive();
              if (telemetry.timestamp == timestamp)
                continue;
              System.out.println("Got telemetry:\n" + telemetry);

              // if (counter++ == 3) {
              // counter = 0;
              // Telecommand telecommand = new Telecommand();
              // if (telemetry.state.stateName != YellowProtoBuffer.StateName.OFF) {
              // telecommand.setState(StateName.OFF);
              // } else {
              // telecommand.setState(StateName.MANUAL);
              // // telecommand.setVelocities(0.1f, 0.0f);
              // }
              // telecommand.requestLidarData = 10;
              // System.out.println("\nSending Telecommand:\n" + telecommand);
              // robot.send(telecommand);
              // }
            } catch (Exception e) {
              System.err.println("Error receiving telemetry: " + e.getMessage());
            }
          }
        } else {
          // Simulate
          ZMQSubscriber subscriber = new ZMQSubscriber("127.0.0.1:" + 2000);
          subscriber.addObserver(new Observer() {
            @Override public void update(Observable o, Object arg) {
              try {
                System.out.println("Got: " + YellowProtoBuffer.Telemetry.parseFrom((byte[]) arg));
              } catch (Exception e) {
                e.printStackTrace();
              }
            }
          });
          while (true)
            Thread.sleep(100);
        }

      } catch (Exception e) {
        e.printStackTrace();
        System.exit(0);
      }
    }

    try {

      if (args.length > 0) {

        // Read from file
        Telemetry t = SerialClient.parseFromFile(args[0]);
        System.out.println("Pose read: x=" + t.odometry.pose.x);
        System.out.println("Telemtry\n" + t);

      } else {

        // Create data
        Telemetry telemetry = new Telemetry();
        telemetry.odometry.pose.x = 5;
        byte[] m = createMessage(telemetry);
//        Telemetry t2 = SerialClient.parse(new String(m));

        YellowProtoBuffer.Telemetry te = YellowProtoBuffer.Telemetry.parseFrom(m);
        PrintWriter writer = new PrintWriter("telemetry.txt");
        writer.println(te.toString());
        writer.close();
      }

    } catch (Exception e) {
      e.printStackTrace();
      System.exit(1);
    }
    System.exit(0);
  }
}
