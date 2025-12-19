//Group 03
//Title: Book Store system

//1211207735 See Chwan Kai
//1211208688 Tee Kian Hao
//1211211485 Kho Wei Cong
//1211208756 Tee Chin Yean

#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<stdlib.h>//using with system("CLS") to clear screen
#include<sstream>//reading the quote we have store in txt file
#include<thread>//sleep_for
#include<vector>//use to preprocessor directive
#include<chrono>//use for time
#include<ctime>//use for time

using namespace std;

//function prototype
void c_menu(string username);

struct product{
    //using while reading the data we have store in books.txt file
    string book_name, book_description, book_author;
    float price, cost;
    int stock, id, sold_stock=0;
};//end of struct product

struct customer{
    //using while reading the data we have store in customers.txt file
    string name;
    string password;
    string cfn, cln, cun, cpw, cpn, cadd;
};//end of struct customer

struct order{
    //using while reading the data we have store in orders.txt file
    int order_id=2000, order_bookid,order_bookquantity;
    float order_bookprice;
    string order_username;
};//end of struct order

struct sales{
    //using while reading the data we have store in sales.txt file
    int sales_id, quantity;
    float sales_costtotal=0, sales_total=0;
    string sales_username, sales_status;
};//end of struct sales

struct Book {
    //using while reading the data we have store in books.txt file
    int bookid;
    string title;
    string author;
    double cost;
    double price;
    string description;
    int stock;
    int sold_stock;
};//end of struct Book

class functionAdmin{
private:
    product p;
    customer c;
    order o;
    sales s;

public:
    void addbook(){
        char choice;

        do{
            int auto_id = 1000;
            //open file
            ifstream readbook("books.txt");
            ofstream addbook("books.txt", ios::app);

            if(readbook.is_open()){
                string line;

                //count the existing records in the txt file
                while(getline(readbook, line)){
                    auto_id++;
                }//end of while
            }//end of if

            //ask for book's information
            system("CLS");
            cout<<"\n-------------------------------------"<<endl;
            cout<<"\t\tADD NEW BOOK"<<endl;
            cout<<"-------------------------------------"<<endl;
            cout<<"Enter book's title : ";
            fflush(stdin);
            getline(cin,p.book_name);
            cout<<"Enter book's author : ";
            fflush(stdin);
            getline(cin,p.book_author);
            cout<<"Enter book's cost price : ";
            cin>>p.cost;
            cout<<"Enter book's sell price : ";
            cin>>p.price;
            cout<<"Enter book's description : ";
            fflush(stdin);
            getline(cin,p.book_description);
            cout<<"Enter book's stock : ";
            cin>>p.stock;

            //write into file
            if(addbook.is_open()){
                addbook<<(auto_id+1)<<" \""<<p.book_name<<"\" \""<<p.book_author<<"\" "<<p.cost<<" "<<p.price<<" \""<<p.book_description<<"\" "<<p.stock<<" "<<p.sold_stock<<endl;
            }

            //display successful message
            system("CLS");
            cout<<endl<<"--------------------------------"<<endl;
            cout<<"Book added successfully."<<endl;
            cout<<"--------------------------------"<<endl;
            cout<<"Book ID : "<<(auto_id+1)<<endl;
            cout<<"Book Name : "<<p.book_name<<endl;
            cout<<"Book Author : "<<p.book_author<<endl;
            cout<<"Book Cost Price : "<<p.cost<<endl;
            cout<<"Book Sell Price : "<<p.price<<endl;
            cout<<"Book Description : "<<p.book_description<<endl;
            cout<<"Book Available Stock : "<<p.stock<<endl;

            //close file
            addbook.close();
            readbook.close();

            //ask user if they want to add another book
            cout<<endl<<"Do you want to add another book? [Y/N] : ";
            cin>>choice;

        }while(choice=='Y' || choice == 'y');
        system("CLS");
    }//end of addbook

    void displayBook(){
        string line;
        int sold_book;

        //open file
        ifstream readbook("books.txt");

        system("CLS");

        //display all book
        cout<<endl<<"--------------------------------"<<endl;
        cout<<"\tBook Details"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<setw(10)<<"Book ID#"<<setw(20)<<"Book Name"<<setw(20)<<"Author"<<setw(15)<<"Cost Price"<<setw(15)<<"Sell Price"<<setw(25)<<"Description"<<setw(15)<<"Stock"<<setw(15)<<"Sold"<<endl;

        while(getline(readbook,line)){
            istringstream iss(line);

            //extraction values from the line
            if(!(iss >> p.id >> quoted(p.book_name) >> quoted(p.book_author) >> p.cost >> p.price >> quoted(p.book_description) >> p.stock >> sold_book)){
                cerr<<"Error parsing line : " <<line<<endl;
                continue;
            }

            //DIsplay result
            cout<<setw(10)<<p.id<<setw(20)<<p.book_name<<setw(20)<<p.book_author<<setw(15)<<fixed<<setprecision(2)<<p.cost<<setw(15)<<fixed<<setprecision(2)<<p.price<<setw(25)<<p.book_description<<setw(15)<<p.stock<<setw(15)<<sold_book<<endl;
        }
        readbook.close();
        cout<<endl;
    }//end of displayBook

    void deleteBook(){
        int *delete_id=new int;
        string line;
        char choice = 'n';

        do{
            bool found=false;

            //open file
            ifstream readbook("books.txt");
            ofstream temp("temp.txt");
            ofstream deletebook("delete_logs.txt",ios::app);

            //display all book
            displayBook();

            //ask for book id
            cout<<"Enter book ID that you wished to delete : ";
            cin>>*delete_id;

            //search if book id exist in book.txt
            while(getline(readbook, line)){
                istringstream iss(line);

                //Extracting values from the line
                if(!(iss>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock)){
                    cerr<<"Error parsing line : "<<line<<endl;
                    continue;
                }

                //write into temp file
                if(temp.is_open() && p.id!=*delete_id){
                    temp<<p.id<<" \""<<p.book_name<<"\" \""<<p.book_author<<"\" "<<p.cost<<" "<<p.price<<" \""<<p.book_description<<"\" "<<p.stock<<" "<<p.sold_stock<<endl;
                }
                else if(deletebook.is_open() && p.id==*delete_id){
                    deletebook<<p.id<<" \""<<p.book_name<<"\" \""<<p.book_author<<"\" "<<p.cost<<" "<<p.price<<" \""<<p.book_description<<"\" "<<p.stock<<" "<<p.sold_stock<<endl;
                    found=true;
                }
        }

            //close file
            temp.close();
            readbook.close();
            deletebook.close();

            //delete book.txt and rename temp.txt to book.txt
            remove("books.txt");
            rename("temp.txt", "books.txt");

            if(found==false){
                cout<<"Book not found, please try again..."<<endl;
                return;
            }
            else{
                system("CLS");
                //display successful message
                cout<<endl<<"--------------------------------"<<endl;
                cout<<"Book deleted successfully."<<endl;
                cout<<"--------------------------------"<<endl;

                //display deleted book
                cout<<"\nDo you want to delete another book? [Y/N] : ";
                cin>>choice;

            }
        }while(choice=='Y' || choice=='y');

        //delete dynamic memory
        delete delete_id;
    }//end of deleteBook

