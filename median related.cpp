#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	
	int t;
	cin>>t;
	while(t--){
	    int n,k;
	    cin>>n>>k;
	    int arr[n];
	    for(int i=0;i<n;++i){
	        cin>>arr[i];
	    }
	    int median = (n&1) ? arr[n/2] : ((arr[n/2 - 1]+arr[n/2])/2);
	    int rightExtreme = median + k/2;
	    int leftExtreme = median - (k-1)/2;\
	    long ans = 0;
	    for(int i=0;i<n;++i){
            long maxDist = max(abs(rightExtreme-arr[i]),abs(arr[i]-leftExtreme));
            ans += maxDist;
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
