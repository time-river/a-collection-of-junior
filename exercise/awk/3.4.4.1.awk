# pipeline to sotr address list by last names

BEGIN {
    RS = ""
    FS = "\n"
}
{
    printf("%s!!#", x[split($1, x, " ")])
    for (i = 1; i <= NF; ++i) {
       printf("%s%s", $i, i < NF ? "!!#" : "\n") 
    }
}