    void updatebook(){
        int *update_id=new int;
        int update_stock;
        float update_price, update_cost;
        string update_name, update_author, update_description, line;
        char choice;

        do{
            bool found=false;

            //open file
            ifstream readbook("books.txt");
            ofstream temp("temp.txt");
            ofstream updatebook("update_logs.txt", ios::app);

            //display all book
            displayBook();

            //ask for book id
            cout<<"Enter book ID that you wished to update : ";
            cin>>*update_id;

            //search if book id exist in book.txt
            while(getline(readbook, line)){
                istringstream iss(line);

                //Extracting if book id exist in book.txt
                if(!(iss>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock)){
                    cerr<<"Error parsing line : "<<line<<endl;
                    continue;
                }

                //write into file
                if(temp.is_open() && p.id!=*update_id){
                    temp<<p.id<<" \""<<p.book_name<<"\" \""<<p.book_author<<"\" "<<p.cost<<" "<<p.price<<" \""<<p.book_description<<"\" "<<p.stock<<" "<<p.sold_stock<<endl;
                }
                else if(p.id==*update_id){
                    updatebook<<p.id<<" \""<<p.book_name<<"\" \""<<p.book_author<<"\" "<<p.cost<<" "<<p.price<<" \""<<p.book_description<<"\" "<<p.stock<<" "<<p.sold_stock<<endl;
                    found=true;

                    //ask for book's information
                    cout<<"Enter book's new title : ";
                    fflush(stdin);
                    getline(cin, update_name);
                    cout<<"Enter book's new author : ";
                    fflush(stdin);
                    getline(cin, update_author);
                    cout<<"Enter book's new cost price : ";
                    cin>>update_cost;
                    cout<<"Enter book's new sale price : ";
                    cin>>update_price;
                    cout<<"Enter book's new description : ";
                    fflush(stdin);
                    getline(cin, update_description);
                    cout<<"Enter book's new stock : ";
                    cin>>update_stock;

                    //write into file
                    if(temp.is_open()){
                        temp<<p.id<<" \""<<update_name<<"\" \""<<update_author<<"\" "<<update_cost<<" "<<update_price<<" \""<<update_description<<"\" "<<update_stock<<" "<<p.sold_stock<<endl;
                    }
                    //display successful message
                    system("CLS");
                    cout<<endl<<"--------------------------------"<<endl;
                    cout<<"Book updated successfully."<<endl;
                    cout<<"--------------------------------"<<endl;
                    cout<<"Book ID : "<<p.id<<endl;
                    cout<<"Book Name : "<<update_name<<endl;
                    cout<<"Book Author : "<<update_author<<endl;
                    cout<<"Book Cost Price : "<<update_cost<<endl;
                    cout<<"Book Sell Price : "<<update_price<<endl;
                    cout<<"Book Description : "<<update_description<<endl;
                    cout<<"Book Available Stock : "<<update_stock<<endl;
                }
            }

            //close file
            temp.close();
            readbook.close();
            updatebook.close();

            //delete book.txt and rename temp.txt to book.txt
            remove("books.txt");
            rename("temp.txt","books.txt");

            if(found==false){
                //display error message
                cout<<"Book not found, please try again..."<<endl;
                return;
            }
            else{
                //ask user if they want to update another book
                cout<<"\nDo you want to update another book? [Y/N] : ";
                cin>>choice;

            }

            //delete dynamic memory
            delete update_id;

        }while(choice=='Y' || choice == 'y');
    }//end of updatebook

    void displayOrder(){
        string status, name;
        float total;
        int quantity, bookid, orderid, list_num;
        bool found = false;

        //open file
        ifstream pd("books.txt");
        ifstream sales("sales.txt");

        system("CLS");
        //display all order
        cout<<"\n-------------------------------------"<<endl;
        cout<<"\tTRANSACTION HISTORY"<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<setw(8)<<"Order ID"<<setw(10)<<"Order By"<<setw(10)<<"Total"<<setw(15)<<"Status"<<endl;

        //read from orders.txt and sales.txt
        //compare if order,txt order_id=sales.txt order_id
        //if yes, display the record
        while(sales>>p.id>>quoted(name)>>p.cost>>total>>quoted(status)){
            cout<<setw(8)<<p.id<<setw(10)<<name<<setw(10)<<fixed<<setprecision(2)<<total<<setw(15)<<status<<endl;
            found=true;
        }

        sales.clear();//clear any error flags
        sales.seekg(0, ios::beg);//move to the beginning of the file

        if(found==false){
            cout<<"No transaction history found."<<endl;
        }
        else{
            cout<<"\n[1] Check details of the order."<<endl;
            cout<<"[2] Main Menu"<<endl;
            cout<<"Please insert your option [1-2]: ";
            cin>>list_num;

            while(list_num!=1 && list_num!=2){
                cout<<"Invalid option, please try again!"<<endl;
                cout<<"[1] Check Details of the order"<<endl;
                cout<<"[2] Main Menu"<<endl;
                cout<<"Please insert your option [1-2]: ";
                cin>>list_num;
            }

            if(list_num==1){
                checkOrder();
            }
            else if(list_num==2){
                return;
            }
        }

        pd.close();
        sales.close();
    }//end of displayOrder

    void checkOrder(){
        int selection, orderid, id, b_id, quantity;
        string check_name, status;
        double total;
        bool found=false;

        //open file
        ifstream sales("sales.txt");
        ifstream orders("orders.txt");
        ifstream pd("books.txt");
        ifstream customer("customers.txt");

        //display all order
        cout<<"Enter Order ID : ";
        cin>>selection;

        //read from orders.txt and sales.txt
        while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
            if(selection==s.sales_id){
                system("CLS");
                cout<<"-------------------------------------"<<endl;
                cout<<"  Order ID #"<<s.sales_id<<endl;
                cout<<"-------------------------------------"<<endl;
                cout<<"Total                 : RM "<<fixed<<setprecision(2)<<s.sales_total<<endl;

                found=true;
                check_name=s.sales_username;
            }
        }

        //read from customers.txt
        while(customer>>quoted(c.cfn)>>quoted(c.cln)>>quoted(c.cun)>>quoted(c.cpw)>>quoted(c.cpn)>>quoted(c.cadd)){
            if(check_name==c.cun){
                cout<<"Customer Name         : "<<c.cfn<<" "<<c.cln<<endl;
                cout<<"Customer Phone Number : "<<c.cpn<<endl;
                cout<<"Customer Address      : "<<c.cadd<<endl;

                cout<<"\n-------------------------------------"<<endl;
                cout<<"  Order Details: "<<endl;
                cout<<"-------------------------------------"<<endl;
                break;
            }//end of if
        }//end of while

