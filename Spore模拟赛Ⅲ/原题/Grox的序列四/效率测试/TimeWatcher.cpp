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
const string dst="目标CPP.cpp",
			 org="源CPP.cpp" ,
			 ans="统计文档.cpp";
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
	char mod=0;//0为普通 1为// 2为/* 3为双引号 4为单引号 
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
		ThrowError("缺少文件"+org,"请将需要测试的源程序粘贴至此目录并更改名称");
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
		ThrowError("缺少文件"+codeconst,"请在BackUp文件夹中找到并复制到运行目录下");
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
		ThrowError("本次运行尚未处理任何程序","请先调用process");
		return;
	}
	ifstream input(result.c_str());
	if(access(result.c_str(),0)==-1){
		ThrowError("缺少文件"+result,"请检查程序是否正常结束或者至少调用统计函数一次,且已经处理、编译、运行");
		return;
	}
	int i,cnt;int tmp;
	if(!(input>>tmp)){
		ThrowError("数据为空","请检查程序是否正常结束或者至少调用统计函数一次,且已经处理、编译、运行");
		return;
	}
	if(tmp!=totcnt){
		ThrowError("数据不匹配","请检查程序是否正常结束或者至少调用统计函数一次,且已经处理、编译、运行");
		return; 
	}
	for(cnt=1;cnt<=totcnt;cnt++){
		if(!(input>>tmp)){
			ThrowError("数据缺失","请重新运行目标程序");
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
	printf("输入process以处理源码，编译运行后输入print以打印结果(过程中不要关闭本程序)\n");
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
