class page
{
public:
    int pg_no;
    int size_;
    page(int,int);
    int rm_sz;
    int data[100][2];
    int no_of_elements;
    bool search(int);
    ~page();
    bool insert(int);
};

page::page(int a,int sz)
{
    pg_no = a;
    size_ = sz;
    rm_sz = sz-16;
    no_of_elements = 0;
}

bool page::search(int value){
    for(int i = 0;i<no_of_elements;i++){
        if(data[no_of_elements][0] == value){
            return true;
        }
    }
    else{
        return false;
    }
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
    ~book();
};

book::book(int sz)
{
    size_ = sz;
    no_of_pages = 0;
}

bool book::insert(int value,int sz){
    int flag = 0;
    for(int i =0 ; i < no_of_pages;i++){
        if(pgs[i]->insert(value,sz)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        page* obj = new page(no_of_pages,size_);
        no_of_pages++;
        pgs.pushback(obj);
    }
}

book::~book()
{
}


int main(){

}