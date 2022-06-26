#include <iostream>
#include <iomanip>

using namespace std;

double investAmount;  //initial investment amount
double monthlyDeposit; //how much will be deposited per month
double annualInterest; //interest percentage per year
double yearEndInt; //will show year end earned interest without monthly deposits
double yearEndMInt; //will show year end earned interest with monthly deposits
int investYears; //how many years the investment will accumulate

class Invest { 
	private:
		double newInvestAmount;
		double yearEndInterest;
	public:
		void balanceWOmonthly(double investAmount, double annualInterest, int investYears) {  //finds total balance year end without factoring monthly deposits 
			double yearEndInterest{};
			double balanceWODeposits{};
			newInvestAmount = investAmount;

			int i;
			for (i = 0; i < investYears; ++i) {
				yearEndInterest = newInvestAmount * (annualInterest / 100);
				balanceWODeposits = yearEndInterest + newInvestAmount;
				newInvestAmount = balanceWODeposits;
			}
			yearEndInt = yearEndInterest;

			cout << setw(16) << fixed << setprecision(2) << "$" << balanceWODeposits;
		}

		void balanceMonthly(double investAmount, double annualInterest, double monthlyDeposits, int investYears) { //finds total balance year end factoring month deposits
			int month = investYears * 12;
			double monthEndInterest{};
			double balanceMonth{};
			newInvestAmount = investAmount;

			int i;
			for (i = 0; i < month; ++i) { 
				if (i % 12 == 0) { //a conditional to reset year end earned interest because this for loop functions off of months instead of years
					yearEndMInt = 0;
				}
				monthEndInterest = (newInvestAmount + monthlyDeposits) * ((annualInterest / 100) / 12);
				balanceMonth = monthEndInterest + newInvestAmount + monthlyDeposit;
				newInvestAmount = balanceMonth;
				yearEndMInt += monthEndInterest;
				
			}
	
			cout << setw(16) << fixed << setprecision(2) << "$" << balanceMonth;
		}

		void initMenu(double invAmount, double monDeposit, double annInterest, int invYears) { //allows user to input info needed for the tables
			std::cout << std::string(26, '*') << endl;
			std::cout << std::string(7, '*') << " Data Input " << std::string(7, '*') << endl;

			cout << "Initial Investment Amount: ";
			cin >> invAmount;
			if (!cin) {
				cout << "Invalid value, please enter again" << endl;
				cout << "Initial Investment Amount: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> invAmount;
			}
			investAmount = invAmount;
			cout << endl;

			cout << "Monthly Deposit: ";
			cin >> monDeposit;
			if (!cin) {
				cout << "Invalid value, please enter again" << endl;
				cout << "Monthly Deposit: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> monDeposit;
			}
			monthlyDeposit = monDeposit;
			cout << endl;

			cout << "Annual Interest: ";
			cin >> annInterest;
			if (!cin) {
				cout << "Invalid value, please enter again" << endl;
				cout << "Annual Interest: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> annInterest;
			}
			annualInterest = annInterest;
			cout << endl;

			cout << "Number of years: ";
			cin >> invYears;
			if (!cin) {
				cout << "Invalid value, please enter again" << endl;
				cout << "Number of years: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> invYears;
			}
			investYears = invYears;
			cout << endl << endl;

		}

		void invTableWOMonthly() { // to print table without monthly deposits
			cout << "   Balance and Interest without Additional Monthly Deposits   " << endl;
			std::cout << std::string(63, '=') << endl;
			cout << setw(6) << "Year";
			cout << setw(23) << "Year End Balance";
			cout << setw(30) << "Year End Earned Interest" << endl;
			std::cout << std::string(63, '-') << endl;

			int i;
			for (i = 1; i <= investYears; ++i) {  //loops my balance without monthly to get values, loops for i which represents years inputted
				cout << setw(6) << i;
				balanceWOmonthly(investAmount, annualInterest, i);
				cout << setw(24) << fixed << setprecision(2) << "$" << yearEndInt << endl << endl;
			}
			cout << endl;
		}

		void invTableMonthly() { //to print table with monthly deposits being a factor
			cout << "      Balance and Interest with Additional Monthly Deposits" << endl;
			std::cout << std::string(63, '=') << endl;
			cout << setw(6) << "Year";
			cout << setw(23) << "Year End Balance";
			cout << setw(30) << "Year End Earned Interest" << endl;
			std::cout << std::string(63, '-') << endl;

			int i;
			for (i = 1; i <= investYears; ++i) {  //loops my balance with monthly to get values, loops for i which represents years inputted
				cout << setw(6) << i;
				balanceMonthly(investAmount, annualInterest, monthlyDeposit, i);
				cout << setw(24) << setprecision(2) << "$" << yearEndMInt << endl << endl;
			}
		}
};

int main() {
	Invest user;
	bool programState = true;
	int userInput;

	while (programState == true) {
		bool notValidInput = true;

		user.initMenu(investAmount, monthlyDeposit, annualInterest, investYears);
		user.invTableWOMonthly();
		user.invTableMonthly();

		cout << "if you would like to input more data press 1, if you want to quit press 2" << endl;
		cin >> userInput;
		while (notValidInput == true) { //a while loop just for the switch statement in case of invalid input from user
			switch (userInput) {
			case 1:
				notValidInput = false;
				continue;
			case 2:
				notValidInput = false;
				programState = false;
				break;
			default:
				cout << "Invalid input, please type 1 or 2" << endl;
				cin >> userInput;
			}
		}
	}

	return 0;
}