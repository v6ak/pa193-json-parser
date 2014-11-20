#!/bin/zsh
# Well, Bash 4.2.25(1)-release on Ubuntu 12.04 segafaults :(

if ! [ -e Makefile ]; then
	cmake .
fi
make || exit 1

# npm install sprintf-js

fail=0

parserOut=$(mktemp)
nodeOut=$(mktemp)

function run-test {
	param="$1"
	file="$2"
	if valgrind ./parser "$param" < "$file" > "$parserOut" 2> /dev/null; then
		parserSucceeded=1
	else
		parserSucceeded=0
	fi
	if node node-parse.js < "$file" > "$nodeOut" 2> /dev/null; then
		nodeSucceeded=1
	else
		nodeSucceeded=0
	fi
	if [ "$parserSucceeded" != "$nodeSucceeded" ]; then
		fail=1
		echo "Failed on $file:"
		echo "$parserSucceeded" != "$nodeSucceeded"
	fi
	if ! diff "$parserOut" "$nodeOut" ; then
		echo "^^^^ Failed on $file: diff ^^^^"
		fail=1
	fi

}

for file in data/string/*; do
	run-test read-string "$file"
done

for file in data/number/*; do
	run-test read-number "$file"
done

for file in data/number/*; do
	# Test with different locale. Czech has decimal ',' instead of decimal point (i.e. '.').
	(
		export LC_ALL="cs_CZ.utf8"
		run-test read-number "$file"
	)
done


if [ "$fail" != 0 ]; then
	echo TEST FAILED!
	exit 1
fi
