/* SerialClient.java
 * Copyright (c) 2018, BFH
 * All rights reserved.
 */

package ch.bfh.roboticsLab.yellow;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

/**
 * <p>
 * This class connects to a Yellow robot server and offers methods to read and write messages to and from the robot.
 * </p>
 * <p>
 * The class also offers static methods to parse Yellow telemetry messages and create the corresponding Java Telemetry objects.
 * </p>
 * <p>
 * The class spanws a private thread that reads incoming telemetry messages as they arrive. A call to method {@link SerialClient#receive()} will
 * return immediately with the latest Telemetry message received. Hence the call is non blocking but the Telemetry message returned may be old. Use
 * the {@link Telemetry#timestamp} entry to check this.
 * </p>
 * <p>
 * Usage example:
 * </p>
 * 
 * <pre>
 * try {
 *   // Connect to a Yellow robot
 *   SerialClient robot = SerialClient.getInstance();
 *   // Get the latest incoming message
 *   Telemetry telemetry = robot.receive();
 *   System.out.println("Got telemetry:\n" + telemetry);
 * 
 *   // Send a command
 *   robot.set("state { stateName: OFF }");
 * 
 *   // Disconnect from the robot
 *   robot = null;
 * } catch (Exception e) {
 *   e.printStackTrace();
 *   System.exit(0);
 * }
 * </pre>
 * 
 * <p>To see debuging log console messages start with <pre>-Dyellow.debug=true</pre></p>
 * 
 * @author gabriel.gruener@bfh.ch
 * @see Telemetry
 * @see yellow.proto
 */
public class SerialClient {

  /** Socket to connect to Yellow. */
  private Socket socket;
  /** Input stream from Yellow socket. */
  private InputStream inFromServer;
  /** Output stream to Yellow socket. */
  private OutputStream outToServer;
  /** A serial encoder to encode and decode messages to and from Yellow. */
  private SerialEncoder encoder;
  /** Timestamp upon connection to server. Used to set telecommand timestamps. */
  private static long startTime;

  /** Future of private thread to handle incomming Telemetry and Telecommand queue. */
  private Future<?> privateThread;
  /** Latest telemetry received. */
  private Telemetry telemetry;

  /** Telecommand queue (for appended commands as json Strings). */
  private ConcurrentLinkedQueue<String> telecommands;

  /** Flag to keep running read thread. */
  private boolean keepRunning;

  /** SerialServer singleton. */
  private static SerialClient instance = null;

  /** Log facility for debugging. */
  private static final boolean DEBUG = Boolean.parseBoolean(System.getProperty("yellow.debug"));

  private static void log(String message) {
    if (DEBUG) System.out.println("\n>> " + (System.currentTimeMillis() - startTime) + ": " + message);
  }

  /**
   * Retrieve the singleton instance of a SerialClient.
   * 
   * @return The SerialClient object.
   * @throws Exception If an error happens while creating the singleton.
   */
  public static SerialClient getInstance() throws Exception {
    if (instance == null) {
      instance = new SerialClient();
    }
    return instance;
  }

  /** The IP address of the robot. */
  public static final String IP_ADDRESS = "192.168.1.1";
  /** The IP port to connect to on the robot. */
  public static final int IP_PORT = 2000;

  /**
   * Connects to the Yellow robot server at {@link #IP_ADDRESS}:{@link #IP_PORT}.
   * 
   * @throws Exception If an error happens while connecting to the robot.
   */
  private SerialClient() throws Exception {

    startTime = System.currentTimeMillis();

    // Connect to Yellow server
    socket = new Socket(IP_ADDRESS, IP_PORT);
    outToServer = socket.getOutputStream();
    inFromServer = socket.getInputStream();
    encoder = new SerialEncoder();

    // Create initial empty telemetry object, until something is received below
    telemetry = new Telemetry();
    // Create telecommand queue
    telecommands = new ConcurrentLinkedQueue<>();

    keepRunning = true;

    // Start private thread to read incoming messages and send enqueued commands
    privateThread = Executors.newFixedThreadPool(1).submit(new Runnable() {
      @Override public void run() {
        String command = null;
        YellowProtoBuffer.StateName currentState = YellowProtoBuffer.StateName.OFF;
        while (!Thread.currentThread().isInterrupted()) {
          try {
            Thread.sleep(100);
            telemetry = parse(read());

            // Show state changes on console if debugging
            if (DEBUG && telemetry.state.stateName != currentState) {
              log("SerialClient.privateThread: State change from " + currentState + " to " + telemetry.state.stateName);
              currentState = telemetry.state.stateName;
            }

            command = telecommands.poll();
            if (command != null) {
              if (!command.isEmpty()) {
                log("SerialClient: Sending new command: '" + command + "', queue size: " + telecommands.size());
                transmit(stringToTelecommand(command).toByteArray());
              }
              command = null;
            }

          } catch (Exception e) {
            e.printStackTrace();
          }
        }
      }
    });
  }

