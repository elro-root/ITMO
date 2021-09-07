#!/bin/bash
grep -E "(WW)" $HOME/lab1/anaconda/X.log | sed "s/WW/Warning/" > $HOME/lab1/full.log
grep -E "(II)" $HOME/lab1/anaconda/X.log | sed "s/II/Information/" >> $HOME/lab1/full.log