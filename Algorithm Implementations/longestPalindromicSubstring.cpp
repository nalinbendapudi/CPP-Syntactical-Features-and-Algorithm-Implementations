// Display the longest palindromic substring of the given string

#include<iostream>
#include<string>

using namespace std;

int expandFromCenter(string s, int left, int right){
	while(left>=0 && right<s.length() && s[left]==s[right]){
		left--;
		right++;
	}
	return right-left-1;
}

string longstPalindrome(string s){
	int startIndex = 0, endIndex = 0, start, end;
	
	for(int i=0; i<s.length(); i++){
		
		int len1 = expandFromCenter(s,i,i);   // for palindromes like "abcba"
		int len2 = expandFromCenter(s,i,i+1); // for palindromes like "abccba"
		if (len1>len2){				//len1 is an odd number
			start = i-len1/2;
			end = i+len1/2;
		}
		else{						//len2 is an even number
			start = i-(len2-2)/2;
			end = (i+1)+(len2-2)/2;
		}
		
		if ((endIndex-startIndex) < (end-start)){
			startIndex = start;
			endIndex = end;
		}
		//cout<<start<<" "<<end<<" "<<len1<<" "<<len2<<endl;
	}
	//cout<<startIndex<<" "<<endIndex<<endl;
	return s.substr(startIndex,endIndex);
}
	

int main(){
	string s = "a racecar";
	string ss = longstPalindrome(s);
	cout<<ss<<endl;
	
	return 0;
}