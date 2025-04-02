※clock.c為計算clock的function使用範例

在input中包含一些prefix是沒有length的
x.0.0.0 這種prefix表示length是8
x.y.0.0 length是16 
x.y.z.0 lenght是24
x.y.z.w length是32

In the input file，some of the prefix has no length means that 
x.0.0.0 is of length 8, 
x.y.0.0 is of length 16, 
x.y.z.0 is of length 24, 
x.y.z.w is of length 32

./pA2 routing_table.txt inserted_prefixes.txt deleted_prefixes.txt trace_file.txt

The file initializing the routing table: /share/HW10/pA/routing_table.txt
The file for extra insertion into the routing table: /share/HW10/pA/inserted_prefixes.txt
The file to delete specific IPs from the routing table: /share/HW10/pA/deleted_prefixes.txt
The file for IP lookups: /share/HW10/pA/trace_file.txt

The total number of prefixes in the routing_table.txt is : 84633

the number of prefixes with prefix length 3 = 1
the number of prefixes with prefix length 5 = 1
the number of prefixes with prefix length 6 = 3
the number of prefixes with prefix length 7 = 4
the number of prefixes with prefix length 8 = 107
the number of prefixes with prefix length 9 = 3
the number of prefixes with prefix length 10 = 5
the number of prefixes with prefix length 11 = 9
the number of prefixes with prefix length 12 = 47
the number of prefixes with prefix length 13 = 70
the number of prefixes with prefix length 14 = 164
the number of prefixes with prefix length 15 = 317
the number of prefixes with prefix length 16 = 6117
the number of prefixes with prefix length 17 = 1083
the number of prefixes with prefix length 18 = 1769
the number of prefixes with prefix length 19 = 4489
the number of prefixes with prefix length 20 = 5553
the number of prefixes with prefix length 21 = 4246
the number of prefixes with prefix length 22 = 6090
the number of prefixes with prefix length 23 = 7772
the number of prefixes with prefix length 24 = 43679
the number of prefixes with prefix length 25 = 383
the number of prefixes with prefix length 26 = 387
the number of prefixes with prefix length 27 = 439
the number of prefixes with prefix length 28 = 338
the number of prefixes with prefix length 29 = 989
the number of prefixes with prefix length 30 = 454
the number of prefixes with prefix length 31 = 1
the number of prefixes with prefix length 32 = 113