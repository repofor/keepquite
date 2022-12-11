#include <bits/stdc++.h>

using namespace std;
int main()
{
      int n,temp=0,tt=0,min,d=0,i,j;
      float atat=0,awt=0,stat=0,swt=0;

      cout<<"Enter the no. of processes: ";
      cin>>n;
      int at[n],bt[n],ct[n],tat[n],wt[n];
  
      for(i=0;i<n;i++)
      {
            cout<<"Enter arrival time of process "<<i+1<<": ";
            cin>>at[i];
      }
      for(i=0;i<n;i++)
      {
            cout<<"Enter burst time of process "<<i+1<<": ";
            cin>>bt[i];
      }
      for(i=0;i<n;i++)
      {
         for(j=i+1;j<n;j++)
          {
                if(bt[i]>bt[j])
                {
                      temp=at[i];
                      at[i]=at[j];
                      at[j]=temp;

                      temp=bt[i];
                      bt[i]=bt[j];
                      bt[j]=temp;
                }
          }
      }
      min=at[0];
      for(i=0;i<n;i++)
      {
            if(min>at[i])
            {
                  min=at[i];
                  d=i;
            }
      }
      tt=min;
      ct[d]=tt+bt[d];
      tt=ct[d];

      for(i=0;i<n;i++)
      {
            if(at[i]!=min)
            {
                  ct[i]=bt[i]+tt;
                  tt=ct[i];
            }
      }
      for(i=0;i<n;i++)
      {

            tat[i]=ct[i]-at[i];
            stat=stat+tat[i];
            wt[i]=tat[i]-bt[i];
            swt=swt+wt[i];
      }
      atat=stat/n;
      awt=swt/n;
      cout<<"Process\t\tArrival Time\tBurst Time\tCompletion Time\t  Waiting Time\tTurn Around Time\n";

    for(i=0;i<n;i++)
    {
    cout<<"P"<<i+1<<"\t\t"<<at[i]<<"\t\t"<<bt[i]<<"\t\t"<<ct[i]<<"\t\t"<<"  "<<wt[i]<<"\t\t"<<tat[i]<<endl;
    }

    cout<<"Average Waiting Time = "<<awt<<endl<<"Average Turn Around Time = "<<atat;
}