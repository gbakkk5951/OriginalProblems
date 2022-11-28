struct Big{
	int num[100];
	Big (char *a){
		*this=toBig(a);
	}
	Big toBig (char *a){
		int len;
		int i;
		Big ans;
		for(len=0;*a;a++);
		for(i=0;i<=len;i++){
			a--;
		}
		return ans;
	}
	Big (){
		
	}

	
}a;

int main(){
	
	
	
}
