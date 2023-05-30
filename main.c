/**
 * @file main.c
 * @brief
 * @author Arestov Roman <arv34@mail.ru>
 */

#include "user_interface.h"
#include "file_io.h"

int main(int argc, char *argv[])
{
	crypt_info_t data;
	crypt_status_t status;

	if(argc != MIN_NUM_PARAM && argc != MAX_NUM_PARAM) {
		UI_PrintMessage(ERROR_FORMAT_CMD);
		UI_PrintHelp();	
		return 1;
	}

	if(UI_ParsingCommand(&data, argv)){
		UI_PrintHelp();	
		return 1;
	}

	switch(data.cmd) 
	{
		case UI_CMD_HELP:
			UI_PrintHelp();	
		break;
		case UI_CMD_SET:
			status = FileWriteRun(&data);
			if(status){
				UI_PrintMessage(status);
				return 1;
			}
			UI_PrintEncryptionData(&data);
		break;
		case UI_CMD_GET:
			status = FileReadRun(&data);
			if(status){
				UI_PrintMessage(status);
				return 1;
			}
			UI_PrintDecryptionData(&data);
		break;
		
		default: break;
	}
	UI_PrintMessage(NOTIFICATION_DONE);

	return 0;
}