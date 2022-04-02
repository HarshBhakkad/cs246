#include <bits/stdc++.h>

using namespace std;

class Bucket
{
private:
    /* data */
    int local_depth ;
    int size;
    vector<int> data ;
    int occupancy ;
public:
    Bucket(int , int);
    ~Bucket();

    int insert(int value){
        if(occupancy < size){
            data.push_back(value);
            occupancy++;
            return 1;
        }
        else{
            return -1;
        }
    }

    bool search(int value){
        return (find(data.begin(),data.end(),value)!= data.end());
    }

    bool delete_(int value){
        vector<int>iterator:: it;
        for(auto it = data.begin();it != data.end(); ++it){
            if(*it == value){
                data.erase(it);
                return 1;
            }
        }
        return 0;
    }
};

Bucket::Bucket(int ld , int sz)
{
    local_depth = ld;
    size = sz;
    occupancy = 0;
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
    int hash(int value){
        int ans;
        ans = (value & ((1<<global_depth)-1));
    }
    ~hashtable();
    Bucket* createBucketPointer(int ,int);
    bool insert(int );
};

bool hashtable::insert(int value){
    int hv = hash(value);
    int status = directory[hv]->insert(value);
    if(status == -1){
        if(directory[hv]->local_depth == global_depth){
            global_depth++;
            int newhv = hash(value);
            for(int i =0 ; i < (1<<global_depth) ; i++){
                if( i == hv){
                    directory.push_back(createBucketPointer(global_depth,size));
                }
                else{
                directory.push_back(createBucketPointer(global_depth-1,size));
                }
            }
            // hv = hash(value);
            
            for(int i = 0 ; i < size ; i++){
               int temp= directory[hv]->data[i];
               int temphv = hash(temp);
               if(temphv != hv){
                   directory[hv]->delete_(temp);
                   directory[newhv]->insert(temp);
               }
            }
        }
        else{

        }
    }
    else{
        return true;
    }
}

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
