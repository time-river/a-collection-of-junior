# data convert - convert mmddyy into yymmdd in $1
# data.txt is test file

{ $1 = substr($1, 5, 3) substr($1, 1, 2) substr($1, 3, 2); print }
