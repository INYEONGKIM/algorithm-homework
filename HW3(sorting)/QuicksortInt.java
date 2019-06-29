package HW3;

public class QuicksortInt {
    static int exchange = 0;
    static int comparison = 0;

    static int [ ] qsort(int items[]){
        qs(items, 0, items.length - 1);
        return items;
    }

    private static void qs(int items[], int left, int right){
        int i, j;
        int pivot, temp;
        i = left;
        j = right;
        pivot = items [(left + right) / 2];


        do{
            while ((items [i] < pivot) && (i < right)){
                i++;
                comparison++;
            }

            while ((pivot < items [j]) && (j > left)){
                j--;
                comparison++;
            }

            if (i <= j){
                exchange++;
                temp = items [i];
                items [i] = items [j];
                items [j] = temp;
                i++;
                j--;
                comparison++;
            }

        }while (i <= j);

        if (left < j){
            qs (items, left, j);
        }

        if (i < right){
            qs (items, i, right);
        }
    }
}