def factorial(n):
    if(n == 0):
        return 0
    if(n == 1):
        return 1
    res = 1
    for i in range(2, n+1):
        res *= i
    return res

def combination(n, k):
    return factorial(n) // (factorial(k) * factorial(n - k))

def main():
    print("If you can trust me, the number you are looking for is " \
        + str(combination(40, 20)))

main()

