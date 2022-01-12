// 매수 매도 주문을 처리할 수 있어야한다.

// --매수 조건--
// 매수 주문의 희망 가격이 매도 주문의 희망 가격 이상일 경우에만, 두 주문의 거래가 체결될 수 있다.
// 매수 주문이 새로 들어오면 미체결 매도 주문들과 거래를 체결한다.
// 거래를 체결할 미체결 매도 주문은 매도 희망 가격이 낮은 주문, 가격이 동일하다면 주문 번호가 낮은 주문 순으로 선택한다.
// 이때 체결되는 주문 수량은 두 주문의 남은 주문 수량 중 최솟값이며, 체결 가격은 매도 주문의 희망 가격이다.

// --매도 조건--
// 매도 주문이 새로 들어오면 미체결 매수 주문들과 거래를 체결한다.
// 거래를 체결할 미체결 매수 주문은 매수 희망 가격이 높은 주문, 가격이 동일하다면 주문 번호가 낮은 주문 순으로 선택한다.
// 이때 체결되는 주문 수량은 두 주문의 남은 주문 수량 중 최솟값이며, 체결 가격은 매수 주문의 희망 가격이다.

// 프로그램은 미체결 주문을 취소할 수 있어야 한다.

// mStock을 입력하면 아래의 값을 반환하는 함수를 요구했다.
// (mStock 주식의 임의의 시점(B)에서의 체결 가격 – mStock 주식의 임의의 시점(A)에서의 체결 가격)의 최댓값

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_BUY 2
#define CMD_SELL 3
#define CMD_CANCEL 4
#define CMD_BEST_PROFIT 5

extern void init();
extern int buy(int mNumber, int mStock, int mQuantity, int mPrice);
extern int sell(int mNumber, int mStock, int mQuantity, int mPrice);
extern void cancel(int mNumber);
extern int bestProfit(int mStock);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

#define SELL first
#define BUY  second

struct UnSignedOrder {
    int mNumber;
    int mQuantity;
    int mPrice;

    UnSignedOrder(int n, int q, int p) : mNumber(n), mQuantity(q), mPrice(p) {}
};

vector<UnSignedOrder> entityList;

struct compareSellTable {
    bool operator()(int a, int b) {
        if(entityList[a].mPrice > entityList[b].mPrice) return true;
        if(entityList[a].mPrice == entityList[b].mPrice) return entityList[a].mNumber > entityList[b].mNumber;
        return false;
    }
};
struct compareBuyTable {
    bool operator()(int a, int b) {
        if(entityList[a].mPrice < entityList[b].mPrice) return true;
        if(entityList[a].mPrice == entityList[b].mPrice) return entityList[a].mNumber > entityList[b].mNumber;
        return false;
    }
};

vector<priority_queue<int, vector<int>, compareSellTable>> mStockSellTable; 
vector<priority_queue<int, vector<int>, compareBuyTable>> mStockBuyTable;

vector<vector<int>> signedTable;
vector<int> deleteOrderList;

vector<int> bestProfitStore;
vector<int> lastIndex;

void init()
{
    vector<UnSignedOrder>(0, UnSignedOrder(0,0,0)).swap(entityList);

    vector<priority_queue<int, vector<int>, compareSellTable>>(6).swap(mStockSellTable); 
    vector<priority_queue<int, vector<int>, compareBuyTable>>(6).swap(mStockBuyTable);

    vector<vector<int>>(6).swap(signedTable);
    vector<int>(0).swap(deleteOrderList);

    vector<int>(6, 0).swap(bestProfitStore);
    vector<int>(6, 1).swap(lastIndex);
}

bool ifDelete(int num) {
    int size = deleteOrderList.size();

    for(int i = 0; i < size; i++) 
        if(deleteOrderList[i] == num) 
            return true;
    
    return false;
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice)
{
    int idx = 0, size = mStockSellTable[mStock].size();
    while(idx < size && mQuantity) { // 대기 중인 미체결 매도 주문이 있고, 매수자의 매수 물량이 남아있을 때 까지
        auto topEntity = entityList[mStockSellTable[mStock].top()];

        if(ifDelete(topEntity.mNumber)) {
            mStockSellTable[mStock].pop();
        }
        else if(topEntity.mPrice <= mPrice) {
            if(topEntity.mQuantity <= mQuantity) {
                mQuantity -= topEntity.mQuantity;
                signedTable[mStock].emplace_back(topEntity.mPrice);
                mStockSellTable[mStock].pop();
            }
            else {
                entityList[mStockSellTable[mStock].top()].mQuantity -= mQuantity;
                return 0;
            }
        }
        idx++;
    }
    entityList.emplace_back(mNumber, mQuantity, mPrice);

    mStockBuyTable[mStock].push(entityList.size()-1);
    return mQuantity;
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
    int idx = 0, size = mStockBuyTable[mStock].size();
    while(idx < size && mQuantity) { // 대기 중인 미체결 매수 주문이 있고, 매도자의 매도 물량이 남아있을 때 까지
        auto topEntity = entityList[mStockBuyTable[mStock].top()];

        if(ifDelete(topEntity.mNumber)) {
            mStockBuyTable[mStock].pop();
        }
        else if(topEntity.mPrice >= mPrice) {
            if(topEntity.mQuantity <= mQuantity) {
                mQuantity -= topEntity.mQuantity;
                signedTable[mStock].emplace_back(topEntity.mPrice);
                mStockBuyTable[mStock].pop();
            }
            else {
                entityList[mStockBuyTable[mStock].top()].mQuantity -= mQuantity;
                return 0;
            }
        }
        idx++;
    }
    entityList.emplace_back(mNumber, mQuantity, mPrice);
    mStockSellTable[mStock].push(entityList.size()-1);
    return mQuantity;
}

void cancel(int mNumber)
{
    deleteOrderList.emplace_back(mNumber);
}

int bestProfit(int mStock)
{
    auto & table = signedTable[mStock];
    int size = table.size();
    int ans = bestProfitStore[mStock];

    for(int i = size - 1; i >= lastIndex[mStock]; i--) {
        for(int j = 0; j < i; j++) {
            if(table[i] >= table[j]) {
                ans = max(ans, table[i] - table[j]);
            }
        }
    }
    bestProfitStore[mStock] = ans;
    lastIndex[mStock] = (size - 1 > 0 ? (size - 1) : 1);
    return ans;
}

/////////////////////////////////////////////////////////////////////////

static bool run()
{
    int numQuery;

    int mNumber, mStock, mQuantity, mPrice;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            init();
            isCorrect = true;
            break;
        case CMD_BUY:
            scanf("%d %d %d %d", &mNumber, &mStock, &mQuantity, &mPrice);
            userAns = buy(mNumber, mStock, mQuantity, mPrice);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        case CMD_SELL:
            scanf("%d %d %d %d", &mNumber, &mStock, &mQuantity, &mPrice);
            userAns = sell(mNumber, mStock, mQuantity, mPrice);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        case CMD_CANCEL:
            scanf("%d", &mNumber);
            cancel(mNumber);
            break;
        case CMD_BEST_PROFIT:
            scanf("%d", &mStock);
            userAns = bestProfit(mStock);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    init();

    return 0;
}