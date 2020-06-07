#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
class PI{
public:
    vector<unsigned int> index;
    char chars[4] = {'0','0','0','0'};
    int num_of_ones;
    PI(unsigned data){
        index.push_back(data);
        unsigned int bitmask = 1;
        num_of_ones = 0;
        for(int i =0;i<4;i++)
        {
            if(data & bitmask)
            {
                chars[i] = '1';
                num_of_ones ++;
            }
            else{
                chars[i] = '0';
            }
            bitmask <<=1;

        }
    }
    void view(){
        cout << "index = ";
        for(int i = 0; i<index.size();i++)
        {
            cout << index.at(i) << " ";
        }
        cout << endl;
        cout << " n_of 1 = "<< num_of_ones <<endl;
        cout << "chars = "<< chars[3] <<chars[2]<<chars[1]<<chars[0] <<endl;
    }
};
int main()
{
    unsigned int data, num_of_data;
    cin >> num_of_data;
    vector<unsigned int> datas;
    vector<PI> pis;
    for(int i =0; i<num_of_data;i++){
        cin >> data;
        datas.push_back(data);
    }
    sort(datas.begin(), datas.end());

    for(int i = 0; i<datas.size();i++)
    {
        pis.push_back(PI(datas.at(i)));
    }
    for(int i = 0; i<pis.size();i++)
    {
        pis.at(i).view();
    }
    return 0;
}
