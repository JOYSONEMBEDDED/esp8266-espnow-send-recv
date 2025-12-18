#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_now.h"
#include "esp_system.h"
#include "tcpip_adapter.h"
#include "driver/gpio.h"
#include "ads111x.h"

static const char *TAG = "espnow_slave";
static bool node_busy = false;

// Master's MAC address
static uint8_t master_mac[ESP_NOW_ETH_ALEN] = {0x60,0x01,0x94,0x06,0x46,0xAD};

// Built-in LED (GPIO2 for most ESP8266 boards)
#define LED_GPIO 2
#define SDA_GPIO 4
#define SCL_GPIO 5
#define I2C_PORT 0


static i2c_dev_t ads_dev;      // global descriptor
static float ads_gain_val;     // gain factor

// --- INIT FUNCTION ---
void ads1115_init(void)
{
    i2cdev_init(); // initialize i2cdev library

    if (ads111x_init_desc(&ads_dev, ADS111X_ADDR_GND, I2C_PORT, SDA_GPIO, SCL_GPIO) != ESP_OK) {
        printf("Failed to init ADS1115\n");
        return;
    }

    ads111x_set_mode(&ads_dev, ADS111X_MODE_SINGLE_SHOT);
    ads111x_set_gain(&ads_dev, ADS111X_GAIN_4V096);
    ads111x_set_input_mux(&ads_dev, ADS111X_MUX_0_GND);

    ads_gain_val = ads111x_gain_values[ADS111X_GAIN_4V096];

    printf("ADS1115 initialized.\n");
}

// --- MEASURE FUNCTION ---
float ads1115_measure(void)
{
    int16_t raw = 0;
    if (ads111x_get_value(&ads_dev, &raw) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read ADS1115");
        return -1.0f;  // error
    }

    float voltage = (ads_gain_val / ADS111X_MAX_VALUE) * raw;
    ESP_LOGI(TAG, "Raw: %d, Voltage: %.4f V", raw, voltage);

    // Send ADC raw value to master
    esp_err_t res = esp_now_send(master_mac, &raw, sizeof(raw));
    if (res != ESP_OK) {
        ESP_LOGE(TAG, "Failed to send ADC to master: %d", res);
    }

    return voltage;
}



// add send callback
static void example_espnow_send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (!mac_addr) return;
    ESP_LOGI(TAG, "Slave send cb: to " MACSTR " status=%d", MAC2STR(mac_addr), status);
}

static void example_espnow_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len)
{
    if (!mac_addr || !data || len <= 0) return;

    ESP_LOGI(TAG, "RX from " MACSTR " len=%d", MAC2STR(mac_addr), len);
    printf("RX data: ");
    for (int i = 0; i < len; ++i) printf("%02X ", data[i]);
    printf("\n");

    uint8_t cmd = data[0];
    switch (cmd) {
        case 0x01:
            gpio_set_level(LED_GPIO, 1);
            ESP_LOGI(TAG, "LED turned ON");
            break;
        case 0x00:
            gpio_set_level(LED_GPIO, 0);
            ESP_LOGI(TAG, "LED turned OFF");
            break;
        case 0x02:
            node_busy = true;
            // ads1115_measure();
            node_busy = false;
            break;
        default:
            ESP_LOGW(TAG, "Unknown command: 0x%02X", cmd);
            break;
    }

    uint8_t status = node_busy ? 0x01 : 0x00;
    esp_err_t res = esp_now_send(master_mac, &status, sizeof(status));
    ESP_LOGI(TAG, "reply status esp_now_send result: %d", res);
}



static void wifi_init(void)
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_channel(1, 0));
}

static void espnow_init(void)
{
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(example_espnow_recv_cb));
        ESP_ERROR_CHECK(esp_now_register_send_cb(example_espnow_send_cb)); // added


    // Add master as peer
    esp_now_peer_info_t peer;
    memset(&peer, 0, sizeof(peer));
    memcpy(peer.peer_addr, master_mac, ESP_NOW_ETH_ALEN);
    peer.channel = 1;
    peer.encrypt = false;
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));
}






void app_main()
{
     ESP_ERROR_CHECK(nvs_flash_init());
        gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);

    gpio_set_level(LED_GPIO, 1); // Start with LED OFF
        // ads1115_init();   
   
    wifi_init();
    espnow_init();
}



// #include "esp_wifi.h"
// #include "esp_log.h"
// #include "nvs_flash.h"
// #include "esp_event.h"
// #include "tcpip_adapter.h"

// static const char *TAG = "wifi_init";

// void wifi_init(void)
// {
//     // 1. Init NVS
//     ESP_ERROR_CHECK(nvs_flash_init());

//     // 2. Init TCP/IP stack
//     tcpip_adapter_init();

//     // 3. Init default event loop
//     ESP_ERROR_CHECK(esp_event_loop_create_default());

//     // 4. Configure Wi-Fi
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));
//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
//     ESP_ERROR_CHECK(esp_wifi_start());

//     // 5. Print MAC address
//     uint8_t mac[6];
//     ESP_ERROR_CHECK(esp_wifi_get_mac(WIFI_IF_STA, mac));
//     ESP_LOGI(TAG, "Device MAC address: %02X:%02X:%02X:%02X:%02X:%02X",
//              mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
// }

// void app_main()
// {
//     wifi_init();
//     // other init code
// }