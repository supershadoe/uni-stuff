import sys


class Node:
    def __init__(self, var: str, deps: list['Node']) -> None:
        self._var = var
        self._deps = deps
        self.register: int | None = None

    def add_deps(self, deps: list['Node']) -> None:
        self._deps.extend(d for d in deps if d not in self._deps)

    @property
    def var(self) -> str:
        return self._var

    @property
    def deps(self) -> list['Node']:
        return self._deps

    def __repr__(self) -> str:
        return f"Node({self._var}, deps={[d._var for d in self._deps]})"


def graph_coloring(graph: list[Node], color_count: int) -> None:
    def _is_safe(node: Node, color: int):
        for deps in node.deps:
            if deps.register == color:
                return False
        return True

    def _color(i: int) -> bool:
        if i == len(graph):
            return True

        node = graph[i]
        for j in range(0, color_count):
            if _is_safe(node, j):
                node.register = j
                if _color(i+1):
                    return True
                node.register = None

        return False
    
    if not _color(0):
        print("Cannot allocate registers (need to spill)")
        return
    
    print("Allocated registers as follows")
    for node in graph:
        print(f"{node.var} = {node.register}")


with open(sys.argv[1]) as f:
    vars: dict[str, Node] = {}
    for instr in f:
        lval, _, op1, opr, op2 = instr.split()
        deps: list[Node] = []
        if op1 not in vars:
            node = Node(op1, [])
            vars[op1] = node
        deps.append(vars[op1])
        if op2 not in vars:
            node = Node(op2, [])
            vars[op2] = node
        deps.append(vars[op2])
        if lval in vars:
            vars[lval].add_deps(deps)
        else:
            vars[lval] = Node(lval, deps)
        vars[op1].add_deps([vars[lval], vars[op2]])
        vars[op2].add_deps([vars[lval], vars[op1]])
    graph = sorted(vars.values(), key=lambda x: x.var)
    graph_coloring(graph, 3)
