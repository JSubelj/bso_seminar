#include "telnet_server.h"

char no_of_connections = 0;

void telnet_connection(void *pvParameters) {
    no_of_connections++;
    struct netconn *pxNetCon;
    pxNetCon = (struct netconn *)pvParameters;
    struct netbuf *pxRxBuffer;
    portCHAR *pcRxString;
    unsigned portSHORT usLength;
    char buff[64] ={0};
    char ret_buff[64] = {0};
    struct whole_config conf;
    get_config_from_flash(&conf);

    sprintf(buff,"\nThis is a %d. telnet thread.\n", no_of_connections);
    netconn_write(pxNetCon, buff, strlen(buff), NETCONN_COPY);
    sprintf(ret_buff, "> ");
    netconn_write( pxNetCon, ret_buff, strlen(ret_buff), NETCONN_COPY );

    while(1){
            netconn_recv( pxNetCon, &pxRxBuffer );
            if ( pxRxBuffer != NULL ){
                    netbuf_data( pxRxBuffer, ( void * ) &pcRxString, &usLength );
                    if (  pcRxString != NULL){
                            
                            memset(buff, 0, sizeof(buff));
                            strncpy(buff,pcRxString,usLength);

                            memset(ret_buff, 0, sizeof(ret_buff));
                            act_on_command(buff,&conf,ret_buff);
                            netconn_write( pxNetCon, ret_buff, strlen(ret_buff), NETCONN_COPY );
                            sprintf(ret_buff, "> ");
                            netconn_write( pxNetCon, ret_buff, strlen(ret_buff), NETCONN_COPY );
   

                            //printf("\n%s\n",buff);
                    }
                    netbuf_delete( pxRxBuffer );
            }
            delay_ms(10);
    }
}

void telnet_server(void *pvParameters){
    struct netconn *pxTCPListener, *pxNewConnection;
    pxTCPListener = netconn_new( NETCONN_TCP );

    

    netconn_bind(pxTCPListener, NULL, 23 );
    netconn_listen( pxTCPListener );

    while(1){
            netconn_accept(pxTCPListener, &pxNewConnection);
            if(pxNewConnection != NULL){
                    if(no_of_connections < MAX_TELNET_CONNECTIONS){
                        xTaskCreate(telnet_connection, "telnet connection", 512, pxNewConnection, 3, NULL);
                    }else{
                        char buff[] = "\nMax number of connections reached.\n\n";
                        netconn_write(pxNewConnection, buff, strlen(buff), NETCONN_COPY);
                        netconn_delete(pxNewConnection);
                    }
                    //EchoRequest(pxNewConnection);
            }
            delay_ms(100);
    }
}

char what_command(char* command){
    if(strncmp(command,IP_SET_COMMAND,IP_SET_COMMAND_LEN)==0) return IP_SET_COMMAND_NO;
    else if(strncmp(command,GW_SET_COMMAND,GW_SET_COMMAND_LEN)==0) return GW_SET_COMMAND_NO;
    else if(strncmp(command,NETMASK_SET_COMMAND,NETMASK_SET_COMMAND_LEN)==0) return NETMASK_SET_COMMAND_NO;
    else if(strncmp(command,SSID_SET_COMMAND,SSID_SET_COMMAND_LEN)==0) return SSID_SET_COMMAND_NO;
    else if(strncmp(command,PASS_SET_COMMAND,PASS_SET_COMMAND_LEN)==0) return PASS_SET_COMMAND_NO;
    else if(strncmp(command,STATIC_IP_SET_COMMAND,STATIC_IP_SET_COMMAND_LEN)==0) return STATIC_IP_SET_COMMAND_NO;
    else if(strncmp(command,DYNAMIC_IP_SET_COMMAND,DYNAMIC_IP_SET_COMMAND_LEN)==0) return DYNAMIC_IP_SET_COMMAND_NO;
    else if(strncmp(command,SAVE_COMMAND,SAVE_COMMAND_LEN)==0) return SAVE_COMMAND_NO;
    else if(strncmp(command,HELP_COMMAND,HELP_COMMAND_LEN)==0) return HELP_COMMAND_NO;
    else if(strncmp(command,EXIT_COMMAND,EXIT_COMMAND_LEN)==0) return EXIT_COMMAND_NO;
    else if(strncmp(command,DISPLAY_CURRENT_COMMAND,DISPLAY_CURRENT_COMMAND_LEN)==0) return DISPLAY_CURRENT_COMMAND_NO;
    else if(strncmp(command,DISPLAY_SAVED_COMMAND,DISPLAY_SAVED_COMMAND_LEN)==0) return DISPLAY_SAVED_COMMAND_NO;

    return INCORRECT_COMMAND_NO;                      
}

void string2ip(char* string, char * ip){
    char *token;
    token = strtok(string,".");
    char i=0;
    while(token != NULL){
        if(atoi(token) > 255) {
            memset(ip, 0, sizeof(IP_SIZE));
            return;
        }
        *(ip+i) = atoi(token);
        i++;
        token = strtok(NULL, ".");

    }
}

void act_on_command(char* org_command, struct whole_config * conf, char * ret){
    char command = what_command(org_command);
    switch(command){
        //case INCORRECT_COMMAND_NO: {strcpy(ret, "Invalid command. Try help.\n"); break;}
        case IP_SET_COMMAND_NO: {
            string2ip((org_command+strlen(IP_SET_COMMAND)+1),&(conf->ip[0]));
            sprintf(ret, "IP set to: %d.%d.%d.%d\n", conf->ip[0],conf->ip[1],conf->ip[2],conf->ip[3]);            
            break;
        } 

        default: {
            strcpy(ret, "cmnds: \nip [ip]\ngw [ip]\nnetmask [ip]\nssid [name]\npass [pass]\nstatic \ndynamic\nsave\nhelp\ndisplay_current\ndisplay_saved\nexit \n"); 
            break;
            }
    }
}

