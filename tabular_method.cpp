#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
class PI{
public:
    vector<unsigned int> index;
    char chars[4] = {'0','0','0','0'};
    bool checked = false;
    PI(unsigned int data  = 0 ){
        index.push_back(data);
        unsigned int bitmask = 1;
        for(int i =0;i<4;i++)
        {
            if(data & bitmask)
            {
                chars[i] = '1';
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
void erase_same(vector<PI> &pi);
int main()
{
    unsigned int data, num_of_data;
    cin >> num_of_data;
    vector<unsigned int> datas;
    vector<unsigned int> dont_cares;
    vector<PI> pis;

    for(int i =0; i<num_of_data;i++){
        cin >> data;
        datas.push_back(data);
    }

    int number_of_dc;
    cin >> number_of_dc;
    for( int i=0;i<number_of_dc;i++){
        cin >> data;
        datas.push_back(data);
        dont_cares.push_back(data);
    }

    sort(datas.begin(), datas.end());
    // end data input and sort

    for(int i = 0; i<datas.size();i++)
    {
        pis.push_back(PI(datas.at(i)));
    }//make pi

    vector<PI> pi;
    while(pis.size() > 2){
        sizeup_pi(pis,pi);
    }
    while(!pis.empty()){
        pi.push_back(pis.back());
        pis.pop_back();
    }
    erase_same(pi);

    vector<PI> epis;
    int row = datas.size();
    int column = pi.size();
    bool *checked_data = new bool[datas.size()];
    bool *epi = new bool[pi.size()];

    int **table = new int *[column];
    for(int i =0; i < column; i++){
        table[i] = new int[row];
    }
    for(int i=0;i<datas.size();i++){
        if(find(dont_cares.begin(), dont_cares.end(), datas.at(i)) != dont_cares.end()){
            checked_data[i] = true;
        }
        else{
            checked_data[i] = false;
        }
    }

    cout <<"     ";
    for(int i=0;i<datas.size();i++){
        if(datas.at(i) > 9){
            cout<< datas.at(i) << " ";
        }
        else
            cout << datas.at(i) <<"  ";
    }
    cout <<endl;


    for(int i = 0; i<pi.size();i++)
    {
        cout <<"p"<<i+1<<"   ";
        for(int j =0;j<datas.size();j++){
            if(find(pi.at(i).index.begin(), pi.at(i).index.end(), datas.at(j)) != pi.at(i).index.end()){
                table[i][j] = 1;
                cout<< 1 << "  ";
            }
            else{
                table[i][j] = 0;
                cout << 0 << "  ";
            }
        }
        cout<<endl;
    }
    for(int i =0; i<row;i++){
        int count = 0;
        if(checked_data[i])
            break;
        for (int j=0;j<column;j++){
            count += table[j][i];
        }
        if(count == 1){
            for(int j=0; j<column;j++){
                if(table[j][i] == 1){
                    epis.push_back(pi.at(j));
                    for(int k=0;k<row;k++){
                        if(table[j][k] == 1)
                            checked_data[k] = true;
                    }
                }
            }
        }
    }


    cout <<"epi" <<endl;
    for(int i=0;i<epis.size();i++){
        epis.at(i).view();
    }
    for(int i=0; i<pi.size();i++){
        if(pi.at(i).checked)
            continue;
        cout << "p"<< i<<" ";
        for(int j=0; j<datas.size();j++){
            if(checked_data[j])
                cout << "-"<<" ";
            else
                cout <<table[i][j]<<" ";
        }
        cout<<endl;
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
void erase_same(vector<PI> &pi){
    for( int i =0; i<pi.size()-1;i++){
        for(int j =i+1;j<pi.size();j++){
            if(pi.at(i).equal(pi.at(j))){
                pi.erase(pi.begin()+j);
                j --;
            }
        }
    }
}
/*void row_dominance(vector<PI> pi, bool **table, bool*checked_data,int row, int column){
    for(int i=0;i<row-1;i++){
        for(int j=i+1;j<row;j++){
            if()
        }
    }
}*/
