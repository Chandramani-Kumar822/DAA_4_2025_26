import java.util.Arrays;

public class JobScheduling {
    static class Job {
        int id, deadline, profit;
        
        Job(int id, int deadline, int profit) {
            this.id = id;
            this.deadline = deadline;
            this.profit = profit;
        }
    }
    
    static int maxProfit(Job[] jobs) {
        Arrays.sort(jobs, (a, b) -> b.profit - a.profit);
        
        int maxDeadline = 0;
        for (Job job : jobs) {
            maxDeadline = Math.max(maxDeadline, job.deadline);
        }
        
        boolean[] slot = new boolean[maxDeadline + 1];
        int totalProfit = 0;
        
        for (Job job : jobs) {
            for (int j = job.deadline; j > 0; j--) {
                if (!slot[j]) {
                    slot[j] = true;
                    totalProfit += job.profit;
                    break;
                }
            }
        }
        return totalProfit;
    }
    
    public static void main(String[] args) {
        Job[] jobs = {
            new Job(1, 4, 20),
            new Job(2, 1, 10),
            new Job(3, 2, 40),
            new Job(4, 2, 30)
        };
        
        int result = maxProfit(jobs);
        System.out.println("Maximum profit: " + result);
    }
}
