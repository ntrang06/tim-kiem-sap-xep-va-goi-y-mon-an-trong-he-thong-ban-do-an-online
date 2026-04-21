#include "recommend.h"
#include <algorithm>
// RULE-BASED
vector<Food> recommendRuleBased(vector<Food>& foods, string keyword) {
    vector<Food> result;

    for (auto f : foods) {
        // cùng loại (có keyword trong tên)
        if (f.name.find(keyword) != string::npos) {
            result.push_back(f);
        }
    }

    return result;
}

// SCORING (chấm điểm)
vector<Food> recommendScoring(vector<Food>& foods, string keyword) {
    vector<pair<Food, float>> scored;

    for (auto f : foods) {
        float score = 0;

        // nếu chứa keyword → +5 điểm
        if (f.name.find(keyword) != string::npos)
            score += 5;

        // rating càng cao → điểm càng cao
        score += f.rating;

        // giá thấp → cộng nhẹ
        score += (50 - f.price) * 0.1;

        scored.push_back({ f, score });
    }

    // sort theo score giảm dần
    sort(scored.begin(), scored.end(), [](auto a, auto b) {
        return a.second > b.second;
        });

    vector<Food> result;

    // lấy top 10–15 món
    for (int i = 0; i < scored.size() && i < 15; i++) {
        result.push_back(scored[i].first);
    }

    return result;
}