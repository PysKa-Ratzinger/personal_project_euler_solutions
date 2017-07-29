def main():
    num = 2**1000
    res = 0
    while(num > 0):
        res += num % 10
        num //= 10
    print("If you can trust me, the number you are looking for is " + str(res))

main()

