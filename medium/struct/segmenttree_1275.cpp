#include <iostream> 

using namespace std;

const int N = 2e5;
typedef long long LL;

struct node{
    int l,r;
    int v;
}tr[4*N];

void build(int u, int l, int r)
{
    tr[u] = {l,r};
    if(l==r) return;
    int mid = l + ((r-l)>>1);
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

int query(int u, int l, int r)
{
    if(tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    int v=0;
    int mid = tr[u].l + ((tr[u].r-tr[u].l)>>1);
    if(l <= mid) v=query(u<<1,l,r);
    if(r > mid) v=max(v,query(u<<1|1,l,r));

    return v;
}

void modify(int u, int idx, int v)
{
    if(tr[u].l==tr[u].r){
        tr[u].v=v;
        return;
    }
    int mid = tr[u].l + ((tr[u].r-tr[u].l)>>1);
    if(idx<=mid){
        modify(u<<1,idx,v);
    }
    if(idx>mid){
        modify(u<<1|1,idx,v);
    }
    tr[u].v = max(tr[u<<1].v, tr[u<<1|1].v);
}

int main()
{
    int m,p;
    int n=0;
    int last=0;
    cin >> m >> p;
    build(1, 1, m);
    while(m--){
        char op;
        int t;
        cin >> op >> t;
        if(op=='A'){
            modify(1, ++n, ((LL)t+last)%p);
        } else{
            int v = query(1,n-t+1,n);
            last=v;
            cout<<v<<endl;
        }
    }
}
