#!/bin/bash

getent passwd | while IFS= read -r LINE; do
  ID=$(echo $LINE | cut -d ':' -f 3)
  printf "${LINE}"
  if (( ID >= 1000 )); then
    printf "\e[33m%s\e[m" " < Common User"
  fi
  echo ""
done