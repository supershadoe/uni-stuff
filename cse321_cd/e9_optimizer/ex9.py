import sys

with open(sys.argv[1]) as f:
    exprs: dict[str, str | None] = {}
    # Common subexpr elimination
    for instr in f:
        lval, rval = instr.split('=')
        lval, rval = lval.strip(), rval.strip()
        var = exprs.get(rval)
        if var is None:
            for expr in exprs:
                if lval in expr:
                    exprs[expr] = None
            exprs[rval] = lval
            print(f"{lval} = {rval}")
        else:
            print(f"{lval} = {var}")
