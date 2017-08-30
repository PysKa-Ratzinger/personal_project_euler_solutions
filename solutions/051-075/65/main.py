def main():
	terms = []
	for i in range(100):
		if i == 0: terms.append(2)
		elif (i+1)%3 == 0: terms.append(((i+1)/3)*2)
		else: terms.append(1)
	numerador = terms[-1]
	denominador = 1
	for i in reversed(terms[:-1]):
		# Switch
		temp = numerador
		numerador = denominador
		denominador = temp

		numerador += denominador * i
	#print(str(numerador) + "/" + str(denominador))
	sum = 0
	while (numerador) :
		sum += numerador % 10
		numerador = numerador / 10
	print("If you can trust me, the number you are looking for is " + str(sum))

main()

