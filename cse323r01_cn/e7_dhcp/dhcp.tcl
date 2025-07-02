set ns [new Simulator]

set tf [open out.tr w]
$ns trace-all $tf
set nam [open out.nam w]
$ns namtrace-all $nam

set server [$ns node]
set client [$ns node]

$ns duplex-link $server $client 10Mb 20ms DropTail

set s_agt [new Agent/UDP]
$ns attach-agent $server $s_agt
set c_agt [new Agent/UDP]
$ns attach-agent $client $c_agt
set s_sink [new Agent/Null]
$ns attach-agent $server $s_sink
set c_sink [new Agent/Null]
$ns attach-agent $client $c_sink

$ns connect $s_agt $c_sink
$ns connect $c_agt $s_sink

set c_traffic [new Application/Traffic/Exponential]
$c_traffic attach-agent $c_agt
set s_traffic [new Application/Traffic/Exponential]
$s_traffic attach-agent $s_agt

$ns at 1 "$c_traffic start"
$ns at 2 "$s_traffic start;"
$ns at 3 "$c_traffic stop; $s_traffic stop"
$ns at 3 "$ns flush-trace; close $tf; close $nam; exit 0"
$ns run
