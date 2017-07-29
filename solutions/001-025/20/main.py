def fact(n):
    if(n == 0): return 1
    if(n == 1): return 1
    res = 1
    for i in range(2, n+1):
        res *= i
    return res

def main():
    n = fact(100)
    res = 0
    while(n > 0):
        res += n % 10
        n //= 10
    print("If you can trust me, the number you are looking for is " + \
        str(res))

main()

