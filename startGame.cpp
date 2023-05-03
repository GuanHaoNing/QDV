//a_little_target.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "little_target.h"
#include "structure_define.h"

using namespace std;

void readData(role player){
    ifstream fin;
    fin.open("player.txt", ios::trunc);
    if (fin.fail()){
        cout << "fail to archive" << endl;
    }else{
        fin >> player.cash;
        fin >> player.total_assets;
        fin >> player.health;
        fin >> player.fame;
        fin >> player.age;
        fin >> player.retire_age;
        fin >> player.storehouse_capacity;
        fin >> player.isSick;
        fin.close();
    }
}

int startGame(){
    role player{100000, 100000, 100, 0, 20, 70, 100, false};

    //选择读取存档（Load game) 或开始新游戏 (New game)

    cout << "..." << endl; //游戏界面，选择存档或新游戏, to be completed
    int temp;

    if (temp == 2){
        ifstream fin;
        string line;
        string str;
        istringstream line_in(line);

        fin.open("player.txt");
        getline(fin, line);
        line_in >> player.cash;
        line_in >> player.total_assets;
        line_in >> player.health;
        line_in >> player.fame;
        line_in >> player.age;
        line_in >> player.retire_age;
        line_in >> player.storehouse_capacity;
        line_in >> player.isSick;
        //读取存档，to be complete,从file中获取角色信息
        //to be completed
    }

    if (temp == 1){
        //初始化角色
        //建立一个文档储存数据,to be completed
        readData(player);
    }

    //仓库 (使用linked list)
    product *storehouse;
    storehouse = new product;

    //商品，to be completed
    goods liquor;        //白酒
    goods imported_car;  //进口汽车
    goods jade;          //玉石
    goods melon_seed;    //瓜子
    goods domian_name;   //域名
    goods gold;          //黄金
    goods copycat_phone; //山寨手机
    goods bit_coin;      //比特币
    goods goods_list[8] = {liquor, imported_car, jade, melon_seed, domian_name, gold, copycat_phone, bit_coin};

    company gaming_industry(7, 0, 0.6, 0.1, 0.02, 2, 0, 1);                //氪金游戏公司
    company real_estate_company(40, 0, 0.8, 0.2, 0.01, 5, 0, 10);          //房地产公司
    company electric_manufacture(5, 0, 0.6, 0.1, 0.02, 3, 0, 1);           //电器制造厂
    company energy_drink_factory(10, 0, 0.6, 0.05, 0.03, 2, 0, 1);         //运动饮料厂
    company internet_celebrity_anchor(0.5, 0, 0.5, 0.1, 0.01, 0, 0, 0.1);  //网红主播

    company *company_list = new company[5];
    company_list[0] = gaming_industry;
    company_list[1] = real_estate_company;  
    company_list[2] = electric_manufacture;
    company_list[3] = energy_drink_factory;
    company_list[4] = internet_celebrity_anchor;

    string *company_charlist = new string[5];
    company_charlist[0] = "gaming industry";
    company_charlist[1] = "real estate company";
    company_charlist[2] = "electric manufacture";
    company_charlist[3] = "energy drink factory";
    company_charlist[4] = "internet celebrity anchor";

    bool *isSetUpCompany = new bool[5];
    bool *isBankrupt = new bool[5];
    for (int i = 0; i < 5; i++){
        isSetUpCompany[i] = false;
        isBankrupt[i] = false;
    } 

    int market_value = 0;
    
    //游戏主循环
    while (player.age <= player.retire_age){
        player.age += 1;

        //公司投资
        for(int i = 0; i < 5; i++){
            //是否破产
            if (company_list[i].bankrupt()){
                isBankrupt[i] = true;
                isSetUpCompany[i] = false;
                continue;
            }

            //股价浮动
            company_list[i].floating();

            //分红
            if (isSetUpCompany[i] = true && company_list[i].startProfit()){
                player.cash += company_list[i].dividend();
                player.total_assets += company_list[i].market_value();
                cout << company_charlist[i] << " pays dividends of " << company_list[i].dividend() << " dollar" << endl;
            }
        }

        for (int i = 0; i < 5; i++){
            if (isSetUpCompany[i]){
                market_value = company_list[i].market_value();
            }
        }
                        
        player.total_assets = player.cash + market_value;  //还要再加车的价值和房的价值

        cout << "..." << endl; // 游戏界面,从8个商品选5个出来展示，可以用file或直接cout,to be completed



        //买卖（market），创业（business）会损失健康值，
        if (player.health <= 50){
            //有几率住院
            srand(time(nullptr));
            int a = rand() % 4; //25%
            if (a == 1){
                player.isSick = true;
            }

        }
        
        //手动操作
        char input;
        bool GoToNextYear = false;

        if (!player.isSick){
            while (cin >> input){
                
                //market, 市场
                if (input == 'm'){
                    cout << "..." << endl; //游戏界面，写market的来设计一下按键
                    //function, to be completed




                }
                
                //business, 创业
                else if (input == 'b'){
                    cout << "..." << endl; //游戏界面，写business的来设计按键
                    int cash = player.cash;
                    business(cash, isBankrupt, isSetUpCompany, company_list, company_charlist);
                    player.cash = cash;
                    

                }

                //spend money，花钱
                else if (input == 's'){
                    cout << "..." << endl; //游戏界面，写spend money的来设计界面
                    //function, to be completed




                }

                //next year
                else if (input == 'n'){
                    GoToNextYear = true;
                }

                else{

                }

                for (int i = 0; i < 5; i++){
                    if (isSetUpCompany[i]){
                        market_value = company_list[i].market_value();
                    }
                }
                        
                player.total_assets = player.cash + market_value;  //还要再加车的价值和房的价值
                //将更新后的数据储存到文档，to be completed

                if (GoToNextYear){
                    readData(player);
                    break;
                }
            }
        }
        else{
            cout << "you are sick this year and could not do anything this year" << endl;
            cout << "..." << endl;     //游戏界面，按n进入下一年，按q提前退休




            string input;
            while(true){
                cin >> input;
                if (input == "n"){
                    readData(player);
                    break;
                }else{
                    cout << "you are sick this year and could not do anything this year" << endl;
                    continue;
                }
                
            }
        }
    }
        
    
    //游戏结束，结算界面（x岁资产超百万，y岁资产超千万，z岁资产过亿，a岁资产最多为m，退休时资产为n，etc.）
    cout << "..." << endl;
    delete[] company_charlist;
    delete[] company_list;
    delete[] isSetUpCompany;
    delete[] isBankrupt;

    //清空存档中的内容
    ofstream fout;
    fout.open("player.txt", ios::trunc);
    fout.close();

    return 0;
}

int main(){
    startGame();
}
