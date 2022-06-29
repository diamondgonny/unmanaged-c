#!/bin/zsh

echo "translate execute file has been activated"
./a.out abc def < input1.txt > output1.txt
./a.out abc defghi < input2.txt > output2.txt
./a.out abcdefg hijk < input3.txt > output3.txt
./a.out aba cde < input4.txt > output4.txt
./a.out -i abc cde < input5.txt > output5.txt
./a.out 'ab\n\t' cdnt < input6.txt > output6.txt
./a.out 'a-b-\\-a' cdefj < input7.txt > output7.txt
./a.out '--/\n\"' cdens < input8.txt > output8.txt
