#!/bin/bash

FILE=$1
GREEN="\e[32m%s\e[m\n"
RED="\e[31m%s\e[m\n"

[ $# -eq 0 ] && echo "Usage: $0 filename" && exit

if [ -r $FILE ]; then
  printf $GREEN "You can read this file"
else
  printf $RED "You can not read this file"
fi

if [ -w $FILE ]; then
  printf $GREEN "You can write to this file"
else
  printf $RED "You can not write to this file"
fi