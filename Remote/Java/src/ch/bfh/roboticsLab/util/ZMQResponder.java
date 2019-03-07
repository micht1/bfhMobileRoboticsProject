/* Copyright (C) 2018, BFH roboticsLab
 * All rights reserved.
 */

package ch.bfh.roboticsLab.util;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Context;

/**
 * <p>
 * This class defines an abstract ZMQResponder that responds to requests.
 * </p>
 * <p>
 * Implementing classes must implement the #request method that will be called when a request arrives.
 * </p>
 * <p>
 * Example:
 * </p>
 * 
 * <pre>
 * public class MyZMQResponder extends ZMQResponder {
 *   public MyZMQResponder(int port) {
 *     super(port);
 *   }
 * 
 *   public byte[] respond(byte[] request) {
 *     // Parse the request and send a response
 *     byte[] response = new byte[] { 0, 0, 0, 0 };
 *     return response;
 *   }
 * }
 * </pre>
 * 
 * Note: This implementation is compatible to Java 1.6 so it is usable on the Kuka LBR iiwa.
 *
 * @author gabriel.gruener@bfh.ch
 */
public abstract class ZMQResponder {

  private final Logger log = LogManager.getLogger();
  private Future<?> future;

  /**
   * Creates a new ZMQRequester connecting to the given URL.
   * 
   * @param port Port to listen to for incoming requests.
   * @throws Exception If an error happens while creating the socket.
   */
  public ZMQResponder(final int port) {

    ExecutorService executor = Executors.newFixedThreadPool(1);

    future = executor.submit(new Runnable() {
      @Override public void run() {
        Context context = ZMQ.context(1);
        log.debug("Creating ZMQ REP socket");
        org.zeromq.ZMQ.Socket socket = context.socket(ZMQ.REP);
        log.info("Starting gripper command responder on port {}", port);
        socket.bind("tcp://*:" + port);
        log.debug("Gripper command responder socket ready on port {} ", port);
        while (!Thread.currentThread().isInterrupted()) {
          byte[] incoming = socket.recv();
          socket.send(respond(incoming));
        }
        socket.close();
      }
    });
  }

  /**
   * Responds to a request.
   * 
   * @param incoming Incoming request.
   * @return Outgoing response.
   */
  public abstract byte[] respond(byte[] incoming);

  @Override protected void finalize() throws Throwable {
    if (future != null) future.cancel(true);
  };

}
