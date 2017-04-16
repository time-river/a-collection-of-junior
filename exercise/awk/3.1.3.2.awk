# addcomma - put commas in numbers
#   input:  a number per line
#   output: the input number followed by
#       the number with commas and two decimal places
# num.txt is test file

    { printf("%-12s %20s\n", $0, addcomma($0)) }

function addcomma (x, num) {
    if (x < 0) {
       return "-" addcomma(-x) 
    }
    num = sprintf("%.2f", x) # num is dddddd.dd
    while (num ~ /[0-9][0-9][0-9][0-9]/) { $ 4 个数字
        sub(/[0-9][0-9][0-9][,.]/, ",&", num) # 注意 & 的使用
    }
# An & in the replacement string s is replaced 
#    by the matched substring of t.
    return num
}   