        //read from orders.txt and books.txt
        while(orders>>o.order_id>>quoted(o.order_username)>>o.order_bookid>>o.order_bookquantity>>o.order_bookprice){
            if(selection==o.order_id){
                cout<<"Book ID: "<<o.order_bookid<<" | ";
                while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
                    if(o.order_bookid==p.id){
                        cout<<"Title: "<<setw(20)<<p.book_name<<" | Author: "<<setw(15)<<p.book_author<<" | Price: RM"<<p.price;
                    }
                }
                cout<<" | Quantity: "<<o.order_bookquantity<<endl;

                pd.clear();//clear any error flags
                pd.seekg(0, ios::beg);//move to the beginning of the file
            }
        }

        //display error message if not found
        if(found==false){
            cout<<"Order not found."<<endl;
        }

        //close file
        sales.close();
        orders.close();
        pd.close();
        customer.close();

        cout<<endl;
    }//end of checkOrder

    void searchOrder(){
        int list_num, Status_num;
        string input_name, O_Status;
        bool found=false;

        //open file
        ifstream sales("sales.txt");
        ifstream orders("orders.txt");
        ifstream pd("books.txt");
        ifstream customer("customers.txt");

        system("CLS");
        //display all order
        cout<<"-------------------------------------"<<endl;
        cout<<"\t\tSEARCH ORDER"<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"Search order by : "<<endl;
        cout<<"[1] Customer Name"<<endl;
        cout<<"[2] Order Status"<<endl<<endl;

        //ask for user input
        do{
            cout<<"Please select your option : ";
            cin>>list_num;

            //display error message if user enter invalid code
            if(list_num<1 || list_num>2){
                cout<<"Invalid option. Please enter either 1 or 2."<<endl;
            }
        }while(list_num<1 || list_num>2);

        //search order by customer name
        if(list_num==1){
            system("CLS");
            cout<<"Please enter the customer's name : ";
            fflush(stdin);
            getline(cin, input_name);

            //read from customers.txt
            while(customer>>quoted(c.cfn)>>quoted(c.cln)>>quoted(c.cun)>>quoted(c.cpw)>>quoted(c.cpn)>>quoted(c.cadd)){
                if(input_name==c.cun || input_name==c.cfn || input_name==c.cln){
                    system("CLS");
                    cout<<"-------------------------------------"<<endl;
                    cout<<"  Customer Details: "<<endl;
                    cout<<"-------------------------------------"<<endl;
                    cout<<"Customer Name         : "<<c.cfn<<" "<<c.cln<<endl;
                    cout<<"Customer Phone Number : "<<c.cpn<<endl;
                    cout<<"Customer Address      : "<<c.cadd<<endl;
                    input_name=c.cun;
                    cout<<"\n-------------------------------------"<<endl;
                    cout<<"  Order Placed by ["<<c.cfn<<"]"<<endl;
                    cout<<"-------------------------------------"<<endl;
                    break;
                }
            }

            //read from orders.txt and sales.txt
            while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
                if(input_name==s.sales_username){
                    cout<<"Order ID #"<<s.sales_id;
                    cout<<": RM "<<fixed<<setprecision(2)<<s.sales_total<<endl;

                    found=true;
                    input_name=s.sales_username;
                }
            }

            //display error message if not found
            if(found==false){
                cout<<"Order not found..."<<endl;
            }
        }

        //search order by order status
        else if(list_num==2){
            do{
                system("CLS");
                //ask for order status
                cout<<"[1] Order Placed"<<endl;
                cout<<"[2] Preparing"<<endl;
                cout<<"[3] Delivered"<<endl<<endl;
                cout<<"Enter order status [1-3] : ";
                cin>>Status_num;

                if(Status_num==1){
                    O_Status="Order placed";
                }
                else if(Status_num==2){
                    O_Status="Preparing";
                }
                else if(Status_num==3){
                    O_Status="Delivered";
                }
                else{
                    cout<<"Invalid option. Please enter either 1, 2 or 3."<<endl;
                }

            }while(Status_num<1 || Status_num>3);

            system("CLS");
            //read from orders.txt and sales.txt
            cout<<"\n-------------------------------------"<<endl;
            cout<<"  Orders with status ["<<O_Status<<"] "<<endl;
            cout<<"-------------------------------------"<<endl;

            while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
                if(O_Status==s.sales_status){
                    cout<<"Order ID #"<<s.sales_id;
                    cout<<" : RM "<<fixed<<setprecision(2)<<s.sales_total<<endl;

                    found=true;
                }
            }

            //display error message if not found
            if(found==false){
                cout<<"Order not found..."<<endl;
            }
        }

        //further action if order found
        if(found==true){
            do{
                cout<<"\n[1] Check Details of the order "<<endl;
                cout<<"[2] Main Menu"<<endl;

                cout<<"Please insert your option : ";
                cin>>list_num;

                if(list_num!=1 && list_num!=2){
                    system("CLS");
                    cout<<"Invalid Option, Please Try again!!!";
                }
            }while(list_num!=1 && list_num!=2);

            if(list_num==1){
                checkOrder();
            }

            else if(list_num==2){
                system("CLS");
                return;
            }
        }

        //close file
        sales.close();
        orders.close();
        pd.close();
        customer.close();
    }//end of searchOrder

    void editOrder(){
        int list_num, selection, status_num;
        string N_Status, check_name;
        bool found=false;

        //open file
        ifstream sales("sales.txt");
        ifstream orders("orders.txt");
        ifstream pd("books.txt");
        ifstream customer("customers.txt");

        //display all order
        system("CLS");
        cout<<"-------------------------------------"<<endl;
        cout<<"\t\tEDIT ORDER"<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<setw(10)<<"Order ID"<<setw(10)<<"Order by"<<setw(10)<<"Total"<<setw(15)<<"Status"<<endl;

        //read from orders.txt and sales.txt
        while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
            cout<<setw(10)<<s.sales_id<<setw(10)<<s.sales_username<<setw(10)<<s.sales_total<<setw(15)<<s.sales_status<<endl;
            found = true;
        }

        //display error message if not found
        if(found==false){
            cout<<"No transaction history found."<<endl;
            return;
        }

        //ask for order id
        cout<<"\nEnter Order ID : ";
        cin>>selection;

        found=false;
        sales.clear();
        sales.seekg(0, ios::beg);

        //read from orders.txt and sales.txt
        while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
            if(selection==s.sales_id){
                system("CLS");
                cout<<"-------------------------------------"<<endl;
                cout<<"  Order ID #"<<s.sales_id<<endl;
                cout<<"-------------------------------------"<<endl;
                cout<<"Total                 : RM"<<fixed<<setprecision(2)<<s.sales_total<<endl;

                found = true;
                check_name = s.sales_username;
            }
        }

        //read from customers.txt
        while(customer>>quoted(c.cfn)>>quoted(c.cln)>>quoted(c.cun)>>quoted(c.cpw)>>quoted(c.cpn)>>quoted(c.cadd)){
            if(check_name==c.cun){
                cout<<"Customer Name         : "<<c.cfn<<" "<<c.cln<<endl;
                cout<<"Customer Phone Number : "<<c.cpn<<endl;
                cout<<"Customer Address      : "<<c.cadd<<endl;

                cout<<"\n-------------------------------------"<<endl;
                cout<<"  Order Details: "<<endl;
                cout<<"-------------------------------------"<<endl;
                break;
            }
        }

        //read from orders.txt and books.txt
        while(orders>>o.order_id>>quoted(o.order_username)>>o.order_bookid>>o.order_bookquantity>>o.order_bookprice){
            if(selection==o.order_id){
                cout<<"Book ID: "<<o.order_bookid<<" | ";
                while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
                    if(o.order_bookid==p.id){
                        cout<<"Title: "<<setw(20)<<p.book_name<<" | Author: "<<setw(15)<<p.book_author<<" | Price: RM"<<p.price;
                    }
                }
                cout<<" | Quantity: "<<o.order_bookquantity<<endl;

                pd.clear();//clear any error flags
                pd.seekg(0, ios::beg);//move to the beginning of the file
            }
        }

        //display error message if not found
        if(found==false){
            cout<<"Order not found..."<<endl;
            sales.close();
            orders.close();
            pd.close();
            customer.close();
            return;
        }

        //ask for new status
        do{

            cout<<"\n[1] Order Placed"<<endl;
            cout<<"[2] Preparing"<<endl;
            cout<<"[3] Delivered"<<endl;
            cout<<"Enter New Status [1-3] : ";
            cin>>status_num;

            if(status_num==1){
                N_Status="Order placed";
            }
            else if(status_num==2){
                N_Status="Preparing";
            }
            else if(status_num==3){
                N_Status="Delivered";
            }
            else{
                cout<<"Invalid option. Please enter either 1, 2 or 3."<<endl;
            }

        }while(status_num<1 || status_num>3);

        sales.clear();
        sales.seekg(0, ios::beg);

        //write into temp file
        ofstream temp("temp.txt");

        while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
            if(selection==s.sales_id){
                temp<<s.sales_id<<" \""<<s.sales_username<<"\" "<<s.sales_costtotal<<" "<<s.sales_total<<" \""<<N_Status<<"\" "<<endl;
            }
            else{
                temp<<s.sales_id<<" \""<<s.sales_username<<"\" "<<s.sales_costtotal<<" "<<s.sales_total<<" \""<<s.sales_status<<"\" "<<endl;
            }
        }

        //close file
        sales.close();
        temp.close();
        orders.close();
        pd.close();
        customer.close();

        //delete sales.txt and rename temp.txt to sales.txt
        remove("sales.txt");
        rename("temp.txt", "sales.txt");

        //display successful message
        system("CLS");
        cout<<"Order Status Updated..."<<endl;
        system("break");
    }//end of editOrder

    void salesreport(){
        int op;
        system("CLS");

        do{
            //ask for user input
            cout<<"-------------------------------------"<<endl;
            cout<<"\tSales Report "<<endl;
            cout<<"-------------------------------------"<<endl;
            cout<<"[1] Earning and Profit"<<endl;
            cout<<"[2] Sold Book"<<endl;
            cout<<"[3] Main Menu"<<endl<<endl;

            cout<<"Please Select Your Option : ";
            cin>>op;

            //display error message if user enter invalid code
            if(op<1 || op>3){
                cout<<"Invalid Option, Please Try Again...";
            }
        }while(op<1 || op>3);

        //display sales report
        if(op==1){
            earning_profit();
        }

        //display sold book
        else if(op==2){
            sold_book();
        }
        else if(op==3){
            return;
        }
    }//end of salesreport

    void earning_profit(){
        //open file
        ifstream sales("sales.txt");
        ifstream orders("orders.txt");
        float tc=0, te=0, profit=0;

        //read from sales.txt and calculate the total cost and total earning
        while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
            tc+=s.sales_costtotal;
            te+=s.sales_total;
        }

        //calculate the profit
        profit = te-tc;

        //display the result
        system("CLS");
        cout<<"-------------------------------------"<<endl;
        cout<<"\tEarning and Profit"<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"Total cost    : RM "<<tc<<endl;
        cout<<"Total earning : RM "<<te<<endl;
        cout<<"Profit        : RM "<<profit<<endl<<endl;

        //close file
        sales.close();
        orders.close();
    }//end of earning_profit

    void sold_book(){
        //open file
        ifstream books("books.txt");

        system("CLS");
        //display title
        cout<<"-------------------------------------"<<endl;
        cout<<"\tSold Book"<<endl;
        cout<<"-------------------------------------"<<endl;

        //display the result
        cout<<setw(8)<<"Book ID"<<setw(20)<<"Title"<<setw(15)<<"Sold Stock"<<setw(10)<<"Cost"<<setw(10)<<"Earning"<<setw(10)<<"Profit"<<endl;
        while(books>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
            cout<<setw(8)<<p.id<<setw(20)<<p.book_name<<setw(15)<<p.sold_stock<<setw(10)<<fixed<<setprecision(2)<<(p.cost*p.sold_stock)<<setw(10)<<fixed<<setprecision(2)<<(p.price*p.sold_stock)<<setw(10)<<fixed<<setprecision(2)<<((p.price*p.sold_stock)-(p.cost*p.sold_stock))<<endl;

        }

        //close file
        books.close();

        cout<<endl;
    }//end of sold_book
};//end of functionAdmin class

