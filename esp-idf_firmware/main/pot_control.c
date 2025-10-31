#include <stdio.h>
#include "pot_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"
#include "dsp.h"
#include "bt_app_av.h"

#define POT_ADC_CHANNEL     ADC1_CHANNEL_4  // GPIO 32
#define POT_ADC_ATTEN       ADC_ATTEN_DB_11
#define POT_ADC_WIDTH       ADC_WIDTH_BIT_12

#define VOLUME_MIN_DB       -75  // Minimum volume in dB (from sysmgmt.c)
#define VOLUME_MAX_DB       30   // Maximum volume in dB (from dsp.c)
#define AVRCP_VOLUME_MAX    127  // AVRCP standard maximum volume

#define HYSTERESIS_THRESHOLD 20  // ADC units to prevent noise triggering changes
#define POT_READ_INTERVAL_MS 100 // Read potentiometer every 100ms

static const char* TAG = "POT_CTRL";
static uint16_t last_adc_value = 0;
static uint8_t current_avrcp_volume = 0;
static int8_t current_master_volume_db = -9;

/**
 * @brief Convert ADC reading (0-4095) to Master Volume in dB (-75 to +30)
 */
static int8_t adc_to_master_volume_db(uint16_t adc_value)
{
    // Map 0-4095 to -75 to +30 dB
    int32_t volume_range = VOLUME_MAX_DB - VOLUME_MIN_DB; // 105
    int32_t volume_db = VOLUME_MIN_DB + ((int32_t)adc_value * volume_range) / 4095;

    // Clamp to valid range
    if (volume_db < VOLUME_MIN_DB) volume_db = VOLUME_MIN_DB;
    if (volume_db > VOLUME_MAX_DB) volume_db = VOLUME_MAX_DB;

    return (int8_t)volume_db;
}

/**
 * @brief Convert ADC reading (0-4095) to AVRCP volume (0-127)
 */
static uint8_t adc_to_avrcp_volume(uint16_t adc_value)
{
    // Map 0-4095 to 0-127
    uint32_t avrcp_vol = ((uint32_t)adc_value * AVRCP_VOLUME_MAX) / 4095;

    // Clamp to valid range
    if (avrcp_vol > AVRCP_VOLUME_MAX) avrcp_vol = AVRCP_VOLUME_MAX;

    return (uint8_t)avrcp_vol;
}

/**
 * @brief Task that continuously reads potentiometer and updates volume
 */
static void potentiometer_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Potentiometer task started");

    // Read initial value
    last_adc_value = adc1_get_raw(POT_ADC_CHANNEL);
    current_master_volume_db = adc_to_master_volume_db(last_adc_value);
    current_avrcp_volume = adc_to_avrcp_volume(last_adc_value);

    ESP_LOGI(TAG, "Initial ADC: %d, Master Volume: %d dB, AVRCP Volume: %d",
             last_adc_value, current_master_volume_db, current_avrcp_volume);

    while (1) {
        // Read current ADC value
        uint16_t adc_value = adc1_get_raw(POT_ADC_CHANNEL);

        // Check if value changed significantly (hysteresis)
        int16_t adc_diff = adc_value - last_adc_value;
        if (adc_diff < 0) adc_diff = -adc_diff; // Absolute value

        if (adc_diff > HYSTERESIS_THRESHOLD) {
            // Calculate new volumes
            int8_t new_master_volume_db = adc_to_master_volume_db(adc_value);
            uint8_t new_avrcp_volume = adc_to_avrcp_volume(adc_value);

            // Update if changed
            if (new_master_volume_db != current_master_volume_db ||
                new_avrcp_volume != current_avrcp_volume) {

                ESP_LOGI(TAG, "Volume changed - ADC: %d, Master: %d dB, AVRCP: %d (%d%%)",
                         adc_value, new_master_volume_db, new_avrcp_volume,
                         (new_avrcp_volume * 100) / AVRCP_VOLUME_MAX);

                // Update local (ESP32) volume
                SetMasterVolume(new_master_volume_db);

                // Notify phone/remote device about volume change
                volume_set_by_local_host(new_avrcp_volume);

                // Update state
                current_master_volume_db = new_master_volume_db;
                current_avrcp_volume = new_avrcp_volume;
                last_adc_value = adc_value;
            }
        }

        // Wait before next reading
        vTaskDelay(POT_READ_INTERVAL_MS / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Initialize potentiometer ADC and start reading task
 */
void initPotentiometer()
{
    ESP_LOGI(TAG, "Initializing potentiometer on GPIO 32 (ADC1_CHANNEL_4)");

    // Configure ADC width (12-bit resolution: 0-4095)
    adc1_config_width(POT_ADC_WIDTH);

    // Configure ADC attenuation for full voltage range (0-3.3V)
    adc1_config_channel_atten(POT_ADC_CHANNEL, POT_ADC_ATTEN);

    // Create potentiometer reading task
    xTaskCreatePinnedToCore(
        potentiometer_task,
        "pot_task",
        2048,
        NULL,
        configMAX_PRIORITIES - 3,
        NULL,
        0
    );

    ESP_LOGI(TAG, "Potentiometer initialization complete");
}

/**
 * @brief Get current potentiometer volume (0-127 for AVRCP)
 */
uint8_t getPotentiometerVolume()
{
    return current_avrcp_volume;
}
