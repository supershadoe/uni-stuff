BEGIN {
  routing_updates = 0
  sent = 0
  received = 0
}

$1 == "-" && $5 == "cbr" {
  sent++;
}

$1 == "r" && $5 == "cbr" {
  received++;
}

$1 == "r" && $5 == "rtProtoDV" {
  print "DV shared from " $3 " -> " $4
  routing_updates++
}

END {
  print "Number of routing updates: " routing_updates

  dropped = sent - received

  print "Sent packets: " sent
  print "Received packets: " received
  print "PDR: " (received/sent)*100
  print "PLR: " (dropped/sent)*100
}
