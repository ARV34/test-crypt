/**
 * @file file_io.h
 * @brief
 * @author Arestov Roman <arv34@mail.ru>
 */

#ifndef FILE_IO_H_
#define FILE_IO_H_

#include "user_interface.h"

crypt_status_t FileWriteRun(crypt_info_t* data);
crypt_status_t FileReadRun(crypt_info_t* data);

#endif /* FILE_IO_H_ */
