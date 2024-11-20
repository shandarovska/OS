`# Да се напише SHELL спкрипта која треба да ги најде сите датотеки( во тековниот дирек. и поддир.) кои имаат
наставка (екстензија) ".ip". Потоа, користејќи Python скипта, да се генерираат сите можни IP адреси, за секоја
IP адреса да се провери дали има пристап до истата и анализата да се испише на екран (да се испише секоја ip адреса
и до истата ОК или NOT во продолжение). Проверката дали има пристап или не до дадена IP Адреса се прави со наредбата
"ping -c ! $IP > /dev/null 2>&1;" `

file=$(ls -a | grep ".*\.ip$")
#file=$(find . -type -name ".ip$")  mozhe i vaka

for f in $file; do
    execute=$(Python "piton.py" "$files")
    for ip in $execute; do
        ping -c ! $IP > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            echo "$ip OK"
        else
            echo "$ip NOT"
        fi
    done
done