#!/bin/sh

ent_for_mod()
{
	# don't bother if we don't have sources
	if ! [ -f "./$1/src/Makefile" ]; then
		exit
	fi

	ENT_OUTFILE="./$1/entities.def"
	echo '' > "$ENT_OUTFILE"

	find ./$1/src/ -type f \( -iname \*.qc \) | while read EDEF_N; do
		echo "Scanning for definitions inside $EDEF_N"
		sed -n '/\/*QUAKED/,/*\//p' $EDEF_N >> "$ENT_OUTFILE"
	done;

	cat ./platform/entities.def >> $ENT_OUTFILE
}

# first dump all the general purpose entities
BASE_ENT="./platform/entities.def"
echo '' > "$BASE_ENT"

find ./src/gs-entbase/ -type f \( -iname \*.qc \) | while read EDEF_N; do
	echo "Scanning for definitions inside $EDEF_N"
	sed -n '/\/*QUAKED/,/*\//p' $EDEF_N >> "$BASE_ENT"
done;

# each game gets its own ents + general purpose ents appended at the end
if [ $# -gt 0 ]; then
	ent_for_mod $1
fi
