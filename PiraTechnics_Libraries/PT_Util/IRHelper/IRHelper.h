#ifndef IRHELPER_H
#define IRHELPER_H

/**
 * @brief IRHelper class by PiraTechnics for interfacing with infrared (IR) sensors.
 */
class IRHelper {
public:
  /**
   * @brief Constructor to initialize IRHelper instance with custom values.
   * 
   * @param pin The analog pin to which the IR sensor is connected.
   * @param thresh The threshold value for sensor readings.
   * @param dist The exact distance away from the sensor.
   * @param tol The tolerance range for the exact distance.
   */
  IRHelper(int pin, int thresh, int dist, int tol);
  
  /**
   * @brief Constructor to initialize IRHelper instance with custom threshold and distance values.
   * 
   * @param pin The analog pin to which the IR sensor is connected.
   * @param thresh The threshold value for sensor readings.
   * @param dist The exact distance away from the sensor.
   */
  IRHelper(int pin, int thresh, int dist);
  
  /**
   * @brief Constructor to initialize IRHelper instance with custom threshold value.
   * 
   * @param pin The analog pin to which the IR sensor is connected.
   * @param thresh The threshold value for sensor readings.
   */
  IRHelper(int pin, int thresh);
  
  /**
   * @brief Constructor to initialize IRHelper instance with default values.
   * 
   * @param pin The analog pin to which the IR sensor is connected.
   */
  IRHelper(int pin);
  
  /**
   * @brief Reads the sensor value from the connected analog pin.
   * 
   * @return The sensor value.
   */
  int sensorRead();
  
  /**
   * @brief Checks if the sensor reading is above the threshold.
   * 
   * @return True if the sensor reading is above the threshold, false otherwise.
   */
  bool sensorFlagged();
  
  /**
   * @brief Adjusts the threshold value for sensor readings.
   * 
   * @param thresh The new threshold value.
   */
  void adjustThreshold(int thresh);
  
  /**
   * @brief Adjusts the exact distance away from the sensor.
   * 
   * @param dist The new exact distance value.
   */
  void adjustDistance(int dist);
  
  /**
   * @brief Adjusts the tolerance range around the exact distance.
   * 
   * @param tol The new tolerance value.
   */
  void adjustTolerance(int tol);
  
  /**
   * @brief Checks if the sensor reading falls within the specified tolerance range around the exact distance.
   * 
   * @param tol The tolerance value to use for the check.
   * @return True if the sensor reading falls within the specified tolerance range, false otherwise.
   */
  bool distanceMet(int tol);
  
  /**
   * @brief Checks if the sensor reading falls within the default tolerance range around the exact distance.
   * 
   * @return True if the sensor reading falls within the default tolerance range, false otherwise.
   */
  bool distanceMet();
  
  /**
   * @brief Getter method for retrieving the current threshold value.
   * 
   * @return The current threshold value.
   */
  int getThreshold();
  
  /**
   * @brief Getter method for retrieving the current exact distance value.
   * 
   * @return The current exact distance value.
   */
  int getDistance();
  
  /**
   * @brief Getter method for retrieving the current tolerance value.
   * 
   * @return The current tolerance value.
   */
  int getTolerance();

private:
  static int sensorPin; ///< The analog pin to which the IR sensor is connected.
  static int threshold; ///< The threshold value for sensor readings.
  static int distance;  ///< The exact distance away from the sensor.
  static int tolerance; ///< The tolerance range for the exact distance.
};

#endif
