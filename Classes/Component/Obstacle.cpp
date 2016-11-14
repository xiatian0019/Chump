//
//  Obstacle.cpp
//  Chump
//
//  Created by xiaoming on 16/6/3.
//
//

#include "Obstacle.hpp"
#include "GameTools.hpp"
#include "GameSetting.h"
std::vector<int> Obstacle::getObstacle(int obstacleId)
{
    std::vector<int>obstacleList;
    auto dataList = Obstacle::getObstacleData(GameTools::getRandomNum(0, 9));
    
    for (int i=0; i<dataList.length(); i++) {
        dataList[i];
        int num = dataList[i];
        if (num>96) {
            num=96-num;
        }
        else{
            num=num-48;
        }
        obstacleList.push_back(num);
    }
    return obstacleList;
}


std::string Obstacle::getObstacleData(int index)
{
   // //000000200000000000300000000000
//    00000000030000000000000200000000
//    00000020000c00000000300000000000
//    00000000000000300000000000000000
//    00000000100000000000020000000000
//    000000b0000000000000d00000000000
    
//    00000000c0000002000000000b000000
//    00000020000002000000002000000000
//    0000b000000100000000000d00000000
//    000000c0000000200000000a00000000
//    00001000000000100000000000000000
//    000000200000000000d0000000000000
    
    
    std::vector<std::string>dataList;
//    dataList.push_back("00000003000000000000032100000000");
//    dataList.push_back("00000000040000000000220000000000");
//    dataList.push_back("00000001110000000000003300000000");
//    dataList.push_back("00000000003000000000003000000000");
//    dataList.push_back("00000012300000000000000321000000");
//    dataList.push_back("00000000000012210000000000000000");
//    dataList.push_back("00000000000012000000000004000000");
//    dataList.push_back("00000000002200000000000022000000");
    
    dataList.push_back("00000000200000000000300000000000");
    dataList.push_back("00000000030000000000000200000000");
    dataList.push_back("0000000020000c000000003000000000");
    dataList.push_back("00000000000000300000000000000000");
    dataList.push_back("00000000010000000000002000000000");
    dataList.push_back("0000000b0000000000000d0000000000");
    dataList.push_back("000000000c0000002000000000b00000");
    dataList.push_back("00000002000000200000000200000000");
    dataList.push_back("00000b000000100000000000d0000000");
    dataList.push_back("0000000c0000000200000000a0000000");
    dataList.push_back("00000010000000001000000000000000");
    dataList.push_back("00000000200000000000d00000000000");


    
    return dataList.at(index);
}