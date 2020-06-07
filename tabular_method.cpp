#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
class PI{
public:
    unsigned int number;
    vector<unsigned int> index;
    char chars[4] = {'0','0','0','0'};
    int num_of_ones;
    bool checked = false;
    PI(unsigned int data  = 0 ){
        number = data;
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
        cout << "chars = "<< chars[3] <<chars[2]<<chars[1]<<chars[0] <<endl;
    }
    bool hd_dis(const PI &other) const
    {
        int distance = 0;
        for(int i =0; i<4;i++){
            if(chars[i] == other.chars[i])
                continue;
            else
                distance ++;
        }
        return distance == 1;
    }
    bool equal(const PI &other) const
    {
        bool result = true;
        for(int i =0; i<4;i++){
            if(chars[i] == other.chars[i])
                continue;
            else
                return false;
        }
        return result;
    }
};
PI plus_pi(PI& a, PI&b);
void sizeup_pi(vector<PI> &pis, vector<PI> &pi);
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

    vector<PI> pi;
    bool next = false;
    for(int i=0;i<pis.size()-1;i++)
    {
        for(int j =i+1;j<pis.size();j++){
            if(pis.at(i).hd_dis(pis.at(j))){
                next = true;
                break;
            }
        }
    }
    while(pis.size() > 2){
        sizeup_pi(pis,pi);
    }
    for( int i =0; i<pi.size()-1;i++){
        bool exed = false;
        for(int j =i+1;j<pi.size();j++){
            if(pi.at(i).equal(pi.at(j))){
                pi.erase(pi.begin()+j);
                j --;
                exed = true;
            }
        }
        if(exed)
            i--;
    }
    for(int i = 0; i<pis.size();i++)
    {
        pis.at(i).view();
    }
    for(int i = 0; i<pi.size();i++)
    {
        pi.at(i).view();
    }


    return 0;
}
PI plus_pi(PI& a, PI&b){
    PI result = PI();
    result.index.clear();
    for(int i =0; i<a.index.size();i++){
        result.index.push_back(a.index.at(i));
    }
    for(int i =0; i<b.index.size();i++){
        result.index.push_back(b.index.at(i));
    }
    for(int i =0;i<4;i++){
        if(a.chars[i] != b.chars[i]){
            result.chars[i] = '-';
        }
        else
            result.chars[i] = a.chars[i];
    }
    return result;
}
void sizeup_pi(vector<PI> &pis, vector<PI> &pi){
    vector<PI> nextstep;
    vector<PI> answer;
    for(int i=0;i<pis.size()-1;i++)
    {
        for(int j =i+1;j<pis.size();j++){
            if(pis.at(i).hd_dis(pis.at(j))){
                pis.at(i).checked = true;
                pis.at(j).checked = true;
                pi.push_back(plus_pi(pis.at(i),pis.at(j)));
            }
        }
    }
    for(int k=0;k<pis.size();k++){
        if(pis.at(k).checked){
            pis.erase(pis.begin()+k);
            k--;
        }
    }
    pis.swap(pi);
}
