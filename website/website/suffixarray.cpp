#include<bits/stdc++.h>
using namespace std;

struct tt {
	int first,second,index;
	
};

bool comp(const tt & n1,const tt & n2){
		if(n1.first == n2.first){
			if(n1.second==n2.second)
			{
				return n1.index>n2.index;
			}
			else 
				return n1.second<n2.second;
		}
		else
			return n1.first<n2.first;
	}


#define maxn (int)(1<<20)
int SA[maxn];
string str; //1 based indexed 
int p[20][maxn];
int N;
tt L[maxn];
int pow2[20];
int step;

int LCP[maxn];

void createSuffixArray(){

L[0].first=L[0].second=L[0].index=-7;

if(N==1){
	p[0][1]=1;
}
else{
	for(int i=1;i<=N;i++){
		p[0][i] = str[i]-'a'; 
	}
}

for(int k=0;k<=20;k++)
	pow2[k]= 1<<k;

int k=1;
while(pow2[k-1]<N){
	for(int j=1;j<=N;j++){
		L[j].index=j;
		L[j].first=p[k-1][j];
		L[j].second= ( (j+pow2[k-1]) <= N ? p[k-1][j+pow2[k-1]] :-1);
	}
/*	for(int i=0;i<=N;i++){
		cout<<"L["<<i<<"]"<<' '<<L[i].first<<" "<<L[i].second<<' '<<L[i].index<<'\n';
	}
*/
	sort(L,L+N+1,comp);
/*	for(int i=0;i<=N;i++){
		cout<<"L["<<i<<"]"<<' '<<L[i].first<<" "<<L[i].second<<' '<<L[i].index<<'\n';
	}
*/	
	for(int j=1;j<=N;j++){
		p[k][L[j].index] = ( ( ( j>1 && (L[j].first == L[j-1].first) ) && 
			(L[j].second==L[j-1].second) ) 
			? p[k][L[j-1].index] :
			 j );
	}
 ++k;
}

step=k-1;
//cout<<"step"<<step;
for(int i=1;i<=N;i++){
	SA [ p[step][i] ] =i;
}
/*
for(int k=0;k<=step;k++){
	for(int i=1;i<=N;++i){
		for(int j=i;j<=N;j++)
			cout<<str[j];
		    cout<<':';
		    cout<<p[k][i]<<" ";
	}
	cout<<'\n';
}
*/

}

int lcp(int i,int j){
	if(i==j){
		return N-i+1;
	}
	int ans=0;

	for (int x=step; (j<=N && i<=N) && x>=0  ; x--){
/*			for(int y=i;y<=N;y++)
			cout<<str[y];
		    cout<<':'<<p[x][i]<<" ";
		    for(int y=j;y<=N;y++)
			cout<<str[y];
		    cout<<':'<<p[x][j]<<"\n";
*/		if(p[x][i]==p[x][j]){
			ans+=pow2[x];
			i+=pow2[x];
			j+=pow2[x];
		}
	}
	return ans;
}

int longmtimes(int m){
	int ans=0;
	for(int i=1;i<N-m+1;i++){
		ans=max(ans,LCP[SA[i],SA[i+m-1]]);
	}
}



void pattern(string & t){
	int idx=0;
	int tl=t.length();
	int low=1,high=N,mid=(1+N)>>1;
	while(low<=high){
		mid=(low+high)>>1;
		int k=SA[mid];
		while((k<=N && idx<tl) && (str[k]==t[idx])){
			k++;
			idx++;
		}
		if(idx==tl)
			break;
		else
		if(str[k]<t[idx]){
			low=mid+1;
		}
		else 
			high=mid-1;
	}
	
	set<int>mt;
	

	if(low<=high){

		if(SA[mid]-1 == 0){
			cout<<"mid is 0"<<mid;
		}
		mt.insert(SA[mid]-1);
		int m1=mid-1,m2=mid+1;

		while(m1>=1){	
			if(LCP[m1]>=tl){
				
				mt.insert(SA[m1]-1);
			}
			else
				break;
			m1--;
		}
		while(m2<=N){
			if(LCP[m2-1]>=tl){
				
				mt.insert(SA[m2]-1);
			}
			else
				break;
			m2++;
		}
	}
	for(auto e : mt){
		cout<<e<<" ";
	}


}



int main(){
	string s;
	cin>>s;
	N=s.length();
	str ="a"+s;
	string t;
	cin>>t;
	createSuffixArray();

	for(int j=1;j<N;j++){
		LCP[j]=lcp(SA[j],SA[j+1]);
	}
//	cout<<"LCP :";
//	for(int j=1;j<N;j++){
//	
//		cout<<LCP[j]<<" ";
//	}
//	cout<<"\nsA ";
//	for(int i=1;i<=N;i++){
//		cout<<SA[i]<<" ";
//	}

	//cout<<"\npattern";
	pattern(t);

	
}

