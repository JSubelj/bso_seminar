#include "wifi.h"

char wifi_config(){
    
    if(is_AP_mode()){
        soft_ap_config();
        return AP_WIFI_FLAG;
    }else{
        return client_mode();
    }    
}

char client_mode(){
    if(is_ip_static()){
        client_mode_static();
        return STATIC_WIFI_FLAG;
    }else{
        client_mode_dynamic();
        return DYNAMIC_WIFI_FLAG;
    }
}

void client_mode_static(){
    struct ip_info ipconfig;
    struct whole_config config_all;

    get_config_from_flash(&config_all);

    

    //write_config_to_flash(&full_config);

    IP4_ADDR(&ipconfig.ip, config_all.ip[0], config_all.ip[1], config_all.ip[2], config_all.ip[3]); 
    IP4_ADDR(&ipconfig.gw, config_all.gw[0], config_all.gw[1], config_all.gw[2], config_all.gw[3]); 
    IP4_ADDR(&ipconfig.netmask, config_all.netmask[0], config_all.netmask[1], config_all.netmask[2], config_all.netmask[3]); 

    

    // required to call wifi_set_opmode before station_set_config 
    sdk_wifi_set_opmode(STATION_MODE);
    
    sdk_wifi_station_dhcpc_stop();
 
    sdk_wifi_set_ip_info(0, &ipconfig);
    struct sdk_station_config config_station;
    memcpy(&config_station.ssid, &config_all.ssid[0], SSID_SIZE); 
    memcpy(&config_station.password, &config_all.pass[0], PASS_SIZE);

    sdk_wifi_station_set_config(&config_station);
    
    sdk_wifi_station_connect();
}

void client_mode_dynamic(){
    struct whole_config config_all;

    get_config_from_flash(&config_all);

    struct sdk_station_config config_station;

    memcpy(&config_station.ssid, &config_all.ssid[0], SSID_SIZE); 
    memcpy(&config_station.password, &config_all.pass[0], PASS_SIZE);

    sdk_wifi_set_opmode(STATION_MODE);
    sdk_wifi_station_set_config(&config_station);
    sdk_wifi_station_connect();
}

void soft_ap_config(){
    char const AP_IP[] = {172, 16, 0, 1};
    char const AP_NETMASK[] = {255, 255, 255, 0};
    char const AP_GW[] = {0, 0, 0, 0};


    sdk_wifi_set_opmode(SOFTAP_MODE);
    
    struct ip_info ap_ip_config;

    IP4_ADDR(&ap_ip_config.ip, AP_IP[0], AP_IP[1], AP_IP[2], AP_IP[3]);
    IP4_ADDR(&ap_ip_config.gw, AP_GW[0], AP_GW[1], AP_GW[2], AP_GW[3]);
    IP4_ADDR(&ap_ip_config.netmask, AP_NETMASK[0], AP_NETMASK[1], AP_NETMASK[2], AP_NETMASK[3]);

    sdk_wifi_set_ip_info(SOFTAP_IF, &ap_ip_config);


    struct sdk_softap_config ap_config = { 
        .ssid = AP_SSID, 
        .ssid_hidden = AP_HIDDEN, 
        .channel = AP_CHANNEL,
        .ssid_len = strlen(AP_SSID),
        .authmode = AP_AUTHMODE,
        .password = AP_PASS,
        .max_connection = AP_MAX_CONNECTIONS,
        .beacon_interval = AP_BEACON_INTERVAL,
        };
    
    sdk_wifi_softap_set_config(&ap_config);
    
    ip_addr_t first_client_ip;
    IP4_ADDR(&first_client_ip, 172, 16, 0, 2);
    dhcpserver_start(&first_client_ip, 4);
}

void checking_connection(void *pvParameters){
    printf("PRŠU NOT");
    if(sdk_wifi_get_opmode() == SOFTAP_IF){
        printf("PRŠU NOT");
        
        remove_leds(NO_INTERNET);  
        append_leds(AP_ON_LED);  
        delay_ms(10);
    	vTaskDelete(NULL);    
    }
    printf("TUKI");


    uint8_t status = sdk_wifi_station_get_connect_status();
    while(status != STATION_GOT_IP){
        status = sdk_wifi_station_get_connect_status();
        delay_ms(10);
    }
    remove_leds(NO_INTERNET);  
    if(sdk_wifi_station_dhcpc_status() == DHCP_STOPPED){
        append_leds(STATIC_ON_LED);
    }else{
        append_leds(DYNAMIC_ON_LED);
    }
    delay_ms(10);   
    vTaskDelete(NULL);    
}