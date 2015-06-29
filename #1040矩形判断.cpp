//
//  main.cpp
//  hihoCoder
//
//  Created by chenmingxin on 15/4/1.
//  Copyright (c) 2015年 chenmingxin. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

//首先每次输入的是8个点，按照顺序，每两个点构成一条线段，如果能够矩形，那肯定也是四边形，四边形实际上只有四个点，那么这8个点必定要有重复的相同的点，也就是实际上是四组点，每一组两个点都是相同点
//这道题的大致思路是：从第一个点开始，设置为(x_current,y_current)，即当前需要查找的点，查找与其相同的点是否存在，如果没有直接输出NO，如果有，则将和(x_current,y_current)相同的那个点所对应的组成线段的另外一个点标记为(x_current,y_current)，然后继续循环查找，已经查找过的相同点需要标记，下次不再查找
//如果通过上面步骤找出了不同的四个点，并且是按照顺序可以连接成要构成的四边形，那再进行矩形的判断。通过对边平行且相等的定理判断是否是平行四边形，再通过判断邻边是否垂直判断是否是矩形

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    int T = 0;
    int point[8][2];
    cin >> T;
    int flag = 0;
    for(int i =0;i<T;i++){
        for(int j=0;j<8;j++){
            cin>>point[j][0];
            cin>>point[j][1];
        }
      
        flag = 0;
        
        int point_flag[8];
        memset(point_flag,0,sizeof(point_flag));
        //将第一个点设置为当前需要查找的点，标记为1，在循环查找与其相同点的时候不能再去判断它本身。
        point_flag[0] = 1;
      //  point_flag[1] = 1;
        int x_current = point[0][0],y_current = point[0][1];//记录当前需要查找的点，也就是找和这个点相同的点
        
        int reality_point[4][2];//记录实际的点，如果构成了四边形，那总共只能有4个点
        memset(reality_point,0,sizeof(reality_point));
        reality_point[0][0] = x_current;
        reality_point[0][1] = y_current;
        int real_num = 1;
        for(int m = 0;m<8;m++){
            if(!point_flag[m]){
                if(point[m][0]==x_current&&point[m][1]==y_current){
                    point_flag[m] = 1;
                    if(m%2==0){
                        x_current = point[m+1][0];
                        y_current = point[m+1][1];
                        point_flag[m+1] = 1;
                        
                    }
                    else{
                        x_current = point[m-1][0];
                        y_current = point[m-1][1];
                        point_flag[m-1] = 1;
                    }
                    if(m-1==0)
                        break;
                    real_num++;
                    if(real_num>4)
                        break;
                    reality_point[real_num-1][0] = x_current;
                    reality_point[real_num-1][1] = y_current;

                    
                    m = -1;
                    
                }
            }
            
        }
        
        //已经判断出是四边形了
        if (real_num == 4) {
            int x1 = reality_point[0][0],y1 = reality_point[0][1];
            int x2 = reality_point[1][0],y2 = reality_point[1][1];
            int x3 = reality_point[2][0],y3 = reality_point[2][1];
            int x4 = reality_point[3][0],y4 = reality_point[3][1];
            //判断对边是否平行和相等，这是判断平行四边形的基本定理
            int parallel = (y2-y1)*(x4-x3)-(y4-y3)*(x2-x1);
            int length1 = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
            int length2 = (x3-x4)*(x3-x4)+(y3-y4)*(y3-y4);
            
            //如果满足对边平行且相等则可以判断是平行四边形，那接下来就需要判断是否为矩形，通过判断邻边是否垂直来确定
            if(parallel == 0&&length1 == length2){
                int vertical = (y3-y2)*(y2-y1)+(x3-x2)*(x2-x1);
                if(vertical == 0)
                    flag = 1;
            }
        }
        
        
        if(flag == 1){
            cout<<"YES"<<endl;
        }
        else
            cout<<"NO"<<endl;
    }
        
    
    
    return 0;
}
