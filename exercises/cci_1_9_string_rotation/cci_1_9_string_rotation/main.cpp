// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <string>
/*
* This exercise is quite simple. If the second string is indeed 
* a rotation of the first one, we can split the second string in such a way
* that arranging them in the opposite order will give out the original string
* example:
* 
* s1 Pineapple
* s2 pplePinea
* 
* s2 can be splitted in: [pple] [Pinea]
* if we flip them we get [Pinea] [pple]
* 
* However if we notice:
* [pple] [Pinea]
* 
* seems to be the end and the beginning of the original string, I mean:
* 
* [pple] [Pinea]
* 
* is contained in 
* 
* PineapplePineapple
* 
* If we are only allowed to call substring once,
* we can check if s2 is a substring in s1+s1
* 
*/

bool IsRotationOf(const std::string& original, const std::string& possibleRotation) {
    if (original.size() != possibleRotation.size()) {
        return false;
    }

    std::string duplicatedOriginal = original + original;

    return duplicatedOriginal.find(possibleRotation) != std::string::npos;
}

int main(int argc, char* argv[]) {
    std::string s1 = "Pineapple";
    std::string s2 = "pplePinea";

    spdlog::info("Is [{}] a rotation of [{}]: {}", s2, s1, IsRotationOf(s1, s2));

    s1 = "apples";
    s2 = "oranges";

    spdlog::info("Is [{}] a rotation of [{}]: {}", s2, s1,
                 IsRotationOf(s1, s2));

    s1 = "joystick";
    s2 = "controll";

    spdlog::info("Is [{}] a rotation of [{}]: {}", s2, s1,
                 IsRotationOf(s1, s2));

    return 0;
}
