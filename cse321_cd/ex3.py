import sys

from collections import deque
from typing import Self


EPSILON = "Ɛ"
END_MARKER = "$"

ProductionsT = dict[str, list[str]]
FirstFollowT = dict[str, set[str]]


class NotLL1Error(Exception):
    pass


class LL1ParsingError(Exception):
    pass


class LL1:
    _productions: ProductionsT
    _start_symbol: str
    _first: FirstFollowT
    _follow: FirstFollowT
    _parsing_table: dict[tuple[str, str], tuple[str, str]]

    def __init__(self: Self, productions: ProductionsT, /) -> None:
        self._productions = productions
        self._start_symbol = next(iter(self._productions.keys()))
        self._first = {}
        self._follow = {}
        self._parsing_table = {}

        for var in self._productions:
            self._first[var] = self._compute_first(var)
        for var in self._productions:
            self._follow[var] = self._compute_follow(
                var, var == self._start_symbol,
            )

        self._compute_parsing_table()

    def _compute_first(self: Self, var: str, /) -> set[str]:
        first_var: set[str] = set()
        body = ''

        if len(var) == 1:
            # R1/R2
            if not var.isupper() or var == EPSILON:
                return {var}
            # For variables where first is already calculated
            if var in self._first:
                return self._first[var]
            body = self._productions[var]
        else:
            body = [var]

        # R3
        for production in body:
            for symbol in production:
                first_sym = self._compute_first(symbol)
                first_var |= first_sym - {EPSILON}
                if EPSILON not in first_sym:
                    break
            else:
                first_var |= {EPSILON}

        return first_var

    def _compute_follow(
        self: Self, var: str, is_start: bool = False, /,
    ) -> set[str]:
        # For variables where follow is already calculated
        if var in self._follow:
            return self._follow[var]

        follow_var: set[str] = set()
        # R1
        if is_start:
            follow_var |= {END_MARKER}

        for head, body in self._productions.items():
            if head == var:
                continue # Prevent recursion
            for production in body:
                if var not in production:
                    continue # No match
                split = production.split(var, 1)
                if split[1] != "":
                    # R2: A -> αBβ
                    first_beta = self._compute_first(split[1])
                    follow_var |= first_beta - {EPSILON}
                    # R3: A -> αBβ with Ɛ ∈ FIRST(β)
                    if EPSILON in first_beta:
                        follow_var |= self._compute_follow(head)

                # R3: A -> αB
                if production[-1] == var:
                    follow_var |= self._compute_follow(head)

        return follow_var

    def _set_parsing_table(
        self: Self, *, key: tuple[str, str], val: tuple[str, str],
    ) -> None:
        old_val = self._parsing_table.get(key)
        if old_val is not None and old_val != val:
            raise NotLL1Error("Given grammar is not LL1")
        self._parsing_table[key] = val

    def _compute_parsing_table(self: Self) -> None:
        for head, body in self._productions.items():
            for production in body:
                # R1
                first_alpha = self._compute_first(production)
                for term in first_alpha - {EPSILON}:
                    self._set_parsing_table(
                        key=(head, term), val=(head, production),
                    )

                if EPSILON in first_alpha:
                    # R2
                    follow_a = self._compute_follow(head)
                    for term in follow_a:
                        self._set_parsing_table(
                            key=(head, term), val=(head, production),
                        )
                    # R3
                    if END_MARKER in follow_a:
                        self._set_parsing_table(
                            key=(head, END_MARKER), val=(head, EPSILON),
                        )

    def print_info(self: Self) -> None:
        print("LL(1) parser")
        print("\nFIRST\n")
        for var, first_var in self._first.items():
            print(f"FIRST({var}) = {first_var}")
        print("\nFOLLOW\n")
        for var, follow_var in self._follow.items():
            print(f"FOLLOW({var}) = {follow_var}")
        print("\nParsing Table\n")
        for k, v in self._parsing_table.items():
            print(f"M[{k}] = {v}")
        print()

    def parse(self: Self, word: str, /, *, debug: bool = False) -> bool:
        error_msg = f"Failed to parse {word}"
        stack: deque[str] = deque()
        stack.append(END_MARKER)
        stack.append(self._start_symbol)

        if debug:
            print(f"Parsing {word}:\n\nStack\nInput buffer\nAction taken\n")

        word = f"{word}{END_MARKER}"
        buf = iter(word)
        pointer = next(buf)
        loc = 0

        try:
            while stack:
                if debug:
                    print(f"{stack}\n{word[loc:]}\n", end="")
                x = stack[-1]
                if not x.isupper() or x == END_MARKER:
                    if x == pointer:
                        if debug:
                            print(f"Matched terminal {x}\n")
                        stack.pop()
                        pointer = next(buf)
                        loc += 1
                    else:
                        raise LL1ParsingError(error_msg)
                else:
                    if (rule := self._parsing_table.get((x, pointer))):
                        head, production = rule
                        if debug:
                            print(f"Expanding M[{x}, {pointer}] = {head} -> {production}\n")
                        stack.pop()
                        for symbol in production[::-1]:
                            if symbol != EPSILON:
                                stack.append(symbol)
                    else:
                        raise LL1ParsingError(error_msg)
        except StopIteration: # If input runs out before parsing finishes
            raise LL1ParsingError(error_msg)
        finally:
            return pointer == END_MARKER and not stack


def parse_file(fname: str, /) -> ProductionsT:
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


parser = LL1(parse_file(sys.argv[1]))
parser.print_info()
for word in sys.argv[2:]:
    if parser.parse(word, debug=True):
        print(f"{word} is accepted.")
    else:
        print(f"{word} is not accepted.")
