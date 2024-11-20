# Да се напише PERL скрипта која како аргументи од командна линија добива имиња на датотеки.
# Скриптата треба да ги измине датотеките и да провери колку различни валути на пари ќе најде. Знаците
# на валутите кои што се пребаруваат се: „$“ „€“ „£“ „kn“ „kr“ „Rp“ „CHF“. Секоја валута започнува со
# знакот на валутата, по кое што следи сумата на истата (одделена со празно место). Доколку после
# валутата нема бројка, тогаш валутата не се зема во предвид. Сите валути што ќе бидат пронајдени во
# датотеката се собираат и се добива вкупна сума по валута. За секоја валута што била пронајдена во
# датотеката, му се дозволува на корисникот да внесе колку денари е истата (не се внесува за оние валути
# кои што не биле пронајдени во тековната датотека). На крајот од изминувањето на датотеката да се
# отпечати вкупната сума (во денари) што била пронајдена во датотеката. Скриптата, на крај треба да
# отпечати кои валути биле пронајдени во сите датотеки. 
# $ 500 , $ , 
import sys

if(len(sys.argv) < 2):
    print("Vnesete povekje argumenti!")
    sys.exit(-1)

niza = ['$', 'kn', '€', 'kr', 'Rp', 'CHF', '£']
suma1 = suma2 = suma3 = suma4 = suma5 = suma6 = suma7 = 0
cnt1 = cnt2 = cnt3 = cnt4 = cnt5 = cnt6 = cnt7 = False
najdeniAll = set()

for dat in range(sys.argv[1:]):
    d1 = open(dat, "r")
    d = d1.read()
    words = d.split(" ") # kje ni izlezat kako ["$", "500", "blabla", "kn" "pari"]
    najdeni = set() # NE dozvoluva duklikati
    vk_den = 0
    d.close() 

    for i in range(len(words - 1)):
        curr = words[i] #momentalniot zbor
        sl = words[i + 1]
        if sl.isdigit(): #dali imame integer
            sleden = float(sl)
        
        if curr not in niza:
            print("Ne e pronajdena nikakva valuta")

        if curr in niza: 
            if curr == "$":
                suma1 +=  sleden
                cnt1 = True
                najdeni.add("$")
            elif curr == "kn":
                suma2  += sleden
                cnt2 = True
                najdeni.add("kn")
            elif curr == "€":
                suma3 += sleden
                cnt3 = True
                najdeni.add("€")
            #elif ... isto za ostanatite...

    if cnt1 and "$" in najdeni:
        print("Najdena e valuta '$' so suma " + suma1)
        kurs = float(input("Vnesi kurs za $ vo denari: "))
        vk_den += suma1 * kurs
    if cnt2:
        print("Najdena e 'kn' so suma " + suma2)
        kurs = float(input("Vnesi kurs za kn vo denari: "))
        vk_den += suma2 * kurs
    #istoto za ostanatite...

    print(f"\nVkupna suma vo denari za dat {d} : {vk_den:.2f} MKD")

    if d == sys.argv[1]:
        najdeniAll = najdeni
    else:
        najdeniAll = najdeniAll.intersection(najdeni) #presek, ne dodava duplikati
    
print ("\nValuti najdeni vo site datoteki:")
if najdeniAll:
    for valuta in najdeniAll:
        print(valuta)
else:
    print("Nema najdeno valuta")
    

