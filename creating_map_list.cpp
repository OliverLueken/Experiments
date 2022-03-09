#include <unordered_map>
#include <iostream>
#include <vector>
#include <ranges>

struct Node{
    int val;
    Node* next{nullptr};
};

int main(){
    auto vals = std::vector<int>{0,1,2,3,4,5,6,7};

    auto v = std::unordered_map<int, Node>{};
    Node* start;
    {
        auto addVal = [](auto& map, const auto val){
            return &map.emplace(val, val).first->second;
        };

        auto insertedElement = addVal(v, vals[0]);
        Node* lastInsertedElement = insertedElement;
        start = insertedElement;

        for(auto val : vals | std::views::drop(1))
        {
            insertedElement = addVal(v, val);
            lastInsertedElement->next = insertedElement;
            lastInsertedElement = insertedElement;
        }
    }

    for(auto nodePtr = start; nodePtr!=nullptr;){
        std::cout << nodePtr->val << '\n';
        nodePtr = nodePtr->next;
    }
}

/*
output:
0
1
2
3
4
5
6
*/
7
