#include <bits/stdc++.h>

using namespace std;

class Bucket
{
private:
    int local_depth;
    int size;
    int* data = new int(size); 
public:
    Bucket
(int ,int);
    ~Bucket
();
};

Bucket::Bucket(int ld , int sz)
{
    local_depth = ld;
    size = sz;
}

Bucket::~Bucket()
{
}


class Hash_Table
{
private:
    int global_depth;
    int b_capacity;
    vector<Bucket> bcks;
public:
    Hash_Table(int,int);
    ~Hash_Table();
    insert(int);
    Bucket create_bucket_obj();
};

Hash_Table::Hash_Table(int gd , int buck_cap)
{ 
    global_depth = gd;
    b_capacity = buck_cap;
    for(int i =0 ; i < (int)pow(2,gd) ; i++){
        bcks.push_back(create_bucket_obj());
    }
}

Hash_Table::~Hash_Table()
{
}

Hash_Table::insert(int val){
    
}

Bucket Hash_Table::create_bucket_obj(){
    Bucket* obj = new Bucket(global_depth,b_capacity);
    return *obj;
}


int main(){
    int global_depth ;
    int b_capacity ;
    cin >> global_depth >> b_capacity;
    Hash_Table hash_obj(global_depth,b_capacity);
    while (true){
        int option ;
        cin >> option;
        if(option == 2){
            //insert
        }
        else if (option == 3)
        {
            //search
        }
        else if (option == 4)
        {
            //delete
        }
        else if (option == 5)
        {
            //display status
        }
        else if (option == 6)
        {
            break;
        }  
    }
}