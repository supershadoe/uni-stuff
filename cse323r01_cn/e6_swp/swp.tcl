set ns [new Simulator]

set tf [open out.tr w]
$ns trace-all $tf
set nam [open out.nam w]
$ns namtrace-all $nam

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 10Mb 20ms DropTail

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n1 $sink
$ns connect $tcp $sink

$tcp set window_ 5

set ftp [new Application/FTP]
$ftp attach-agent $tcp

$ns at 0.5 "$ftp start"
$ns at 4 "$ftp stop"
$ns at 4 "$ns flush-trace; close $tf; close $nam; exit 0"

$ns run
