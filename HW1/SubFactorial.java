import java.util.Scanner;

class SubFactorial
{
    public static int Subfact(int n) {
        int res = n!=0?n*Subfact(n-1)+(n%2==0?1:-1):1;
        System.out.println("!"+n+"="+res);
        return res;
    }

    public static void main(String args[]){
        Scanner scanner = new Scanner(System.in);
        int n;
        String test;
        do {
            System.out.println("Enter a number N: ");
            n=scanner.nextInt();
            scanner.nextLine(); //This is needed to pick up the new line
            if(n>12) System.out.println("N is too big ("+n+">12)...");
            else if(n<0) System.out.println("N is too small ("+n+"<0)...");
            else Subfact(n);
            System.out.print("Enter Y/y to continue or enter any key to exit... ");
            test=scanner.nextLine();
        } while(test.equalsIgnoreCase("y"));
    }
}
