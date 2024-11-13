#!/bin/sh

# constants

source=$(dirname $0)/tables.sql
REGEX="^\s*CREATE TABLE ([A-Za-z0-9_]+)\s*\(?\$"
FORMAT="DROP TABLE IF EXISTS %s CASCADE;"

# manually entered filename checking

if [ $# -ne 0 ]
then
    source=$1
fi

if [ ! -f $source ]
then
    >&2 echo "$0: can't read \"$source\": no such file"
    exit 1
fi

# query building

TABLE_NAMES=$(sed -E "s/$REGEX/\1/p" -n $source)
query=""

for name in $TABLE_NAMES
do
    query="$query$(printf "$FORMAT" $name)\n"
done

query="$query\n\\i $source"

echo $query
