#!/bin/bash
git ls-files | xargs wc -l | grep "\.c\|\.h" | sed -e 's/^[ \t]*//' | cut -d' ' -f1 | paste -sd+ - | bc