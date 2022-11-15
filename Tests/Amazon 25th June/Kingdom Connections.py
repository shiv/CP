def f1(wal, vis, p):
    if p in vis:
        return wal[p]

    vis.add(p)
    for cp in wal[p]:
        wal[p] = wal[p].union(f1(wal, vis, cp))

    vis.union(wal)
    return wal[p]

def f2(wal):
    c = set()
    for p in wal:
        vis = set(c)
        f1(wal, vis, p)
        c.add(p)

    for p in wal:
        wal[p].discard(p)
    return wal

def f3(land_adj_list, vis, p):
    global com
    if p in vis:
        return

    vis.add(p)
    com.add(p)
    for cp in land_adj_list[p]:
        f3(land_adj_list, vis, cp)

def f4(wal):
    global com
    conn_by_water = set()
    for p in com:
        conn_by_water = conn_by_water.union(wal[p])

    return len(com.intersection(conn_by_water)) == 0

def f5(N, edges):
    adj_list = {}
    for p in range(1, N+1):
        adj_list[p] = set()

    for edge in edges:
        adj_list[edge[0]].add(edge[1])
        adj_list[edge[1]].add(edge[0])

    return adj_list

com = set()

def solve(A, B, N, land, water):
    global com
    land_adj_list = f5(N, land)
    wal = f5(N, water)
    wal = f2(wal)
    vis = set()
    res = 0
    for p in range(1, N+1):
        com = set()
        if not p in vis:
            f3(land_adj_list, vis, p)
            if len(com) > res and f4(wal):
                res = len(com)

    return res