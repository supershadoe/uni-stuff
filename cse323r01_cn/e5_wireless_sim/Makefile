.PHONY: all run analyze

all: out.tr out.nam

analyze: out.tr
	awk -f analysis.awk out.tr

run: out.nam
	nam out.nam

out.tr out.nam: wireless.tcl
	ns wireless.tcl
