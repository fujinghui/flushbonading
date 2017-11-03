for((i = 1; i <= 1000; i ++));
    do
        printf "%d:" $i
        ./client.out 127.0.0.1 8091
    done
