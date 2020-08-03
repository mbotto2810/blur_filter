#!/bin/sh

make -s threads
cp out.jpg data/out.jpg
make -s clear

echo "Iniciando testes para uma linha de execucao"

x=100
while [ $x -gt 0 ]; do
    /usr/bin/time -a -o doc/simples_raw.txt -p make -s simples
    echo "" >> doc/simples_raw.txt
    make -s clear
    x=$(($x-1))
done


echo "Iniciando testes para multiprocessos"

x=100
while [ $x -gt 0 ]; do
    /usr/bin/time -a -o doc/processos_raw.txt -p make -s process
    echo "" >> doc/processos_raw.txt
    make -s clear
    x=$(($x-1))
done

echo "Iniciando testes para multithreads"

x=100
while [ $x -gt 0 ]; do
    /usr/bin/time -a -o doc/threads_raw.txt -p make -s threads
    echo "" >> doc/threads_raw.txt
    make -s clear
    x=$(($x-1))
done

##########################################################

echo "Plotando real time"

cat doc/simples_raw.txt | grep real | sed -E 's/real//g' >> doc/real_simples.dat
cat doc/processos_raw.txt | grep real | sed -E 's/real//g' >> doc/real_processos.dat
cat doc/threads_raw.txt | grep real | sed -E 's/real//g' >> doc/real_threads.dat

gnuplot -p -e 'set title "Plot de real time de uma linha de execucao";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/real_simples.dat" with points notitle' >> doc/real_simples.png
gnuplot -p -e 'set print "doc/real_simples.log";
stats "doc/real_simples.dat" nooutput;
print "Media do real time executando em uma linha de execucao:";
print STATS_mean;
print "Desvio padrao do real time executando em uma linha de execucao:";
print STATS_stddev_err'

gnuplot -p -e 'set title "Plot de real time de multiprocessos";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/real_processos.dat" with points notitle' >> doc/real_processos.png
gnuplot -p -e 'set print "doc/real_processos.log";
stats "doc/real_processos.dat" nooutput;
print "Media do real time executando em multiprocessos:";
print STATS_mean;
print "Desvio padrao do real time executando em multiprocessos:";
print STATS_stddev_err'

gnuplot -p -e 'set title "Plot de real time de multithreads";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/real_threads.dat" with points notitle' >> doc/real_threads.png
gnuplot -p -e 'set print "doc/real_threads.log";
stats "doc/real_threads.dat" nooutput;
print "Media do real time executando em multithreads:";
print STATS_mean;
print "Desvio padrao do real time executando em multithreads:";
print STATS_stddev_err'

##########################################################

echo "Plotando user time"

cat doc/simples_raw.txt | grep user | sed -E 's/user//g' >> doc/user_simples.dat
cat doc/processos_raw.txt | grep user | sed -E 's/user//g' >> doc/user_processos.dat
cat doc/threads_raw.txt | grep user | sed -E 's/user//g' >> doc/user_threads.dat

gnuplot -p -e 'set title "Plot de user time de uma linha de execucao";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/user_simples.dat" with points notitle' >> doc/user_simples.png
gnuplot -p -e 'set print "doc/user_simples.log";
stats "doc/user_simples.dat" nooutput;
print "Media do user time executando em multithreads:";
print STATS_mean;
print "Desvio padrao do user time executando em multithreads:";
print STATS_stddev_err'

gnuplot -p -e 'set title "Plot de user time de multiprocessos";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet; set terminal png;
set boxwidth 0.5;
plot "user_processos.dat" with points notitle' >> doc/user_processos.png
gnuplot -p -e 'set print "doc/user_processos.log";
stats "doc/user_processos.dat" nooutput;
print "Media do user time executando em multiprocessos:";
print STATS_mean;
print "Desvio padrao do user time executando em multiprocessos:";
print STATS_stddev_err'

gnuplot -p -e 'set title "Plot de user time de multithreads";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/user_threads.dat" with points notitle' >> doc/user_threads.png
gnuplot -p -e 'set print "doc/user_threads.log";
stats "doc/user_threads.dat" nooutput;
print "Media do user time executando em multithreads:";
print STATS_mean;
print "Desvio padrao do user time executando em multithreads:";
print STATS_stddev_err'

##########################################################

echo "Plotando sys time"

cat doc/simples_raw.txt | grep sys | sed -E 's/sys//g' >> doc/sys_simples.dat
cat doc/processos_raw.txt | grep sys | sed -E 's/sys//g' >> doc/sys_processos.dat
cat doc/threads_raw.txt | grep sys | sed -E 's/sys//g' >> doc/sys_threads.dat

gnuplot -p -e 'set title "Plot de sys time de uma linha de execucao";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/sys_simples.dat" with points notitle' >> doc/sys_simples.png

gnuplot -p -e 'set title "Plot de sys time de multiprocessos";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "sys_processos.dat" with points notitle' >> doc/sys_processos.png

gnuplot -p -e 'set title "Plot de sys time de multithreads";
set xlabel "Tentativa";
set ylabel "Tempo";
set fit quiet;
set terminal png;
set boxwidth 0.5;
plot "doc/sys_threads.dat" with points notitle' >> doc/sys_threads.png