class admin:public functionAdmin{
private:
    int choice=0;
    customer c;

public:
    admin(){
        //constructor
        c.name="admin";
        c.password="admin123";
    }//end of constructor

    ~admin(){
        //destructor
        cout<<"Thank you for using the system, have a nice day.\n\n";
    }//end of destructor

    string getName(){
        //accessor
        return c.name;
    }//end of accessor

    string getPassword(){
        //accessor
        return c.password;
    }//end of accessor

    void a_menu(){
        while(choice!=14){
            //display the menu for the admin
            cout<<"---------------------------------------------"<<endl;
            cout<<"\t\tMAIN MENU"<<endl;
            cout<<"---------------------------------------------"<<endl;
            cout<<"1. Register new book"<<endl;
            cout<<"2. Delete book"<<endl;
            cout<<"3. Update book's information"<<endl;

            cout<<"4. Display stock"<<endl;
            cout<<"5. Display customer orders"<<endl;
            cout<<"6. Search customer orders"<<endl;

            cout<<"7. Edit order status"<<endl;
            cout<<"8. Sales record"<<endl;
            cout<<"9. Exit"<<endl<<endl;

            //ask for user input
            cout<<"Enter your choice : ";
            cin>>choice;

            //jump to the function based on user input
            switch(choice){
            case 1:
                addbook();
                cout<<"Press any key to continue...";
                fflush(stdin);
                getchar();
                system("CLS");
                break;

            case 2:
                deleteBook();
                cout<<"Press any key to continue...";
                fflush(stdin);
                getchar();
                system("CLS");
                break;

            case 3:
                updatebook();
                cout<<"Press any key to continue...";
                fflush(stdin);
                getchar();
                system("CLS");
                break;

            case 4:
                displayBook();
                cout<<"Press any key to continue...";
                fflush(stdin);
                getchar();
                system("CLS");
                break;

            case 5:
                displayOrder();
                cout<<"Press any key to continue...";
                fflush(stdin);
                getchar();
                system("CLS");
                break;

            case 6:
                searchOrder();
                cout<<"Press any key to continue...";
                fflush(stdin);
                getchar();
                system("CLS");
                break;

            case 7:
                editOrder();
                cout<<"Press any key to continue...";
                fflush(stdin);
                getchar();
                system("CLS");
                break;

            case 8:
                salesreport();
                cout<<"Press any key to continue...";
                fflush(stdin);
                getchar();
                system("CLS");
                break;

            case 9:
                return;
                break;

            default:
                //this is when the admin enter invalid code
                cout<<"Selection invalid, please enter a valid number.\n\n";
                cout<<"Press any key to continue...";
                cin.ignore();
                getchar();
                break;
            }//end of switch
        }//end of while
    }//end of a_menu
};//end of admin class

class f_login{
private:
    admin a;
    customer c;
    string username, password;
    string fn, ln, pn, add, cpw, pw, un, ucompare, pcompare;

public:
    void main_menu(){
        int action;

        //display the main menu
        cout<<"---------------------------------------------"<<endl;
        cout<<"\tWELCOME TO BOOK STORE SYSTEM"<<endl;
        cout<<"---------------------------------------------"<<endl;
        cout<<"[1] Login"<<endl;
        cout<<"[2] Register"<<endl;

        //ask for user input
        cout<<"Please Select Your Action [1 or 2] : ";
        cin>>action;

        //display error message if user enter invalid code
        while(action!=1 && action!=2){
            cout<<"\n--Code Invalid--"<<endl;
            cout<<"Please Select Your Action [1 or 2] : "<<endl;
            cin>>action;
        }

        //jump to the function based on user input
        if(action==1){
            system("CLS");
            log();
        }
        else if(action==2){
            system("CLS");
            c_register();
        }
    }//end of main_menu

