import sys
import traceback
import typing as t
from collections import deque


EPSILON = "Ɛ"
END_MARKER = "$"


class LRItem(t.NamedTuple):
    head: str
    body: str
    lookahead: frozenset[str]
    pos: int


class Action(t.NamedTuple):
    action: str
    num: int
    head: str
    body: str

def compute_first(var: str) -> set[str]:
    first_var: set[str] = set()
    body = ''

    if len(var) == 1:
        # R1/R2
        if not var.isupper() or var == EPSILON:
            return {var}
        # For variables where first is already calculated
        if var in first:
            return first[var]
        body = productions[var]
    else:
        body = [var]

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


class CLR:
    _start_symbol: str
    _lr_items: list[list[LRItem]] = []
    _action_map: dict[LRItem, int] = {}
    _parsing_table: dict[tuple[int, str], Action] = {}
    _augmented_start_symbol = "START"

    def __init__(self: t.Self) -> None:
        self._start_symbol = next(iter(productions.keys()))
        self._compute_lr1_items()
        self._compute_parsing_table()

    def _lookahead(self: t.Self, beta: str, alpha: frozenset[str]) -> frozenset[str]:
        lookahead: set[str] = set()

        if len(beta) > 0:
            lookahead |= compute_first(beta)

        lookahead |= alpha

        return frozenset(lookahead)

    def _closure(self: t.Self, item: LRItem) -> list[LRItem]:
        items = [item]
        if item.pos == len(item.body):
            return items

        cur_sym = item.body[item.pos]
        beta = item.body[item.pos + 1:]

        if not cur_sym.isupper() or cur_sym == EPSILON:
            return items

        for rule in productions[cur_sym]:
            items += self._closure(LRItem(
                head=cur_sym,
                body=rule,
                lookahead=self._lookahead(beta, item.lookahead),
                pos=0,
            ))

        return items

    def _goto(self: t.Self, item: LRItem) -> list[LRItem]:
        if (item.pos + 1) > len(item.body):
            return []

        new_lr_item = LRItem(
            head=item.head,
            body=item.body,
            lookahead=item.lookahead,
            pos=item.pos + 1
        )

        items = self._closure(new_lr_item)

        return items

    def _compute_lr1_items(self: t.Self) -> None:
        init_item = LRItem(
            head=self._augmented_start_symbol,
            body=self._start_symbol,
            lookahead=frozenset({END_MARKER}),
            pos=0,
        )
        i0 = self._closure(init_item)
        self._lr_items.append(i0)

        q: deque[LRItem] = deque()
        for item in i0:
            q.append(item)

        while q:
            item = q.popleft()
            if item in self._action_map: continue
            items = self._goto(item)
            if len(items) == 0: continue
            self._action_map[item] = len(self._lr_items)
            self._lr_items.append(items)
            for item in items:
                q.append(item)
      
    def _compute_parsing_table(self: t.Self) -> None:
        for i, items in enumerate(self._lr_items):
            for item in items:
                if item.pos == len(item.body):
                    # reduce action
                    for sym in item.lookahead:
                        self._parsing_table[i, sym] = Action(
                            action='reduce',
                            num=0,
                            head=item.head,
                            body=item.body,
                        )
                else:
                    cur_sym = item.body[item.pos]
                    self._parsing_table[i, cur_sym] = Action(
                        action='goto' if cur_sym.isupper() else 'shift',
                        num=self._action_map[item],
                        head=item.head,
                        body=item.body,
                    )
                item.body

    def print_info(self: t.Self) -> None:
        print("CLR parser")

        print("\nFIRST\n")
        for var, first_var in first.items():
            print(f"FIRST({var}) = {first_var}")
        print(first)

        print("\nLR(1) items\n")
        for i, items in enumerate(self._lr_items):
            print(f"I{i}")
            for item in items:
                print(f"{item.head} -> {item.body}, {item.lookahead}, {item.pos}")

        print("\nParsing table\n")
        for (st_sym, buf_sym), act in self._parsing_table.items():
            print(f"M[{st_sym}, {buf_sym}] = ", end="")
            if act.action == 'reduce':
                print(f"Reduce {act.head} -> {act.body}")
            elif act.action == 'shift':
                print(f"Shift {act.num}")
            else:
                print(f"GOTO {act.num}")

    def parse(self: t.Self, word: str) -> None:
        stack: deque[int | str] = deque()
        stack.append(0)
        
        word = f'{word}{END_MARKER}'
        buf = iter(word)
        pointer = next(buf)
        loc = 0

        if debug:
            print(f'\nParsing the word {word}\n')
            print('Stack\nInput buffer\nAction\n')

        while stack:
            state = t.cast(int, stack[-1])
            action = self._parsing_table[state, pointer]
            if debug:
                print(f'{stack}\n{word[loc:]}\n{action}\n')
            if action.action == 'shift':
                stack.extend([pointer, action.num])
                pointer = next(buf)
                loc += 1
            elif action.action == 'reduce':
                for _ in range(len(action.body) * 2):
                    stack.pop()
                if action.head != self._augmented_start_symbol:
                    state = t.cast(int, stack[-1])
                    goto_action = self._parsing_table[state, action.head]
                    stack.extend([action.head, goto_action.num])
                else:
                    break
            else:
                stack.pop()
                stack.append(action.num)

productions = {
    'S': ['CC'],
    'C': ['aC', 'b'],
}
first = {
    'S': {'a', 'b'},
    'C': {'a', 'b'},
}
parser = CLR()
debug = True
if debug:
    parser.print_info()
for word in sys.argv[1:]:
    try:
        parser.parse(word)
        print(f"{word} is accepted")
    except Exception as e:
        print(f"{word} is not accepted")
        if debug:
            print("Error:")
            traceback.print_exc()

