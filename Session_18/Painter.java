class Painter {
    public int minTime(int[] arr, int k) {
        int n = arr.length;
        int low = 0, high = 0;
        for (int len : arr) {
            low = Math.max(low, len);
            high += len;
        }
        int result = high;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (isPossible(arr, k, mid)) {
                result = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return result;
    }
    private boolean isPossible(int[] arr, int k, int maxTime) {
        int painters = 1;
        int currentSum = 0;
        
        for (int len : arr) {
            if (currentSum + len <= maxTime) {
                currentSum += len;
            } else {
                painters++;
                currentSum = len;
                if (painters > k) return false;
            }
        }
        return true;
    }
}
