# 寻找人口最多的国家
$3 > maxpop { maxpop = $3; country = $1 }
END {
    print "country with largest population:",
          country, maxpop
}

