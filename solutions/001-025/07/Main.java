
class Main{
    public static boolean isPrime(int number){
        for(int i=2; i<=number/i; i++){
            if(number%i == 0) return false;
        }
        return true;
    }

    public static void main(String[] args){
        int index = 6;
        int currentNumber = 13;
        while(index != 10001){
            do{
                currentNumber += 2;
            }while(!isPrime(currentNumber));
            index++;
        }
        System.out.println("If you can trust me, the number " +
                "you are looking for is " + currentNumber);
    }
}

