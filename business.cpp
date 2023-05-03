//business.cpp
#ifndef BUSINESS
#define BUSINESS

#include <iostream>
#include <string>
#include "structure_define.h"
#include "little_target.h"
using namespace std;

void business(int &cash, bool* isBankrupt, bool* isSetUpCompany, company* company_list, string* company_charlist){
    char input;
    cout << "" << endl;     //游戏界面

    while (true){
    /*
        游戏界面, to be completed
        按q退出“business”界面
        按1-5可以对对应公司进行操作
        若未设立公司：
            对于未成立公司可以选择set up
        若已设立公司
            对于已成立且超过profit_year的公司可以选择买(b)/卖(s)
            对于已成立但未超过profit_year的公司无法操作，无法获得分红
            对于其他未成立公司无法操作
    */

        bool hasSetCompany = false;
        int temp;

        //check if player has set up a company
        for (int i = 0; i < 5; i++){
            if (isSetUpCompany[i]){
                hasSetCompany = true;
                temp = i;
            }
        }

        bool quit = false;
        cin >> input;

        switch (input){
            case 'q':
                quit = true;
                break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                if (!isBankrupt[input]){
                    //已设立一家公司，且过了profit year，可进行买/卖两种操作
                    if (hasSetCompany && input == temp){
                        if (company_list[temp].startProfit())

                            cout << "..." << endl; // 游戏界面

                            cin >> input;
                            
                            //buy
                            if (input == 'b'){
                                int max_share_to_buy;
                                max_share_to_buy = cash / company_list[temp].cost_per_share;

                                cout << temp << "." << company_charlist[temp] << ":" << endl;
                                cout << "you could buy at most" << max_share_to_buy << "shares" << endl;
                                cout << "enter the number of shares you want to buy: " << endl;
                                int num;
                                cin >> num;

                                if (num >= 0 && num <= max_share_to_buy){
                                    cash -= (num * company_list[temp].cost_per_share);
                                    company_list[temp].average_cost = ((company_list[temp].average_cost * company_list[temp].share_number) + company_list[temp].cost_per_share * num) / (company_list[temp].share_number + num);
                                    company_list[temp].share_number += num;   
                                }

                                else if (num > max_share_to_buy){
                                    cout << "you don't have enough cash" << endl;
                                }

                                else{
                                    cout << "invalid input" << endl;
                                }
                            }
                            
                            //sell
                            else if (input == 's'){
                                
                            cout << "you could sell at most" << company_list[temp].share_number << endl;
                            cout << "enter the number of shares you want to sell: " << endl;
                            int num;
                            cin >> num;
                            
                            //部分卖出
                            if (num >= 0 && num < company_list[temp].share_number){
                                int profit, price;
                                price = num * company_list[temp].cost_per_share;
                                cash += price;
                                cout << "you sold these shares for " << price << " dollar" << endl;

                                company_list[temp].share_number -= num;

                                profit = round((company_list[temp].cost_per_share - company_list[temp].average_cost) * num);
                                
                                if (profit >= 0){
                                    cout << "you earned " << profit << endl;
                                }
                                else{
                                    cout << "you lost " << (-profit) << endl; 
                                }
                            }

                            //全部卖出
                            else if (num == company_list[temp].share_number){
                                int profit, price;
                                price = num * company_list[temp].cost_per_share;
                                cash += price;

                                company_list[temp].share_number = 0;
                                isSetUpCompany[temp] = false;
                                hasSetCompany = false;

                                profit = round((company_list[temp].cost_per_share - company_list[temp].average_cost) * num);

                                if (profit >= 0){
                                    cout << "you earned " << profit << " dollar" << endl;
                                }
                                else{
                                    cout << "you lost " << (-profit) << " dollar" << endl; 
                                }
                            }

                            else if (num > company_list[temp].share_number){
                                cout << "you don't have enough shares" << endl;
                            }

                            else{
                                cout << "invalid input" << endl;
                            }
                        }
                        else{
                            cout << "your company is still developing, you can not operate on it yet" << endl;
                        }
                    }

                    //已设立一家公司，对另一家公司不能再进行操作                        
                    else if (hasSetCompany && input != temp){
                        cout << "you can only set up one company at a time";
                    }

                    //还未设立公司, 可以选择是否设立一家公司
                    else{
                        int temp = input;
                        cout << "Do you want to set up" << company_charlist[temp] << endl;
                        cout << "You need to buy 1000 shares of " << company_charlist[temp] << "to set up this company" << endl;
                        cin >> input;
                        if(input == 'y'){
                            //个人变化
                            cash -= 1000 * company_list[temp].cost_per_share;
                            hasSetCompany = true;
                            isSetUpCompany[temp] = true;

                            //公司变化
                            company_list[temp].average_cost = company_list[temp].cost_per_share;
                            company_list[temp].share_number = 1000;
                            company_list[temp].set_up_years = 0;    
                        }
                        
                        // to be complete   

                    }

                }else{
                    cout << "This company has gone bankrupt due to the recession" << endl;
                    cout << "You could not operate on this company" << endl;
                }

                break;

            default:
                continue;
                break;
        }

        if (quit){
            break;
        }
        
    }
}

#endif
