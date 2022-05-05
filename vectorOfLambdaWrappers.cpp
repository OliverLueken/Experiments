#include <vector>
#include <memory>
#include <iostream>

struct VectorOfLambdas{

    struct Instruction{
        Instruction() = default;
        Instruction(const Instruction&) = default;
        Instruction& operator=(const Instruction&) = default;
        Instruction(Instruction&&) = default;
        Instruction& operator=(Instruction&&) = default;
        virtual ~Instruction() = default;

        virtual void operator()() = 0;
    };

    template<typename Lambda>
    struct Wrapper : public Instruction, public Lambda{

        Wrapper(Lambda &&lambda): Lambda{std::forward<Lambda>(lambda)} {}
        void operator()(){
            Lambda::operator()();
        }
    };

    std::vector<std::unique_ptr<Instruction>> instructions{};

    void addLambda1(const auto value){
        auto lambda1 = [_value = value]() mutable {
            std::cout << "Lambda1: " << _value << '\n';
            ++_value;
        };
        instructions.emplace_back(std::make_unique<Wrapper<decltype(lambda1)>>(std::move(lambda1)));
    }

    void addLambda2(const auto value){
        auto lambda2 = [_value = value]() mutable {
            std::cout << "Lambda2: " << _value << '\n';
            --_value;
        };
        instructions.emplace_back(std::make_unique<Wrapper<decltype(lambda2)>>(std::move(lambda2)));
    }

    void executeInstructions(){
        std::cout << "Amount of lambdas inside vec: " << instructions.size() << '\n';
        for(auto instrPos = 0; std::less{}(instrPos, instructions.size()); ++instrPos){
            instructions[instrPos]->operator()();
        }
    }
};

int main(){
    auto vec = VectorOfLambdas{};
    vec.addLambda1(1);
    vec.addLambda1(3);
    vec.addLambda1(5);
    vec.addLambda1(7);
    vec.addLambda1(9);
    vec.addLambda2(1);
    vec.addLambda2(3);
    vec.addLambda2(5);
    vec.addLambda2(7);
    vec.addLambda2(9);

    vec.executeInstructions();
    vec.executeInstructions();
}

/*
Output:

Amount of lambdas inside vec: 10
Lambda1: 1
Lambda1: 3
Lambda1: 5
Lambda1: 7
Lambda1: 9
Lambda2: 1
Lambda2: 3
Lambda2: 5
Lambda2: 7
Lambda2: 9
Amount of lambdas inside vec: 10
Lambda1: 2
Lambda1: 4
Lambda1: 6
Lambda1: 8
Lambda1: 10
Lambda2: 0
Lambda2: 2
Lambda2: 4
Lambda2: 6
Lambda2: 8
*/