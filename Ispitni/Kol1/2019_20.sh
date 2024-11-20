# Да се напише SHELL скрипта која како аргумент добива листа од имиња од датотеки. Скриптата, за
# секоја датотека (име од датотека) да провери дали ја има како датотека во тековниот директориум, или
# под-директориуми. Доколку ја има, проверува дали датотеката (во нејзината содржина) има барем еден
# валиден датум (DD-MM-YYYY), и доколку нема, ја игнорира. Доколку има валиден датум, тогаш ја
# повикува PERL скриптата и како прв аргумент го праќа името на датотеката, и т.н. со сите датотеки што
# се пратени како аргументи од командна линија. За секоја датотека што ќе биде пратена
# на PERL скриптата, се печати на екран нејзиното име и колку различни датуми се пронајдени.

#!/bin/bash

for dat in $@: do #pokazhuva kon site args passed
    jaIma = $(find . -type f -name $dat)
    if [ -n "$jaIme" ]; then
        valid = $(cat $jaIma | grep "[1-31]\-[1-12]\-[0-9][0-9][0-9][0-9]")
        if [ -n valid ]; then
            rez = $(k1.py $jaIme) #vaka povikuvame py skripta so 1 argument, rez go sodrzhi outputot
            d = "${dat}_out"
            rez1 = $(cat $d | awk 'print $1' | uniq -u | wc -l) #uniq u, filter unique values in the first column
            echo "$dat $rez1"                                   # counts number of unique lines
        fi
    fi
done