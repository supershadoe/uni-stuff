$1 == "r" && $3 == "1" { received++ }
END { print "DHCP requests: " received }
