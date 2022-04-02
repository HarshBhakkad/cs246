#include <bits/stdc++.h>

using namespace std;

class Bucket
{
public:
    /* data */
    int local_depth ;
    int size;
    vector<int> data ;
    int occupancy ;

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
        vector<int>::iterator it;
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
    bool delete_(int value){
        int hashkey = hash(value);
        return (directory[hashkey]->delete_(value));
    }

    bool search(int value){
        int hv = hash(value);
       bool ans = directory[hv]->search(value);
        return ans;
    }

    void display(){
        for(int i =0 ; i < directory.size(); i++){
            cout << "Directory no:" << i << endl;
            cout << "Directory occupancy" << directory[i]->occupancy << endl;
            for(int j = 0 ; j <  directory[i]->occupancy; j++){
                cout << directory[i]->data[j] << " " ;
            }
            cout << endl;
        }
    }
};

bool hashtable::insert(int value){
    int hv = hash(value);
    int status = directory[hv]->insert(value);
    if(status == -1){
        if(directory[hv]->local_depth == global_depth){
            global_depth++;
            directory[hv]->local_depth++;
            int newhv = hash(value);
            for(int i =0 ; i < (1<<(global_depth-1)) ; i++){
                if( i == hv){
                    directory.push_back(createBucketPointer(global_depth,size));
                }
                else{
                directory.push_back(directory[i]);
                }
            }
            // hv = hash(value);
            // sorting the buckets newly formed.
            for(int i = 0 ; i < size ; i++){
               int temp= directory[hv]->data[i];
               int temphv = hash(temp);
               if(temphv != hv){
                   directory[hv]->delete_(temp);
                   directory[newhv]->insert(temp);
               }
            }
            cout << "New bucket created" << endl;
            insert(value);
            return true;
        }
        else{
            int newhv = hv + (1<<(global_depth-1));
            directory[hv]->local_depth++;
            for(int i = 0 ; i < size ; i++){
                int temp = directory[hv]->data[i];
                int temphv = hash(temp);
                if(temphv != hv){
                   directory[hv]->delete_(temp);
                   directory[newhv]->insert(temp);
               }
            }
            insert(value);
            return true;
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
            int val;
            cin >> val;
            bool ans =hash_obj.insert(val);
            cout << ans << endl;
        }
        else if (option == 3)
        {
            //search
            int val;
            cin >> val;
            bool ans = hash_obj.search(val);
            cout << ans << endl;
        }
        else if (option == 4)
        {
            //delete
            int val;
            cin >> val;

            bool ans = hash_obj.delete_(val);
            cout << ans << endl;
        }
        else if (option == 5)
        {
            //display status
            hash_obj.display();
        }
        else if (option == 6)
        {
            break;
        }  
    }
}
