# Да се напише Python скрипта која ќе ги испечати првите линии од
# низа датотеки чии имиња се наведени на командна линија. Да
# се промени делимитерот за крај на ред, така што секоја линија
# да завршува со точка.
import sys

length = len(sys.argv)
if(length < 2) :
    print("Nedovolno argumenti")
    sys.exit(-1)

for i in range(1, length - 1): #od 1 do posledno
    file=open(sys.argv[i + 1], "r")
    file.read()
    lines = file.readLines().strip()
    
    print(lines + ".")
    file.close()
    