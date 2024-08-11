#include "freertos/task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_bt.h"
#include "esp_wifi.h"
// #include "nrf24.h"
#include "esp_log.h"
#include "mirf.h"

#define TAG "BLE_JAMMER"

// CE=10 SCK=4 MISO=5 CNS=2 MOSI=6

// nrf24 config
#define CONFIG_CSN_GPIO     2
#define CONFIG_SCLK_GPIO    4
#define CONFIG_MISO_GPIO    5
#define CONFIG_MOSI_GPIO    6
#define CONFIG_CE_GPIO      10

uint8_t channel = 45;
bool flag = true;

void app_main() {
    esp_wifi_stop();
    esp_wifi_deinit();
    esp_bt_controller_deinit();
    
    NRF24_t radio;
    Nrf24_init(&radio);

    Nrf24_setAutoAck(&radio, false);    //禁用自动应答
    Nrf24_disableCRC(&radio);           //禁用CRC
    Nrf24_stopListen(&radio)            //停止监听（设置为发射模式）
    Nrf24_setRetries(&radio, 0, 0);     //设置自动尝试次数为0
    Nrf24_SetOutputRF_PWR(&radio, RF24_PA_MAX);     //设置最大发射功率
    Nrf24_SetSpeedDataRates(&radio, RF24_2MBPS);    //设置速率2MBPS

    NRF24_startConstCarrier(&radio, RF24_PA_MAX, channel);

    while(1) {
        if(flag) {
            channel++;
        }
        else {
            channel--;
        }
        flag = (i < 79) ? true : false;
        Nrf24_setChannel(&radio, channel);
    }

}
