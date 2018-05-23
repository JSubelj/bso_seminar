#include "ip_flash_storage.h"


void set_dhcp_static_flag(char flag){
    struct whole_config conf;
    get_config_from_flash(&conf);

    if(conf.dhcp_static != flag){
        conf.dhcp_static = flag;
        write_config_to_flash(&conf);
    }
}

bool is_ip_static(){
    struct whole_config conf;
    get_config_from_flash(&conf);

    return conf.dhcp_static;
}

void update_ip_config(struct whole_config * conf_ip){
    struct whole_config conf;
    get_config_from_flash(&conf);

    strncpy(&conf.ip[0],&(conf_ip->ip[0]),IP_SIZE);
    strncpy(&conf.gw[0],&(conf_ip->gw[0]),IP_SIZE);
    strncpy(&conf.netmask[0],&(conf_ip->netmask[0]),IP_SIZE);
    
    write_config_to_flash(&conf);
}

void update_wifi_config(struct whole_config * conf_wifi){
    struct whole_config conf;
    get_config_from_flash(&conf);

    strcpy(&conf.ssid[0],&(conf_wifi->ssid[0]));
    strcpy(&conf.pass[0],&(conf_wifi->pass[0]));

    write_config_to_flash(&conf);
    
}

void get_config_from_flash(struct whole_config * conf){
    char buff[FULL_SIZE];
    read_flash(buff, FULL_SIZE);

    int counter=0;
    
    strncpy(&(conf->ip[0]), (buff+counter),IP_SIZE);
    counter+=IP_SIZE;

    strncpy(&(conf->netmask[0]), (buff+counter),IP_SIZE);
    counter+=IP_SIZE;    

    strncpy(&(conf->gw[0]), (buff+counter),IP_SIZE);
    counter+=IP_SIZE;

    strncpy(&(conf->ssid[0]), (buff+counter),SSID_SIZE);
    counter+=SSID_SIZE;

    strncpy(&(conf->pass[0]), (buff+counter),PASS_SIZE);
    counter+=SSID_SIZE;

    strncpy(&(conf->dhcp_static), (buff+counter),DHCP_STATIC_SIZE);
    counter+=DHCP_STATIC_SIZE;
}

void write_config_to_flash(struct whole_config * conf){
    char buff[FULL_SIZE];
    
    int counter = 0;
    strncpy((buff+counter),&(conf->ip[0]),IP_SIZE);
    counter+=IP_SIZE;

    strncpy((buff+counter),&(conf->netmask[0]),IP_SIZE);
    counter+=IP_SIZE;    

    strncpy((buff+counter),&(conf->gw[0]),IP_SIZE);
    counter+=IP_SIZE;

    strncpy((buff+counter),&(conf->ssid[0]),SSID_SIZE);
    counter+=SSID_SIZE;

    strncpy((buff+counter),&(conf->pass[0]),PASS_SIZE);
    counter+=SSID_SIZE;

    strncpy((buff+counter),&(conf->dhcp_static),DHCP_STATIC_SIZE);
    counter+=DHCP_STATIC_SIZE;

    write_to_flash(buff, FULL_SIZE);//
}

void get_full_conf_string(struct whole_config * conf, char* string){
    sprintf(string,
            "dynamic/static: %d\nIP addr: %d.%d.%d.%d\nnetmask: %d.%d.%d.%d\ngw: %d.%d.%d.%d\nssid: %s\npass: %s\n",
            conf->dhcp_static, conf->ip[0],conf->ip[1],conf->ip[2],conf->ip[3],conf->netmask[0],conf->netmask[1],conf->netmask[2],conf->netmask[3],conf->gw[0],conf->gw[1],conf->gw[2],conf->gw[3],conf->ssid,conf->pass
    );
}