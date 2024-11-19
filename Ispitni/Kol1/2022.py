# Да се напише PERL скрипта со име „prva.plx“ која како аргументи добива најпрво збор кој ќе го
# пребарува, опција (знаменце) и име на датотека во која ќе се прави пребарувањето. Скриптата треба да
# го пребара зборот (што се праќа како прв аргумент) во зависност од опцијата (што се праќа како втор
# аргумент) во датотеката (чие име се праќа како трет аргумент). Опцијата може да биде „l“, „w“ или „f“,
# притоа опцијата „l“ значи дека треба да се вратат броевите од линиите во кои е пронајден зборот,
# „w“ како резултат враќа колку зборови биле пронајдени пред зборот што се бара, и опцијата „f“ враќа
# колку пати е пронајден зборот во датотеката. Доколку зборот го нема во датотеката, опцијата „l“ враќа -
# 1, додека пак опциите „w“ и „f“ враќаат соодветно вредност 0. Зборовите се одделени еден од друг со
# празно место. Доколку добие невалидна опција, скриптата прекинува со извршување.

import sys

if len(sys.argv < 4):
    print("Nemame dovolno argumenti")
    sys.exit(-1)

zbor = sys.argv[1]
zname = sys.argv[2]

if zname not in ['l', 'w', 'r']:
    print("Nevalidno zname!")
    sys.exit(-1)

dat = open(sys.argv[3], "r")
found = False
f = w = l = 0

for lines in dat.readLines():
    lines = lines.strip()
    zborovi = lines.split(".")
    line_found = False

    for z in zborovi:
        if z == zbor:
            if not line_found:
                    line_found = True
                    l += 1 #kolku linii sodrzhat takov zbor
            if zname == "l":
                print("l")
            elif zname == "w":
                print("w")
            else:
                f += 1
                found = True
        w += 1 #kolku linii se najdeni pred toa
    l += 1

if zname == "f":
    print("Zborot '$zbor' e pronajden '$f' pati.")
if zname == "l":
    print("Vo '$l' linii e pronajden zborot '$zbor'.")
if zname == "w":
    print("Ima '$w' zborovi pred da se pronajde zborot '$zbor'.")


if f == 0:
    if zname == "l":
        print(-1)
    if zname == "w":
        print(0)
    else:
        print(0)
