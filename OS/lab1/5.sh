#!/bin/bash
grep -E "INFO" $HOME/lab1/anaconda/syslog | awk '{if ($2=="INFO") print $0}' > $HOME/lab1/info.log