# check2 - print total deposits and checks
# data mul_line_2.txt

BEGIN {
    RS = ""
    FS = "\n"
}

/(^|\n)deposit/ {
    deposits += field("amount")
    next
}
/(^|\n)check/ {
    checks += field("amount")
    next
}

END {
    printf("deposits %.2f, checks %.2f\n",
           deposits, checks)
}

function field (name, i, f) {
    for (i = 1; i <= NF; ++i) {
        split($i, f, " ")
        if (f[1] == name) {
           return f[2] 
        } 
    }
    printf("error: no field %s in record\n%s\n", name, $0)
}
