def main():
    lvl1 = "onetwothreefourfivesixseveneightnine"
    lvl1_5 = "teneleventwelvethirteenfourteen" + \
            "fifteensixteenseventeeneighteennineteen"
    lvl2 = "twentythirtyfortyfiftysixtyseventyeightyninety"

    #Numbers from 1 to 9
    res = len(lvl1)

    #Numbers from 10 to 99
    res += len(lvl1_5)
    res += len(lvl2) * 10 + len(lvl1) * 8

    #Numbers from 100 to 999
    res += len(lvl1) * 100 + len("hundred") * 900 + \
            len("and") * 99 * 9 + res * 9

    #Number 1000
    res += len("onethousand")

    print(res)

main()

