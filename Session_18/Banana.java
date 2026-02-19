class Banana {
    public int minEatingSpeed(int[] piles, int h) {
        int maxpile=Arrays.stream(piles).max().getAsInt();
        int low=1,high=maxpile;
        int ans=maxpile;
        while(low<=high){
            int mid=low+(high-low)/2;
            long Total=calculate(piles,mid);
            if(Total<=h){
                ans=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return ans;

    }
    public long calculate(int[] piles,int speed){
        long total=0;
        for(int banana:piles){
            total+=(int)Math.ceil((double)banana/speed);
        }
        return total;
    }
}