package HW3;

public class HeapSort {
    private static int[] a;
    private static int n;
    private static int left;
    private static int right;
    private static int largest;

    private static int exhangeCnt = 0;
    private static int comparsionCnt = 0;

    // Build-Heap Function
    public static void buildheap(int []a){
        n=a.length-1;
        for(int i=n/2;i>=0;i--){
            maxheap(a,i);
        }
    }

    // Max-Heap Function
    public static void maxheap(int[] a, int i){
        left=2*i+1;
        right=2*i+2;

        if(left <= n && a[left] > a[i]){
            largest=left;
            comparsionCnt ++;
        }
        else{
            largest=i;
            comparsionCnt ++;
        }
        if(right <= n && a[right] > a[largest]){
            largest=right;
            comparsionCnt ++;
        }

        if(largest!=i){
            exchange(i, largest);
            maxheap(a, largest);
        }

    }

    // Exchange Function
    public static void exchange(int i, int j){

        int t=a[i];
        a[i]=a[j];
        a[j]=t;

        exhangeCnt++;

    }

    // Sort Function
    public static void sort(int []a0){
        a=a0;
        buildheap(a);
        for(int i=n;i>0;i--){
            exchange(0, i);
            n=n-1;
            maxheap(a, 0);
        }

        System.out.printf("comparsionCnt = %d\n",comparsionCnt);
        System.out.printf("exchangeCnt = %d\n",exhangeCnt);

    }

}