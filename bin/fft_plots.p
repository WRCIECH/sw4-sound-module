plot "fft_decomposition.txt" using 1:2 title "Noise" with lines, \
"fft_decomposition.txt" u 1:3 t "Low pass filter" w lines

