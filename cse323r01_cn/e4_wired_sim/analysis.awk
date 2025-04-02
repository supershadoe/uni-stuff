BEGIN {
  total_bytes = 0
  duration = 0
  dropped = 0
  received = 0
}

$1 == "+" || $1 == "-" {
  duration = $2
}

$1 == "r" {
  total_bytes += $8
  duration = $2
  received++
}

$1 == "d" {
  dropped++
}

END {
  throughput = 0
  if (duration > 0) {
    throughput = (total_bytes * 8) / (duration * 1e3)
  }
  sent = received + dropped
  pdr = (received / sent) * 100
  plr = (dropped / sent) * 100

  print "Throughput: " throughput " kbps"
  print "Dropped packets: " dropped
  print "Packet Delivery Ratio (PDR): " pdr
  print "Packet Loss Ratio (PLR): " plr
}
