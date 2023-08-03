#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Car
{
	protected:
		string carBrand;
		string carModel;
		string carColor;
		int carPrice;
		int carMileage;
	public:
		int carCode;
		void setCarData();
		void getCarData();
		string setCarBrand()
		{
      		return carBrand;
    	};
    	string setCarModel()
		{
      		return carModel;
    	};
    	string setCarColor()
		{
      		return carColor;
    	};
    	int setCarPrice()
		{
      		return carPrice;
    	};
    	int setCarMileage()
		{
      		return carMileage;
    	};
    	int setCarCode()
		{
      		return carCode;
    	};
};

class Customer
{
	private:
		string customerName;
		string customerAddress;
		string customerMobileNo;
		int customerCitizenshipNo;
	public:
		void setCustomerData();
		void getCustomerData();
};

class SoldCar : public Car , public Customer
{
	public:
		void sellingCar();
};

fstream TC, TTC, AC, TAC, SC, CCL;
Car myCarObj;
Customer myCustomerObj;
SoldCar mySoldCarObj;

void Car :: setCarData()
{
	int CC, D, uniqueCarCodeCheck=0;
	cout << "Enter car's details." << endl;

	ifstream UCC; // UCC = unique car code
	Flag2:
	UCC.open("carCodeList.txt");
	cout << "Car code: "; cin >> D;
	while(UCC >> CC)
	{
		if(D == CC)
		{
			uniqueCarCodeCheck++;
		}
	}

	if(uniqueCarCodeCheck != 0)
	{
		cout << "Sorry! This code number is already assigned." << endl;
		cout << "Please enter different code." << endl;
		uniqueCarCodeCheck = 0;
		UCC.close();
		goto Flag2;

	}
	UCC.close();

	carCode = D;
	fflush(stdin);
	cout << "Brand: "; getline(cin, carBrand);
	fflush(stdin);
	cout << "Model: "; getline(cin, carModel);
	fflush(stdin);
	cout << "Color: "; getline(cin, carColor);
	cout << "Price: "; cin >> carPrice;
	cout << "Mileage(kmph): "; cin >> carMileage;
}
void Car :: getCarData()
{
	cout << setw(10) << carBrand 
		<< setw(10) << carModel 
		<< setw(10) << carColor 
		<< setw(10) << carPrice 
		<< setw(10) << carMileage
		<< setw(10) << carCode <<endl;
}

void Customer :: setCustomerData()
{
	cout << "Enter Customer's details." << endl;
	fflush(stdin);
	cout << "Name: "; getline(cin, customerName);
	fflush(stdin);
	cout << "Address: "; getline(cin, customerAddress);
	fflush(stdin);
	Flag1:
	cout << "Mobile Number: "; cin >> customerMobileNo;
	if(customerMobileNo.length()!=10)
	{
		cout << "Mobile number must be of 10 digits." << endl;
		goto Flag1;
	}
	cout << "Citizenship Number: "; cin >> customerCitizenshipNo;	
}

void Customer :: getCustomerData()
{
	cout << setw(20) << customerName 
		<< setw(20) << customerAddress 
		<< setw(15) << customerMobileNo 
		<< setw(17) << customerCitizenshipNo << endl;
}
void addCar()
{
	char ch='y';
	TC.open("totalCars.txt", ios::app | ios::binary);

	while(ch=='y' || ch=='Y')
	{
		myCarObj.setCarData();
		
		TC.write((char*)&myCarObj,  sizeof(myCarObj));
		CCL.open("carCodeList.txt", ios::app);
		CCL << myCarObj.setCarCode();
		CCL << endl;
		CCL.close();
		
		cout << " ________________________" << endl;
		cout << "|                        |" << endl;
		cout << "|Data Added successfully.|" << endl;
		cout << "|________________________|" << endl;
		
		cout << "Do you want to add more ?\n->";
		cin >> ch;
	}
	
	TC.close();
}

