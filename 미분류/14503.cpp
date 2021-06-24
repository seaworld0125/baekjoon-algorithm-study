#include <iostream>
using namespace std;
 
//0:북, 1: 동, 2:남, 3:서
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
 
int main(){
    int N,M;
    int r,c,d;
    int map[51][51]={0};
    int visited[51][51]={0}; //청소 유무
    cin>>N>>M;
    cin>>r>>c>>d;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d",&map[i][j]);
        }
    }
    int ans=0;
    while(true){
        //후진으로 오는 경우도 있기 때문에 청소 유무 체크
        if(!visited[r][c]){
            ans++;
            visited[r][c]++;
        }
        bool check=false;
        for(int i=0;i<4;i++){
            d=(d+3)%4; //현재 위치에서 왼쪽 방향 회전
            int nr=r+dy[d];
            int nc=c+dx[d];
            if(nr<0 || nr >=N || nc<0 || nc>=M)
                continue;
            if(map[nr][nc] || visited[nr][nc])
                continue;
            check=true;
            r=nr;
            c=nc;
            break;
        }
        //후진 여부
        if(!check){
            r=r+dy[(d+2)%4];
            c=c+dx[(d+2)%4];
            if(r<0 || r >=N || c<0 || c>=M || map[r][c])
                break;
        }
    }
    cout<<ans<<endl;
    return 0;
}