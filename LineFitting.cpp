#include<bits/stdc++.h>

using namespace std;

double sq[1001][1001],m[1001][1001],c[1001][1001]; /*!< Stores sum of least square error */
pair<double,double> arr[1001]; /*!< Stores the points in double format */
double memoization[1001]; /*!< Memoization dp table. */

/**
* Calculates the minimum error for a partition [i...j] considering both - introducing a new line and sum of least square error.
*/
double minError(int index,double C)
{
    if(index<0)return 0;
    if(index==0)return memoization[index]=1000000000;
    if(memoization[index]>0.000001)return memoization[index];

    memoization[index]=C;
    double ans=sq[index-1][index]+minError(index-2,C);
    for(int i=index-2;i>=0;--i)
    {
        ans=min(ans,sq[i][index]+minError(i-1,C));
    }
    memoization[index]+=ans;
    return memoization[index];
}
/**
* Prints the partition of line segments.
*/
void findSegment(int index,int C)
{
    if(index<=0)return;
    double ans=C+sq[0][index];
    int j=0;
    //cout<<ans<<" "<<index<<" "<<sq[0][index]<<endl;
    for(int i=1;i<index;i++)
    {
        if(i>0 and C+sq[i][index]+memoization[i-1]<ans)
        {
            j=i;
            ans=C+sq[i][index]+memoization[i-1];
        }
        else if(i==0 and C+sq[i][index]<ans)
        {
            j=i;
            ans=C+sq[i][index]+memoization[i-1];
        }
        //cout<<ans<<" "<<i<<" "<<index<<" "<<sq[i][index]<<endl;
    }
    //cout<<"[";
    //for(int i=j;i<=index;i++)cout<<"("<<arr[i].first<<","<<arr[i].second<<")";
    //cout<<"]\n";
    cout<<m[j][index]<<" "<<c[j][index]<<endl;
    //cout<<"Line: y="<<m[j][index]<<"x+"<<c[j][index]<<endl;
    //cout<<"Error:"<<sq[j][index]<<endl;
    findSegment(j-1,C);

}
int main()
{
    int n,i,j,C;
    cout<<"Enter the cost of the line"<<endl;
    cin>>C;
    freopen("Input.txt","r",stdin);
    //cout<<"Enter number of points\n";
    cin>>n;

   // cout<<"Enter points in x y format\n";
    for(i=0;i<n;i++)cin>>arr[i].first>>arr[i].second;
    sort(arr,arr+n);
    for(i=0;i<n;i++)
    {
        for(j=i;j<n;j++)
        {
            if(j==i){sq[i][j]=0;continue;}
            double sumx=0,sumy=0,ssumx=0,xy=0;
            for(int k=i;k<=j;k++)
            {
                sumx+=arr[k].first;
                sumy+=arr[k].second;
                ssumx+=arr[k].first*arr[k].first;
                xy+=arr[k].first*arr[k].second;
            }
            double a,b;
            int len=j-i+1;
            a=len*xy-sumx*sumy;
            a/=(len*ssumx-sumx*sumx);
            b=sumy-a*sumx;
            b/=len;
            m[i][j]=m[j][i]=a;
            c[i][j]=c[j][i]=b;
            sq[i][j]=0;
            for(int k=i;k<=j;k++)
            {
                sq[i][j]+=pow( (arr[k].second-a*arr[k].first-b),2);
            }
            sq[j][i]=sq[i][j];
        }
    }

    /*for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cout<<sq[i][j]<<" ";
        }
        cout<<endl;
    }*/


    for(i=0;i<n;i++)memoization[i]=0;
    double ans;

    
    //cout<<fixed<<setprecision(6)
    cout<<"Net error: "<<minError(n-1,C)<<endl;
    freopen("Output.txt","w",stdout);
    cout<<n<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i].first<<" "<<arr[i].second<<endl;
    }
    //for(i=0;i<n;i++)cout<<memoization[i]<<' ';cout<<endl;
    findSegment(n-1,C);


}
