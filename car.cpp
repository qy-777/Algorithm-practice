#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+7;const ll inf=1e15;const int M=17;
ll f[M][N][2],da[N][M][2],db[N][M][2],ga[N],gb[N],H[N];
int n,m;
ll dis(int i,int j) {return abs(H[i]-H[j]);}
void buig(){
    set<pair<ll,int>> s;
    s.insert({inf,0}),s.insert({inf+1,0});
    s.insert({-inf,0}),s.insert({-inf-1,0});
    for(int i=n;i;i--){
        int p1=0,p2=0;ll d1=inf,d2=inf;
        pair<ll,int> now=make_pair(H[i],i);
        auto p=s.lower_bound(now);p++;
        for(int j=0;j!=4;j++,p--){
            ll d=abs(p->first-H[i]);
            if(d<=d1){
                d2=d1,p2=p1;
                d1=d,p1=p->second;
            }
            else if(d<=d2){
                d2=d,p2=p->second;
            }
        }
        ga[i]=p2,gb[i]=p1;
        s.insert(now);
    }
}
void buif(){
    for(int i=1;i<=n;i++) f[0][i][0]=ga[i],f[0][i][1]=gb[i];
    for(int i=1;i<=n;i++) f[1][i][0]=f[0][f[0][i][0]][1],f[1][i][1]=f[0][f[0][i][1]][0];
    for(int i=2;i<M;i++)
        for(int j=1;j<=n;j++)
            for(int k=0;k!=2;k++)
                f[i][j][k]=f[i-1][f[i-1][j][k]][k];
}
void buid(){
    for(int i=1;i<=n;i++) da[0][i][0]=dis(i,ga[i]),db[0][i][1]=dis(i,gb[i]);
    for(int i=1;i<=n;i++) da[1][i][0]=da[0][i][0],db[1][i][1]=db[0][i][1],
                          da[1][i][1]=da[0][f[0][i][1]][0],db[1][i][0]=db[0][f[0][i][0]][1];
    for(int i=2;i<M;i++)
        for(int j=1;j<=n;j++)
            for(int k=0;k!=2;k++)
                da[i][j][k]=da[i-1][j][k]+da[i-1][f[i-1][j][k]][k],
                db[i][j][k]=db[i-1][j][k]+db[i-1][f[i-1][j][k]][k];
}
pair<ll,ll> calc(int p,ll x){
    ll a=0,b=0;
    for(int i=M;~i;i--)
        if(f[i][p][0]&&a+b+da[i][p][0]+db[i][p][0]<=x) {
            a += da[i][p][0], b += db[i][p][0],
            p = f[i][p][0];
        }
    return {a,b};
}
void solv(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>H[i];
    buig();buif();buid();
    pair<ll,ll> res;double ans=1e9,ress;
    ll x;cin>>x;int p;
    for(int i=1;i<=n;i++){
        res=calc(i,x);
        ress=res.second?(double)res.first/res.second:inf;
        if(ress<ans) ans=ress,p=i;
    }
    cout<<p<<endl;
    cin>>m;
    while(m--){
        cin>>p>>x;
        res=calc(p,x);
        cout<<res.first<<" "<<res.second<<endl;
    }
}
int main(){
    solv();
}
