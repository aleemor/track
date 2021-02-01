#!/bin/bash
clear
gcc -o mySerial mySerial.c -L/usr/include/mysql -lmysqlclient
sudo ./mySerial
