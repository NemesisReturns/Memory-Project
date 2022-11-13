#include <bits/stdc++.h>
using namespace std;
#define ll long long
const long long N = 1e5+10;
const ll mod = 1e9 +7;
# define pb push_back
int main() {
    long long mem_size, cache_size, k;
    cin >> mem_size >> cache_size >> k;
    cache_size /= k;
    long long mem[mem_size];
    for (long long i = 0; i < mem_size; ++i) {
        mem[i] = -1;
    }
    long long hit_count=0;
    bitset<32> output;
    bool hit=0;
    vector<long long> LRU[k];
    pair<long long, long long> cache[k][cache_size];
    for (long long i = 0; i < k; ++i) {
        for (long long j = 0; j < cache_size; ++j) {
            cache[i][j].first = -1;
        }
    }
    long long t;
    cin >> t;
    long long test_case = t;
    while(t--){
        long long rw, b, c;
        rw = 0; c=0;
        cin >> b;
        long long data = c;
        long long mem_address = b;
        long long set_bit = ceil(log2(k));
        //cout<<set_bit<<endl;
        bitset<32> b1 = b;
        string temp = b1.to_string();
        string set1 = temp.substr(32-set_bit, set_bit);
        long long set = stoi(set1, 0, 2);
        string tag1 = temp.substr(0, 32-set_bit);
        long long tag = stoi(tag1, 0, 2);
        // cout<<b1<<endl;
        // cout<<set<<endl;
        // cout<<tag<<endl;
        if (rw == 0) {
            long long temp = 0;
            for (long long i = 0; i < cache_size; ++i) {
                hit = 0;
               // cout << "    BABB    " << i << endl;
                if (cache[set][i].first == mem_address) {
                    //cout << "    BABB    " << i << endl;
                    hit_count++;
                    hit = 1;
                    for (long long j = 0; j < LRU[set].size(); ++j)
                    {
                        if(LRU[set][j]==mem_address)
                            temp=j;
                    }
                    //cout << "    TTTT   " << temp << endl;
                    output = cache[set][i].second;
                    for (long long j = temp; j < LRU[set].size()-1; ++j) {
                        LRU[set][j] = LRU[set][j + 1];
                    }
                    LRU[set][LRU[set].size()-1] = mem_address;
                    break;
                }
            }
            if (hit == 0) {
                long long a = 0;
                //output = mem[mem_address];
                for (long long i = 0; i < cache_size; ++i) {
                    if (cache[set][i].first == -1) {
                        a = 1;
                        cache[set][i].first = mem_address;
                        //cache[set][i].second = output.to_ulong();
                        LRU[set].push_back(mem_address);
                        break;
                    }
                }
                if (a == 0) {
                    for (long long i = 0; i < cache_size; ++i) {
                        if (cache[set][i].first == LRU[set][0]) {
                            mem[LRU[set][0]] = cache[set][i].second;
                            cache[set][i].first = mem_address;
                            //cache[set][i].second = output.to_ulong();
                        }
                    }
                    for (long long i = 0; i < cache_size-1; ++i) {
                        LRU[set][i] = LRU[set][i + 1];
                    }
                    LRU[set][cache_size-1] = mem_address;
                }
            }
            //cout << "Output: "<<  output << endl;
        }
        else {
            for (long long i = 0; i < cache_size; ++i) {
                hit = 0;
                long long temp = 0;
                if (cache[set][i].first == mem_address) {
                    hit_count++;
                    hit = 1;
                    cache[set][i].second = data;
                    for (long long j = 0; j < LRU[set].size(); ++j)
                    {
                        if(LRU[set][j]==mem_address)
                            temp=j;
                    }
                    //cout << "    TTTT   " << temp << endl;
                    //output = cache[set][i].second;
                    for (long long j = temp; j < LRU[set].size()-1; ++j) {
                        LRU[set][j] = LRU[set][j + 1];
                    }
                    LRU[set][LRU[set].size()-1] = mem_address;
                    break;
                }
            }
            if (hit == 0) {
                long long a = 0;
                // for (long long i = 0; i < k; ++i)
                // {
                //     for (long long j = 0; j < cache_size; ++j)
                //     {
                //         cout<<cache[i][j].first<<endl;
                //     }
                // }
                for (long long i = 0; i < cache_size; ++i) {
                    if (cache[set][i].first == -1) {
                        //cout<<"BB"<<endl;
                        a = 1;
                        cache[set][i].first = mem_address;
                        //cache[set][i].second = data;
                        LRU[set].push_back(mem_address);
                        break;
                    }
                }
                if (a == 0) {
                    for (long long i = 0; i < cache_size; ++i) {
                        if (cache[set][i].first == LRU[set][0]) {
                            mem[LRU[set][0]]=cache[set][i].second;
                            cache[set][i].first = mem_address;
                            //cache[set][i].second = data;
                        }
                    }
                    for (long long i = 0; i < cache_size-1; ++i) {
                        LRU[set][i] = LRU[set][i + 1];
                    }
                    LRU[set][cache_size-1] = mem_address;
                }
            }
        }
        // cout << "LRU: " << endl;
        // for (long long i = 0; i < k; ++i) {
        //     cout << "Set" << i << ":  ";
        //     for (long long j = 0; j < LRU[i].size(); ++j) {
        //         cout << LRU[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    // cout << endl;
    // cout << "Cache memory: " << endl;
    // for (long long i = 0; i < k; ++i) {
    //     cout << "Set" << i << ":  ";
    //     for (long long j = 0; j < cache_size; ++j) {
    //         if(cache[i][j].first != -1){
    //             cout << cache[i][j].first << " ";
    //         }
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    cout << "HIT COUNT:  " << hit_count << endl;
    cout << "HIT RATE:   " << (hit_count*100.0)/test_case << endl;
    for (long long i = 0; i < mem_size; ++i)
    {
        if(mem[i]!=-1)
            cout << "Mem: " << i << " -- " << mem[i] << endl;
    }
}