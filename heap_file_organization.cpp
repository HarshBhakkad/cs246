#include <bits/stdc++.h>

using namespace std;

class page
{
public:
    int pg_no;
    int size_;
    page(int,int);
    int rm_sz;
    int data[100][2];
    int no_of_elements;
    int search(int);
    ~page();
    bool insert(int,int);
};

page::page(int a,int sz)
{
    pg_no = a;
    size_ = sz;
    rm_sz = sz-16;
    no_of_elements = 0;
}

int page::search(int value){
    for(int i = 0;i<no_of_elements;i++){
        if(data[i][0] == value){
            return i;
        }
    }
    
        return -1;
}

bool page::insert(int value,int sz){
    if(rm_sz >= (sz + 4)){
        data[no_of_elements][0] = value;
        data[no_of_elements][1] = sz;
        rm_sz-=(sz+4);

        no_of_elements++;
        return true;

    }
    else{
        return false;
    }
}

page::~page()
{
}


class book
{
public:
    int size_;
    int no_of_pages;
    bool insert(int ,int);
    vector<page*> pgs;
    book(int);
    bool search(int);
    void display();
    ~book();
};

book::book(int sz)
{
    size_ = sz;
    no_of_pages = 0;
}

void book::display(){
    cout << no_of_pages;
    for(int i =0 ; i < no_of_pages;i++){
        cout << " "<<pgs[i]->no_of_elements;
    }
    cout << endl;
}

bool book::search(int value){
    for(int i=0;i<no_of_pages;i++){
        int check = pgs[i]->search(value);
        if(check != -1){
            cout << i << " " << check << endl ;


            return true;
        }
    }
    cout << -1 << " " << -1 << endl;
}

bool book::insert(int value,int sz){
    int flag = 0;
    for(int i =0 ; i < no_of_pages;i++){
        if(pgs[i]->insert(value,sz)){
            flag = 1;
            break;
        }
    }
    if(flag == 0){
        page* obj = new page(no_of_pages,size_);
        no_of_pages++;
        pgs.push_back(obj);
        pgs[no_of_pages-1]->insert(value,sz);
    }
}

book::~book()
{
}


int main(){
    int size ; 
    cin >> size ; 
    book* obj = new book(size);
    while (true)
    {
        int flag = 0;
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
            int b , c;
            cin >> b >> c;
            obj->insert(c,b);
            break;
        case 3:
            int d;
            cin >> d;
            obj->search(d);
        break;
        case 2:
            obj->display();
        break;
        
        default:
        flag = 1;
            break;
        }
        if(flag){
            break;
        }
    }
    


}