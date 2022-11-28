#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
int pos[6000050][2],num=1,fail[6000050],QUE[6000050],head=1,tail=1,pre[6000050];
bool tag[6000050],digit[6000050];
char target[5000050],templateT[5000050];
int insert()
{
	register int T,i,now=1,lenth,t;
	lenth=strlen(templateT);
	for(i=0;i<lenth;i++)
	{
		t=(int)(templateT[i])-48;
		if(!pos[now][t])
		{
			pos[now][t]=++num;
			now=num;
		}
		else
		{
			now=pos[now][t];
		}
	}
	tag[now]=1;
	return 0;
}
int bfs()
{
	register int number,now,father,t;
	while(head!=tail)
	{
		now=QUE[tail];
		father=pre[tail];
		number=digit[tail];
		if(tag[now])
		{
			fail[now]=1;
			tail++;
			continue;
		}
		if(pos[now][0])
		{
			QUE[head++]=pos[now][0];
			pre[head-1]=now;
			digit[head-1]=0;
		}
		if(pos[now][1])
		{
			QUE[head++]=pos[now][1];
			pre[head-1]=now;
			digit[head-1]=1;
		}
		if(!fail[now])
		{
			t=fail[father];
			while(!pos[t][number]&&t!=1)
			{
				t=fail[t];
			}
			fail[now]=t;
		}
		tail++;
	}
}
int find()
{
	register int i,lenth,ans=0,number,now=1;
	lenth=strlen(target);
	for(i=0;i<lenth;i++)
	{
		number=(int)(target[i])-48;
//		printf("NUMBER=%d ",number);
//		printf("NOW=%d\n",now);
		if(tag[now])
		{
			ans++;
			now=fail[now];
			i--;
//			printf(" END\n");
		}
		else
		{
			while(!pos[now][number])
			{
				now=fail[now];
			}
			now=pos[now][number];
		}
	}
	return ans;
}
int main()
{
	int a,b;
	register int i,j,ans;
	freopen("sugar.in","w",stdin);
	freopen("sugar.out","w",stdout);
	scanf("%d",&a);
	while(1)
	{
		scanf("%s",target);
		if(isdigit(target[0]))
		{
			break;
		}
	}
	for(i=1;i<=a;i++)
	{
		while(1)
		{
			scanf("%s",templateT);
			if(isdigit(templateT[0]))
			{
				break;
			}
		}
		insert();
	}
	fail[1]=1;
	QUE[head++]=1;
	bfs();
	ans=find();
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
5
010101010111
010
01
11
1000
1110
*/
