using namespace std;
int main(){}
#include<cstring>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<sstream>
#include<stack>
#include<io.h>
#include<vector>
#include<fstream>
struct Counter{
	int pos;
	string text;
};

vector<Counter>counter;
const string dst="Ŀ��CPP.cpp",
			 org="ԴCPP.cpp" ,
			 ans="ͳ���ĵ�.cpp";
const string codeconst="codeconst.cpp";
const string result="RunningResult.res";
string source;

struct _Main{
	
void ThrowError(string ErrorType,string Solution){
	cerr<<"Error:"+ErrorType<<endl;
	cerr<<Solution<<endl;
}
	
template<typename Type>
string tostring(Type a){
	stringstream s;
	string tmp;
	s<<a;
	s>>tmp;
	return tmp;
}

vector<bool>del;
int find(int beg){
	int i,j,k;int r,l;
	int cnt;
	for(;beg<source.size();beg++)if(!del[beg] && source[beg]=='{'){
		for(i=beg-1;i>=0;i--){
			if(!del[i] && !isspace(source[i])){
				r=i;
				break;
			}
		}
		if(r<0 || (source[r]!=')' && source[r]!=':') ){

            if(r>=4 &&source.substr(r-3, 4)=="else"){
				if(del[r-4] || (!isdigit(source[r-4]) && !isalpha(source[r-4]))){
					return beg+1;
				}
			}else if(r>=5 && source.substr(r-4, 5)=="const" 
				&& (del[r-5] || (!isdigit(source[r-5]) && !isalpha(source[r-5]) &&source[r-5]!='_')) ){
				    
				return beg+1;
			}
			continue;
		}else if(source[r]==')'){
			for(i=r-1;i>=0;i--){
				if(!del[i] && source[i]=='('){
					l=i;break;
				}
			}
			for(cnt=0,i=l+1;i<=r-1;i++){
				if(!del[i] && (isalpha(source[i])||source[i]=='_'||isdigit(source[i]))){
					cnt++;
					while(i<=r-1&&!del[i] && (isalpha(source[i])||source[i]=='_'||isdigit(source[i]))){
						i++;
					}
				}
			}

			for(i=l-1;i>=0;i--)if(!del[i] && !isspace(source[i])){
				break;
			}
			if(cnt==1){
	
				if( i>=2 && source.substr(i-1,2)=="if"
				&&(del[i-2] || (!isdigit(source[i-2]) && !isalpha(source[i-2]) &&source[i-2]!='_'))){
					cnt=2;
				}else if(i>=3 && source.substr(i-2,3)=="for"
				&&(del[i-3] || (!isdigit(source[i-3]) && !isalpha(source[i-3]) &&source[i-3]!='_'))){
					cnt=2;
				}else if(i>=5 && source.substr(i-4,5)=="while"
				&&(del[i-5] || (!isdigit(source[i-5]) && !isalpha(source[i-5]) &&source[i-5]!='_'))){
					cnt=2;
				}
			}else if(i>=6 &&source.substr(i-5,6)=="switch"
				&&(del[i-6] || (!isdigit(source[i-6]) && !isalpha(source[i-6]) &&source[i-6]!='_'))){

				cnt=1;
			}

			if(cnt!=1){
				return beg+1;
			}
		}else if(source[r]==':'){
			return beg+1;
		}
	}
	return -1;
	
}
void delnote(){
	char mod=0;//0Ϊ��ͨ 1Ϊ// 2Ϊ/* 3Ϊ˫���� 4Ϊ������ 
	char gang=0; 
	int i;
	del.clear();
	del.resize(source.size()+5);
	for(i=0;i<source.size();i++){
		del[i]=1;
		if(mod==1){
			if(source[i]=='\n'){
				del[i]=false;
				mod=0;
				continue;
			}
			continue;
		}else if(mod==2){
			if(source[i]=='*' && i+1<source.size() && source[i+1]=='/'){
				del[i]=del[i+1]=true;
				i++;
				mod=0;
				continue; 
			}
			continue;
		}else if(mod==3){
			if(source[i]=='"'&& gang==0){
				mod=0;
			}else if(source[i]=='\\'){
				gang^=1;
			}else{
				gang=0;
			}
			continue;
		}else if(mod==4){
			if(source[i]=='\'' && gang==0){
				mod=0;
			}else if(source[i]=='\\'){
				gang^=1;
			}else{
				gang=0;
			}
			continue;
		}if(mod==0){
			if( source[i]=='"'){
				mod=3;continue;
			}else if(source[i]=='/'){
				if(i+1<source.size()){
					if(source[i+1]=='/'){
						mod=1;del[i]=del[i+1]=1;
						i++;
						continue;
					}else if(source[i+1]=='*'){
						mod=2;del[i]=del[i+1]=1;
						i++;
						continue;
					}else{
						del[i]=false;
					}
				}else{
					del[i]=false;
				}
			}else if(source[i]=='\''){
				mod=4;continue;
			}else{
				del[i]=false;
			}
		}
	}
	
}
int totcnt;
bool processed;
void process(){
	stringstream os;
	if(access(org.c_str(),0)==-1){
		ThrowError("ȱ���ļ�"+org,"�뽫��Ҫ���Ե�Դ����ճ������Ŀ¼����������");
		return;
	}
	int i;
	int pos;
	totcnt=0;int cnt;
	ifstream orgin(org.c_str());

	os<<orgin.rdbuf();
	source=os.str();
	delnote();
	
	for(pos=0,cnt=0;(pos=find(pos))!=-1;pos++){
		totcnt++;
		counter.resize(totcnt+5);
		counter[totcnt].pos=pos;
		counter[totcnt].text="_TimeWatcherArray_["+tostring(totcnt)+"]++;";
	}
	if(access(codeconst.c_str(),0)==-1){
		ThrowError("ȱ���ļ�"+codeconst,"����BackUp�ļ������ҵ������Ƶ�����Ŀ¼��");
		return;
	}
	
	processed=1;
	
	ifstream constin(codeconst.c_str());

	
	ofstream dstout(dst.c_str());
	dstout<<"#define _TimeWatcherCount_ "<<totcnt<<endl;
	dstout<<constin.rdbuf()<<endl;	

	for(i=0,cnt=1;i<source.size();i++){
		if(cnt<=totcnt && i==counter[cnt].pos){
			dstout<<counter[cnt].text;
			cnt++;
		}
		dstout<<source[i];
	}
	
	dstout.close();
}

void print(){
	if(!processed){
		ThrowError("����������δ�����κγ���","���ȵ���process");
		return;
	}
	ifstream input(result.c_str());
	if(access(result.c_str(),0)==-1){
		ThrowError("ȱ���ļ�"+result,"��������Ƿ����������������ٵ���ͳ�ƺ���һ��,���Ѿ��������롢����");
		return;
	}
	int i,cnt;int tmp;
	if(!(input>>tmp)){
		ThrowError("����Ϊ��","��������Ƿ����������������ٵ���ͳ�ƺ���һ��,���Ѿ��������롢����");
		return;
	}
	if(tmp!=totcnt){
		ThrowError("���ݲ�ƥ��","��������Ƿ����������������ٵ���ͳ�ƺ���һ��,���Ѿ��������롢����");
		return; 
	}
	for(cnt=1;cnt<=totcnt;cnt++){
		if(!(input>>tmp)){
			ThrowError("����ȱʧ","����������Ŀ�����");
			return;
		}
		counter[cnt].text="/* Counter: "+tostring(tmp)+" */"; 
	}
	
	input.close();
	
	ofstream output(ans.c_str());
	for(i=0,cnt=1;i<source.size();i++){
		if(cnt<=totcnt && i==counter[cnt].pos){
			output<<counter[cnt].text;
			cnt++;
		}
		output<<source[i];
	}
	output.close();
	
	
	
}
string cmd;
_Main(){
	ifstream input("CON");
	printf("����process�Դ���Դ�룬�������к�����print�Դ�ӡ���(�����в�Ҫ�رձ�����)\n");
	while(1){
		input>>cmd;
		if(cmd=="process"){
			process();
		}else if(cmd=="print"){
			print();
		}
	}
}
	
	
	
	
	
	
	
}TimeWatcher;
