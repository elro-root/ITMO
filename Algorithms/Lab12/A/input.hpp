//
// Created by Patrik Duksin on 2021-04-19.
//

#ifndef A_INPUT_HPP
#define A_INPUT_HPP
void input(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
}
#endif //A_INPUT_HPP
