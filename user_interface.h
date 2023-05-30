/**
 * @file user_interface.h
 * @brief
 * @author Arestov Roman <arv34@mail.ru>
 */

#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include <stdint.h>

#define MAX_NUM_PARAM     5
#define MIN_NUM_PARAM     2

#define MAX_LEN_PASSWORD 50
#define MIN_LEN_PASSWORD 8
#define MAX_LEN_LOGIN    20
#define MIN_LEN_LOGIN    4

typedef enum { 
	UI_CMD_HELP,
	UI_CMD_SET,        
	UI_CMD_GET
} crypt_cmd_t;

typedef enum { 
	NOTIFICATION_DONE,
	NOTIFICATION_NOT_FOUND,     
	ERROR_FORMAT_CMD,
	ERROR_LEN_KEY,
	ERROR_UNKNOWN_CMD,
	ERROR_INCORRECT_LOGIN,
	ERROR_INCORRECT_PASSWORD,
	ERROR_FILE_ACCESS,
	ERROR_ENCRYPTION
} crypt_status_t;

#define SIZE_BUFF 100

typedef struct
{
	int len_key;  
	crypt_cmd_t cmd;
	uint8_t login[SIZE_BUFF];
	uint8_t login_crypt[SIZE_BUFF];
	uint8_t password[SIZE_BUFF];
	uint8_t password_crypt[SIZE_BUFF];
} crypt_info_t;

int UI_ParsingCommand(crypt_info_t* data, char *arr_cmd[]);
void UI_PrintEncryptionData(crypt_info_t* data);
void UI_PrintDecryptionData(crypt_info_t* data);
void UI_PrintMessage(crypt_status_t status);
void UI_PrintHelp(void);

#endif /* USER_INTERFACE_H_ */