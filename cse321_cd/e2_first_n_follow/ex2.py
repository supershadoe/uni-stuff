import sys


EPSILON = "Ɛ"
END_MARKER = "$"

ProductionsT = dict[str, list[str]]
FirstFollowT = dict[str, set[str]]

productions: ProductionsT = {}
first: FirstFollowT = {}
follow: FirstFollowT = {}


def compute_first(var: str, /) -> set[str]:
    # R1/R2
    if (not var.isupper()) or var == EPSILON:
        return {var}
    
    # For variables where first is already calculated
    if var in first:
        return first[var]

    first_var: set[str] = set()
    body = productions[var] if len(var) == 1 else [var]

    # R3
    for production in body:
        for symbol in production:
            first_sym = compute_first(symbol)
            first_var |= first_sym - {EPSILON}
            if EPSILON not in first_sym:
                break
        else:
            first_var |= {EPSILON}

    return first_var


def compute_follow(var: str, is_start: bool = False, /) -> set[str]:
    # For variables where follow is already calculated
    if var in follow:
        return follow[var]

    follow_var: set[str] = set()
    # R1
    if is_start:
        follow_var |= {END_MARKER}

    for head, body in productions.items():
        if head == var:
            continue # Prevent recursion
        for production in body:
            if var not in production:
                continue # No match
            split = production.split(var, 1)
            if split[1] != "":
                # R2: A -> αBβ
                first_beta = compute_first(split[1])
                follow_var |= first_beta - {EPSILON}
                # R3: A -> αBβ with Ɛ ∈ FIRST(β)
                if EPSILON in first_beta:
                    follow_var |= compute_follow(head)

            # R3: A -> αB
            if production[-1] == var:
                follow_var |= compute_follow(head)

    return follow_var


def parse_file(fname: str) -> ProductionsT:
    productions: ProductionsT = {}
    with open(fname, encoding="utf-8") as f:
        for line in f:
            head, rules = line.split("->")
            body = [s.strip() for s in rules.split("|")]
            head = head.strip()
            if head in productions:
                productions[head].extend(body)
            else:
                productions[head] = body

    return productions


fname = sys.argv[1]
productions = parse_file(fname)

for var in productions:
    first[var] = compute_first(var)
for i, var in enumerate(productions):
    follow[var] = compute_follow(var, i == 0)

print("FIRST\n")
for var, first_var in first.items():
    print(f"FIRST({var}) = {first_var}")
print("\nFOLLOW\n")
for var, follow_var in follow.items():
    print(f"FIRST({var}) = {follow_var}")
