#!/bin/sh

#
make -s threads $1 &> /dev/null
cp out.jpg data/out.jpg
rm ./main out.jpg

echo "Beginning the tests for only one line of execution!"
x=100
make -s simple $1 >& /dev/null
while [ $x -gt 0 ]; do
    echo "Only $x tests remaining!"
    echo "Patience is a virtue!"
    #/usr/bin/time -a -o doc/simples_raw.txt -p make -s simple
    #echo "" >> doc/simples_raw.txt
    #make -s clear
    ./main $1 >> doc/simples_raw.txt
    rm out.jpg
    x=$(($x-1))
done
make -s clear >& /dev/null

echo "Beginning the tests for multiprocess"
x=100
make -s process $1 >& /dev/null
while [ $x -gt 0 ]; do
    echo "Only $x tests remaining!"
    echo "Remember the history of the turtle and the rabbit!"
    #/usr/bin/time -a -o doc/processos_raw.txt -p make -s process
    #echo "" >> doc/processos_raw.txt
    #make -s clear
    ./main $1 >> doc/processos_raw.txt
    rm out.jpg
    x=$(($x-1))
done
make -s clear >& /dev/null

echo "Beginning the tests for multithread"
x=100
make -s threads $1 >& /dev/null
while [ $x -gt 0 ]; do
    echo "Only $x Tests Remaining!"
    echo "GNU/Linux >> Windows!"
    #/usr/bin/time -a -o doc/threads_raw.txt -p make -s threads
    #echo "" >> doc/threads_raw.txt
    #make -s clear
    ./main $1 >> doc/threads_raw.txt
    rm out.jpg
    x=$(($x-1))
done
make -s clear >& /dev/null



##########################################################

echo "Making the real time plot with GNUPlot"

cat doc/simples_raw.txt | grep real: | sed -E 's/real://g' >> doc/real_simples.dat
cat doc/processos_raw.txt | grep real: | sed -E 's/real://g' >> doc/real_processos.dat
cat doc/threads_raw.txt | grep real: | sed -E 's/real://g' >> doc/real_threads.dat

gnuplot -p -e 'set title "Real time plot of one line of execution";
set xlabel "tests";
set ylabel "time in seconds";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/real_simples.dat" with points notitle' >> doc/real_simples.png
gnuplot -p -e 'set print "doc/real_simples.log";
stats "doc/real_simples.dat" nooutput;
print "Mean time of real time with only one line of execution:";
print STATS_mean;
print "Standard deviation of real time with only one line of execution:";
print STATS_stddev_err'

gnuplot -p -e 'set title "Real time plot of multiprocess";
set xlabel "tests";
set ylabel "time in seconds";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/real_processos.dat" with points notitle' >> doc/real_processos.png
gnuplot -p -e 'set print "doc/real_processos.log";
stats "doc/real_processos.dat" nooutput;
print "Mean time of real time with multiprocess:";
print STATS_mean;
print "Standard deviation of real time with multiprocess:";
print STATS_stddev_err'

gnuplot -p -e 'set title "Real time plot of multithreads";
set xlabel "tests";
set ylabel "time in seconds";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/real_threads.dat" with points notitle' >> doc/real_threads.png
gnuplot -p -e 'set print "doc/real_threads.log";
stats "doc/real_threads.dat" nooutput;
print "Mean time of real time with multithreads:";
print STATS_mean;
print "Standard deviation of real time in multithreads:";
print STATS_stddev_err'

##########################################################

echo "Making the user time plot with GNUPlot"

cat doc/simples_raw.txt | grep user: | sed -E 's/user://g' >> doc/user_simples.dat
cat doc/processos_raw.txt | grep user: | sed -E 's/user://g' >> doc/user_processos.dat
cat doc/threads_raw.txt | grep user: | sed -E 's/user://g' >> doc/user_threads.dat

gnuplot -p -e 'set title "User time plot with only one line of execution";
set xlabel "tests";
set ylabel "time in seconds";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/user_simples.dat" with points notitle' >> doc/user_simples.png
gnuplot -p -e 'set print "doc/user_simples.log";
stats "doc/user_simples.dat" nooutput;
print "Mean time of user time with only one line of execution:";
print STATS_mean;
print "Standart deviation of user time with only one line of execution:";
print STATS_stddev_err'

gnuplot -p -e 'set title "Plot de user time de multiprocessos";
set xlabel "tests";
set ylabel "time in seconds";
set fit quiet; set terminal png;
set boxwidth 0.5;
plot "doc/user_processos.dat" with points notitle' >> doc/user_processos.png
gnuplot -p -e 'set print "doc/user_processos.log";
stats "doc/user_processos.dat" nooutput;
print "Mean time of user time in multiprocess:";
print STATS_mean;
print "Standard deviation of user time in multiprocess:";
print STATS_stddev_err'

gnuplot -p -e 'set title "Plot de user time de multithreads";
set xlabel "tests";
set ylabel "time in seconds";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/user_threads.dat" with points notitle' >> doc/user_threads.png
gnuplot -p -e 'set print "doc/user_threads.log";
stats "doc/user_threads.dat" nooutput;
print "Mean time of user time in multithreads:";
print STATS_mean;
print "Standard deviation of user time in multithreads:";
print STATS_stddev_err'

##########################################################

pdflatex doc/template.tex &> /dev/null
rm template.log template.aux
mv template.pdf final_results.pdf
xdg-open final_results.pdf
