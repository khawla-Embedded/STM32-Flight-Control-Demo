// flight_data.h
#ifndef FLIGHT_DATA_H
#define FLIGHT_DATA_H

typedef struct {
    float pitch;     // Angle en radians
    float roll;      // Angle en radians
    float altitude;  // Altitude en mètres
    uint32_t timestamp_ms;
} FlightData;

#endif