void showAllCars()
{
	TC.open("totalCars.txt", ios::in);
	if(!TC)
	{
		cout << "File not found." << endl;
		cout << "Press any key to exit...";
		getch();
		exit(0);
	}
	else
	{
		TC.read((char*)&myCarObj, sizeof(myCarObj));
		
		cout << "                        ALL CARS" << endl;
		cout << "_____________________________________________________________" << endl;
		cout <<setw(10)<<"Brand"<< setw(10)<<"Model"<< setw(10)<<"Color"<< setw(10)<<"Price"<< setw(10)<<"Mileage"<< setw(10)<<"Car code"<< endl;
		while(!TC.eof())
		{
			myCarObj.getCarData();
			TC.read((char*)&myCarObj, sizeof(myCarObj));
		}
	}
	TC.close();
}

void SoldCar :: sellingCar()
{
	int sellingCarCode, SCC, sellingCarCodeCheck=0, CC;

	cout << " ____________________" << endl;
	cout << "|                    |" << endl;
	cout << "|Car Selling Process.|" << endl;
	cout << "|____________________|" << endl;
		
	cout << "Enter car's code: ";
	cin >> sellingCarCode;
		
	TC.open("totalCars.txt", ios::in);
	TC.read((char*)&myCarObj, sizeof(myCarObj));
		
	while(!TC.eof())
	{
		if(sellingCarCode == myCarObj.setCarCode())
		{
			sellingCarCodeCheck++;
			mySoldCarObj.carBrand = myCarObj.setCarBrand();
			mySoldCarObj.carModel = myCarObj.setCarModel();
			mySoldCarObj.carColor = myCarObj.setCarColor();
			mySoldCarObj.carPrice = myCarObj.setCarPrice();
			mySoldCarObj.carMileage = myCarObj.setCarMileage();
			mySoldCarObj.carCode = myCarObj.setCarCode();
			break;
		}
		else
		{
			TC.read((char*)&myCarObj, sizeof(myCarObj));
		}
	
	}
	TC.close();
	if(sellingCarCodeCheck == 0)
	{
		cout << "Car with code no. " << sellingCarCode << " is not found." << endl;
		cout << "Press any key to continue...";
		getch();
	}
	else
	{
		mySoldCarObj.setCustomerData();

		SC.open("soldCars.txt", ios::app);

		SC.write((char*)&mySoldCarObj, sizeof(mySoldCarObj));
		SC.close();

		TC.open("totalCars.txt", ios::in);
		TTC.open("tempTC.txt", ios::out);
		TC.read((char*)&myCarObj, sizeof(myCarObj));
		SCC = myCarObj.carCode;
		while(!TC.eof())
		{
			if(sellingCarCode != SCC)
			{
				TTC.write((char*)&myCarObj, sizeof(myCarObj));
				TC.read((char*)&myCarObj, sizeof(myCarObj));
				SCC = myCarObj.carCode;
			}	
			else
			{
				TC.read((char*)&myCarObj, sizeof(myCarObj));;
				SCC = myCarObj.carCode;
			}
		}
		TC.close();
		TTC.close();
		remove("totalCars.txt");
		rename("tempTC.txt", "totalCars.txt");
		cout << " ______________________" << endl;
		cout << "|                      |" << endl;
		cout << "|Car Sold successfully.|" << endl;
		cout << "|______________________|" << endl;
		cout << "Press any key to continue..." << endl;
	
		getch();
			
	}

}

