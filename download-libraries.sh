#!/bin/bash

if [ -d jast ]
then
	jast=skipped
else
	git clone --depth 1 https://github.com/PrinceDhaliwal/jast.git &&
	jast=OK || jast=fail
fi

if [ -d unit-test/googletest ]
then
	googletest=skipped
else
	git clone --depth 1 https://github.com/google/googletest.git unit-test/googletest &&
	googletest=OK || googletest=fail
fi

echo
echo ========== Download summary ==========
echo "Library                 Status"
echo ======================================
echo "jast                    $jast"
echo "unit-test/googletest    $googletest"
