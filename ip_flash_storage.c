#include "ip_flash_storage.h"

void set_dhcp_static_flag(char flag){
    struct whole_config conf;
    get_config_from_flash(&conf);

    if(conf.dhcp_static != flag){
        conf.dhcp_static = flag;
        write_config_to_flash(&conf);
    }
}

char set_AP_mode(char mode){
    struct whole_config conf;
    char err = get_config_from_flash(&conf);  
    if(err == ERR_CONF_DOSENT_EXIST){
        if(mode == AP_MODE_ON_FLAG) {
            return NO_ERROR;
        }
        return ERR_CONF_DOSENT_EXIST;
    } else{ 
        if(mode == AP_MODE_ON_FLAG || mode == AP_MODE_OFF_FLAG){
            conf.ap_mode = mode;
            write_config_to_flash(&conf);
            return NO_ERROR;
        }
    }
    return ERR_AP_MODE;
    
}

bool is_AP_mode(){
    struct whole_config conf;
    if(get_config_from_flash(&conf) == ERR_CONF_DOSENT_EXIST){
        return true;
    }
    return conf.ap_mode == AP_MODE_ON_FLAG;
}

bool is_ip_static(){
    struct whole_config conf;
    get_config_from_flash(&conf);

    return STATIC_IP_FLAG == conf.dhcp_static;
}

void update_ip_config(struct whole_config * conf_ip){
    struct whole_config conf;
    get_config_from_flash(&conf);

    memcpy(&conf.ip[0],&(conf_ip->ip[0]),IP_SIZE);
    memcpy(&conf.gw[0],&(conf_ip->gw[0]),IP_SIZE);
    memcpy(&conf.netmask[0],&(conf_ip->netmask[0]),IP_SIZE);
    
    write_config_to_flash(&conf);
}

void update_wifi_config(struct whole_config * conf_wifi){
    struct whole_config conf;
    get_config_from_flash(&conf);

    strcpy(&conf.ssid[0],&(conf_wifi->ssid[0]));
    strcpy(&conf.pass[0],&(conf_wifi->pass[0]));

    write_config_to_flash(&conf);
    
}

char get_config_from_flash(struct whole_config * conf){
    char buff[FULL_SIZE];
    read_flash(buff, FULL_SIZE);

    int counter=0;
    
    memcpy(&(conf->ip[0]),(buff+counter),IP_SIZE);
    counter+=IP_SIZE;

    memcpy(&(conf->netmask[0]), (buff+counter),IP_SIZE);
    counter+=IP_SIZE;    

    memcpy(&(conf->gw[0]), (buff+counter),IP_SIZE);
    counter+=IP_SIZE;

    strncpy(&(conf->ssid[0]), (buff+counter),SSID_SIZE);
    counter+=SSID_SIZE;

    strncpy(&(conf->pass[0]), (buff+counter),PASS_SIZE);
    counter+=PASS_SIZE;

    memcpy(&(conf->dhcp_static), (buff+counter),DHCP_STATIC_SIZE);
    counter+=DHCP_STATIC_SIZE;

    memcpy(&(conf->ap_mode), (buff+counter),AP_MODE_SIZE);
    counter+=AP_MODE_SIZE;

    memcpy(&(conf->does_config_exist[0]), (buff+counter),DOES_CONFIG_EXIST_SIZE);
    counter+=DOES_CONFIG_EXIST_SIZE;

    for(char i=0;i<DOES_CONFIG_EXIST_SIZE;i++){
        if(conf->does_config_exist[(int)i] != 0xaa){
            return ERR_CONF_DOSENT_EXIST;
        }
    }

    return NO_ERROR;
}

void write_config_to_flash(struct whole_config * conf){
    char buff[FULL_SIZE];

    int counter = 0;
    memcpy((buff+counter),&(conf->ip[0]),IP_SIZE);
    counter+=IP_SIZE;

    memcpy((buff+counter),&(conf->netmask[0]),IP_SIZE);
    counter+=IP_SIZE;    

    memcpy((buff+counter),&(conf->gw[0]),IP_SIZE);
    counter+=IP_SIZE;

    memcpy((buff+counter),&(conf->ssid[0]),SSID_SIZE);
    counter+=SSID_SIZE;

    strncpy((buff+counter),&(conf->pass[0]),PASS_SIZE);
    counter+=PASS_SIZE;

    strncpy((buff+counter),&(conf->dhcp_static),DHCP_STATIC_SIZE);
    counter+=DHCP_STATIC_SIZE;

    memcpy((buff+counter),&(conf->ap_mode),AP_MODE_SIZE);
    counter+=AP_MODE_SIZE;


    for(char i=1;i<=DOES_CONFIG_EXIST_SIZE;i++){
        buff[(int)FULL_SIZE-i] = 0xaa;
    }

    write_to_flash(buff, FULL_SIZE);
}

void get_full_conf_string(struct whole_config * conf, char* string){
    sprintf(string,
            "dynamic/static: %d\nIP addr: %d.%d.%d.%d\nnetmask: %d.%d.%d.%d\ngw: %d.%d.%d.%d\nssid: %s\npass: %s\nAP_MODE: %d\n",
            conf->dhcp_static, conf->ip[0],conf->ip[1],conf->ip[2],conf->ip[3],conf->netmask[0],conf->netmask[1],conf->netmask[2],conf->netmask[3],conf->gw[0],conf->gw[1],conf->gw[2],conf->gw[3],conf->ssid,conf->pass,conf->ap_mode);
}
