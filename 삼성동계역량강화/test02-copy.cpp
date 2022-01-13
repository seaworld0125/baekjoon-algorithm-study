#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#define MALE   0
#define FEMALE 1

#define INIT         0
#define ADDMEMBER    1
#define GETDISTANCE  2
#define COUNTMEMBER  3

#define COUPLE  0
#define PARENT  1
#define CHILD   2

#define NAME_LEN_MAX 19

////////////////////////////////////////////////////////////////////////////////

extern void init(char initialMemberName[], int initialMemberSex);
extern bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[]);
extern int  getDistance(char nameA[], char nameB[]);
extern int  countMember(char name[], int dist);

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

#define MALE 0
#define FEMALE 1
#define F first
#define S second

using namespace std;

struct Member {
    string name;
    int id;
    int sex;
    int parent[2] = {-1, -1};
    int spouse = -1;
    vector<int> child;

    Member(int id_, char * n, int sx) : id(id_), name(n), sex(sx) {}
    Member(int id_, char * n, int sx, vector<int> & c) : Member(id_, n, sx) { // 자식 공유
        child.assign(c.begin(), c.end());
    }
};

int familyId = 0;

// <name, number>
map<string, int> familyMap;
vector<Member> memberList;

int d[200];
int dd[200][200];

void init(char initialMemberName[], int initialMemberSex)
{
    familyId = 0;
    familyMap.clear();
    vector<Member>().swap(memberList);
    fill(dd[0], dd[0] + 40000, 1e9);
    
    memberList.emplace_back(familyId, initialMemberName, initialMemberSex);
    familyMap.emplace(initialMemberName, familyId);

    familyId++;
}
int getMemberId(char name[])
{
    return familyMap[string(name)];
}
bool canAddSpouse(char* newMemberName, int newMemberSex, char* existingMemberName) // 배우자가 될 수 있나?
{ 
    int id = getMemberId(existingMemberName);

    // 예외 처리
    if(memberList[id].spouse != -1 || memberList[id].sex == newMemberSex) return false;

    // 배우자로 등록
    memberList[id].spouse = familyId;

    // 가족 구성원에 추가
    familyMap.emplace(newMemberName, familyId);
    memberList.emplace_back(familyId, newMemberName, newMemberSex, memberList[id].child); // 배우자의 자식 정보도 복사됨
    memberList[familyId].spouse = id;
    // 배우자 자식들의 부모를 새 멤버로 설정
    for(int i = 0; i < memberList[familyId].child.size(); i++) {
        memberList[memberList[familyId].child[i]].parent[newMemberSex] = familyId;
    }
    familyId++;
    return true;
}
bool canAddParent(char* newMemberName, int newMemberSex, char* existingMemberName) // 부모가 될 수 있나?
{ 
    int id = getMemberId(existingMemberName);

    // 예외 처리
    if(memberList[id].parent[newMemberSex] != -1) return false;

    // 부모로 등록
    memberList[id].parent[newMemberSex] = familyId;

    // 가족 구성원에 추가
    familyMap.emplace(newMemberName, familyId);
    memberList.emplace_back(familyId, newMemberName, newMemberSex);

    // 자식이 부모가 있는 경우 
    int spouseId = memberList[id].parent[(newMemberSex + 1) % 2];
    if(spouseId != -1) {
        // 배우자로 추가하고 
        memberList[familyId].spouse = spouseId;
        memberList[spouseId].spouse = familyId;
        // 배우자의 자식 정보를 공유
        memberList[familyId].child.assign(memberList[spouseId].child.begin(), memberList[spouseId].child.end());
        // 배우자 자식들의 부모를 새 멤버로 설정
        for(int i = 0; i < memberList[familyId].child.size(); i++) 
            memberList[memberList[familyId].child[i]].parent[newMemberSex] = familyId;
    }
    else { // 자식이 부모가 없는 경우
        memberList[familyId].child.emplace_back(id);
    }
    familyId++;

    return true;
}
bool canAddChild(char* newMemberName, int newMemberSex, char* existingMemberName) // 자식이 될 수 있나?
{ 
    int id = getMemberId(existingMemberName);

    // 예외 처리 : 없음
    // 자식으로 등록
    memberList[id].child.emplace_back(familyId);
    // 가족 구성원에 추가
    familyMap.emplace(newMemberName, familyId);
    memberList.emplace_back(familyId, newMemberName, newMemberSex);
    // 부모 정보 추가
    memberList[familyId].parent[memberList[id].sex] = memberList[id].id;
    // 부모의 배우자 정보를 추가하기
    memberList[familyId].parent[(memberList[id].sex + 1) % 2] = memberList[id].spouse;
    familyId++;

    return true;
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[])
{
// relationship 
// 0 : newMemberName 을 existingMemberName 의 배우자로 추가
// 1 : newMemberName 을 existingMemberName 의 부모로 추가
// 2 : newMemberName 을 existingMemberName 의 자식으로 추가
    switch (relationship)
    {
    case 0:
        return canAddSpouse(newMemberName, newMemberSex, existingMemberName);
    case 1:
        return canAddParent(newMemberName, newMemberSex, existingMemberName);
    case 2:
        return canAddChild(newMemberName, newMemberSex, existingMemberName);
    }
}

