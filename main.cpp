#include <stdio.h>
#include <windows.h>
#include <iostream>

float position(int A,int T, int cnt);
float mul_squ(float a, int n);

int main()
{
    float pos;
    printf("Hello World\n");
    for(int i=1;i<700;i++)
    {
        pos = position(1,7,i);
        std::cout<<"i="<<i<<"  pos = "<<std::fixed<<pos<<std::endl;
    }
    system("pause");
    return 0;
}

float mul_squ(float a, int n)
{
    float res = a;
    int i = 1;
    while(i<=n)
    {
        i++;
        res = res*a;
    }
    return res;
}

float position(int A,int T, int cnt)  //将T一般设置为7的倍数
{
    //增益
    float amp =A*0.0000035543;      //将幅值转换为A°
    //float amp = 0.0000000031239;      //将幅值转换为1
    //std::cout<<"amp= "<<amp<<std::endl;
    //参数设置
    int Cnt = 100;  // 没个环节分段 
    int j = 1 ; //加加速度
    float Tp = T / 7 ; //每段速度
    float a_max = j*Cnt;   //最大加速度
    float vs = 0; //初始速度
    float pos; //位移数据
    float v1,v2,v3,v4,v5,v6,v7; // 7个阶段的节点速度
    float p1,p2,p3,p4,p5,p6,p7; // 7个阶段的节点位移
    float half = 0.5;
    float thre_half = 0.333;
    float six_half = 0.166;
    //std::cout<<"half = "<<half<<std::endl;
    //std::cout<<"thre_half = "<<thre_half<<std::endl;
    //std::cout<<"six_half = "<<six_half<<std::endl;
    //-----------S速度曲线轨迹-------------
        // 加加速段   t = [0,100)*T
        if(cnt>=0&&cnt<100)
        {
            //std::cout<<"mul_squ = "<<mul_squ(cnt,3)<<std::endl;
             pos = six_half*j*mul_squ(cnt,3);    // cnt对应轨迹
             pos = amp*pos;
            //come2position
        }
        v1 = vs + half * j * mul_squ(Cnt,2);  // 节点速度  周期T未加上 应有T1 = Cnt*Tp
        p1 = vs * Cnt + six_half * j * mul_squ(Cnt,3);   // 节点位移
        //匀加速段
        if(cnt>=100&&cnt<200)
        {
             pos = p1 + v1 * (cnt-Cnt) + half * j*Cnt* ((cnt-Cnt)^3);// cnt对应轨迹
             pos = amp*pos;
            //come2position
        }
        v2 = v1 + a_max * Cnt;// 节点速度  周期T未加上 应有T1 = Cnt*Tp 
        p2 = p1 + v1*Cnt + half*j*(Cnt^3);     // 节点位移  
        //减加速段
        if(cnt>=200&&cnt<300)
        {
             pos = p2 + v2 * (cnt-2*Cnt) + half*j*Cnt*((cnt-2*Cnt)^2)-six_half*j*((cnt-2*Cnt)^3);// cnt对应轨迹
             pos = amp*pos;
            //come2position
        }
        v3 = v2 + half* j*(Cnt^2);// 节点速度  周期T未加上 应有T1 = Cnt*Tp    
        p3 = p2 + v2*Cnt + (thre_half)*j*(Cnt^3); // 节点位移     
        // 匀速阶段
        if(cnt>=300&&cnt<400)
        {
             pos = p3 + v3 * (cnt-3*Cnt);// cnt对应轨迹
             pos = amp*pos;
            //come2position
        }
        v4 = v3;// 节点速度  周期T未加上 应有T1 = Cnt*Tp    
         p4 = p3 + v3*Cnt; // 节点位移      
        // 加减速段
        if(cnt>=400&&cnt<500)
        {
             pos = p4 + v4 * (cnt-4*Cnt) - six_half*j*((cnt-4*Cnt)^3);// cnt对应轨迹
             pos = amp*pos;
            //come2position
        }
        v5 = v4 - half* j*(Cnt^2);// 节点速度  周期T未加上 应有T1 = Cnt*Tp    
        p5 = p4 + v4*Cnt - six_half*j*(Cnt^3);// 节点位移   
        //匀减速段
        if(cnt>=500&&cnt<600)
        {
             pos = p5 + v5*(cnt-5*Cnt) - half*j*(Cnt*(cnt-5*Cnt)^2);// cnt对应轨迹
             pos = amp*pos;
            //come2position
        }
        v6 = v5 - a_max*(Cnt);// 节点速度  周期T未加上 应有T1 = Cnt*Tp    
        p6 = p5 + v5*Cnt - half*j*(Cnt^3);// 节点位移  
        // 减减速段
        if(cnt>=600&&cnt<700)
        {
             pos = p6 + v6*(cnt-6*Cnt) - half*j*(Cnt*(cnt-6*Cnt)^2) + six_half*j*((cnt-6*Cnt)^3);// cnt对应轨迹
             pos = amp*pos;
            //come2position
        }
        v7 = v6 - half*j*(Cnt^2);// 节点速度  周期T未加上 应有T1 = Cnt*Tp    
        p7 = p6 + v6*Cnt - (thre_half)*j*(Cnt^3);// 节点位移  
    
     return pos;   
}

