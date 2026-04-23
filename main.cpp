#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

double dp[21][21];
bool computed[21][21];

// dp[i][j] = expected days to eat exactly j apples starting with i apples
double solve(int i, int j) {
    if (j == 0) return 0.0;
    if (i < j) return 1e9; // impossible
    if (computed[i][j]) return dp[i][j];
    
    double result = 1.0; // we take 1 day
    double sum = 0.0;
    
    // On this day, we can eat 1, 2, ..., i apples with equal probability 1/i
    for (int k = 1; k <= i; k++) {
        if (k <= j) {
            // We eat k apples, need to eat j-k more from i-k apples
            sum += solve(i - k, j - k);
        }
        // If k > j, we've eaten too many, but this contributes 0 to expected days
        // (we've already finished our goal)
    }
    
    result += sum / i;
    
    computed[i][j] = true;
    dp[i][j] = result;
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    memset(computed, false, sizeof(computed));
    
    double answer = solve(n, m);
    
    cout << fixed << setprecision(2) << answer << endl;
    
    return 0;
}
