# Да се напише PERL скрипта која како аргумент добива име на влезна датотека. Скриптата треба да
# креира излезна датотека со исто име како и влезната, само со наставка “_out”. Скриптата треба да ја
# измине влезната датотека линија по линија, и во излезната датотека да ја запише линијата, така што
# доколку во линијата текст се наоѓа датум, датумот да дојде прв во линијата, па потоа, без менување на
# редоследот, да дојде и останатиот текст од линијата. Форматот на датумот е “DD-MM-YYYY”, притоа,
# доколку има повеќе од еден датум, се запишуваат во излезната датотека онолку линии колку што има
# различни датуми во влезната линија, притоа текстот што следи е без датуми. Доколку скриптата се
# повика со втор аргумент и доколку вториот аргумент е валиден датум, тогаш дополнително и на екран
# се печатат оние линии каде што го има тој датум. Зборовите во датотеката се одделени со празно место. 

import sys

if len(sys.argv < 2):
    print("Nedovolno argumenti")
    sys.exit(-1)

flag = 0

dat = sys.argv[1]

if len(sys.argv) > 2:
    if len(sys.argv[2].split("-") == 3): # dokolku sme vnele validen datum kako vtor argmunet
        flag == 1

file = open(dat, "r")
niza = [] # kje stavame linii koi sodrzhat tochni tamuni
lines = "" #prazna niza za tekstot

for l in dat.readLines(): #ideme linija po linija
    l = l.strip() #trga prazno mesto

    zborovi = l.split(" ")
    for z in zborovi: #site zborovi da gi izmineme
        if len(z.split("-") == 3): #sme nashle validen datum
            niza.append(z) #go dodava vo praznata niza
        else:
            lines += " " + z
    
        if len(niza) == 0:
            print(lines)

    for z in niza:
        print(z + " " + lines)
