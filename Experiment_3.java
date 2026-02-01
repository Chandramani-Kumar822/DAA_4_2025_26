import java.util.*;

public class Experiment_3{

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();   
        char[] arr = new char[n];
        for(int i = 0; i < n; i++) {
            arr[i] = sc.next().charAt(0);
        }
        HashMap<Integer, Integer> mp = new HashMap<>();
        mp.put(0, -1); 
        int prefixSum = 0;
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] == 'P') {
                prefixSum += 1;
            } else { 
                prefixSum -= 1;
            }
            if (mp.containsKey(prefixSum)) {
                int prevIndex = mp.get(prefixSum);
                maxLen = Math.max(maxLen, i - prevIndex);
            } else {
                mp.put(prefixSum, i);
            }
        }
        System.out.println(maxLen);
    }
}