    void log(){

        cout<<"\n-----------------------------\n";
        cout<<"|           LOGIN           |\n";
        cout<<"-----------------------------\n";

        //to check whether the user is admin or customer
        cout<<"Please Enter Your Username : ";
        fflush(stdin);
        getline(cin, username);
        cout<<"Please Enter Your Password : ";
        fflush(stdin);
        getline(cin, password);

        if(username==a.getName() && password==a.getPassword()){
            system("CLS");
            a.a_menu();
        }
        else{
            system("CLS");
            c_login(username, password);
        }
    }//end of log

    void c_login(string &username, string &password){
        int log_attemp=4;
        bool found=false;

        do{
            //read the file to get user information
            ifstream fread("customers.txt");

            //check if the file is exist
            if(!fread.is_open()){
                cerr<<"Error opening file!!!"<<endl;
                return;
            }

            fread.clear();
            fread.seekg(0,ios::beg);

            //read the file to get user information
            while(fread>>quoted(c.cfn)>>quoted(c.cln)>>quoted(c.cun)>>quoted(c.cpw)>>quoted(c.cpn)>>quoted(c.cadd)){
                if(c.cun==username && c.cpw==password){
                    username=c.cun;
                    found=true;
                    break;
                }
            }

            //close the file
            fread.close();

            if(!found){
                log_attemp--;

                //display error message
                cout<<"Username or Password incorrect."<<endl;
                cout<<"\nLogin Failed, you have "<<log_attemp<<" more attempts.\n\n";

                //exit the program if user enter wrong password for 3 times
                if(log_attemp==0){
                    cout<<"You have exceeded the maximum login attempts."<<endl;
                    cout<<"Press try again later."<<endl;
                    exit(0);
                }

                //ask to re-enter username and password
                cout<<"Please re-enter your Username : ";
                fflush(stdin);
                getline(cin, username);
                cout<<"Please re-enter your Password : ";
                fflush(stdin);
                getline(cin, password);
                cout<<endl;
            }
        }while(!found);

        system("CLS");
        //display successful message
        cout<<"Welcome Back, "<<c.cfn<<endl;
        this_thread::sleep_for(chrono::seconds(2));

        //go to customer main menu
        c_menu(username);
    }//end of c_login

    void c_register(){
        //open file
        ifstream fread("customers.txt");
        ofstream cf("customers.txt", ios::app);

        string line;

        //ask user for get the information
        cout<<"Please enter your first name : ";
        fflush(stdin);
        getline(cin, fn);
        cout<<"Please enter your last name : ";
        fflush(stdin);
        getline(cin, ln);
        cout<<"Please enter your phone number : ";
        fflush(stdin);
        getline(cin, pn);
        cout<<"Please enter your delivery address : ";
        fflush(stdin);
        getline(cin, add);
        cout<<"Please enter your username : ";
        fflush(stdin);
        getline(cin, un);

        //read the file to get user information
        while(getline(fread, line)){
            istringstream iss(line);

            //Extracting values from the line
            if(!(iss>>quoted(c.cfn)>>quoted(c.cln)>>quoted(c.cun)>>quoted(c.cpw)>>quoted(c.cpn)>>quoted(c.cadd))){
                cerr<<"Error Parsing Line : "<<line<<endl;
                continue;
            }

            if(c.cun==un){
                cout<<"Username already exist!"<<endl;
                cout<<"Waiting..."<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                return;
            }
        }

        //close the file
        fread.close();

        do{
            cout<<"Please enter your password : ";
            fflush(stdin);
            getline(cin, pw);
            cout<<"Please confirm your password : ";
            fflush(stdin);
            getline(cin,cpw);

            //display error message if password doesn't match
            if(pw != cpw){
                cout<<endl<<endl<<"Your password doesn't match. Please re-enter again..."<<endl<<endl;
            }
        }while(pw!=cpw);

        //write into file
        if(cf.is_open()){
            cf<<"\""<<fn<<"\" \""<<ln<<"\" \""<<un<<"\" \""<<pw<<"\" \""<<pn<<"\" \""<<add<<"\""<<endl;
        }

        //close the file
        cf.close();

        //display successful message
        cout<<endl<<"Registration Successful."<<endl;
        cout<<"Press any key to continue...";
        fflush(stdin);
        getchar();

        system("CLS");
        //go to login page
        log();
    }//end of c_register

    string getUsername(){
        //accessor
        return username;
    }//end of getUsername

};//end of f_login

class functionUsers :public functionAdmin{
private:
    string fn, ln, pn, add, pw, un, ucompare, pcompare;
    product p;
    sales s;
    f_login fl;
    customer c;
    order o;

public:
    void add_cart(const string& username){
        bool found=false;
        int input_id, quantity;

        //open file
        ifstream pd("books.txt");
        ofstream cart("cart.txt", ios::app);

        //check if the file is exist
        if(!pd.is_open()){
            cerr<<"Error opening file"<<endl;
            return;
        }

        //display all books
        displayBook();

        do{
            //ask for user input
            cout<<"Enter book ID to add in your cart : ";
            cin>>input_id;

            pd.clear();//clear any error flags
            pd.seekg(0,ios::beg);//move to the beginning of the file

            while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
                if(input_id==p.id){
                    cout<<"Enter Quantity : ";
                    cin>>quantity;

                    cart<<"\""<<username<<"\" "<<p.id<<" "<<quantity<<endl;

                    cout<<"Book added to cart."<<endl;
                    found=true;
                    cout<<"Press any key to continue...";
                    fflush(stdin);
                    getchar();
                    break;
                }
            }

            if(found==false){
                cout<<"Book not found, please try again.";
            }
        }while(input_id!=p.id);

        cart.close();
        pd.close();

