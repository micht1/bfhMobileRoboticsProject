/* Copyright (C) 2018, BFH roboticsLab
 * All rights reserved.
 */

package ch.bfh.roboticsLab.util;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Context;
import org.zeromq.ZMQ.Socket;

/**
 * <p>
 * This class defines a ZMQRequester that sends requests to a responder.
 * </p>
 * <p>
 * Example:
 * </p>
 * 
 * <pre>
 * ZMQRequester requester = new ZMQRequester(controllerIPAddress + ":" + controllerRequestPort);
 * // Make a request with a meaningful payload
 * byte[] request = { 0, 0, 0, 0 };
 * byte[] response = requester.request(myRequest);
 * </pre>
 * 
 * Note: This implementation is compatible to Java 1.6 so it is usable on the Kuka LBR iiwa.
 *
 * @author gabriel.gruener@bfh.ch
 */
public class ZMQRequester {

//  private final Logger log = LogManager.getLogger();
  private Socket socket;

  /**
   * Creates a new ZMQRequester connecting to the given URL.
   * 
   * @param url URL of the server.
   * @throws Exception If an error happens while creating the socket.
   */
  public ZMQRequester(String url) { // throws Exception {

    Context context = ZMQ.context(1);
//    log.debug("Creating ZMQ REQ socket");
    socket = context.socket(ZMQ.REQ);
//    log.info("Starting requester on {}", url);
    socket.connect("tcp://" + url);
//    log.debug("Requester socket connected to {} ", url);
  }

  @Override protected void finalize() throws Throwable {
    socket.close();
  };

  /**
   * Make a request to the responder.
   * 
   * @param outgoing The message with the request.
   * @return The response from the server.
   */
  public byte[] request(byte[] outgoing) {

    socket.send(outgoing);
    return socket.recv();
  }
}
