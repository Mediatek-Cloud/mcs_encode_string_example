#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "os.h"
#include "net_init.h"
#include "network_init.h"
#include "wifi_api.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "lwip/sockets.h"
#include "ethernetif.h"
#include "lwip/sockets.h"
#include "netif/etharp.h"
#include "mcs.h"

/* md5 module */
#include "hal_md5.h"
#define MAX_DATA_SIZE 1024

/* mcs setting */
#define ENCODE_MD5_CHANNEL "encodeByMD5"
#define DECODE_MD5_CHANNEL "decodeByMD5"

void wifi_connect_init(void *args)
{
    LOG_I(common, "enter connect init.");
    uint8_t opmode  = WIFI_MODE_STA_ONLY;
    uint8_t port = WIFI_PORT_STA;

    /* ssid */
    char ssid[15];
    int nvdm_ssid_len = sizeof(ssid);
    nvdm_read_data_item("STA", "Ssid", (uint8_t *)ssid, (uint32_t *)&nvdm_ssid_len);

    /* password */
    char pwd[15];
    int nvdm_pwd_len = sizeof(pwd);
    nvdm_read_data_item("STA", "Password", (uint8_t *)pwd, (uint32_t *)&nvdm_pwd_len);

    // nvram set STA Ssid mcs
    // nvram set STA password mcs12345678

    wifi_auth_mode_t auth = WIFI_AUTH_MODE_WPA_PSK_WPA2_PSK;
    wifi_encrypt_type_t encrypt = WIFI_ENCRYPT_TYPE_TKIP_AES_MIX;

    uint8_t nv_opmode;

    if (wifi_config_init() == 0) {
        wifi_config_get_opmode(&nv_opmode);
        if (nv_opmode != opmode) {
            wifi_config_set_opmode(opmode);
        }
        wifi_config_set_ssid(port, ssid ,strlen(ssid));
        wifi_config_set_security_mode(port, auth, encrypt);
        wifi_config_set_wpa_psk_key(port, pwd, strlen(pwd));
        wifi_config_reload_setting();

        network_dhcp_start(opmode);
    }
    vTaskDelete(NULL);
}

void tcp_callback(char *rcv_buf) {
    char *arr[7];
    char *del = ",";
    mcs_split(arr, rcv_buf, del);
    // Dln7lL0G,zLfxhiabFnCEZZJc,1459307476444,encodeByMD5,test
    if (0 == strncmp (arr[3], ENCODE_MD5_CHANNEL, strlen(ENCODE_MD5_CHANNEL))) {
        /* encode BY MD5 */
        uint8_t digest[HAL_MD5_DIGEST_SIZE] = {0};
        printf("User give: %s \n", arr[4]);
        hal_md5_context_t context = {0};
        hal_md5_init(&context);
        hal_md5_append(&context, arr[4], strlen(arr[4]));
        hal_md5_end(&context, digest);

        uint8_t i;
        char str_buffer [50] = {0};
        strcpy(str_buffer, "");
        for (i = 0; i < sizeof(digest); i++) {
          if (i % 16 == 0) {
              printf("\r\n");
          }
          char buffer [2];
          sprintf (buffer, "%02x", digest[i]);
          strcat(str_buffer, buffer);
        }

        /* send to MCS */
        char data_buf [MAX_DATA_SIZE] = {0};
        strcat(data_buf, DECODE_MD5_CHANNEL);
        strcat(data_buf, ",,");
        strcat(data_buf, str_buffer);
        mcs_upload_datapoint(data_buf);
    }
}

void wifi_connected_task(void *parameter) {
  mcs_tcp_init(tcp_callback);
  for (;;) {
    ;
  }
}

void wifi_connected_init(const struct netif *netif) {
  xTaskCreate(wifi_connected_task, "wifiConnectedTask", 8048, NULL, 2, NULL);
}

int main(void)
{
    system_init();
    wifi_register_ip_ready_callback(wifi_connected_init);
    network_init();
    xTaskCreate(wifi_connect_init, "wifiConnect", 1024, NULL, 1, NULL);
    smart_config_if_enabled();
    vTaskStartScheduler();
    while (1) {
    }
    return 0;
}