        browse(username);

    }//end of add cart


    //need to change
    //
    //
    //
    //
    //
    //(make you see this)
    //
    //
    //
    //
    bool partialMatch(const string& text, const string& pattern) {
                return text.find(pattern) != string::npos;
    }//end of partialMatch

    void searchBook(const string& username){
        string s_Book, bookID,line;
        char ans;
        bool found=false;

        do
        {
        system("CLS");
        //display title
        cout<<"######################Search######################"<<endl;
        cout<<"\t\tSEARCH BAR"<<endl;
        cout<<"######################Search######################"<<endl<<endl;

        //display book, take function from void display book
        ifstream readbook("books.txt");
        cout<<setw(10)<<"Book ID#"<<setw(20)<<"Book Name"<<setw(20)<<"Author"<<setw(15)<<"Cost Price"<<setw(15)<<"Sell Price"<<setw(25)<<"Description"<<setw(15)<<"Stock"<<endl;
            while(getline(readbook,line)){
            istringstream iss(line);
            //extraction values from the line
            if(!(iss >> p.id >> quoted(p.book_name) >> quoted(p.book_author) >> p.cost >> p.price >> quoted(p.book_description) >> p.stock)){
                cerr<<"Error parsing line : " <<line<<endl;
                continue;
            }
            //DIsplay result
            cout<<setw(10)<<p.id<<setw(20)<<p.book_name<<setw(20)<<p.book_author<<setw(15)<<fixed<<setprecision(2)<<p.cost<<setw(15)<<fixed<<setprecision(2)<<p.price<<setw(25)<<p.book_description<<setw(15)<<p.stock<<endl;
        }

        //close file
        readbook.close();

        string searchTerm;
        cout<<"\nBased on Title or Author to search"<<endl;
        cout << "Enter search name: ";
        cin >> searchTerm;

        // Open the file
        ifstream inputFile("books.txt");

        // Check if the file is opened successfully
        if (!inputFile.is_open()) {
            cerr << "Error opening the file." << endl;
            return;
        }

        // Read books from the file into a vector
        vector<Book> books;
        Book currentBook;
        while (inputFile >> currentBook.bookid >> quoted(currentBook.title) >> quoted(currentBook.author) >>
            currentBook.cost >> currentBook.price >> quoted(currentBook.description) >> currentBook.stock >>
            currentBook.sold_stock) {
            books.push_back(currentBook);
        }

        // Filter books containing the partial search term
        vector<Book> filteredBooks;

        for (const Book& book : books) {
            if ( partialMatch(book.title, searchTerm) ||
                partialMatch(book.author, searchTerm) ) {
                filteredBooks.push_back(book);
            }

        }

        if (filteredBooks.empty()) {
            cout << "Book not found." << endl;
            return; // Return to the last function
        }
        // Output the filtered books
        system("CLS");
        cout<<endl;
        cout << setw(10) << "Book ID" << setw(20) << "Title" << setw(20) << "Author"
            << setw(10) << "Cost" << setw(10) << "Price" << setw(30) << "Description"
            << setw(10) << "Stock" << endl;

        for (const Book& filteredBook : filteredBooks) {
            cout << setw(10) << filteredBook.bookid << setw(20) << filteredBook.title
                << setw(20) << filteredBook.author << setw(10) << filteredBook.cost
                << setw(10) << filteredBook.price << setw(30) << filteredBook.description
                << setw(10) << filteredBook.stock << endl;
        }

        // Close the file
        inputFile.close();

        cout<<"\nDo you want to search another book? [Y/N]"<<endl;
        cout<<"If you want to add book to wishlist or cart please enter [N]: ";
        cin>>ans;
        }while(ans=='Y'||ans=='y');
        int option;
        cout<<"\n-------------------------------------"<<endl;
        cout<<"Enter 1 to add to cart"<<endl;
        cout<<"Enter 2 to add to wishlist"<<endl;
        cout<<"Enter 3 to browse"<<endl;
        cout<<"Enter 4 to Main menu"<<endl;
        cout<<"Please select your option [1-4] : ";
        cin>>option;

        while(option<1 || option>4){
            cout<<"\nInvalid Option"<<endl;
            cout<<"Please select either 1, 2, 3 or 4 : ";
            cin>>option;
        }

        if(option==1){
            system("CLS");
            add_cart(username);
        }
        else if(option==2){
            system("CLS");
            add_wishlist(username);
        }
        else if(option==3){
            system("CLS");
            browse(username);
        }
        else if(option==4){
            system("CLS");
            c_menu(username);
        }

    }//end of search book

    void add_wishlist(const string& username){
        int input_id;
        bool found=false;

        system("CLS");

        //open file
        ifstream pd("books.txt");
        ofstream wish("wishlist.txt", ios::app);

        //check if the file is exist
        if(!pd.is_open()){
            cerr<<"Error opening file !";
            return;
        }

        //display all books
        displayBook();

        do{
            //ask for user input
            cout<<"Enter book ID to add in wishlist : ";
            cin>>input_id;

            //read the file to get user information
            if(input_id){
                while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
                    if(input_id==p.id){
                        wish<<"\""<<username<<"\" "<<p.id<<" \""<<p.book_name<<"\""<<endl;
                        cout<<"Successfully added in your wishlist."<<endl;
                        cout<<"Press any key to continue...";
                        fflush(stdin);
                        getchar();
                        found=true;
                        break;
                    }
                }
            }

            pd.clear();
            pd.seekg(0, ios::beg);

            //display error message if book not found
            if(found==false){
                cout<<"Book not found, Please try again."<<endl;
            }
        }while(input_id!=p.id);

        //close file
        wish.close();
        pd.close();

        system("CLS");
        browse(username);

    }//end of add wishlist

    void delete_wishlist(const string& username){
        char selection;
        string name;
        int input_ID;
        bool found=false;

        do{
            //open file
            ifstream wl("wishlist.txt");
            ofstream temp("temp_wishlist.txt");

            //check if the file is exist
            cout<<"Enter Book ID you wish to delete: ";
            cin>>input_ID;

            wl.clear();
            wl.seekg(0,ios::beg);

            //read the file to get user information
            while(wl>>quoted(name)>>p.id>>quoted(p.book_name)){
                if(input_ID==p.id && name==username){
                    found=true;
                    continue;
                }

                else{
                    temp<<"\""<<name<<"\" "<<p.id<<" \""<<p.book_name<<"\""<<endl;
                }
            }

            //close file
            wl.close();
            temp.close();

            //delete wishlist.txt and rename temp_wishlist.txt to wishlist.txt
            remove("wishlist.txt");
            rename("temp_wishlist.txt","wishlist.txt");

            if(found==false){
                system("CLS");
                //display error message if book not found
                cout<<"Book is not found, Please try again."<<endl;
            }
            else if(found==true){
                system("CLS");
                //display successful message
                cout<<"Your wishlist you have choose have been deleted."<<endl;
                cout<<"Do you want to delete another book? [Y/N] : ";
                cin>>selection;
            }

        }while(selection=='Y' || selection == 'y');

    }//end of delete wishlist

    void wishlist(string username){
        int list_num, wl_id;
        string name, wl_book_name;

        //open file
        ifstream wl("wishlist.txt");
        ifstream pd("books.txt");

        system("CLS");
        //display title
        cout<<"######################Wish List######################"<<endl;
        cout<<"                      Wish List"<<endl;
        cout<<"######################Wish List######################"<<endl;
        cout<<setw(8)<<"Book ID"<<setw(20)<<"Book Title"<<setw(15)<<"Price"<<endl;

        //read the file to get user information
        while(wl>>quoted(name)>>wl_id>>quoted(wl_book_name)){
            while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
                if(wl_id==p.id && name==username){
                    cout<<setw(8)<<p.id<<setw(20)<<p.book_name<<fixed<<setprecision(2)<<setw(15)<<p.price<<endl;
                }
            }
            pd.clear();
            pd.seekg(0, ios::beg);
        }

        //close file
        wl.close();
        pd.close();

        do{
            //ask for user input
            cout<<"\n[1] Add items to wishlist"<<endl;
            cout<<"[2] Delete item form wishlist"<<endl;
            cout<<"[3] Main Menu"<<endl<<endl;

            cout<<"Please select your option : ";
            cin>>list_num;
        }while(list_num<1 || list_num>3);

        if(list_num==1){
            //add item to wishlist
            add_wishlist(username);
            return;
        }

        else if(list_num==2){
            //delete item from wishlist
            delete_wishlist(username);

        }
        else if(list_num==3){
            system("CLS");
            //go to main menu
            c_menu(username);
        }
    }//end of wishlist

    void browse(const string& username){
        int option;

        //display title
        system("CLS");
        cout<<"##########################################################"<<endl;
        cout<<"#                         BOOKSTORE                      #"<<endl;
        cout<<"##########################################################"<<endl;

        //display all books
        ifstream pl("books.txt");

        cout<<setw(8)<<"Book ID"<<setw(20)<<"Title"<<setw(20)<<"Author"<<setw(10)<<"Price"<<endl;
        while(pl>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
            cout<<setw(8)<<p.id<<setw(20)<<p.book_name<<setw(20)<<p.book_author<<setw(10)<<fixed<<setprecision(2)<<p.price<<endl;
        }

        //close file
        pl.close();

        //ask for user input
        cout<<"\n[1] Add to cart"<<endl;
        cout<<"[2] Add to wishlist"<<endl;
        cout<<"[3] Search product"<<endl;
        cout<<"[4] Main menu"<<endl;

        cout<<"Please select your option [1-4] : ";
        cin>>option;

        //display error message if user enter invalid code
        while(option<1 || option>4){
            cout<<"\nInvalid Option"<<endl;
            cout<<"Please select either 1, 2, 3 or 4 : ";
            cin>>option;
        }

        if(option==1){
            system("CLS");
            add_cart(username);
        }
        else if(option==2){
            system("CLS");
            add_wishlist(username);
        }
        else if(option==3){
            system("CLS");
            searchBook(username);
        }
        else if(option==4){
            system("CLS");
            c_menu(username);
        }
    }//end of browse

    void shopping_cart(const string& username){
        int list_num, input_ID, ID;
        bool found=false;

        //open file
        ifstream sc("cart.txt");
        ifstream pd("books.txt");

        system("CLS");
        //display title
        cout<<"##################SHOPPING CART#################"<<endl;
        cout<<"                  SHOPPING CART"<<endl;
        cout<<"##################SHOPPING CART#################"<<endl<<endl;
        cout<<setw(8)<<"Book ID"<<setw(20)<<"Name"<<setw(10)<<"Price"<<setw(10)<<"Quantity"<<endl;

        //read the file to get user information
        while(sc>>quoted(s.sales_username)>>s.sales_id>>s.quantity){
            while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
                    if(p.id==s.sales_id && s.sales_username==username){
                        cout<<setw(8)<<p.id<<setw(20)<<p.book_name<<setw(10)<<fixed<<setprecision(2)<<p.price<<setw(10)<<s.quantity<<endl;
                        s.sales_total+=(p.price*s.quantity);
                        found=true;
                    }
                }

                pd.clear();
                pd.seekg(0, ios::beg);
            }

            //close file
            sc.close();
            pd.close();

            //display error message if cart is empty
            if(found==false){
                cout<<" Your cart is empty..."<<endl<<endl;
            }
            else{
                //display total price
                cout<<endl<<"Total : RM "<<fixed<<setprecision(2)<<s.sales_total<<endl;
                s.sales_total=0;

                system("break");

                do{
                    //display action list
                    cout<<"\n[1] Add item to cart "<<endl;
                    cout<<"[2] Delete Item from cart"<<endl;
                    cout<<"[3] Checkout"<<endl;
                    cout<<"[4] Main Menu"<<endl<<endl;

                    cout<<"Please Select your option : ";
                    cin>>list_num;
                }while(list_num<1 || list_num>4);

                if(list_num==1){
                    browse(username);
                    system("CLS");
                }
                else if(list_num==2){
                    delete_cart(username);
                    system("CLS");
                }
                else if(list_num==3){
                    checkout(username);
                }
                else if(list_num==4){
                    system("CLS");
                    c_menu(username);
                }
            }

    }//end of shopping_cart

    void delete_cart(const string& username){
        char selection;
        int input_ID;
        bool found=false;

        do{
            //open file
            ifstream sc("cart.txt");
            ofstream temp("temp_cart.txt");

            //check if the file is exist
            cout<<"Enter Book ID you want to delete in your cart : ";
            cin>>input_ID;

            sc.clear();
            sc.seekg(0, ios::beg);

            //read the file to get user information
            while(sc>>quoted(s.sales_username)>>s.sales_id>>s.quantity){
                if(input_ID==s.sales_id && s.sales_username==username){
                    found=true;
                    continue;
                }
                else{
                    temp<<"\""<<s.sales_username<<"\" "<<s.sales_id<<" "<<s.quantity<<endl;
                }
            }

            //close file
            sc.close();
            temp.close();

            //delete cart.txt and rename temp_cart.txt to cart.txt
            remove("cart.txt");
            rename("temp_cart.txt", "cart.txt");

            //display error message if book not found
            if(found==false){
                cout<<"Book doesn't found, please try again."<<endl;
            }
            else if(found==true){
                cout<<"Your book have been deleted from your cart."<<endl<<endl;
                cout<<"Do you have another book want to delete?[Y/N] : ";
                cin>>selection;
            }

        }while(selection=='Y' || selection=='y');

        shopping_cart(username);
    }//end of delete_cart

    void checkout(const string& username){
        //open file
        ifstream sc("cart.txt");
        ifstream pd("books.txt");
        ofstream temp("temp_books.txt");
        ifstream tempb("temp_books.txt");
        ofstream tempcart("temp_cart.txt");
        ofstream orderw("orders.txt", ios::app);
        ofstream sales("sales.txt", ios::app);
        ifstream salesr("sales.txt");

        string name;
        double cost, book_p;
        int orderid=2000, id, quantity, updated_stock, updated_sold_stock, order_book_id;

        time_t now;
        struct tm nowLocal;
        now = time(NULL);//get the time from the OS
        nowLocal =* localtime(&now);

        //check if the file is exist
        if(salesr.is_open()){
            string line;

            //count the existing records in the file -> to get the book ID
            while(getline(salesr, line)){
                orderid++;
            }
        }

        //read from cart.txt
        while(sc>>quoted(name)>>id>>quantity){
            bool bookFound = false;
            while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
                if(p.id==id && name==username){
                    if(p.stock>=quantity){
                        //update the stock and sold stock
                        updated_stock = p.stock - quantity;
                        updated_sold_stock = p.sold_stock + quantity;
                        //assign value
                        book_p = p.price;
                        order_book_id = p.id;
                        //calculate the total
                        s.sales_total += (book_p*quantity);
                        s.sales_costtotal += (p.cost*quantity);
                        //write into temp_books.txt
                        temp<<p.id<<" \""<<p.book_name<<"\" \""<<p.book_author<<"\" "<<p.cost<<" "<<p.price<<" \""<<p.book_description<<"\" "<<updated_stock<<" "<<updated_sold_stock<<endl;
                        bookFound = true;
                    }
                    else{
                        //display error message if book is out of stock
                        cout<<"Book ID "<<p.id<<" is out of stock."<<endl;
                        cout<<"Please try again."<<endl;
                        return;
                    }
                }
            }

            //write into orders.txt
            if (bookFound) {
                orderw<<orderid+1<<" \""<<username<<"\" "<<order_book_id<<" "<<quantity<<" "<<book_p<<endl;
            }
            pd.clear(); // clear any error flags
            pd.seekg(0, ios::beg); // move to the beginning of the file
        }

        string temp_title, temp_author, temp_description;
        int temp_id, temp_stock, temp_soldstock;
        double temp_cost, temp_price;

        //read from books.txt to transfer non-updated value to temp_books.txt
        while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
            bool bookFound = false;
            while(tempb>>temp_id>>quoted(temp_title)>>quoted(temp_author)>>temp_cost>>temp_price>>quoted(temp_description)>>temp_stock>>temp_soldstock){
                if(p.id==temp_id){
                    bookFound = true;
                }
            }

            if (!bookFound) {
                temp<<p.id<<" \""<<p.book_name<<"\" \""<<p.book_author<<"\" "<<p.cost<<" "<<p.price<<" \""<<p.book_description<<"\" "<<p.stock<<" "<<p.sold_stock<<endl;
            }
            tempb.clear(); // clear any error flags
            tempb.seekg(0, ios::beg); // move to the beginning of the file
        }

        sc.clear(); // clear any error flags
        sc.seekg(0, ios::beg); // move to the beginning of the file

        //delete cart.txt where username == username
        while(sc>>quoted(name)>>id>>quantity){
            if(name!=username){
                tempcart<<"\""<<name<<"\" "<<id<<" "<<quantity<<endl;
            }
        }

        //write into sales.txt
        sales<<orderid+1<<" \""<<username<<"\" "<<fixed<<setprecision(2)<<s.sales_costtotal<<" "<<fixed<<setprecision(2)<<s.sales_total<<" \"Order placed\""<<endl;

        //close file
        sc.close();
        pd.close();
        temp.close();
        tempb.close();
        salesr.close();
        sales.close();
        tempcart.close();
        orderw.close();

        //delete books.txt and rename temp_books.txt to books.txt
        remove("books.txt");
        rename("temp_books.txt","books.txt");
        //delete cart.txt and rename temp_cart.txt to cart.txt
        remove("cart.txt");
        rename("temp_cart.txt","cart.txt");

        system("CLS");
        //display successful message
        cout<<"Order placed successfully."<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"               Receipt"<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"Order Date/Time: "<<nowLocal.tm_mday<<"/"<<nowLocal.tm_mon+1<< "/"<<nowLocal.tm_year+1900<<" "<<nowLocal.tm_hour<<":"<<nowLocal.tm_min<<endl;
        cout<<"Order ID #"<<orderid+1<<endl;
        cout<<"Total    : RM "<<fixed<<setprecision(2)<<s.sales_total<<endl<<endl;

    }//end of checkout

    void transaction_history(const string& username){
        int list_num;

        //open file
        ifstream pd("books.txt");
        ifstream sales("sales.txt");

        bool found=false;

        system("CLS");
        //display title
        cout<<"######################Transaction History######################"<<endl;
        cout<<"                      Transaction History"<<endl;
        cout<<"######################Transaction History######################"<<endl<<endl;
        cout<<setw(8)<<"Order ID"<<setw(10)<<"Total"<<setw(15)<<"Status"<<endl;

        //read from orders.txt and sales.txt;
        //compare if orders.txt order_id=sales.txt order_id
        while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
            if(s.sales_username==username){
                cout<<setw(8)<<s.sales_id<<setw(10)<<s.sales_total<<setw(15)<<s.sales_status<<endl;
                found=true;
            }
        }
        sales.clear();
        sales.seekg(0,ios::beg);

        //display error message if no transaction history found
        if(found==false){
            cout<<"No Transaction history found."<<endl;
        }

        do{
            cout<<"\n[1] Check details of the order"<<endl;
            cout<<"[2] Main Menu"<<endl;

            //ask for user input
            cout<<"Please select your option : ";
            cin>>list_num;

            if(list_num!=1 && list_num!=2){
                system("CLS");
                cout<<"Invalid option, please try again...";
            }
        }while(list_num!=1 && list_num!=2);

        if(list_num==1){
            transaction_details(username);
        }
        else if(list_num==2){
            system("CLS");
            c_menu(username);
        }

        pd.close();
        sales.close();
    }//end of transaction_history

    void transaction_details(string username){
        int input_OID;
        bool found=false;

        //open file
        ifstream sales("sales.txt");
        ifstream orders("orders.txt");
        ifstream pd("books.txt");

        //check if the file is exist
        cout<<"-------------------------------------"<<endl;
        cout<<"         Order Details"<<endl;
        cout<<"-------------------------------------"<<endl;

        //ask for user input
        cout<<"Enter Order ID : ";
        cin>>input_OID;

        //read the file to get user information
        while(sales>>s.sales_id>>quoted(s.sales_username)>>s.sales_costtotal>>s.sales_total>>quoted(s.sales_status)){
            if(input_OID==s.sales_id && s.sales_username==username){
                system("CLS");
                cout<<"-------------------------------------"<<endl;
                cout<<"  Order ID #"<<s.sales_id<<endl;
                cout<<"-------------------------------------"<<endl;
                cout<<"Total    : RM "<<fixed<<setprecision(2)<<s.sales_total<<endl;
                cout<<"Status   : "<<s.sales_status<<endl<<endl;

                found=true;

                cout<<"-------------------------------------"<<endl;
                cout<<"  Order Details :"<<endl;
                cout<<"-------------------------------------"<<endl;
            }
        }

        //read the file to get user information
        while(orders>>o.order_id>>quoted(o.order_username)>>o.order_bookid>>o.order_bookquantity>>o.order_bookprice){
            if(input_OID==o.order_id && o.order_username==username){
                cout<<"Book ID : "<<o.order_bookid<<" | ";

                while(pd>>p.id>>quoted(p.book_name)>>quoted(p.book_author)>>p.cost>>p.price>>quoted(p.book_description)>>p.stock>>p.sold_stock){
                    if(p.id==o.order_bookid){
                        cout<<"Title : "<<setw(20)<<p.book_name<<" | Author : "<<setw(15)<<p.book_author<<" | Price : "<<p.price;
                    }
                }
                cout<<setw(10)<<" | Quantity : "<<o.order_bookquantity<<endl;

                pd.clear();
                pd.seekg(0, ios::beg);
            }
        }
        if(found==false){
            system("CLS");
            cout<<"Order not found...\n";
        }

        //close file
        sales.close();
        orders.close();
        pd.close();

        cout<<endl;
    }//end of transaction_details

    //friend class
    friend class f_login;
};//end of class functionUsers

