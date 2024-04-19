#!/bin/sh
set -xe

usage() {
	echo "Usage: $(basename "$0") <directory>"
	exit 1
}

directory="$1"
[ -z "$directory" ] && usage

mkdir --parents "$directory"

cd "$directory"

mkdir include src

cp ../assets/license_header.h src/"$(echo "$directory" | tr '[:upper:]' '[:lower:]').c"

cp ../Makefile.template Makefile
