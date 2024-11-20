`#Да се напише SHELL скрипта која ги листа сите датотеки од тековниот директориум. Потоа, имињата
на оние датотеки кои што имаат помалку од 1000 зборови ги праќа како аргументи од командна линија
на повик од PERL скриптата (сите имиња ги праќа во еден повик). За оние датотеки кои што имаат
повеќе од 1000 зборови, креира посебен повик и нивните имиња ги праќа како еден аргумент од
командна линија`
#!/bin/bash

file = $(cat ls -a) # listanje na site datoteki
file_array = ($file)
num_files = ${#files[@]} 
small_files=()
big_files=()

`#
for files in $file; do
    wrds = $(wc - w < "$file") `

for ((i = 0; i < num_files; i++)); do
    wrds_cnt = $(wc -w < "${file_array[i]}") #broime zborovi
    wrds = $(wrds) + $(wrds_cnt)

    if [ "$wrds" -lt 1000 ];then
        small_files += $(file_array[i])
    else
        big_files += $(file_array[i])
    fi
done

if [ ${#small_files[@]} -gt 0 ]; then  
    small_files_list =$(echo "${small_files[@]}") # gi smestuva vo single strings
    execute=$(Python "p1.py" $small_files_list)
fi

for file in "${big_files[@]}"; do
    execute=$(Python "p1.py" $file)
done

echo "Total word count: $wrds"