#! /bin/bash

cd $1

first=`ls -v  | egrep "*.png"| awk -F'.' '{print $1}'|sort -rn | awk END{print}`
ls -v  | egrep "*.png"| awk -vmin=$first -F'.' '{system("mv " $0 " " $1-min".png")}'

