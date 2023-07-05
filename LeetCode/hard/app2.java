package hard;
public class app2 {
        public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
            double median=0;
            int n1=nums1.length, n2=nums2.length;
            int ntot=n1+n2;
            int i=0,j=0;
            int cnt=0;
            int center;
            int change=0;
            if(ntot%2==0)change=1;

            while(cnt<ntot/2-change){
                if(n1<=i)j++;
                else if (n2<=j)i++;
                else if(nums1[i]<nums2[j])i++;
                else j++;
                cnt++;
            }

            if(ntot%2==0){
                if(n1<=i)return (nums2[j]+nums2[j+1])/2.0d;
                else if(n2<=j) return (nums1[i]+nums1[i+1])/2.0d;
                else {
                    if(nums1[i]<nums2[j])center=nums1[i++];
                    else center=nums2[j++];

                    if(n1<=i)return (center+nums2[j])/2.0d;
                    else if(n2<=j) return (center+nums1[i])/2.0d;
                    else if(nums1[i]<nums2[j])return (center+nums1[i])/2.0d;
                    else return (center+nums2[j])/2.0d;
                }
            }else{
                if(n1<=i)return nums2[j];
                else if(n2<=j) return nums1[i];
                else{
                    if(nums1[i]<nums2[j])return nums1[i];
                    else return nums2[j];
                }
            }
        }
        
        
        public static void main(String[] args){
            int[] a={1,2,3,4};
            int[] b={5,6,7,8};
            double test = findMedianSortedArrays(a,b);
            System.out.println(test);
        }
    
}
