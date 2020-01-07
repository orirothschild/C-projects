#!/bin/bash

FILE=$1

if [ -e "$FILE" ] ; then
    cp $FILE /tmp/ ; else
    echo "not found" >> ~/tests/message
fi
