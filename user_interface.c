/**
 * @file user_interface.c
 * @brief
 * @author Arestov Roman <arv34@mail.ru>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_interface.h"

enum { 
	UI_POS_CMD = 1,    
	UI_POS_LEN_KEY,
	UI_POS_LOGIN,
	UI_POS_PASSWORD
};

static int CheckHex(const char hex)
{
	if(
		(hex < 0x30 || hex > 0x39) &&
		(hex < 0x41 || hex > 0x46) &&
		(hex < 0x61 || hex > 0x66) 
	) return 1;
	return 0;
}

static int HexToString(const char *in, uint8_t *out)
{
	int num = strlen(in);
	if((num % 2) != 0){
		return 1;
	}
	num /= 2;
    for (int i = 0; i < num; i++) {
		if(CheckHex(in[i * 2]) || CheckHex(in[(i * 2) + 1]))
			return 1;
		if(sscanf(in + i * 2, "%2x", (int*)&out[i]) == 0)
			return 1;
    }
	out[num] = '\0';
	return 0;
}

static void PrintStringHex(const uint8_t* str, int len_str)
{
    for (int i = 0; i < len_str; i++) {
        printf("%02x", str[i]);
    }
}

static void PrintString(const uint8_t* str, int len_str)
{
    for (int i = 0; i < len_str; i++) {
        printf("%c", str[i]);
    }
}

static int CheckParameLen(int len, int max, int min)
{
	if(len < min || len > max) return 1;
	return 0;
}

static int CheckLogin(const char* login, int len)
{
    for (int i = 0; i < len; i++) {
		if(
			(login[i] < 0x30 || login[i] > 0x39) &&
			(login[i] < 0x41 || login[i] > 0x5A) &&
			(login[i] < 0x61 || login[i] > 0x7A) &&
			login[i] != 0x5F
		) 
			return 1;
    }
	return 0;
}

int UI_ParsingCommand(crypt_info_t* data, char *arr_cmd[])
{
	if(strncmp(arr_cmd[UI_POS_CMD], "help", 4) == 0) {
		data->cmd = UI_CMD_HELP;
		return 0;
	} else if(strncmp(arr_cmd[UI_POS_CMD], "set", 3) == 0) {
		data->cmd = UI_CMD_SET;
	} else if(strncmp(arr_cmd[UI_POS_CMD], "get", 3) == 0 ) {
		data->cmd = UI_CMD_GET;
	} else {
		UI_PrintMessage(ERROR_UNKNOWN_CMD);
		return 1;
	}

	data->len_key = atoi(arr_cmd[UI_POS_LEN_KEY]);
	if(!(data->len_key == 128 || data->len_key == 192 || data->len_key == 256)) {
		UI_PrintMessage(ERROR_LEN_KEY);
		return 1;
	}

	int login_len = strlen(arr_cmd[UI_POS_LOGIN]);
	int password_len = strlen(arr_cmd[UI_POS_PASSWORD]);
	switch(data->cmd) 
	{
		case UI_CMD_SET:
			if(
				CheckParameLen(login_len, MAX_LEN_LOGIN, MIN_LEN_LOGIN) ||
				CheckLogin(arr_cmd[UI_POS_LOGIN], login_len)
			){
				UI_PrintMessage(ERROR_INCORRECT_LOGIN);
				return 1;
			}

			if(CheckParameLen(password_len, MAX_LEN_PASSWORD, MIN_LEN_PASSWORD)){
				UI_PrintMessage(ERROR_INCORRECT_PASSWORD);
				return 1;
			}

			strcpy((char*)data->login, arr_cmd[UI_POS_LOGIN]);
			strcpy((char*)data->password, arr_cmd[UI_POS_PASSWORD]);
		break;
		case UI_CMD_GET:
			if(
				CheckParameLen(login_len, MAX_LEN_LOGIN * 2, MIN_LEN_LOGIN * 2) ||
				HexToString(arr_cmd[UI_POS_LOGIN], data->login_crypt)
			){
				UI_PrintMessage(ERROR_INCORRECT_LOGIN);
				return 1;
			}

			if(
				CheckParameLen(password_len, MAX_LEN_PASSWORD * 2, MIN_LEN_PASSWORD * 2) ||
				HexToString(arr_cmd[UI_POS_PASSWORD], data->password_crypt) 
			){
				UI_PrintMessage(ERROR_INCORRECT_PASSWORD);
				return 1;
			}
		break;
		
		default: break;
	}

	return 0;
}

void UI_PrintEncryptionData(crypt_info_t* data)
{
	printf("Encryption result...\n");
	printf("Login:    ");
	PrintStringHex(data->login_crypt, strlen((char*)data->login));
	printf("\nPassword: ");
	PrintStringHex(data->password_crypt, strlen((char*)data->password));
	printf("\n");
}

void UI_PrintDecryptionData(crypt_info_t* data)
{
	printf("Decryption result...\n");
	printf("Login:    ");
	PrintString(data->login, strlen((char*)data->login));
	printf("\nPassword: ");
	PrintString(data->password, strlen((char*)data->password));
	printf("\n");
}
void UI_PrintMessage(crypt_status_t status)
{
	switch(status) 
	{
		case NOTIFICATION_DONE:
			printf("Done! \n");
		break;
		case NOTIFICATION_NOT_FOUND:
			printf("Encrypted data not found! \n");
		break;
		case ERROR_FORMAT_CMD:
			printf("Error: Invalid input format! \n");
		break;
		case ERROR_LEN_KEY:
			printf("Error: Invalid key length! \n");
		break;
		case ERROR_UNKNOWN_CMD:
			printf("Error: Unknown command! \n");
		break;
		case ERROR_INCORRECT_LOGIN:
			printf("Error: Incorrect login! \n");
		break;
		case ERROR_INCORRECT_PASSWORD:
			printf("Error: Incorrect password! \n");
		break;
		case ERROR_FILE_ACCESS:
			printf("Error: No access to file! \n");
		break;
		case ERROR_ENCRYPTION:
			printf("Error: Encryption failure! \n");
		break;

		default: break;
	}
}

void UI_PrintHelp(void)
{
	printf("Help... \n");
	printf("Data encryption: \n");
	printf("\tset <len key 128|192|256> <login 4-20 (0-9, a-z, A-Z, _)> <password 8-50> \n");
	printf("Data decryption: \n");
	printf("\tget <len key 128|192|256> <login hex 4-20> <password hex 8-50> \n");
}
