# cumcomma - add up numbers conttaining commas

    { gsub(/,/, ""); sum += $0 }

END {
    print sum
}