void c_menu(string username){
    int *option = new int;
    f_login fl;
    functionUsers fu;

    do{
        //display the menu for the customer
        cout<<"---------------------------------------------"<<endl;
        cout<<"\t\tMAIN MENU"<<endl;
        cout<<"---------------------------------------------"<<endl;
        cout<<"1. Browse all books"<<endl;
        cout<<"2. Search books"<<endl;
        cout<<"3. Review wishlist"<<endl;
        cout<<"4. Checkout shopping cart"<<endl;
        cout<<"5. Display transaction history"<<endl;
        cout<<"6. Log Out"<<endl;
        cout<<"7. Exit"<<endl<<endl;

        //ask for user input
        cout<<"Enter your option : ";
        cin>>*option;

        //jump to the function based on user input
        switch(*option){
            case 1:
                fu.browse(username);
                cout<<"Press any key to continue...";
                cin.ignore();
                getchar();
                system("CLS");
                break;

            case 2:
                fu.searchBook(username);
                cout<<"Press any key to continue...";
                cin.ignore();
                getchar();
                system("CLS");
                break;

            case 3:
                fu.wishlist(username);
                cout<<"Press any key to continue...";
                cin.ignore();
                getchar();
                system("CLS");
                break;

            case 4:
                fu.shopping_cart(username);
                cout<<"Press any key to continue...";
                cin.ignore();
                getchar();
                system("CLS");
                break;

            case 5:
                fu.transaction_history(username);
                cout<<"Press any key to continue...";
                cin.ignore();
                getchar();
                system("CLS");
                break;

            case 6:
                fl.main_menu();
                return;
                break;

            case 7:
                exit(0);
                break;

            default:
                cout<<"Selection invalid, Please enter a valid number..."<<endl;
                cout<<"Press any key to continue...";
                cin.ignore();
                getchar();
                system("CLS");
                break;
        }//end of switch
    }while(*option != 6 || *option != 7);

    //delete the pointer
    delete option;
}//end of c_menu

class DT {
    private:
        chrono::system_clock::time_point dateTime;

    public:
        //Constructor taking the current date and time
        DT() : dateTime(chrono::system_clock::now()) {}

        //Declaration of the friend function
        friend void showDateTime(const DT& obj);
};//end of class DT

void showDateTime(const DT& obj) {
    time_t currentTime = chrono::system_clock::to_time_t(obj.dateTime);
    cout << "Current Date and Time: " << ctime(&currentTime);
}//end of showDateTime

int main(){
    f_login fl;
    DT datetime;
    system("CLS");
    //display the date and time
    showDateTime(datetime);
    //go to main menu
    fl.main_menu();
}//end of main
