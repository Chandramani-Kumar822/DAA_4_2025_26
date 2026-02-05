import java.util.*;

public class ScoreStream {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int K = sc.nextInt(); 
        int N = sc.nextInt(); 
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for(int i = 0; i < N; i++) {
            int score = sc.nextInt(); 
            if(minHeap.size() < K) {
                minHeap.add(score);
            } else if(score > minHeap.peek()) {
                minHeap.poll();
                minHeap.add(score);
            }

            if(minHeap.size() < K) {
                System.out.println(-1);
            } else{
                System.out.println(minHeap.peek());
            }
        }
    }
}