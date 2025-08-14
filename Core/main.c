#include "flight_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void HAL_Delay(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 1000; i++);
}

uint32_t HAL_GetTick() {
    static uint32_t tick = 0;
    return tick++;
}
// Exemple de lecture capteur
void MPU6050_Read(float* pitch, float* roll) {
    uint8_t data[6];
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H, 1, data, 6, 100);
    *pitch = (int16_t)(data[0] << 8 | data[1]) / 16384.0f;
    *roll = (int16_t)(data[2] << 8 | data[3]) / 16384.0f;
}

int main(void) {
    FlightData flight;
    
    while (1) {
        // Simulation de données réalistes
        flight.pitch = 0.1f * sinf(HAL_GetTick() * 0.001f);
        flight.roll = 0.2f * cosf(HAL_GetTick() * 0.0015f);
        flight.altitude = 1000 + rand() % 50;
        flight.timestamp_ms = HAL_GetTick();

        // Envoi des données via UART (simulé avec printf)
        printf("%.2f,%.2f,%.1f,%lu\n", 
               flight.pitch, flight.roll, flight.altitude, flight.timestamp_ms);
        
        HAL_Delay(100); // 10Hz
    }
}
