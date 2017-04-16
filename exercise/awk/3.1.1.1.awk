# sum1 - print column sums
#   input:  rows of each numbers
#   output: sum of each column
#       missing entries are treated as zeros
BEGIN {
    FS = "\t"
}

{
    for (i = 1; i <= NF; ++i) {
        sum[i] += $i
    }
    if (NF > maxfld) {
        maxfld = NF
    }
}
END {
    for (i = 1; i <= maxfld; ++i) {
        printf("%g", sum[i])
        if (i < maxfld) {
            printf("\t")
        }
        else {
            printf("\n")
        }
    }   
}