int getDistance(char nameA[], char nameB[]) // start = A, goal = B
{
    // index 설정
    int startId = getMemberId(nameA);
    int goalId = 0;
    if(nameB) goalId = getMemberId(nameB);

    // 거리 초기화
    fill(d, d + 200, 1e9);
    d[startId] = 0;

    // 큐 설정
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, startId); 

    // 탐색

    int next, nextDistance;
    while(!pq.empty()) {
        int distance = -pq.top().F;
        int now = pq.top().S;
        pq.pop(); 

        if(d[now] < distance && dd[startId][now] < distance) continue;

        Member & nowMember = memberList[now];
        // 부모부터
        for(int i = 0; i < 2; i++) {
            if(nowMember.parent[i] != -1) {
                next = nowMember.parent[i]; 
                nextDistance = distance + 1; // 부모는 무조건 거리가 1
                if(nextDistance < d[next]) {
                    d[next] = nextDistance;
                    dd[startId][next] = nextDistance;
                    dd[next][startId] = nextDistance;
                    pq.emplace(-nextDistance, next);
                }
            }
        } 
        // 자식
        for(int i = 0; i < nowMember.child.size(); i++) {
            next = nowMember.child[i]; 
            nextDistance = distance + 1; // 자식은 무조건 거리가 1
            if(nextDistance < d[next]) {
                d[next] = nextDistance;
                dd[startId][next] = nextDistance;
                dd[next][startId] = nextDistance;
                pq.emplace(-nextDistance, next);
            }
        }
        // 배우자
        if(nowMember.spouse != -1) {
            next = nowMember.spouse; 
            nextDistance = distance; // 
            if(nextDistance < d[next]) {
                d[next] = nextDistance;
                dd[startId][next] = nextDistance;
                dd[next][startId] = nextDistance;
                pq.emplace(-nextDistance, next);
            }
        }
    }
	return d[goalId];
}

int countMember(char name[], int dist)
{
    getDistance(name, NULL);
    
    int count = 0;
    int id = getMemberId(name);

    for(int i = 0; i < 200; i++) 
        if(d[i] == dist && id != i) {
            count++;
        }
    
	return count;
}


////////////////////////////////////////////////////////////////////////////////

static int score = 0;

static void cmd_init()
{
	char initialMemberName[NAME_LEN_MAX + 1];
	int initialMemberSex;

	scanf("%s %d", initialMemberName, &initialMemberSex);
	
	init(initialMemberName, initialMemberSex);
}

static void cmd_addMember()
{
	char newMemberName[NAME_LEN_MAX + 1];
	int newMemberSex;
	int relationship;
	char existingMemberName[NAME_LEN_MAX + 1];

	scanf("%s %d %d %s", newMemberName, &newMemberSex, &relationship, existingMemberName);
	
	bool userAns = addMember(newMemberName, newMemberSex, relationship, existingMemberName);

	int ans;
	scanf("%d", &ans);
	bool ansbool = ans == 1 ? true : false;
	
	if (ansbool != userAns)
	{
		score = 0;
        cout << "addMember error\n";
        // printMembersInfo();
	}
}

static void cmd_getDistance()
{
	char nameA[NAME_LEN_MAX + 1];
	char nameB[NAME_LEN_MAX + 1];

	scanf("%s %s", nameA, nameB);
	
	int userAns = getDistance(nameA, nameB);

	int ans;
	scanf("%d", &ans);
	
	if (ans != userAns)
	{
		score = 0;
        cout << "getDistance error\n";
        // printMembersInfo();
	}
}

static void cmd_countMember()
{
	char name[NAME_LEN_MAX + 1];
	int dist;

	scanf("%s %d", name, &dist);
	
	int userAns = countMember(name, dist);

	int ans;
	scanf("%d", &ans);
	
	if (ans != userAns)
	{
		score = 0;
        cout << "countMember error\n";
        // printMembersInfo();
	}
}

int main()
{
	setbuf(stdout, NULL);

		freopen("sample_input_2.txt", "r", stdin);

	int T, scoreIdx;
	scanf("%d %d", &T, &scoreIdx);
	
	for (int TC = 1; TC <= T; TC++)
	{
		score = scoreIdx;
		
		int cmdL;
		scanf("%d", &cmdL);
		
		for (int cmdIdx = 0; cmdIdx < cmdL; ++cmdIdx)
		{
			int c_num;
			scanf("%d", &c_num);
			
			switch (c_num)
			{
			case INIT: 
				cmd_init(); 
				break;
				
			case ADDMEMBER: 
				cmd_addMember();  
				break;
				
			case GETDISTANCE: 
				cmd_getDistance();  
				break;
				
			case COUNTMEMBER: 
				cmd_countMember();  
				break;
				
			default: 
				break;
			}
		}
		printf("#%d %d\n", TC, score == scoreIdx ? scoreIdx : 0);
	}
	return 0;
}