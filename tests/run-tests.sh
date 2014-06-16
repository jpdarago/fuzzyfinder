#!/bin/bash
for i in tests/*_test; do
   if test -f "$i"; then
       if ./$i 2>> tests/tests.log; then
           echo $i PASS
       fi
   fi
done