void carByCustomers()
{
	int soldCarCheck = 0;
	SC.open("soldCars.txt", ios::in);
	if(!SC)
	{
		cout << "File not found." << endl;
		cout << "Press any key to exit...";
		getch();
		exit(0);
	}
	else
	{
		SC.read((char*)&mySoldCarObj, sizeof(mySoldCarObj));
		while(!SC.eof())
		{
			soldCarCheck++;
			cout << "------------------------------------------------------------------------" << endl;
			cout << "CUSTOMER ->" << endl;                                    
			cout << setw(20)<<"Name"<< setw(20)<<"Addrss"<< setw(15)<<"Mobile No."<< setw(17)<<"Citizenship No."<< endl;
			mySoldCarObj.getCustomerData();
			cout << endl;
			cout <<"CAR ->" << endl;
			cout << setw(10)<<"Brand"<< setw(10)<<"Model"<< setw(10)<<"Color"<< setw(10)<<"Price"<< setw(10)<<"Mileage"<< setw(10)<<"Car code"<< endl;
			mySoldCarObj.getCarData();
			cout << "------------------------------------------------------------------------" << endl;
		
			SC.read((char*)&mySoldCarObj, sizeof(mySoldCarObj));
		}
	}
	SC.close();
	if(soldCarCheck == 0)
	{
		cout << "No any car have been sold." << endl;
		cout << "Press any key to continue...";
		getch();
	}
	else
	{
		cout << "Press any key to continue...";
		getch();
	}
}

void searchCar()
{
	int searchCount = 0;
	string searchCarName, searchCarBrand;
	cout << "SEARCH CAR" << endl;
	cout << "Enter car's brand name: ";
	cin >> searchCarName;
	
	TC.open("totalCars.txt", ios::in);
	TC.read((char*)&myCarObj, sizeof(myCarObj));
	cout << "			SEARCHED CAR" << endl;
	cout << "_____________________________________________________________" << endl;
	cout << setw(10)<<"Brand"<< setw(10)<<"Model"<< setw(10)<<"Color"<< setw(10)<<"Price"<< setw(10)<<"Mileage"<< setw(10)<<"Car code"<< endl;
	while(!TC.eof())
	{
		searchCarBrand = myCarObj.setCarBrand();
		if(searchCarName == searchCarBrand)
		{
			searchCount++;
			myCarObj.getCarData();
			TC.read((char*)&myCarObj, sizeof(myCarObj));
		}
		else
		{
			TC.read((char*)&myCarObj, sizeof(myCarObj));
		}
	}
	TC.close();
	if(searchCount==0)
	{
		cout << "\nNo car with brand name " << searchCarName << " is found.\n" << endl;
	}
	cout << "Press any key to continue...";
	getch();
}

void modifyCarDetails()
{
	int modifyCarCount = 0;
	int modifyCarCode;
	fstream CCL;

	cout << "For Modification of car's details:" << endl;
	cout << "Enter car's code: ";
	cin >> modifyCarCode;
	TC.open("totalCars.txt", ios::in);
	TTC.open("tempTC.txt", ios::out);
	TC.read((char*)&myCarObj, sizeof(myCarObj));
	CCL.open("carCodeList.txt", ios::app);
	while(!TC.eof())
	{
		if(modifyCarCode==myCarObj.carCode)
		{
			modifyCarCount++;
			cout << "Enter new details of the cars:-" << endl;
			myCarObj.setCarData();
			CCL << myCarObj.carCode;
			CCL << endl;
			TTC.write((char*)&myCarObj, sizeof(myCarObj));
			TC.read((char*)&myCarObj, sizeof(myCarObj));
		}
		else
		{
			TTC.write((char*)&myCarObj, sizeof(myCarObj));
			TC.read((char*)&myCarObj, sizeof(myCarObj));
		}
	}
	TC.close();
	TTC.close();
	CCL.close();
	
	if(modifyCarCount==0)
	{
		cout << "\nCar with code number " << modifyCarCode << " is not found.\n" << endl;
		remove("tempTC.txt");
	}
	else
	{
		remove("totalCars.txt");
		rename("tempTC.txt", "totalCars.txt");
			
		int CC, D;

		fstream CCL, TCCL;
		CCL.open("carCodeList.txt", ios::in);
		TCCL.open("tempCCL.txt", ios::out);
		while(CCL >> CC)
		{
			if(modifyCarCode != CC)
			{
				TCCL << CC;
				TCCL << endl;
			}
		}
		CCL.close();
		TCCL.close();

		remove("carCodeList.txt");
		rename("tempCCL.txt", "carCodeList.txt");

		cout << " __________________________________" << endl;
		cout << "|                                  |" << endl;
		cout << "|Car Details Modified Successfully.|" << endl;
		cout << "|__________________________________|" << endl;
	}
	
	cout << "Press any key to continue...";
	getch();
}

