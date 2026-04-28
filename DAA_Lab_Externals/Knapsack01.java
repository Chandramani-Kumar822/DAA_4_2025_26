public class Knapsack01 {
    static int knapsack(int capacity, int[] weights, int[] values, int n) {
        if (n == 0 || capacity == 0) {
            return 0;
        }
        if (weights[n - 1] > capacity) {
            return knapsack(capacity, weights, values, n - 1);
        }
        return Math.max(values[n - 1] + knapsack(capacity - weights[n - 1], weights, values, n - 1),
                        knapsack(capacity, weights, values, n - 1));
    }

    public static void main(String[] args) {
        int[] weights = {2, 3, 4, 5};
        int[] values = {3, 4, 5, 6};
        int capacity = 8;
        int n = weights.length;

        int maxVal = knapsack(capacity, weights, values, n);
        System.out.println( maxVal);
    }
}
