#!/bin/sh

# success
../examples/test1 --help  > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test40.out; then
	exit 0
else
	exit 1
fi

