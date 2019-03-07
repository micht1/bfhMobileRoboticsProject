/* Copyright (C) 2018, BFH roboticsLab
 * All rights reserved.
 */

package ch.bfh.roboticsLab.util;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Context;

/**
 * <p>
 * This class defines a ZMQPublisher that publishes messages.
 * </p>
 * <p>
 * Example:
 * </p>
 * 
 * <pre>
 * ZMQPublisher publisher = new ZMQPublisher(1234);
 * publisher.publish(new byte[] { 0, 0, 0, 0 });
 * </pre>
 * 
 * Note: This implementation is compatible to Java 1.6 so it is usable on the Kuka LBR iiwa.
 *
 * @author gabriel.gruener@bfh.ch
 */
public class ZMQPublisher {

  private final Logger log = LogManager.getLogger();
  private org.zeromq.ZMQ.Socket socket;

  /**
   * Creates a new ZMQPublisher that publishes on the given port.
   * 
   * @param port Port to publish.
   */
  public ZMQPublisher(int port) {
    Context context = ZMQ.context(1);
    log.debug("Creating ZMQ PUB socket");
    socket = context.socket(ZMQ.PUB);
    log.info("Starting publisher on port {}", port);
    socket.bind("tcp://*:" + port);
    log.debug("Publishing on port {} ", port);
  }

  public void publish(byte[] outgoing) {
    socket.send(outgoing);
  }
}
