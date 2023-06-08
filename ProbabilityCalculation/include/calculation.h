#pragma once
/*#include <iostream>
#include <vector>

struct Characteristics
{
    int str;
    int t;
    int sv;
    int ap;
    bool isRapid;
    bool isShock;
    bool isShred;
    bool isPower;
};

Characteristics ourCharacteristics;



int main()
{
    int coutZeros = 0;
    int countOnes = 0;
    int countTwos = 0;
    int countThirds = 0;

    ourCharacteristics.str = 4;
    ourCharacteristics.t = 3;
    ourCharacteristics.sv = 4;
    ourCharacteristics.ap = -1;
    ourCharacteristics.isRapid = false;
    ourCharacteristics.isShock = false;
    ourCharacteristics.isShred = false;
    ourCharacteristics.isPower = false;

    for (int rapidRoll = 1; rapidRoll < 7; rapidRoll++)
        for (int critRoll = 1; critRoll < 7; critRoll++)
            for (int firstWoundRoll = 1; firstWoundRoll < 7; firstWoundRoll++)
                for (int secondWoundRoll = 1; secondWoundRoll < 7; secondWoundRoll++)
                    for (int thirdWoundRoll = 1; thirdWoundRoll < 7; thirdWoundRoll++)
                    {
                        std::vector<int> woundRolls = {firstWoundRoll, secondWoundRoll, thirdWoundRoll};
                        for (int firstSaveRoll = 1; firstSaveRoll < 7; firstSaveRoll++)
                            for (int secondSaveRoll = 1; secondSaveRoll < 7; secondSaveRoll++)
                                for (int thirdSaveRoll = 1; thirdSaveRoll < 7; thirdSaveRoll++)
                                {
                                    std::vector<int> saveRolls = {firstSaveRoll, secondSaveRoll, thirdSaveRoll};
                                    int result = Calculation(rapidRoll, critRoll, woundRolls, saveRolls);
                                    if (result == 0)
                                    {
                                        coutZeros++;
                                    }
                                    if (result == 1)
                                    {
                                        countOnes++;
                                    }
                                    if (result == 2)
                                    {
                                        countTwos++;
                                    }
                                    if (result == 3)
                                    {
                                        countThirds++;
                                    }
                                }
                    }

    int sum = coutZeros + countOnes + countTwos + countThirds;
    std::cout << "veroiatnost is\n";
    std::cout << "0 " << static_cast<double>(coutZeros) / sum << "\n";
    std::cout << "1 " << static_cast<double>(countOnes) / sum << "\n";
    std::cout << "2 " << static_cast<double>(countTwos) / sum << "\n";
    std::cout << "3 " << static_cast<double>(countThirds) / sum << "\n";
}
*/