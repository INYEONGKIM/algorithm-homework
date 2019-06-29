package HW3;

public class quick {
    private static int exnum = 0;
    private static int conum = 0;

    public static void qsort(int[] S){

        quicksort(S, 0, S.length - 1);
        System.out.println("=========quickSort=========");
        System.out.println("comparison : " + conum);
        System.out.println("exchange : " + (exnum));
    }

    public static void quicksort(int[] arr, int low, int high){
        if( arr == null || arr.length == 0)
            return;
        if(low >= high)
            return;
        int j = low;
        int pivotpoint = low;
        for(int i = low + 1 ; i <= high ; i++){
            if(arr[i] < arr[pivotpoint]){
                j++;
                exnum++;
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
            ++conum;
        }
        int k = arr[j];
        arr[j] = arr[pivotpoint];
        arr[pivotpoint] = k;
        exnum++;

        pivotpoint = j;
        quicksort(arr, low, pivotpoint-1);
        quicksort(arr, pivotpoint+1, high);
    }
}