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

using namespace std;

#define SELL first
#define BUY  second

struct UnSignedOrder {
    int mNumber;
    int mQuantity;
    int mPrice;

    UnSignedOrder(int n, int q, int p) : mNumber(n), mQuantity(q), mPrice(p) {}
};

struct compareSellTable {
    bool operator()(UnSignedOrder a, UnSignedOrder b) {
        if(a.mPrice > b.mPrice) return true;
        if(a.mPrice == b.mPrice) return a.mNumber > b.mNumber;
        return false;
    }
};
struct compareBuyTable {
    bool operator()(UnSignedOrder a, UnSignedOrder b) {
        if(a.mPrice < b.mPrice) return true;
        if(a.mPrice == b.mPrice) return a.mNumber > b.mNumber;
        return false;
    }
};

vector<pair<priority_queue<UnSignedOrder, vector<UnSignedOrder>, compareSellTable>, priority_queue<UnSignedOrder, vector<UnSignedOrder>, compareBuyTable>>> mStockTable(6);
vector<vector<int>> signedTable(6);

vector<int> deleteOrderList;

void init()
{
    vector<pair<priority_queue<UnSignedOrder, vector<UnSignedOrder>, compareSellTable>, priority_queue<UnSignedOrder, vector<UnSignedOrder>, compareBuyTable>>>(6).swap(mStockTable);
    vector<vector<int>>(6).swap(signedTable);
    vector<int>(0).swap(deleteOrderList);
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
    // cout << "buy > " << mNumber << ", " << mStock << ", " << mQuantity << ", " << mPrice << endl;
    auto & sellTable = mStockTable[mStock].SELL;

    int idx = 0, size = sellTable.size();
    while(idx < size && mQuantity) { // 대기 중인 미체결 매도 주문이 있고, 매수자의 매수 물량이 남아있을 때 까지
        if(ifDelete(sellTable.top().mNumber)) {
            sellTable.pop();
        }
        else if(sellTable.top().mPrice <= mPrice) {
            if(sellTable.top().mQuantity <= mQuantity) {
                mQuantity -= sellTable.top().mQuantity;
                signedTable[mStock].emplace_back(sellTable.top().mPrice);
                sellTable.pop();
            }
            else {
                sellTable.emplace(sellTable.top().mNumber, (sellTable.top().mQuantity - mQuantity), sellTable.top().mPrice);
                signedTable[mStock].emplace_back(sellTable.top().mPrice);
                sellTable.pop();
                // cout << "no remain\n";
                return 0;
            }
        }
        idx++;
    }
    mStockTable[mStock].BUY.emplace(mNumber, mQuantity, mPrice);
    // cout << "buy remain > " << mQuantity << endl;
    return mQuantity;
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
    // cout << "sell > " << mNumber << ", " << mStock << ", " << mQuantity << ", " << mPrice << endl;
    auto & buyTable = mStockTable[mStock].BUY;

    int idx = 0, size = buyTable.size();
    while(idx < size && mQuantity) { // 대기 중인 미체결 매수 주문이 있고, 매도자의 매도 물량이 남아있을 때 까지
        // cout << "buyer [" << buyTable.top().mPrice << ", " << buyTable.top().mQuantity << "]\n";
        if(ifDelete(buyTable.top().mNumber)) {
            buyTable.pop();
        }
        else if(buyTable.top().mPrice >= mPrice) {
            // cout << "buyer is come\n";
            if(buyTable.top().mQuantity <= mQuantity) {
                mQuantity -= buyTable.top().mQuantity;
                signedTable[mStock].emplace_back(buyTable.top().mPrice);

                buyTable.pop(); // pop이 안되나?
            }
            else {
                buyTable.emplace(buyTable.top().mNumber, (buyTable.top().mQuantity - mQuantity), buyTable.top().mPrice);
                signedTable[mStock].emplace_back(buyTable.top().mPrice);
                buyTable.pop();
                // cout << "no remain\n";
                return 0;
            }
        }
        idx++;
    }
    mStockTable[mStock].SELL.emplace(mNumber, mQuantity, mPrice);
    // cout << "sell remain > " << mQuantity << endl;
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
    int ans = 0;

    for(int i = size - 1; i >= 1; i--) {
        for(int j = 0; j < i; j++) {
            // cout << table[i] << ", " << table[j] << endl;
            if(table[i] >= table[j]) {
                ans = max(ans, table[i] - table[j]);
            }
        }
    }
    // cout << "bestProfit > " << ans << endl;
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