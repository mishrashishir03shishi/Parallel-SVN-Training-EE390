#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
#include <string.h>
#include <sys/time.h>


using namespace std;

double getHingeloss(double &x1, double &x2, double &y, double &w1, double &w2, double &b){
    double loss = 0;
    if (y==1){
        loss = 1-(w1*x1 +w2*x2+b);
    }
    else{
        loss = 1+(w1*x1 + w2*x2 +b);
    }
    if(loss < 0){
        loss = 0;
    }
    return loss;
}

double getSVMcost(vector<double> &x1, vector<double> &x2, vector<double> &y, double w1, double w2, double b, double &dw1, double &dw2, double &db){
    int n = static_cast<int>(y.size());
    double cost = 0;
    dw1 = 0; dw2 = 0; db = 0;
    for(int i=0; i<n; i++){
        double loss = getHingeloss(x1[i], x2[i], y[i], w1, w2, b);
        cost += loss;
        if(loss>0){
            dw1 += (-x1[i]*y[i]);
            dw2 += (-x2[i]*y[i]);
            db += (-y[i]);
        }
    }
    cost /= n; dw1 /= n; dw2 /= n; db /= n;
    return cost;
}


void trainSVM(vector<double> &x1, vector<double> &x2, vector<double> &y){
    double lrate = 0.0005, threshold = 0.001, w1 = 1, w2 = 1, b = 0, dw1 = 0, dw2 = 0, db = 0;
    int iter = 0;

    while(true){
        double cost = getSVMcost(x1,x2,y,w1,w2,b,dw1,dw2,db);
        if(iter%1000==0){
            std::cout<<"Iter: "<<iter<<" cost: "<<cost<<" dw1 = "<<dw1<<" dw2 = "<<dw2<<" db = "<<db<<endl;
        }
        iter++;
        if(abs(dw1)<threshold && abs(dw2)<threshold && abs(db)<threshold){
            std::cout<<"y = "<<w1<<"*x1 + "<<w2<<"*x2 + "<<b<<endl;
            return;
        }
        w1 -= lrate*dw1;
        w2 -= lrate*dw2;
        b -= lrate*db;
    }
}

int main(){
    struct timeval tv1, tv2;
    struct timezone tz, tz1;
    vector<double> x1;
    vector<double> x2;
    for(int i=0; i<1000; i++){
      x1.push_back(rand()%100);
    }
    for(int i=0; i<1000; i++){
      x2.push_back(rand()%100);
    }
    vector<double> y(1000,-1);
    gettimeofday(&tv1, &tz);
    trainSVM(x1, x2, y);
    gettimeofday(&tv2, &tz1);
    double elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Time elapsed to sequentially train a SVM is = %f seconds.\n", elapsed);

    return 0;
}
