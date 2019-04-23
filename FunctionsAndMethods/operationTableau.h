#ifndef OPERATIONTABLEAU
#define OPERATIONTABLEAU
#include <bits/stdc++.h>
using namespace std;
void quicksort_Matrix_Nx2(int**  mat,int first,int last){
    int i, j, pivot, temp1,temp0;
    
    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(mat[i][1]<=mat[pivot][1]&&i<last){
                i++;}
            while(mat[j][1]>mat[pivot][1]) {
                j--;
            }

            if(i<j){
                temp0=mat[i][0];
                temp1=mat[i][1];
                mat[i][0]=mat[j][0];
                mat[i][1]=mat[j][1];
                mat[j][0]=temp0;
                mat[j][1]=temp1;
            }
        }

        temp0=mat[pivot][0];
        temp1=mat[pivot][1];
        mat[pivot][0]=mat[j][0];
        mat[pivot][1]=mat[j][1];
        mat[j][0]=temp0;
        mat[j][1]=temp1;
        quicksort_Matrix_Nx2(mat,first,j-1);
        quicksort_Matrix_Nx2(mat,j+1,last);

    }
}
void print_tab(int * tab, int v){
    for (int i=0; i<v;i++) cout<<i<<" : "<<tab[i]<<endl;
}
void print_mat(int ** mat, int n, int m){
    for (int i=0; i<n;i++){ 
        cout<<"[";
        for(int j=0; j<m;j++) 
            {
            cout<<mat[i][j]<<",";
            }
        cout<<"]"<<endl;
    }
}
int binarySearch(int arr[], int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
        if (arr[mid] == x) {
            return (1+binarySearch(arr, l, mid - 1, x)+binarySearch(arr, mid + 1, r, x)); 
        }
        if (arr[mid] > x) {
            return binarySearch(arr, l, mid - 1, x); 
        } 
        return binarySearch(arr, mid + 1, r, x); 
    } 
    return 0; 
};
int binarySearchMax(int arr[], int l, int r) 
{ 
    if (r > l) { 
        int mid = l + (r - l) / 2;
        cout<<mid<<endl; 
        int val1= binarySearchMax(arr, l, mid );
        int val2= binarySearchMax(arr,mid+1,r);
        return val1>val2?val1:val2; 
    } 
    if (r==l){
        return arr[r];
    }
    return 0; 
};
#endif
