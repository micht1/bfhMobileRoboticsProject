/* Telemetry.java
 * Copyright (c) 2018, BFH
 * All rights reserved.
 */

package ch.bfh.roboticsLab.yellow;

import java.util.ArrayList;

import ch.bfh.roboticsLab.yellow.YellowProtoBuffer.StateName;

/**
 * This class holds a Yellow telemetry packet in a Java object.
 * 
 * @author gabriel.gruener@bfh.ch
 * @see yellow.proto
 */
public class Telemetry {

  /** State message. */
  public class State {
    /** Robot state. */
    public StateName stateName;

    @Override public String toString() {
      return new String("State = " + stateName);
    }
  }

  /**
   * Pose message. This message contains a robot global pose.
   */
  public class Pose {
    /** Estimated global x position [m] */
    public float x;
    /** Estimated global y position [m] */
    public float y;
    /** Estimated global orientation [rad] */
    public float alpha;

    @Override public String toString() {
      return new String("Pose = [ " + x + ", " + y + ", " + alpha + " ]");
    }
  }

  /**
   * Covariance matrix message. This message contains the covariance matrix of the pose estimation.
   */
  public class CovarianceMatrix {
    /** Covariance matrix. */
    public float[][] p = new float[3][3];

    @Override public String toString() {
      StringBuilder sb = new StringBuilder("[ ");
      for (int i = 0; i < p.length; i++) {
        for (int j = 0; j < p[0].length; j++) {
          sb.append(p[i][j]);
          sb.append(", ");
        }
        sb.delete(sb.length() - 2, sb.length());
        sb.append("\n");
      }
      sb.delete(sb.length() - 1, sb.length());
      sb.append(" ]");
      return sb.toString();
    }
  }

  /** Odometry message. */
  public class Odometry {
    /** Estimated global robot pose */
    public Pose pose;
    /** Covariance matrix of the pose estimation */
    public CovarianceMatrix covarianceMatrix;

    /** Creates a default Odometry object. */
    public Odometry() {
      pose = new Pose();
      covarianceMatrix = new CovarianceMatrix();
    }

    @Override public String toString() {
      return new String("Pose: " + pose + "\nCovariance Matrix:\n" + covarianceMatrix);
    }
  }

  /**
   * LIDAR point message. This message contains one individual LIDAR point measurement.
   */
  public class LidarPoint {
    /** The angle of the LIDAR measurement */
    public int angle;
    /** The distance measured */
    public int distance;
    /** The quality level of the measurement */
    public int quality;

    @Override public String toString() {
      return new String("[ " + angle + ", " + distance + ", " + quality + " ]");
    }
  }

  /**
   * LIDAR message. This message contains an array of LIDAR point measurements.
   */
  public class Lidar {
    /** Lidar message timestamp */
    public int timestamp;
    /** Array of Lidar points. */
    public ArrayList<LidarPoint> points = new ArrayList<>();

    @Override public String toString() {
      return new String("Lidar at time: " + timestamp + "\n" + points);
    }
  }

  /**
   * One line (from LIDAR analysis).
   */
  public class Line {
    /** Line start pose (note 'alpha' is meaningless if 'end' is not null). */
    public Pose start;
    /** Line end pose. */
    public Pose end;

    public Line() {
      start = new Pose();
      end = new Pose();
    }

    @Override public String toString() {
      return new String("[ " + start + "; " + end + " ]");
    }
  }

  /**
   * LIDAR line analysis message. This message contains an array of lines found through LIDAR analysis.
   */
  public class LidarLines {
    /** Lines found. */
    public ArrayList<Line> lines;

    public LidarLines() {
      lines = new ArrayList<>();
    }
    @Override public String toString() {
      return new String("Lidar lines: " + lines);
    }
  }

  /**
   * IR Sensor message. This message contains one IR sensor measurement.
   */
  public class IRSensor {
    /** IR sensor measurement distance [m]. */
    public float distance;

    @Override public String toString() {
      return new String("" + distance);
    }
  }

  public class IRSensors {
    /** Lidar message timestamp */
    public int timestamp;
    /** Array of IR sensors. */
    public ArrayList<IRSensor> sensors = new ArrayList<>();

    @Override public String toString() {
      return new String("IRSensors: " + sensors);
    }
  }

  /** Telemetry message timestamp */
  public int timestamp;
  /** State entry. */
  public State state;
  /** Odometry entry. */
  public Odometry odometry;
  /** Lidar entry. */
  public Lidar lidar;
  public LidarLines lidarLines;
  public IRSensors ir;

  /** Create a new default Telemetry object with no contents and timestamp 0. */
  public Telemetry() {}

  @Override public String toString() {
    return new String("At time: " + timestamp + "\nstate: " + (state != null ? state : "null") + "\n" + (odometry != null ? odometry : "null") + "\n"
        + (lidar != null ? lidar : "null") + "\n"
        + (lidarLines != null ? lidarLines : "null") + "\n"
        + ir);

  }
}
