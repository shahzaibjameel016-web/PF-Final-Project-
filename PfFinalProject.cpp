#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
struct Movie {
    string name;
    int price;
};

const int Rows = 5;
const int Cols = 5;
int seats[Rows][Cols] = {0};   
vector<Movie> movies;            

void initializeMovies() {
    movies.push_back({"Avengers", 500});
    movies.push_back({"Inception", 600});
    movies.push_back({"Titanic", 400});
    movies.push_back({"Interstellar", 700});
    movies.push_back({"Joker", 550});
    movies.push_back({"Spider-Man", 650});
}

void showMenu() {
    cout << "\n Cinema Ticket Booking  \n";
    cout << "1. Book Ticket\n";
    cout << "2. View Booking History\n";
    cout << "3. Exit\n";
    cout << "Enter choice: ";
}

int selectMovie(){
    cout << "\nSelect Your Favourite  Movie:\n";
    for (int i = 0; i < movies.size(); i++){
        cout << i + 1 << ". " << movies[i].name
             << " (" << movies[i].price << " PKR)\n";
    }
    int choice;
    cin >> choice;
   if(choice<1 || choice>movies.size()){
     return -1;
   }
    return choice - 1; 
}

string selectTime(){
    int t;
    cout << "\nSelect Time when you want to watch:\n";
    cout << "1. 12:00 PM\n2. 3:00 PM\n3. 6:00 PM\n";
    cin >> t;

    if(t == 1){
    return "12:00 PM";}
    if(t == 2){ 
    return "3:00 PM";}
    if(t == 3){
    return "6:00 PM";
    }
    return "Invalid";
}

void showSeats(){
    cout << "\nThe Seat Layout is (0 = Available, X = Booked)\n\n ";
    for(int c=0; c<Cols; c++){
    cout <<c+1<<" ";
    cout <<endl;

    for(int i=0; i<Rows; i++){
        cout<<"R"<<i+1<< " ";
        for (int j=0; j<Cols; j++){
            cout<<(seats[i][j]==0 ? "0 " : "X ");
        cout<<endl;
        }
    }
  }
}

int selectSeats(int price){
    int count;
    cout<< "\nHow many seats? ";
    cin>>count;

    int booked = 0;
    while (booked < count) {
        int r, c;
        showSeats();
        cout << "Please Enter Row Number : "; 
        cin >> r;
        cout << "Enter Column Number : "; 
        cin >> c;

        if(r<1 || r>Rows || c<1 || c>Cols || seats[r-1][c-1] == 1){
            cout << "Invalid seat! Try again.\n";
        }else{
            seats[r-1][c-1] = 1;
            booked++;
        }
    }
    return count * price; 
}

string selectPaymentWay() {
    int choice;
    cout<< "\nSelect Payment Method:\n";
    cout<< "1. Cash\n";
    cout << "2. EasyPaisa\n";
    cout << "3. JazzCash\n";
    cout<< "4. Bank\n";
    cout << "Enter choice: ";
    cin>>choice;

    if(choice == 1){ 
    return "Cash";}
    if(choice == 2){
    return "EasyPaisa";}
    if(choice == 3){
    return "JazzCash";}
    if(choice == 4){ 
    return "Bank";
}
    return "Invalid";
}

bool paymentProcess(int total, string &method){
    method = selectPaymentWay();
    if(method == "Invalid"){
        cout<<"Invalid payment method\n";
        return false;
    }

    int amount;
    cout<<"\nTotal Amount:" <<total<<" PKR\n";
    cout<<"Paying via:" <<method <<endl;
    cout<<"Enter payment amount: ";
    cin>>amount;
        if(amount<total){
        cout << "Payment Failed\n";
        return false;
    }

    cout<<"Payment Successful\n";
    return true;
}

void saveBooking(const string &movie, const string &time, int total, const string &method){
    ofstream fout("booking.txt", ios::app);
    fout<<movie<<" | "<<time<< " | " 
         <<total<< " | " <<method<<endl;
    fout.close();
}

void bookYourTicket() {
    int index = selectMovie();
    if(index == -1){
        cout << "Sorry for! Invalid movie selection!\n";
        return;
    }

    string time = selectTime();
    if(time=="Invalid"){
        cout<<"Invalid time selection!\n";
        return;
    }

    int total = selectSeats(movies[index].price);

    string paymentMethod;
    if(!paymentProcess(total, paymentMethod)){
        cout<<"Sorry for Booking cancelled\n";
        return;
    }

    cout<< "\nTICKET \n";
    cout<< " Movie    : " << movies[index].name << endl;
    cout<< "Show Time : " << time << endl;
    cout<< " Total   : " << total << " PKR\n";
    cout << " Paid via : " << paymentMethod << endl;
    cout<< " Status : BOOKED\n";
    cout<< "---------------------------------\n";

    saveBooking(movies[index].name, time, total, paymentMethod);
}

void viewHistory(){
    ifstream fin("booking.txt");
    if(!fin){
        cout << "No booking history found\n";
        return;
    }

    string line;
    cout<<"\n BOOKING HISTORY\n";
    while(getline(fin, line))
        cout<<line<<endl;
fin.close();
}

int main(){
    initializeMovies();
 int choice;
    while(true){
        showMenu();
        cin>>choice;

        if(choice==1)
          bookYourTicket();
        else if(choice == 2)
            viewHistory();
        else if (choice==3)
            break;
        else
            cout<< "Invalid choice\n";
    }
    return 0;
}
