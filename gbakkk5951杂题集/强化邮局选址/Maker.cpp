using namespace std;
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
int pos;
char out[20],in[20],cmd[100];
int arr[3500];
int inline lrand(){
	return (rand()<<15) | rand();
}
void run(){
	int I;
	for(I=24;I<25;I++){
		sprintf(in,"post%d.in",I);
		sprintf(out,"post%d.out",I);
		sprintf(cmd,"std.exe > %s < %s",out,in);
		system(cmd);	
	}	
	
	
}
void make(){
	int n,m;int i,j,k;int I,J,K;int a,b,c;int mx;
	for(I=24;I<25;I++){
		sprintf(out,"post%d.in",I);
		freopen(out,"w",stdout);
		/*
		if(I<5)n=10,mx=50;
		else if(I<10)n=200,mx=2500;
		else n=2000,mx=10000;
		for(i=0;i<(n*3/2);i++){
			arr[i]=1+lrand()%mx;
		}sort(arr,arr+(n*3/2));
		a=unique(arr,arr+(n*3/2))-arr;
		n=min(2000,a);
		
		for(i=1;i<n;i++){
			swap(arr[i],arr[lrand()%(i+1)]);
		}
		m=lrand()%min(n,1000)+1;
		if(I==11)m=1;
		else if(I==6)m=n;
		printf("%d %d\n",n,m);
		for(i=0;i<n;i++){
			printf("%d ",arr[i]);
		}		
		*/
		if(I==23){
			n=2000,m=1000;
			printf("%d %d\n",n,m);
			int now=0;
			for(i=1;i<=n;i++){
				printf("%d ",now);
				if(i<=1000){
					now+=rand()%100+1+i*3000;
				}else{
					now+=rand()%3+1;
				}
			}
			
		}else if(I==24){
			n=2000,m=1000;
			printf("%d %d\n",n,m);
			int now=0;
			for(i=1;i<=n;i++){
				printf("%d ",now);
				if(i<=1000){
					now+=i*1003-i;
				}else{
					now+=rand()%3+1;
				}
			}			
		}
		fclose(stdout);
	}/*
	for(I=22;I<=22;I++){
		sprintf(out,"post%d.in",I);
		freopen(out,"w",stdout);
		m=998;n=2000;
		arr[0]=1;
		for(i=1;i<1300;i++){
			if(i%10<5)
			arr[i]=arr[i-1]+6;
			else arr[i]=arr[i-1]+5;
		}
		for(i=1300;i<2000;i++){
			arr[i]=arr[i-1]+1;
		}
		printf("%d %d\n",n,m);
		for(i=0;i<n;i++){
			printf("%d ",arr[i]);
		}			
		fclose(stdout);
	}	
	for(I=21;I<=21;I++){
		sprintf(out,"post%d.in",I);
		freopen(out,"w",stdout);
		m=999;n=2000;
		for(i=0;i<1000;i++){
			arr[i]=1+i*5;
		}
		for(i=1000;i<2000;i++){
			arr[i]=arr[i-1]+1;
		}
		printf("%d %d\n",n,m);
		for(i=0;i<n;i++){
			printf("%d ",arr[i]);
		}
		fclose(stdout);
	}		
	*/
}
int main(){
	srand(time(0));	
	make();
	run();
	
	
	
	
	
	
}
