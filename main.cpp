// show, allItems, soldItems, addNewItem, editItem, deleteItem, searchById, searchByName, checkQuantity, addNewSale2
#include<iostream>
#include<iostream>
#include<fstream>
#include<cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
class Canteen
{
private:
    char id[20];
    char item[10];
    char status[10];
    float quantity;
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
    bool searchByName();
    bool checkQuantity();
    void addNewSale();
};
void Canteen::read_data()
{
    cout<<"\nEnter id Number: ";
    cin>>id;
    cout<<"Enter item Name: ";
    cin>>item;
    cout<<"Enter Last status(sale/sold): ";
    cin>>status;
    cout<<"Enter quantity: ";
    cin>>quantity;
    cout<<endl;
}
void Canteen::show_data()
{
    cout<<"id Number: "<<id<<endl;
    cout<<"item Name: "<<item<<endl;
    cout<<"Last status: "<<status<<endl;
    cout<<"Current quantity:"<<quantity<<endl;
    cout<<"-------------------------------"<<endl;
}
void Canteen::write_rec()
{
    ofstream outfile;
    outfile.open("record.Canteen", ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}
void Canteen::read_rec()
{
    ifstream infile;
    infile.open("record.Canteen", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this)))
        {
            show_data();
        }
    }
    infile.close();
}
void Canteen::search_rec()
{
    int n;
    ifstream infile;
    infile.open("record.Canteen", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter id Number to Search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_data();
}
void Canteen::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("record.Canteen", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" item in the file";
    cout<<"\n Enter id Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"id "<<n<<" has following data"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.Canteen", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void Canteen::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("record.Canteen", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" item in the file";
    cout<<"\n Enter id Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.Canteen", ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0; i<count; i++)
    {
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.Canteen");
    rename("tmpfile.Canteen", "record.Canteen");
}
int main()
{
    Canteen A;
    int choice;
    cout<<"***Canteen Management System***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add item";
        cout<<"\n\t2-->Show item";
        cout<<"\n\t3-->Search item by id";
        cout<<"\n\t4-->Edit item";
        cout<<"\n\t5-->Delete item";
        cout<<"\n\t6-->Sold Items";
        cout<<"\n\t7-->Search item by name";
        cout<<"\n\t8-->Check Quantity";
        cout<<"\n\t9-->Add New Sale";
        cout<<"\n\t10-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        // show, allItems, soldItems, addNewItem, editItem, deleteItem, searchById, searchByName, checkQuantity, addNewSale2
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            //A.soldItems();
            break;
        case 7:
            //A.searchByName();
            break;
        case 8:
            //A.checkQuantity();
            break;
        case 9:
            //A.addNewSale();
            break;
        case 10:
            exit(0);
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
} 