#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <random>

#define INNODE 2 // number of inputs(in_features)
#define HIDDENNODE 4 // 
#define OUTNODE 1

double learningRate = 0.01;   // 学习率
double threshold = 1e-4;   //
double eposides = 100;


struct sample{
    std::vector<double> in, out;   // 输入 输出 都是double类型变量
};

struct node {
    double value{}, bias{}, bias_delta{};
    std::vector<double> weight, weight_delta;
};

namespace utils{
    inline double sigmoid(double x){
        double res = 1.0 / (1.0+std::exp(-x));
        return res;
    }
    std::vector<double> getFileData(std::string filename){
        std::vector <double> res;
        std::ifstream in(filename);
        if(in.is_open()){
            while(in.eof()){   // eof 文件结尾
                double buffer;  //临时变量
                in >>  buffer;
                res.push_back(buffer);
            }
            in.close();
        } else{
            std::cout<<"error in reading file\n";
        }
        return res;
    }

    std::vector<sample> getTrainData(std::string filename){
        // 把每一行数据，训练集包含input outout
        std::vector<sample> res;
        std::vector<double> buffer = getFileData(filename);
        for(size_t i=0; i<buffer.size(); i+= INNODE+OUTNODE){   //buffer[i]是第i行第一个数值
            sample tmp;  // 临时变量
            for(size_t t=0; t<INNODE; t++){
                tmp.in.push_back(buffer[i+t]);   //第i行前INNODE个数值输入sample.in
            } 
            for(size_t t=INNODE; t<INNODE+OUTNODE; t++){
                tmp.out.push_back(buffer[i+t]); 
            }
            res.push_back(tmp);
        }
        return res;
    }

    std::vector<sample> getTestData(std::string filename){
        // 测试集只有输入没有输出 只有input
        std::vector<sample> res;
        std::vector<double> buffer = getFileData(filename);
        for(size_t i=0; i<buffer.size(); i+=INNODE){
            sample tmp;
            for(size_t t=0; t<INNODE; t++){
                tmp.in.push_back(buffer[i+t]);
            }
        }
    }
}


node *inputLayer[INNODE], *hiddenLayer[HIDDENNODE], *outLayer[OUTNODE];
inline void init(){
    // 网络初始化
    std::mt19937 rd;
    rd.seed(std::random_device()());   //设定随机数种子
    std::uniform_real_distribution<double> distribution(-1,1);
    
    // 初始化输入层到隐藏层
    for(size_t i=0; i<INNODE ; i++){    //input layer 一共INNODE个节点，每个节点HIDDENNODE个权重
        ::inputLayer[i] = new node();
        for(size_t j=0; j<HIDDENNODE ; j++){
            ::inputLayer[i]->weight.push_back(distribution(rd));
            ::inputLayer[i]->weight_delta.push_back(0.f);
        }
    }
    // 初始化隐藏层到输出层
    for(size_t i=0; i<HIDDENNODE ; i++){
        ::hiddenLayer[i] = new node();
        ::hiddenLayer[i]->bias = distribution(rd);
        ::hiddenLayer[i]->bias_delta = 0.f;

        for(size_t j=0; j<OUTNODE; j++){
            ::hiddenLayer[i]->weight.push_back(distribution(rd));
            ::hiddenLayer[i]->weight_delta.push_back(0.f);
        }
    }
    // 初始化输出层bias
    for(size_t i=0; i<OUTNODE; i++){
        ::outLayer[i] = new node();
        ::outLayer[i]->bias = distribution(rd);
        ::outLayer[i]->bias_delta = 0.f;
    }
}


inline void resetDelta(){
    for(size_t i=0; i<INNODE; i++){
        
    }
}

int main(){

    using namespace std;
    cout << "hello world" <<endl;
    return 0;
}