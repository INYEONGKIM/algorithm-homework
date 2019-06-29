package HW3;

import java.util.*;


public class Main {

    public static void main(String[] args) {
        Random random = new Random();

        Scanner s = new Scanner(System.in);

        System.out.print("n = ");
        int n = s.nextInt();
        int[] S = new int[n]; //gen
        int[] S1 = new int[n]; //heap
        int[] S4 = new int[n]; //quick

        //gen Array
        for (int i = 0; i < n; i++) {
            S[i] = random.nextInt(200);
            S1[i] = S4[i] = S[i];
        }

        //quickSort
        long start4 = System.currentTimeMillis();
        QuicksortInt.qsort(S4);
        long end4 = System.currentTimeMillis();

        System.out.println("comparison : " + QuicksortInt.comparison);
        System.out.println("exchange : " + QuicksortInt.exchange);
        System.out.println( "quick : " + ( end4 - start4 )/1000.0);

        //heapSort
        long start1 = System.currentTimeMillis();
        HeapSort.sort(S1);
        long end1 = System.currentTimeMillis();
        System.out.println( "Heap : " + ( end1 - start1 )/1000.0);

    }

} //class
