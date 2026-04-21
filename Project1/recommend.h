#pragma once
#ifndef RECOMMEND_H
#define RECOMMEND_H

#include <vector>
#include "food.h"

using namespace std;

vector<Food> recommendRuleBased(vector<Food>& foods, string keyword);
vector<Food> recommendScoring(vector<Food>& foods, string keyword);

#endif