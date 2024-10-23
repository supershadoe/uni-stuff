import sys

class Node:
    def __init__(self, i: int, parents: list['Node'], expr: str) -> None:
        self._expr = expr
        self._id = i
        self._var = expr.split('=')[0].strip()
        self._child_count = 0
        self._parents: list[Node] = parents
        self.visited = False
        self._register_child_with_parent()

    @property
    def var(self) -> str:
        return self._var

    @property
    def expr(self) -> str:
        return self._expr
    
    @property
    def parents(self) -> list['Node']:
        return self._parents
    
    @property
    def priority(self) -> int:
        return self._child_count

    def _register_child_with_parent(self) -> None:
        for p in self._parents:
            p._inc_child_count()

    def _inc_child_count(self) -> None:
        self._child_count += 1
        self._register_child_with_parent()

    def __repr__(self) -> str:
        return f'Node({self._expr}, parents={[p.var for p in self._parents]}, children={self._child_count})'

with open(sys.argv[1]) as f:
    vars: dict[str, list[Node]] = {}
    for i, instr in enumerate(f):
        lval, _, op1, opr, op2 = instr.split()
        parents: list[Node] = []
        if op1 in vars:
            parents.append(vars[op1][-1])
        if op2 in vars:
            parents.append(vars[op2][-1])
        node = Node(i, parents, instr.strip())
        if lval in vars:
            vars[lval].append(node)
        else:
            vars[lval] = [node]
    graph = list([j for i in vars.values() for j in i])
    instructions = sorted(graph, key=lambda n: n.priority, reverse=True)
    for instr in instructions:
        print(instr.expr)
