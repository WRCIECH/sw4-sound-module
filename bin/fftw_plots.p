plot "fft_decomposition.txt" u 1:4 t "Low pass filter spectral" w lines


while (1) {
    replot
    pause 5
}
