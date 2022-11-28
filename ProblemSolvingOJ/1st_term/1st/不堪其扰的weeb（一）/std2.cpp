using namespace std;
#include <iostream>
char s[] = 
R"(AAA    AAA
 AAA  AAA 
  AAAAAA  
   AAAA   
   AAAA   
  AAAAAA  
 AAA  AAA 
AAA    AAA
)";
int main() {
	int Tn;
	cin >> Tn;
	char c;
	for (int T = 1; T <= Tn; T++) {
		cin >> c;
		for (int i = 0; s[i]; ++i) {
			cout << (s[i] == 'A' ? c : s[i]);
		}
	}
	return 0;
}
