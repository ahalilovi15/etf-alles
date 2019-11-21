package ba.unsa.etf.rpr;

import java.util.Scanner;

public class Main {

    public int sumaCifara(int i) {
        int suma;
        for(suma = 0; i != 0; i /= 10) {
            suma += i % 10;
        }
        return suma;
    }

    public static void main(String[] args) {
        System.out.println("Type in a number:");
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        Main main = new Main();

        for(int i = 1; i <= n; ++i) {
            if (i % main.sumaCifara(i) == 0) {
                System.out.println(i);
            }
        }
    }
}
