//structure_define.h
#ifndef NEW_STRUCT
#define NEW_STRUCT

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

//商品属性
struct goods{
    int high_price;
    int normal_price;
    int low_price;
    double high_price_possiblity;
    double normal_price_possibility;
    double low_price_possibility;
};

//角色属性
class role{
    public:
        int cash;
        int total_assets;
        int health;
        int fame;
        int age;
        int retire_age;
        int storehouse_capacity; //仓库容量 
        bool isSick;

        role(int Cash, int TotalAsset, int Health, int Fame, int Age, int RetireAge, int StorehouseCapacity, bool IsSick){
            cash = Cash;
            total_assets = TotalAsset;
            health = Health;
            fame = Fame;
            age = Age;
            retire_age = RetireAge;
            storehouse_capacity = StorehouseCapacity;
            isSick = IsSick;
        }

        //天赋：倒爷
        void updateCash(int a){
            cash += a;
            total_assets += a;
        }

        //天赋：名门望族
        void updateFame(int a){
            fame += a;
        }
        
        //天赋：常青树
        void updateRetire_age(int a){
            retire_age += a;
        }

        //天赋
        void updateCapacity(int a){
            storehouse_capacity += a;
        }

};

//仓库物品 (linked list)
struct product{
    goods name;
    int number;
    product *next;
};

//公司属性
class company{
        double ups_possibility;     //上浮概率 (x%)
        double amplitude;           //最高上浮/下跌幅度 (y%)
        double dividend_rate;       //分红比例 (z%)
        int profit_year;            //建立后多少年开始盈利
        double bankrupt_threshold;  //破产阈值

        public:
            double cost_per_share;      //每股价格
            double average_cost;        //平均成本价
            int share_number;           //持股数
            int set_up_years = 0;           //成立时间

            company(double a, double b, double c, double d, double e, int f, int g, double h){
                cost_per_share = a;       
                average_cost = b;             
                ups_possibility = c;        
                amplitude = d;              
                dividend_rate = e;          
                profit_year = f;            
                share_number = g;           
                bankrupt_threshold = h;     
            }

            company(){

            }
        

            int dividend(){
                int money;
                money = round(cost_per_share * (share_number * dividend_rate));
                return money;
            }

            void floating(){
                //to determine whether increase or decrease
                bool *increase = new bool[100];
                for (int i = 0; i < 100; i++){
                    if (i < ups_possibility*100){
                        increase[i] = true;
                    }else{
                        increase[i] = false;
                    }
                }

                srand(time(nullptr));

                int random_number1 = rand() % 100;

                bool isIncrease = false;
                if (increase[random_number1]){
                    isIncrease = true;
                }

                delete[] increase;

                //to determine the rate of increase or decrease
                int temp = amplitude * 100;
                int random_number2;
                random_number2 = rand() % temp;

                //update cost_per_share
                if (isIncrease){
                    cost_per_share = cost_per_share * (1+(random_number2/100));
                }else{
                    cost_per_share = cost_per_share * (1-(random_number2/100));
                }

            }

            bool bankrupt(){
                if (cost_per_share < bankrupt_threshold){
                    cost_per_share = 0;
                    return true;
                }else{
                    return false;
                }
            }

            int market_value(){
                int temp;
                temp = round(cost_per_share * share_number);
                return temp; 
            }

            bool startProfit(){
                if (profit_year <= set_up_years){
                    return true;
                }
                return false;
            }

    };

#endif
