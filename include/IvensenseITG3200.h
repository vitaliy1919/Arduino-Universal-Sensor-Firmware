#ifndef Invensense_ITG3200_h
#define Invensense_ITG3200_h
#include <Adafruit_Sensor.h>
#include "_ITG3200.h"

class IvensenseITG3200_Unified {
public:
    IvensenseITG3200_Unified( int sId,int addr):gyro(addr),gyro_ptr(&gyro), sensorAddress(addr), sensorId(sId){}
    class Temperature: public Adafruit_Sensor {
    public:
        Temperature(IvensenseITG3200_Unified *outer):parent(outer){}
        virtual bool begin() {
            parent->gyro.init();
            parent->gyro.zeroCalibrate(200,10);
            return true;
        }

        virtual bool getEvent(sensors_event_t *event) {
            // Serial.print("In ITG3200 temperature: ");
            memset(event, 0, sizeof(sensors_event_t));
            double temp = parent->gyro.getTemperature();
            // Serial.println(temp);
            event->version   = sizeof(sensors_event_t);
            event->sensor_id = parent->sensorId;
            event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
            event->timestamp = millis();
            event->temperature = temp;
            return true;
        }

        virtual void getSensor(sensor_t *sensor)
        {
            /* Clear the sensor_t object */
            memset(sensor, 0, sizeof(sensor_t));

            /* Insert the sensor name in the fixed length char array */
            strncpy(sensor->name, "ITG3200", sizeof(sensor->name) - 1);
            sensor->name[sizeof(sensor->name) - 1] = 0;
            sensor->version = 1;
            sensor->sensor_id = parent->sensorId;
            sensor->type = SENSOR_TYPE_AMBIENT_TEMPERATURE;
            sensor->min_delay = 0;
            sensor->max_value = -40; /* -16g = 156.9064 m/s^2  */
            sensor->min_value = 80;  /*  16g = 156.9064 m/s^2  */
            sensor->resolution = 0.03923F;  /*  4mg = 0.0392266 m/s^2 */
        }
    private:
        IvensenseITG3200_Unified *parent;
    };
    class Gyro: public Adafruit_Sensor {
    public:
        Gyro(IvensenseITG3200_Unified *outer): parent(outer){}
        virtual bool begin() {
            parent->gyro.init();
            parent->gyro.zeroCalibrate(200,10);
            return true;
        }

        virtual bool getEvent(sensors_event_t *event) {
            
            memset(event, 0, sizeof(sensors_event_t));
            float ax, ay, az;
            parent->gyro_ptr->getAngularVelocity(&ax, &ay, &az);
            event->version   = sizeof(sensors_event_t);
            event->sensor_id = parent->sensorId;
            event->type      = SENSOR_TYPE_GYROSCOPE;
            event->timestamp = millis();
            event->gyro.x = ax;
            event->gyro.y = ay;
            event->gyro.z = az;
        }

        virtual void getSensor(sensor_t *sensor)
        {
            /* Clear the sensor_t object */
            memset(sensor, 0, sizeof(sensor_t));

            /* Insert the sensor name in the fixed length char array */
            strncpy(sensor->name, "ITG3200", sizeof(sensor->name) - 1);
            sensor->name[sizeof(sensor->name) - 1] = 0;
            sensor->version = 1;
            sensor->sensor_id = parent->sensorId;
            sensor->type = SENSOR_TYPE_GYROSCOPE;
            sensor->min_delay = 0;
            sensor->max_value = -2000; /* -16g = 156.9064 m/s^2  */
            sensor->min_value = 2000;  /*  16g = 156.9064 m/s^2  */
            sensor->resolution = 0.03923F;  /*  4mg = 0.0392266 m/s^2 */
        }
    private:
        IvensenseITG3200_Unified *parent;
    };

    
private:
    _ITG3200 gyro;
    _ITG3200* gyro_ptr;
    int sensorAddress;
    int sensorId;
};

#endif