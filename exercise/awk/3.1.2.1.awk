# percent
#   input:  a column of nonnegative numbers
#   output: each number and its percentage of the total
BEGIN {
    FS = "\t"
}

    { x[NR] = $2; sum += $2 }

END {
    if (sum != 0) {
        for (i = 1; i <= NR; ++i) {
           printf("%10.2f %5.1f\n", x[i], 100*x[i]/sum) 
        }
    }
}

