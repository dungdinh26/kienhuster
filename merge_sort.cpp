//Xay dung sap xep nhanh 
#include<iostream>
using namespace std;
// Tron 2 day da duoc sap xep trong day A
// Day L1={A[m],A[m+1],...,A[n]}, day L2={A[n+1],...,A[p]}
void merge_array(int A[],int m,int n,int p){
    int i=m,j=n+1;
    while(i<j && j<=p){
        if(A[i]<A[j]) i++;
        else{
            int x=A[j];
            for(int k=j-1;k>=i;i++){
                A[j+1]=A[j];
            }
            A[i]=x;
            i++;
            j++;

        }
        
    }
}
void Split_merge(int a[],int first, int last){
    if(first>=last) return;
    int mid=(first+last)/2;
    Split_merge(a, first, mid);
    Split_merge(a,mid+1,last);
    merge_array(a,first,mid,last);
}
void Mergesort(int a[],int N){
    if(N<2) return;
    Split_merge(a,0,N-1);
}
int main(){
    int a[100];
    int n;
    cout<<"Nhap so gia tri cua day: ";
    cin>>n;
    cout<<endl<<"Nhap day so: ";
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    Mergesort( a,n);
    for(int i=0;i<n;i++){
        cout<<a[i];
    }
    return 0;
}