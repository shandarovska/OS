# Да се напише Python скрипта која како аргументи од командна линија добива име на
# датотека и знаменце (flag). Датотеката го чува излезот од ls –al наредбата на тековниот
# директориум (прикажано на сликата). Доколку скриптата се повика со знаменце „–d“
# тогаш на екран треба да се испишат различните датуми на кои биле
# креирани/модифицирани директориумите или датотеките сместени во влезната датотека.
# Доколку скриптата се повика со знаменце „-f“, тогаш треба, за секој датум да се отпечати
# колку датотеки или директориуми биле креирани/модифицирани.

#!/usr/bin/python3

# vlez: ./zad2.py primer.txt -d || -f

import sys
if len(sys.argv) != 3:
    print("Greshka")
    sys.exit(-1)

filename = sys.argv[1]
flag = sys.argv[2]

file = open(filename, "r")
linii = file.splitlines()
file.close() #neophodno e

dates = {} #prazna niza

for line in linii[1:]: #da gleda od vtora linija, 1: ja skoka prvata i odi na sledna
    parts = line.split()
    date = ' '.join(parts[5:7]) # 5 i 7 kolona da ja zeme
    if flag == "-d" :
        if date not in dates:
            dates[date] = 1
        elif flag == "-f" :
            if date in dates:
                    dates[date] += 1
            else:
                dates[date] = 1

if flag == "-d":
     for date in dates.keys():
          print(date)
elif flag == "-f":
    for date, count in dates.items():
         print(f"{dates}:{count}")
else:
     print("Greshka")