  /**
   * Implements {@link java.lang.Object#finalize} by calling {@link SerialClient#disconnect()}.
   */
  @Override protected void finalize() throws Throwable {
    disconnect();
    super.finalize();
  }

  /**
   * Disconnects from the robot.
   * 
   * @throws IOException If an error happens when disconnecting from the robot.
   */
  private void disconnect() throws IOException {
    keepRunning = false;
    if (privateThread != null) privateThread.cancel(true);
    socket.close();
    instance = null;
  }

  /**
   * Retrieve the last incoming message from the robot. This method returns immediately with the latest message received from the robot.
   * 
   * @return Telemetry object holding the incoming message.
   */
  public Telemetry receive() {
    return telemetry;
  }

  /**
   * Read a payload packet from the server. This method blocks until a message arrives.
   * 
   * @return payload The payload received.
   * @throws IOException If an error happens while reading.
   */
  private byte[] read() throws IOException, InterruptedException {

    encoder.reset();
    while (keepRunning) {
      Thread.sleep(1);
      if (inFromServer.available() > 0) {
        SerialEncoder.ReadState state = encoder.push(inFromServer.read());
        if (state == SerialEncoder.ReadState.ERROR) return null;
        if (state == SerialEncoder.ReadState.DONE) return encoder.getMessage();
      }
    }
    return null;
  }

  /**
   * Appends the given telecommand to the queue.
   * 
   * @param telecommand The telecommand to append in protobuf UTF-8 text json format.
   */
  public void append(String telecommand) {
    if (telecommand != null) {
      telecommands.offer(telecommand);
      log("SerialClient.append: " + telecommand + "   queue size: " + telecommands.size());
    }
  }

  /**
   * Sets the given telecommand at the front of the queue, removing any remaining commands from the queue.
   * 
   * @param telecommand The telecommand to send in protobuf UTF-8 text json format.
   */
  public void set(String telecommand) {
    if (telecommand != null) {
      telecommands.clear();
      telecommands.offer(telecommand);
      log("SerialClient.set: '" + telecommand + "'");
    }
  }

  /**
   * Sends the given payload to the robot.
   * 
   * @param payload Payload to send. The payload will be encoded.
   * @throws IOException If an error happens while writing.
   * @see SerialEncoder
   */
  private void transmit(byte[] payload) throws IOException {
    byte[] e = encoder.encode(payload);
    for (byte b : e) {
      outToServer.write(b);
      try {
        Thread.sleep(1);
      } catch (Exception e1) {}
    }
  }

  /**
   * Creates a Protobuf Telecommand object of the given Telecommand string by applying the protobuf. Note this method sets the timestamp of the
   * Telecommand right before converting it.
   * 
   * @param telecommand The telecommand in protobuf UTF-8 text json format.
   * @return Telecommand
   * @throws IOException If an error happens while parsing the string.
   * @see YellowProtoBuffer
   */
  private static YellowProtoBuffer.Telecommand stringToTelecommand(final String telecommand) throws IOException {
    YellowProtoBuffer.Telecommand.Builder builder = YellowProtoBuffer.Telecommand.newBuilder();
    com.google.protobuf.TextFormat.merge(telecommand, builder);
    builder.setTimestamp((int) (System.currentTimeMillis() - startTime));
    return builder.build();
  }

  /**
   * Parse a telemetry message in text form from file. This method is useful to test functionality without robot communication.
   * 
   * @param filename Path to the file to read the message from.
   * @return Telemetry object.
   * @throws IOException If an error happens while parsing the message.
   */
  public static Telemetry parseFromFile(String filename) throws IOException {

    String message = new String(Files.readAllBytes(Paths.get(filename)));
    YellowProtoBuffer.Telemetry.Builder tb = YellowProtoBuffer.Telemetry.newBuilder();
    com.google.protobuf.TextFormat.merge(message, tb);
    YellowProtoBuffer.Telemetry t = tb.build();
    return decode(t);
  }

