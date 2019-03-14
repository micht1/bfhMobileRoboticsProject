/* SerialClient.java
 * Copyright (c) 2018, BFH
 * All rights reserved.
 */

package ch.bfh.roboticsLab.yellow;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * This class allows to encode and decode byte arrays to be handled through a serial (UART) interface. The encoding used here must match the one used
 * on the Yellow robot. Note: This encoding is necessary because the Yellow robot has only serial access to the WiFi connection. That is, there is no
 * TCP/IP stack to handle packet communication.
 * 
 * @author gabriel.gruener@bfh.ch
 */
public class SerialEncoder {

  /** The communication message start delimiter. */
  public static final byte START_DELIMITER = (byte) 0x7E;
  /** The communication message escape byte. */
  public static final byte ESCAPE_BYTE = (byte) 0x7D;
  /** The communication message escape modifier. */
  public static final byte ESCAPE_MODIFIER = (byte) 0x20;

  /**
   * Create a new SerialEncoder object.
   */
  public SerialEncoder() {
    readState = ReadState.WAITING_FOR_HEADER;
    encodedMessage = new ArrayList<>();
    checksum = 0;
  }

  /** Flag whether we just read a escape byte. */
  private boolean escapedByte;
  /** Payload size. */
  private int payloadSize;
  /** Payload read. */
  private byte[] payload;
  /** Counter of payload bytes read. */
  private int byteCounter;

  /**
   * State of read buffer.
   * 
   * @see #push
   */
  public enum ReadState {
    /** Waiting for the header byte to arrive. */
    WAITING_FOR_HEADER,
    /** Reading first size byte. */
    SIZE_1,
    /** Reading second size byte. */
    SIZE_2,
    /** Reading payload bytes. */
    PAYLOAD,
    /** Reading CRC byte. */
    CRC,
    /** CRC mismatch */
    ERROR,
    /** Done reading, message is ready. */
    DONE;
  };

  /** The current read state. */
  private ReadState readState;

  /** Reset the read decoder so it is ready to decode the next incoming message. */
  public void reset() {
    readState = ReadState.WAITING_FOR_HEADER;
  }

  /**
   * Retrieve the state of the read decoder.
   * 
   * @return
   */
  public ReadState getState() {
    return readState;
  }

  /**
   * Pushes a received byte into the message, removing escaped bytes and checksum. Updates #readState as the payload is parsed, arriving to the state
   * ReadState.DONE when the message is complete.
   * 
   * @param i the byte received.
   */
  public ReadState push(int i) {

    byte b = (byte) (i & 0xFF);

    if (b == ESCAPE_BYTE) {
      escapedByte = true;
      return readState;
    }

    if (escapedByte) {
      b = (byte) (b ^ ESCAPE_MODIFIER);
      escapedByte = false;
    }

    switch (readState) {
    case WAITING_FOR_HEADER:
      if (b == START_DELIMITER) readState = ReadState.SIZE_1;
      break;
    case SIZE_1:
      payloadSize = ((int) b & 0xFF) << 8;
      readState = ReadState.SIZE_2;
      break;
    case SIZE_2:
      payloadSize += ((int) b) & 0xFF;
      if (payloadSize <= 0) {
        System.err.println("Bad size: " + payloadSize);
        readState = ReadState.ERROR;
      } else {
        payload = new byte[payloadSize];
        byteCounter = 0;
        readState = ReadState.PAYLOAD;
      }
      break;
    case PAYLOAD:
      payload[byteCounter++] = b;
      if (byteCounter == payloadSize) readState = ReadState.CRC;
      break;
    case CRC:
      byte crc = b;
      int checksum = 0;
      for (byte p : payload)
        checksum += ((int) p & 0xFF);
      byte myCRC = (byte) (0xFF - (checksum & 0xFF));
      if (crc != myCRC) {
        System.err.println("Checksum mismatch: got 0x" + Integer.toHexString(myCRC) + ", expected 0x" + Integer.toHexString(crc));
        readState = ReadState.ERROR;
      }
      readState = ReadState.DONE;
      break;
    case ERROR:
    case DONE:
      break;
    }

    return readState;
  }

  /**
   * Retrieves the decoded message. Note the message will only be complete if the decode state is ReadState.DONE
   * 
   * @return Byte array with message payload.
   */
  public byte[] getMessage() {
    byte[] m = Arrays.copyOf(payload, payload.length);
    reset();
    return m;
  }

  /**
   * ArrayList to store an encoded message of unknown length. Note the length is unknown because we don't know how many bytes will be escaped.
   */
  private ArrayList<Byte> encodedMessage;
  /** Encoded message checksum. */
  int checksum;

  /**
   * Encode the given byte array for serial transmission.
   * 
   * @param payload The byte array to encode.
   * @return The encoded byte array.
   */
  public byte[] encode(byte[] payload) {

    encodedMessage.clear();
    encodedMessage.add(START_DELIMITER);

    int size = payload.length;
    escapeData((byte) ((size & 0xff00) >> 8));
    escapeData((byte) (size & 0x00ff));

    checksum = 0; // checksum does not include start delimiter and size
    for (int i = 0; i < size; ++i) {
      escapeData(payload[i]);
    }

    escapeData(crc());

    byte[] out = new byte[encodedMessage.size()];
    for (int i = 0; i < out.length; i++)
      out[i] = encodedMessage.get(i);
    return out;
  }

  /**
   * Escapes a byte, if necessary, before putting it in the encoded message.
   * 
   * @param data Byte to escape, if necessary.
   */
  private void escapeData(byte data) {
    checksum += data;
    switch (data) {
    case START_DELIMITER:
    case ESCAPE_BYTE:
      encodedMessage.add(ESCAPE_BYTE);
      encodedMessage.add((byte) (data ^ ESCAPE_MODIFIER));
      break;
    default:
      encodedMessage.add(data);
      break;
    }
  }

  /**
   * Retrieves the encoded message CRC.
   * 
   * @return The CRC.
   */
  private byte crc() {
    return (byte) (0xFF - (checksum & 0xFF));
  }

}
