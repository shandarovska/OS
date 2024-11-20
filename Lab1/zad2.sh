# Да се напише SHELL скрипта која како аргумент од командна линија добива име на влезна
# датотека. Доколку не се прати аргумент на командна линија, тогаш се пребарува датотека со име
# „naredbi.txt“ во тековниот директориум и неговите поддиректориуми и доколку се најде, тогаш се
# копира таа датотека во тековниот директориум (доколку истата не е во тековниот директориум).
# Доколку се најде датотеката, тогаш се печати нејзината содржина на екран, инаку се печати
# порака дека датотеката не е пронајдена.

#!/bin/bash 

# vlez -> ./zad2.sh tekst.txt || ./zad2.sh

if [ $? -eq 1]; then #dali komandata nad ova e so vrednost 1
    vlez="$1"
else
    echo "Ne vnesovte datoteka, zapochnuva prebaruvanje na naredbi.txt"

    for file in $(find .type f -name "naredbi.txt"); do 
        vlez="$file" #ni go vrakja pahtot na naredba.txt, pr. /home/sandra/naredbi.txt
        break;
    done

fi

if [ -n "$vlez" ]; then #ako ne e prazna datoteka
    base_name = $(basename "$vlez") #ni go dava basename, odnosno poslenoto neshto vo pathot, pr. naredbi.txt
    if [ ! -f "$base_name" ]; then #ako ne postoi naredbi.txt vo tekovniot direktorium
        cp "$vlez" "$base_name" #se kopira
        echo "Premesten e"
    fi
fi
    echo "Datotekata e najdena"
    cat "$base_name"
exit(1)


#Slichna zadacha, ja smestuva datotekata vo sporeden direktorium

input="$1" #nosime cel path
if [ -n "input" ]; then
    base_name=$(basename "input")
    if [ -s "input" ]; then #dali postoi && dali ne e prazen
        dir1="dir1"
        if [ ! -d "$dir1" ]; then #dokolku ne postoi direktoriumot
            mkdir "$dir1"
        fi
        mv "$input" "$dir1/$base_name"
        echo "Datotekata '$input' e premestena vo '$dir1'"
    else
        echo "Datotekata '$input' e prazna ili ne mozhe da se najde"
    fi
fi