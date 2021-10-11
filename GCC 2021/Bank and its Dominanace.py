
def sol(n):
    seg = n.split('1')
    v = [0] + [len(s) for s in seg]
    v.sort()

    if v[-1] == 0:
        return 'B'

    if v[-1] % 2 == 0:
        return 'B'

    if v[-1] == v[-2]:
        return 'B'

    if int((v[-1] + 1) / 2) <= v[-2]:
        return 'B'

    return 'A'

# do not edit below code
def main():
    n=input()
    print(sol(n))

if __name__ == '__main__':
    main()
