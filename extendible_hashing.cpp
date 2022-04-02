#include <bits/stdc++.h>

using namespace std;

class Bucket
{
private:
    /* data */
    int local_depth ;
    int size;
    int *data = new int[size];
public:
    Bucket(int , int);
    ~Bucket();
};

Bucket::Bucket(int ld , int sz)
{
    local_depth = ld;
    size = sz;
}

Bucket::~Bucket()
{
}

class hashtable
{
private:
    /* data */
    int global_depth;
    int size;
    int occupancy = 0;
    vector<Bucket*> directory;
public:
    hashtable(int , int);
    ~hashtable();
    Bucket* createBucketPointer(int ,int);
    insert(int );
};

hashtable::insert(int value)

hashtable::hashtable(int gd , int sz)
{
    global_depth = gd;
    size = sz;
    for(int i =0 ; i < (int)pow(2,gd); i++){
        directory.push_back(createBucketPointer(gd,sz));
    }
}

hashtable::~hashtable()
{
}

Bucket* hashtable::createBucketPointer(int gd,int sz){
    Bucket* obj = new Bucket(gd,sz);
     return obj;
}




int main(){
    int global_depth ;
    int b_capacity ;
    cin >> global_depth >> b_capacity;
    hashtable hash_obj(global_depth,b_capacity);
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