  /**
   * Parse a telemetry message in binary form.
   * 
   * @param incoming Byte array holding the incoming telemetry message.
   * @return Telemetry object.
   * @throws IOException If an error happens while parsing the message.
   */
  private static Telemetry parse(byte[] incoming) throws IOException {

    if (incoming == null) return new Telemetry();

    return decode(YellowProtoBuffer.Telemetry.parseFrom(incoming));
  }

  /**
   * Decode a protobuf Yellow.Telemetry message and parse it into a Telemetry object.
   * 
   * @param telemetryPB Yellow.Telemetry message.
   * @return Telemetry object.
   * @throws IOException If an error happens while parsing the message.
   */
  private static Telemetry decode(YellowProtoBuffer.Telemetry telemetryPB) throws IOException {

    Telemetry telemetry = new Telemetry();

    telemetry.timestamp = telemetryPB.hasTimestamp() ? telemetryPB.getTimestamp() : 0;

    if (telemetryPB.hasState()) {

      YellowProtoBuffer.State s = telemetryPB.getState();
      telemetry.state = telemetry.new State();
      telemetry.state.stateName = s.getStateName();
    }

    if (telemetryPB.hasOdometry()) {

      YellowProtoBuffer.Odometry o = telemetryPB.getOdometry();
      telemetry.odometry = telemetry.new Odometry();

      if (o.hasPose()) {
        YellowProtoBuffer.Pose p = o.getPose();
        telemetry.odometry.pose.x = p.getX();
        telemetry.odometry.pose.y = p.getY();
        telemetry.odometry.pose.alpha = p.getAlpha();
      }
      if (o.hasCovarianceMatrix()) {
        YellowProtoBuffer.CovarianceMatrix cm = o.getCovarianceMatrix();
        int m = telemetry.odometry.covarianceMatrix.p.length;
        int n = telemetry.odometry.covarianceMatrix.p[0].length;
        if (n * m != cm.getPCount()) throw new RuntimeException("Size mismatch for covariance matrix");
        for (int i = 0; i < m; i++) {
          for (int j = 0; j < n; j++) {
            telemetry.odometry.covarianceMatrix.p[i][j] = cm.getP(i * n + j);
          }
        }
      }
    }

    if (telemetryPB.hasLidar()) {

      YellowProtoBuffer.Lidar l = telemetryPB.getLidar();
      telemetry.lidar = telemetry.new Lidar();
      for (int i = 0; i < l.getPointsCount(); i++) {
        Telemetry.LidarPoint p = telemetry.new LidarPoint();
        YellowProtoBuffer.LidarPoint lp = l.getPoints(i);
        p.angle = lp.getAngle();
        p.distance = lp.getDistance();
        if (lp.hasQuality()) p.quality = lp.getQuality();
        telemetry.lidar.points.add(p);
      }
    }

    if (telemetryPB.hasLidarLines()) {

      YellowProtoBuffer.LidarLines lidarLines = telemetryPB.getLidarLines();
      telemetry.lidarLines = telemetry.new LidarLines();
      for (int i = 0; i < lidarLines.getLinesCount(); i++) {
        Telemetry.Line line = telemetry.new Line();
        YellowProtoBuffer.LidarLines.Line l = lidarLines.getLines(i);
        line.start.x = l.getStart().getX();
        line.start.y = l.getStart().getY();
        line.start.alpha = l.getStart().getAlpha();
        if (l.hasEnd()) {
          line.end.x = l.getEnd().getX();
          line.end.y = l.getEnd().getY();
          line.end.alpha = l.getEnd().getAlpha();
        }
        telemetry.lidarLines.lines.add(line);
      }
    }

    if (telemetryPB.hasIr()) {
      YellowProtoBuffer.IRSensors irs = telemetryPB.getIr();
      telemetry.ir = telemetry.new IRSensors();
      for (int i = 0; i < irs.getSensorCount(); i++) {
        Telemetry.IRSensor s = telemetry.new IRSensor();
        YellowProtoBuffer.IRSensor ir = irs.getSensor(i);
        s.distance = ir.getDistance();
        telemetry.ir.sensors.add(s);
      }
    }

    return telemetry;
  }

}
