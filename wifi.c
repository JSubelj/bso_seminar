#include "wifi.h"


// TODO: Če ne obstaja configuracija v flashu potem pejt v AP mode
// TODO: Če je AP mode flag nastavlen pejt v AP mode

void wifi_config(){
    struct ip_info ipconfig;
    /*struct whole_config full_config={
        .ip={10,0,0,83},
        .gw={10,6,4,210},
        .netmask={255,255,255,0},
        .ssid=WIFI_SSID,
        .pass=WIFI_PASS,
        .dhcp_static=1
    };**/

    

    //write_config_to_flash(&full_config);

    IP4_ADDR(&ipconfig.ip, 10,6,4,83); 
    IP4_ADDR(&ipconfig.gw, 10,6,4,210); 
    IP4_ADDR(&ipconfig.netmask, 255,255,255,0); 

    

    /* required to call wifi_set_opmode before station_set_config */
    sdk_wifi_set_opmode(STATION_MODE);
    
    sdk_wifi_station_dhcpc_stop();
 
    sdk_wifi_set_ip_info(0, &ipconfig);
    struct sdk_station_config config = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        };
    sdk_wifi_station_set_config(&config);
    
    sdk_wifi_station_connect();
}
