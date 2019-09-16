#ifndef Sparkfun_ADXL345_h
#define Sparkfun_ADXL345_h

#include <Adafruit_Sensor.h>

inline int ReadAxis(int axisPin, int sampleSize)
{
    long reading = 0;
    analogRead(axisPin);
    delay(1);
    for (int i = 0; i < sampleSize; i++)
    {
        reading += analogRead(axisPin);
    }
    return reading / sampleSize;
}
class Spartkfun_ADXL345_Unified: public Adafruit_Sensor {
public:
    Spartkfun_ADXL345_Unified(int sId, int pX, int pY, int pZ): sensorId(sId), portX(pX),portY(pY),portZ(pZ) {}
    virtual bool begin() {return true;}
    virtual bool getEvent(sensors_event_t *event) {
        memset(event, 0, sizeof(sensors_event_t));
        int xRaw = ReadAxis(portX, 10);
        int yRaw = ReadAxis(portY, 10);
        int zRaw = ReadAxis(portZ, 10);
        float maxG = 3.6;
        // Convert raw values to 'milli-Gs"
        long xScaled = map(xRaw, RawMin, RawMax, -1000*maxG, 1000*maxG);
        long yScaled = map(yRaw, RawMin, RawMax, -1000*maxG, 1000*maxG);
        long zScaled = map(zRaw, RawMin, RawMax, -1000*maxG, 1000*maxG);

        // re-scale to fractional Gs
        float xAccel = (float)xScaled / 1000.0;
        float yAccel = (float)yScaled / 1000.0;
        float zAccel = (float)zScaled / 1000.0;
        event->version   = sizeof(sensors_event_t);
        event->sensor_id = sensorId;
        event->type      = SENSOR_TYPE_ACCELEROMETER;
        event->timestamp = millis();
        event->acceleration.x = xAccel*SENSORS_GRAVITY_EARTH;
        event->acceleration.y = yAccel*SENSORS_GRAVITY_EARTH;
        event->acceleration.z = zAccel*SENSORS_GRAVITY_EARTH;
  
        return true;
    }
    virtual void getSensor(sensor_t *sensor)
    {
        /* Clear the sensor_t object */
        memset(sensor, 0, sizeof(sensor_t));

        /* Insert the sensor name in the fixed length char array */
        strncpy(sensor->name, "ADXL345", sizeof(sensor->name) - 1);
        sensor->name[sizeof(sensor->name) - 1] = 0;
        sensor->version = 1;
        sensor->sensor_id = sensorId;
        sensor->type = SENSOR_TYPE_ACCELEROMETER;
        sensor->min_delay = 0;
        sensor->max_value = -3.6*SENSORS_GRAVITY_EARTH; /* -16g = 156.9064 m/s^2  */
        sensor->min_value = 3.6F*SENSORS_GRAVITY_EARTH;  /*  16g = 156.9064 m/s^2  */
        sensor->resolution = 0.03923F;  /*  4mg = 0.0392266 m/s^2 */
    }

private:
    int portX, portY, portZ;
    int sensorId;
    const static int RawMin = 0;
    const static int RawMax = 1023;
} ;
#endif  // Adafruit_ADXL345_h