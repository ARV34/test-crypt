# Encryptor-decryptor of login and password
Test project. The utility encrypts-decrypts the entered login and password. 
The encryption result is saved to a binary file. 
AES encryption algorithm, the key is generated randomly.

## Project build
Project build command
```console
make
```
Project cleanup command
```console
make clean
```

## Usage
Show help
```console
./crypt help
```
Encrypt username and password
```console
./crypt set <len key 128|192|256> <login 4-20 (0-9, a-z, A-Z, _)> <password 8-50>
```
Login and password decryption
```console
./crypt get <len key 128|192|256> <login hex 4-20> <password hex 8-50>
```
