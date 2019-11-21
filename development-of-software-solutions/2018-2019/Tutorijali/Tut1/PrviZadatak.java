import java.util.Scanner;

public class PrviZadatak {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Type in two numbers");
        int firstNumber, secondNumber;
        firstNumber = scanner.nextInt();
        secondNumber = scanner.nextInt();
        System.out.println(Integer.toString(firstNumber) + " " + Integer.toString(secondNumber));
    }
}