#!/bin/bash
for i in tests/*_test; do
   if test -f "$i"; then
       if ./$i 2>&1; then
           echo $i PASS
       fi
   fi
done
