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

static const char *TAG = "espnow_master";


// CC:50:E3:33:2E:11
//  A4:CF:12:B0:A0:DA
// 5C:CF:7F:BE:21:B9
// 5C:CF:7F:86:E8:8A

// MAC addresses of the slaves
static uint8_t slave1_mac[ESP_NOW_ETH_ALEN] = {0xCC,0x50,0xE3,0x33,0x2E,0x11};
static uint8_t slave2_mac[ESP_NOW_ETH_ALEN] = {0xA4,0xCF,0x12,0xB0,0xA0,0xDA};
static uint8_t slave3_mac[ESP_NOW_ETH_ALEN] = {0x5C,0xCF,0x7F,0xBE,0x21,0xB9};
static uint8_t slave4_mac[ESP_NOW_ETH_ALEN] = {0x5C,0xCF,0x7F,0x86,0xE8,0x8A};
uint8_t broadcast_mac[ESP_NOW_ETH_ALEN] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};




static void example_espnow_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len) {
    ESP_LOGI(TAG, "MASTER CALLBACK ENTERED");
    if (!mac_addr || !data || len <= 0) return;

    if (len == 1) {
        // Status message
        ESP_LOGI(TAG, "Status from " MACSTR ": %s", MAC2STR(mac_addr), data[0] ? "BUSY" : "FREE");
    } else if (len == 2) {
        // ADC raw value (int16_t)
        int16_t raw;
        memcpy(&raw, data, sizeof(raw));
        ESP_LOGI(TAG, "ADC raw value from " MACSTR ": %d", MAC2STR(mac_addr), raw);
    
    } else {
        ESP_LOGW(TAG, "Unknown message length %d from " MACSTR, len, MAC2STR(mac_addr));
    }
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

static void espnow_send_task(void *pvParameter)
{
    uint8_t led_on  = 0x01;
    uint8_t led_off = 0x00;
    uint8_t ADC     = 0x02;
    uint8_t max     = 0x03;
    while (1)
    {
        
        // --- Turn ON all slaves' LEDs ---
        esp_now_send(slave1_mac, &led_on, sizeof(led_on));
        ESP_LOGI(TAG, "Sent LED ON to all slaves");
        esp_now_send(slave2_mac, &led_on, sizeof(led_on));
        ESP_LOGI(TAG, "Sent LED ON to all slaves");
         esp_now_send(slave3_mac, &led_on, sizeof(led_on));
        ESP_LOGI(TAG, "Sent LED ON to all slaves");
        esp_now_send(slave4_mac, &led_on, sizeof(led_on));
        ESP_LOGI(TAG, "Sent LED ON to all slaves");
        vTaskDelay(pdMS_TO_TICKS(2000));  // LED stays ON for 2 seconds

        // --- Turn OFF all slaves' LEDs ---
        esp_now_send(slave1_mac, &led_off, sizeof(led_off));
        ESP_LOGI(TAG, "Sent LED OFF to all slaves");
         esp_now_send(slave2_mac, &led_off, sizeof(led_off));
        ESP_LOGI(TAG, "Sent LED OFF to all slaves");
         esp_now_send(slave3_mac, &led_off, sizeof(led_off));
        ESP_LOGI(TAG, "Sent LED OFF to all slaves");
       esp_now_send(slave4_mac, &led_off, sizeof(led_off));
        ESP_LOGI(TAG, "Sent LED OFF to all slaves");
        vTaskDelay(pdMS_TO_TICKS(2000));  // LED stays OFF for 2 seconds


esp_err_t ADS = esp_now_send(slave3_mac, &ADC, sizeof(ADC));
        if (ADS == ESP_OK)
            ESP_LOGI(TAG, "Sent ADC request to slave3");
        else
            ESP_LOGE(TAG, "Failed to send ADC request: %d", ADS);


        vTaskDelay(pdMS_TO_TICKS(3000));  // Wait before next full cycle
    }
}


static void espnow_init(void)
{
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(example_espnow_recv_cb));

    // Add peers
    esp_now_peer_info_t peer;
    memset(&peer, 0, sizeof(peer));
    memcpy(peer.peer_addr, slave1_mac, ESP_NOW_ETH_ALEN);
    peer.channel = 1;
    peer.encrypt = false;
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));

    memset(&peer, 0, sizeof(peer));
    memcpy(peer.peer_addr, slave2_mac, ESP_NOW_ETH_ALEN);
    peer.channel = 1;
    peer.encrypt = false;
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));


        memset(&peer, 0, sizeof(peer));
    memcpy(peer.peer_addr, slave3_mac, ESP_NOW_ETH_ALEN);
    peer.channel = 1;
    peer.encrypt = false;
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));


            memset(&peer, 0, sizeof(peer));
    memcpy(peer.peer_addr, slave4_mac, ESP_NOW_ETH_ALEN);
    peer.channel = 1;
    peer.encrypt = false;
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));


        // uint8_t broadcast_mac[ESP_NOW_ETH_ALEN] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    // memset(&peer, 0, sizeof(peer));
    // memcpy(peer.peer_addr, broadcast_mac, ESP_NOW_ETH_ALEN);
    // peer.channel = 1;
    // peer.encrypt = false;
    // ESP_ERROR_CHECK(esp_now_add_peer(&peer));


    xTaskCreate(espnow_send_task, "espnow_send_task", 2048, NULL, 4, NULL);
}

void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init();
    espnow_init();
}









// // CC:50:E3:33:2E:11
// //  A4:CF:12:B0:A0:DA


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
