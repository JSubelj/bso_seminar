#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "ip_flash_storage.h"

#define INCORRECT_COMMAND_NO 0

#define IP_SET_COMMAND "ip" // ok
#define IP_SET_COMMAND_NO 1
#define IP_SET_COMMAND_LEN 2

#define GW_SET_COMMAND "gw" // ok
#define GW_SET_COMMAND_NO 2
#define GW_SET_COMMAND_LEN 2

#define NETMASK_SET_COMMAND "netmask" // ok
#define NETMASK_SET_COMMAND_NO 3
#define NETMASK_SET_COMMAND_LEN 7

#define SSID_SET_COMMAND "ssid" // ok
#define SSID_SET_COMMAND_NO 4
#define SSID_SET_COMMAND_LEN 4

#define PASS_SET_COMMAND "pass"
#define PASS_SET_COMMAND_NO 5
#define PASS_SET_COMMAND_LEN 4

#define STATIC_IP_SET_COMMAND "static"
#define STATIC_IP_SET_COMMAND_NO 6
#define STATIC_IP_SET_COMMAND_LEN 6

#define DYNAMIC_IP_SET_COMMAND "dynamic"
#define DYNAMIC_IP_SET_COMMAND_NO 7
#define DYNAMIC_IP_SET_COMMAND_LEN 7

#define SAVE_COMMAND "save"
#define SAVE_COMMAND_NO 8
#define SAVE_COMMAND_LEN 4

#define HELP_COMMAND "help"
#define HELP_COMMAND_NO 9
#define HELP_COMMAND_LEN 4

#define EXIT_COMMAND "exit"
#define EXIT_COMMAND_NO 10
#define EXIT_COMMAND_LEN 4

#define DISPLAY_CURRENT_COMMAND "display_current" // ok
#define DISPLAY_CURRENT_COMMAND_NO 11
#define DISPLAY_CURRENT_COMMAND_LEN 15

#define DISPLAY_SAVED_COMMAND "display_saved" // ok
#define DISPLAY_SAVED_COMMAND_NO 12
#define DISPLAY_SAVED_COMMAND_LEN 13

#define RESTART_COMMAND "restart"
#define RESTART_COMMAND_NO 13
#define RESTART_COMMAND_LEN 7

#define HELP_STRING "cmnds: \nip [ip]\ngw [ip]\nnetmask [ip]\nssid [name]\npass [pass]\nstatic \ndynamic\nsave\nhelp\ndisplay_current\ndisplay_saved\nexit\nrestart \n"

#define COMMAND_MAX_STRING_LEN  SSID_SET_COMMAND_LEN+SSID_SIZE


#endif