void deleteCarRecord()
{
	int deleteCarCount = 0;
	int deleteCarCode;
	
	showAllCars();

	cout << "Enter car's code: ";
	cin >> deleteCarCode;
	TC.open("totalCars.txt", ios::in);
	TTC.open("tempTC.txt", ios::out);
	fstream TCCL;
	TCCL.open("tempCCL.txt", ios::out);
	TC.read((char*)&myCarObj, sizeof(myCarObj));
	while(!TC.eof())
	{
		if(deleteCarCode==myCarObj.carCode)
		{
			deleteCarCount++;
			TC.read((char*)&myCarObj, sizeof(myCarObj));
		}
		else
		{
			TTC.write((char*)&myCarObj, sizeof(myCarObj));
			TCCL << myCarObj.carCode;
			TCCL << endl;
			TC.read((char*)&myCarObj, sizeof(myCarObj));
		}
	}
	TC.close();
	TTC.close();
	TCCL.close();
	
	if(deleteCarCount==0)
	{
		cout << "\nCar with code number " << deleteCarCode << " is not found.\n" << endl;
		remove("tempTC.txt");
	}
	else
	{
		remove("totalCars.txt");
		rename("tempTC.txt", "totalCars.txt");
		
		remove("carCodeList.txt");
		rename("tempCCL.txt", "carCodeList.txt");
		
		cout << " __________________________________" << endl;
		cout << "|                                  |" << endl;
		cout << "| Car Record Deleted Successfully. |" << endl;
		cout << "|__________________________________|" << endl;
	}
	
	cout << "Press any key to continue...";
	getch();
}

int main()
{
	int menuChoice;
	char sellChoice, exitChoice;
	string sellingCar;
	
	Flag:
	system("cls");
	cout << "					-------------------------" << endl;
	cout << "					|       Main Menu       |" << endl;
	cout << "					-------------------------" << endl;
	cout << "					1. Add a car" << endl;
	cout << "					2. Show all cars" << endl;
	cout << "					3. Sell a car" << endl;
	cout << "					4. Search a car" << endl;
	cout << "					5. Modify car's details" << endl;
	cout << "					6. Delete car record" << endl;
	cout << "					7. Sold Cars" << endl;
	cout << "					8. Exit" << endl;
	cout << "					Enter your choice: ";
	cin >>  menuChoice;
	
	switch(menuChoice)
	{
		case 1:
			addCar();
			cout << "Press any key for Main Menu...";
			getch();
			goto Flag;
		case 2:
			showAllCars();
			cout << "Press any key for Main Menu...";
			getch();
			goto Flag;
		case 3:
			showAllCars();
			cout << "Do you want to sell any of the above cars? (y/n)\n->";
			cin >> sellChoice;
			if(sellChoice == 'y')
			{
				mySoldCarObj.sellingCar();
			}
			goto Flag;
		case 4:
			searchCar();
			goto Flag;
		case 5:
			showAllCars();
			modifyCarDetails();
			goto Flag;
		case 6:
			deleteCarRecord();
			goto Flag;
		case 7:
			carByCustomers();
			goto Flag;
		case 8:
			cout << "Are you sure? (y/n)" << endl;
			cin >> exitChoice;
			if(exitChoice == 'y')
			{
				exit(0);
			}
			else
			{
				goto Flag;
			}
		default:
			cout << "\nInvalid Input \nEnter any key to continue...";
			getch();
			goto Flag;		
	}
		
	return 0;
}
