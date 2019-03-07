/* Copyright (C) 2018, BFH roboticsLab
 * All rights reserved.
 */

package ch.bfh.roboticsLab.util;

import java.util.Observable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Context;
import org.zeromq.ZMQ.Socket;

/**
 * <p>
 * This class defines a 0MQ subscriber and extends observable. If you want to be notified when incoming packets arrive you need to use
 * {@link #addObserver(java.util.Observer)}.
 * </p>
 * <p>
 * Example:
 * </p>
 * 
 * <pre>
 * ZMQSubscriber subscriber = new ZMQSubscriber("localhost:1234");
 * subscriber.addObserver((object, argument) -> {
 *   // Process 'argument' which contains the incoming message
 * });
 * </pre>
 * 
 * Note: This implementation is compatible to Java 1.6 so it is usable on the Kuka LBR iiwa.
 *
 * @author gabriel.gruener@bfh.ch
 */
public class ZMQSubscriber extends Observable {

//  private final Logger log = LogManager.getLogger();
  private Future<?> future;

  /**
   * Create a new ZMQSubscriber that subscribes to a publisher on the given url.
   * 
   * @param url URL of the publisher.
   */
  public ZMQSubscriber(final String url) {
    ExecutorService executor = Executors.newFixedThreadPool(1);
    future = executor.submit(new Runnable() {
      @Override public void run() {
//        log.debug("Creating ZMQ context");
        Context context = ZMQ.context(1);
//        log.debug("Creating ZMQ SUB socket");
        Socket inputSocket = context.socket(ZMQ.SUB);
//        log.info("Starting subscriber on {}", url);
        inputSocket.connect("tcp://" + url);
        // Subscribe to all messages
        inputSocket.subscribe(new byte[] {});
//        log.debug("Subscriber socket bound to: {}", url);
        while (!Thread.currentThread().isInterrupted()) {
          try {
            byte[] incoming = inputSocket.recv();
            setChanged();
            notifyObservers(incoming);
            // ProtoCommunication.RobotTelemetry telemetry = ProtoCommunication.RobotTelemetry.parseFrom();
            // // log.debug("Received telemetry: {}", telemetry);
            // processTelemetry(telemetry);
          } catch (Exception e) {
//            log.warn("Error reading from {}: {}", url, e);
          }
        }
//        log.info("Subscriber disconnected");
      }
    });
  }

  @Override protected void finalize() throws Throwable {
    if (future != null) future.cancel(true);
  }
}
