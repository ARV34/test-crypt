/**
 * @file file_io.c
 * @brief
 * @author Arestov Roman <arv34@mail.ru>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "file_io.h"
#include "cryption.h"

static const char* file_name = "data.bin";

typedef struct {
	uint8_t key_random_crypt[32];
	uint8_t login_crypt[SIZE_BUFF];
	uint8_t password_crypt[SIZE_BUFF];
} crypt_file_t;

crypt_status_t FileWriteRun(crypt_info_t* data)
{
    crypt_file_t data_file;
    uint8_t key_random_temp[32] = {0};
    int login_len = strlen((char*)data->login);
    int password_len = strlen((char*)data->password);
    Crypt_GenerateKey(data->len_key, key_random_temp);
    Crypt_EncryptFixedKey(key_random_temp, data->len_key / 8, data_file.key_random_crypt);
    Crypt_Encrypt(data->login, login_len, key_random_temp, data->len_key, data_file.login_crypt);
    Crypt_Encrypt(data->password, password_len, key_random_temp, data->len_key, data_file.password_crypt);

    //Encryption check
    uint8_t login_temp[SIZE_BUFF] = {0};
    uint8_t password_temp[SIZE_BUFF] = {0};
    Crypt_Decrypt(data_file.login_crypt, login_len, key_random_temp, data->len_key, login_temp);
    Crypt_Decrypt(data_file.password_crypt, password_len, key_random_temp, data->len_key, password_temp);

    if(
        (memcmp(data->login, login_temp, login_len) != 0) ||
        (memcmp(data->password, password_temp, password_len) != 0)
    ) {
        return ERROR_ENCRYPTION;
    }

    FILE *fd = fopen(file_name, "ab");
    if (fd == NULL) 
        return ERROR_FILE_ACCESS;

    if(fwrite(&data_file, sizeof(crypt_file_t), 1, fd) == 0){
        return ERROR_FILE_ACCESS;
    }
    fclose(fd);

    memcpy(data->login_crypt, data_file.login_crypt, login_len);
    memcpy(data->password_crypt, data_file.password_crypt, password_len);

    return NOTIFICATION_DONE;
}

crypt_status_t FileReadRun(crypt_info_t* data)
{
    FILE *fd = fopen(file_name, "rb");
    if (fd == NULL) 
        return ERROR_FILE_ACCESS;

    crypt_status_t status = NOTIFICATION_NOT_FOUND;
    crypt_file_t data_file;
    uint8_t key_random_temp[32] = {0};
    int login_len = strlen((char*)data->login_crypt);
    int password_len = strlen((char*)data->password_crypt);
    while(fread(&data_file, sizeof(crypt_file_t), 1, fd) == 1)
    {
        if(
            (memcmp(data_file.login_crypt, data->login_crypt, login_len) == 0) &&
            (memcmp(data_file.password_crypt, data->password_crypt, password_len) == 0)
        ) {
            Crypt_DecryptFixedKey(data_file.key_random_crypt, data->len_key / 8, key_random_temp);
            Crypt_Decrypt(data_file.login_crypt, login_len, key_random_temp, data->len_key, data->login);
            Crypt_Decrypt(data_file.password_crypt, password_len, key_random_temp, data->len_key, data->password);
            status = NOTIFICATION_DONE; 
        }
    }
    fclose(fd);
    return status;  
}