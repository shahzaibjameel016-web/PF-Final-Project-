#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Car
{
    int id;
    string name;
    int pricePerDay;
};

vector<Car> cars;

void initializeCars()
{
    cars.push_back({ 1, "Toyota Corolla", 5000});
    cars.push_back({ 2, "Honda Civic", 6000});
    cars.push_back({ 3, "Suzuki Alto", 3000});
    cars.push_back({ 4, "Bogatti", 8000});
}

void showCars()
{
    cout <<"\n---Available Cars---\n";
    for (int i = 0; i<cars.size(); i++)
    {
        cout<<cars[i].id<<". "<<cars[i].name<<" => Rs "<<cars[i].pricePerDay<<" per day\n";
    }
}

void saveBooking(string carName, int days, int bill)
{
    ofstream file("car_booking.txt", ios::app);
    file<<"Car: "<< carName<< " => Days: "<<days<< " => Bill: Rs "<<bill<<endl;
    file.close();
}

void bookYourCar()
{
    int choice, days;
    showCars();
    cout<<"\nSelect For Car ID: ";
    cin>>choice;

    if(choice<1 || choice>cars.size())
    {
        cout<<"Invalid Car Selection!\n";
        return;
    }

    cout<<"Please Enter the number of days:";
    cin>>days;

    if(days <= 0)
    {
        cout << "Invalid days!\n";
        return;
    }

    int bill = cars[choice - 1].pricePerDay * days;

    cout << "\n   Booking Detail   \n";
    cout<< "Car Name : " << cars[choice - 1].name << endl;
    cout<< "Days : " << days << endl;
    cout<< "Total Bill : Rs " << bill << endl;
    cout<< "Status : BOOKED\n";

    saveBooking(cars[choice-1].name, days, bill);
}

void viewBookingHistory()
{
    ifstream file("car_booking.txt");
    if(!file)
    {
        cout<<"\nNo booking history found.\n";
        return;
    }

    string line;
    cout<<"\n Booking History \n";
    while(getline(file, line))
    {
        cout<<line<<endl;
    }
    file.close();
}

int main()
{
    initializeCars();
    int choice;
    while(true)
    {
        cout<< "\n  Car RENTAL System \n";
        cout<< "1.  View for Cars\n";
        cout << "2. Select to Book Car\n";
        cout<< "3. View Your Booking History\n";
        cout << "4.  Exit\n";
        cout<< " Enter choice:  ";
        cin>> choice;

        if(choice == 1){
            showCars();
        }
        else if(choice == 2){
            bookYourCar();
        }
        else if(choice == 3){
            viewBookingHistory();
        }
        else if(choice == 4)
        {
            cout<<"Thank you for using our System";
            break;
        }
        else
            cout<<"Invalid choice!\n";
    }

    return 0;
}
