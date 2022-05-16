g++-11 -std=c++17 brute.cpp -o brute.out -O2

for x in a b c d e f; do
# for x in c; do
    echo $x
    ./brute.out < $x > $x.out
done

