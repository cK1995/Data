/*
Developer : cK1995
Apriori code in C++.
*/

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

class node
{
  public:
	int l1,l2,l3,sum;
	node *next;
	node()
	{
	  l1=0;l2=0;l3=0;sum=0;next=NULL;
	}
	node(int a,int b,int c,int d)
	{
	  l1=a;l2=b;l3=c;sum=d;next=NULL;
	}
};

int main()
{
  int t,n,i,j,support,confidence;
  cout<<"Enter the number of transactions\n";
  cin>>t;
  cout<<"Enter the number of items\n"; 
  cin>>n;
  cout<<"Enter the support";
  cin>>support;
  cout<<"Enter the confidence";
  cin>>confidence;
  int bool_table[t][n],total[n],temp=0;
  char *ch[n];
  cout<<"Entering the boolean table entries from file input_apriori.txt\n";
  FILE *f=fopen("input_apriori.txt","r");
  char ch1;
  i=0,j=0;
  while(i<t)
  {
    j=0;
    while(j<n)//for(j=0;j<n;j++)
    {
      ch1=getc(f);
      if(ch1==48)
      {
	bool_table[i][j]=0;
        j++;
      }
      else if(ch1==49)
      {
	bool_table[i][j]=1;
        j++;
      }
      //cout<<(int)ch1<<"\n";
    }
    i++;
  }
  fclose(f);
  for(i=0;i<n;i++)
  {
    for(j=0;j<t;j++)
    {
      temp=temp+bool_table[j][i];
    }
    total[i]=temp;
    temp=0;
  }
  cout<<"Enter the names of items";
  for(i=0;i<n;i++)
  {
    ch[i]=new char[20];
    cin>>ch[i];
  }
  node *head1=NULL,*head2=NULL,*head3=NULL;
  node *prev1,*prev2,*prev3,*travel,*travel1,*max_p,*p12,*p23;
  int pass=1,flag=1,count=0,max=0;
  while(flag==1)
  {
    if(pass==1)
    {
      for(i=0;i<n;i++)
      {
        if(total[i]>=support)
        {
          node *tem1=new node(i,0,0,total[i]);
	  if(head1==NULL)
          {
            head1=tem1;
	    prev1=tem1;
          }
	  else
	  {
	    prev1->next=tem1;
	    prev1=tem1;
	  }
        }
      }
      if(head1==NULL)
      {
        flag=0;
      }
      travel=head1;
      while(travel!=NULL)
      {
        cout<<ch[travel->l1]<<":"<<travel->sum<<"\n";
	travel=travel->next;
      }
    pass++;
    }  
    else if(pass==2)
    {
      travel=head1;
      travel1=head1->next;
      while(travel!=NULL)
      {
        while(travel1!=NULL)
	{
	  for(i=0;i<t;i++)
	  {
	    if(bool_table[i][travel->l1]==1 && bool_table[i][travel1->l1]==1)
		count++;
	  }
	  if(count>=support)
	  {
	    node *tem2=new node(travel->l1,travel1->l1,0,count);
	    if(head2==NULL)
	    {
	      head2=tem2;
	      prev2=tem2;
	    }
	    else
	    {
	      prev2->next=tem2;
	      prev2=tem2;	
	    }
          }
	  count=0;
	  travel1=travel1->next;
	}
	travel=travel->next;
	if(travel!=NULL)
	  travel1=travel->next;
      }
      if(head2==NULL)
        flag=0;
      travel=head2;
      cout<<"\n";
      while(travel!=NULL)
      {
        cout<<ch[travel->l1]<<"-"<<ch[travel->l2]<<":"<<travel->sum<<"\n";
        travel=travel->next;
      }
      pass++;
    }
    else if(pass==3)
    {
      travel=head2;count=0;
      travel1=head2->next;
      while(travel!=NULL)
      {
          while(travel1!=NULL)
          {
	    if(travel->l1==travel1->l1){
            for(i=0;i<t;i++)
            {
              if(travel->l1==travel1->l1)
                if(bool_table[i][travel->l1]==1 && bool_table[i][travel->l2]==1 && bool_table[i][travel1->l2]==1)
                  count++;
            }
            if(count>=support)
            {
              node *tem3=new node(travel->l1,travel->l2,travel1->l2,count);
	      if(count>max)
	      {
		max=count;
		max_p=tem3;
                p12=travel;
                p23=travel1;
	      }
	      if(head3==NULL)
	      {
	        head3=tem3;
	        prev3=tem3;
	      }
	      else
	      {
	        prev3->next=tem3;
	        prev3=tem3;
	      }
	    }
            }
 	    travel1=travel1->next;
	    count=0;
	  }
        travel=travel->next;
	if(travel!=NULL)
	  travel1=travel->next;
      }
      flag=0;
      travel=head3;
      cout<<"\n";
      while(travel!=NULL)
      {
        cout<<ch[travel->l1]<<"-"<<ch[travel->l2]<<"-"<<ch[travel->l3]<<":"<<travel->sum<<"\n";
        travel=travel->next;
      }
    }
  }
  if(head3!=NULL)
  {
    float max_conf;
    max_conf=((float)max_p->sum/(float)total[max_p->l1])*100;
    if(max_conf<(((float)max_p->sum/(float)total[max_p->l2])*100))
      max_conf=((float)max_p->sum/(float)total[max_p->l2])*100;
    else if(max_conf<(((float)max_p->sum/(float)total[max_p->l3])*100))
      max_conf=((float)max_p->sum/(float)total[max_p->l3])*100;
    else if(max_conf<(((float)max_p->sum/(float)p12->sum)*100))
      max_conf=((float)max_p->sum/(float)p12->sum)*100;
    else if(max_conf<(((float)max_p->sum/(float)p23->sum)*100))
      max_conf=((float)max_p->sum/(float)p23->sum)*100; 
    cout<<max_conf;    
  }
  return 0;
}

